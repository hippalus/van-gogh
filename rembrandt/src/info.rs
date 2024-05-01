// You can use below imports (and the warnings 
// about them being unused) as hints
use std::{
    ffi::{c_uint, CStr},
    path::Path,
    str::Utf8Error,
};

use image::{DynamicImage, ImageError};


#[allow(dead_code)]
pub enum ImageInfoError {
    Utf8(Utf8Error),
    Image(ImageError),
    UnsupportedPixelType,
}

impl From<Utf8Error> for ImageInfoError {
    fn from(e: Utf8Error) -> Self {
        Self::Utf8(e)
    }
}

impl From<ImageError> for ImageInfoError {
    fn from(e: ImageError) -> Self {
        Self::Image(e)
    }
}

#[repr(u8)]
pub enum ColorType {
    Grayscale = 0,
    Rgb = 2,
    Palette = 3,
    GrayscaleAlpha = 4,
    RgbAlpha = 6,
}

impl From<ColorType> for c_uint {
    fn from(value: ColorType) -> Self {
        (value as u8).into()
    }
}

#[repr(u8)]
pub enum BitDepth {
    Depth1 = 1,
    Depth2 = 2,
    Depth4 = 4,
    Depth8 = 8,
    Depth16 = 16,
}

impl From<BitDepth> for c_uint {
    fn from(value: BitDepth) -> Self {
        (value as u8).into()
    }
}

// #[cfg(never)]
mod ffi {
    // (PART 1): TODO expose extern "C" interface that corresponds to
    // the interface defined in image_info.h. You can use the `image` crate to
    // load the image data.
}
