#include "image_info.h"
#include "png.h"

#include <stdlib.h>

ImageInfo image_info(const char* path) {
    // Based on https://gist.github.com/niw/5963798
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    FILE *fp = fopen(path, "rb");

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

    size_t row_size = png_get_rowbytes(png, info);

    ImageInfo foo = {.width = width, .height = height, .channels = color_type, .bitdepth = bit_depth};
    return foo;
}

unsigned image_buf_size(ImageInfo info) {
    return info.height * image_row_size(info);
}

unsigned image_row_size(ImageInfo info) {
    return info.width * info.channels;
}