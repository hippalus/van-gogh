#ifndef IMAGE_INFO_H
#define IMAGE_INFO_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct ImageInfo {
    unsigned width;
    unsigned height;
    unsigned color_type;
    unsigned bit_depth;
}  ImageInfo;

int image_info(const char* path, ImageInfo* info);
unsigned image_buf_size(ImageInfo info);
unsigned image_row_size(ImageInfo info);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // IMAGE_INFO_H
