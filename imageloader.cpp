#include "imageloader.h"
#include <png.h>

ImageLoader::ImageLoader()
{
}

QImage ImageLoader::loadImage(QString imagePath)
{
    // Based on https://gist.github.com/niw/5963798
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    std::string imgPathStr = imagePath.toStdString();
    const char *imgPathCStr = imgPathStr.c_str();
    FILE *fp = fopen(imgPathStr.c_str(), "rb");

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
        abort();

    if (setjmp(png_jmpbuf(png)))
        abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    // libpng wants a series of pointers for it to store the row data into.
    // It'll write the data of each row into the buffers those pointers point to.
    // However, the QImage just wants all of the image data in one chunk,
    // so we allocate one big buffer for all the rows, as well as a list
    // of pointers to the start of each of the chunks where each row is supposed to go.
    // Because of the way this is set up, the first entry in the row pointers list points
    // to the start of the data buffer. Both the data buffer and the list of row pointers
    // are supposed to be freed manually at some point. In this case, ImageLoader::cleanupPngData will
    // take care of that.
    size_t row_size = png_get_rowbytes(png, info);
    png_bytep image_data = new png_byte[height * row_size];

    png_bytep *row_pointers = new png_bytep[height];

    for (int y = 0; y < height; y++)
    {
        row_pointers[y] = image_data + y * row_size;
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    png_destroy_read_struct(&png, &info, NULL);

    return QImage((uchar *)image_data, width, height, row_size, QImage::Format_RGBA8888, ImageLoader::cleanupPngData, row_pointers);
}

void ImageLoader::storeImage(QImage image, QString imagePath)
{
   image.save(imagePath);
}

void ImageLoader::cleanupPngData(void *info)
{
    png_bytep *row_pointers = (png_bytep *)info;
    delete[] *row_pointers; // Free image_data
    delete[] row_pointers;  // Free row_pointers
}