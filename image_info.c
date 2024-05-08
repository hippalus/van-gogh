#include "image_info.h"
#include "png.h"

// (PART 1) TODO replace me with an implementation defined in Rust

int image_info(const char* path, ImageInfo* img_info) {
    // Based on https://gist.github.com/niw/5963798
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    FILE *fp = fopen(path, "rb");

    png_structp png = png_create_read_struct("1.6.43", NULL, NULL, NULL);
    if (!png)
        return -1;

    png_infop info = png_create_info_struct(png);
    if (!info)
        return -1;

    if (setjmp(png_jmpbuf(png)))
        return -1;

    png_init_io(png, fp);

    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);

    size_t row_size = png_get_rowbytes(png, info);

    *img_info = (ImageInfo){.width = width, .height = height, .color_type = color_type, .bit_depth = bit_depth};
    return 0;
}

unsigned image_buf_size(ImageInfo info) {
    return info.height * image_row_size(info);
}

unsigned image_row_size(ImageInfo info) {
    return info.width * 4;
}