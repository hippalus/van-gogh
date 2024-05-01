#include "imageloader.h"
#include "image_info.h"
#include <png.h>

ImageLoader::ImageLoader()
{
}

QImage ImageLoader::loadImage(QString imagePath)
{
    std::string imgPathStr = imagePath.toStdString();
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
    png_read_update_info(png, info);
    ImageInfo img_info;

    if(image_info(imgPathStr.c_str(), &img_info) != 0) {
        abort();
    }

    // libpng wants a series of pointers for it to store the row data into.
    // It'll write the data of each row into the buffers those pointers point to.
    // However, the QImage just wants all of the image data in one chunk,
    // so we allocate one big buffer for all the rows, as well as a list
    // of pointers to the start of each of the chunks where each row is supposed to go.
    // Because of the way this is set up, the first entry in the row pointers list points
    // to the start of the data buffer. Both the data buffer and the list of row pointers
    // are supposed to be freed manually at some point. In this case, ImageLoader::cleanupPngData will
    // take care of that.
    auto image_data = std::make_unique<std::vector<uint8_t>>(image_buf_size(img_info));
    auto image_row_ptrs = std::vector<png_bytep>();
    image_row_ptrs.reserve(img_info.height);

    for (int y = 0; y < img_info.height; y++)
    {
        image_row_ptrs.push_back(image_data.get()->data() + y * image_row_size(img_info));
    }

    png_read_image(png, image_row_ptrs.data());

    fclose(fp);

    png_destroy_read_struct(&png, &info, NULL);

    // Do not delete the buffer at the end of scope, but when QImage calls cleanupPngData
    auto image_data_ptr = image_data.release();
    return QImage(image_data_ptr->data(), img_info.width, img_info.height, image_row_size(img_info), QImage::Format_RGBA8888, ImageLoader::cleanupPngData, image_data_ptr);
}

void ImageLoader::storeImage(QImage image, QString imagePath)
{
    image.save(imagePath);
}

void ImageLoader::cleanupPngData(void *info)
{
    // Note of the author: I really don't want to use delete, but even cppreference.com uses delete in their release example...
    delete reinterpret_cast<std::vector<uint8_t>*>(info);
}