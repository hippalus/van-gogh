#ifndef IMAGE_INFO_H
#define IMAGE_INFO_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct ImageInfo {
    unsigned width;
    unsigned height;
    unsigned channels;
    unsigned bitdepth;
}  ImageInfo;

ImageInfo image_info(const char* path);
unsigned image_buf_size(ImageInfo info);
unsigned image_row_size(ImageInfo info);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // IMAGE_INFO_H
