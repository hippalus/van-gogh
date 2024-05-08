use std::{
    ffi::{c_char, c_uint, c_int, CStr},
    path::Path,
    str::Utf8Error,
};

use image::{DynamicImage, GenericImageView, ImageError};

#[repr(C)]
pub struct ImageInfo {
    pub width: c_uint,
    pub height: c_uint,
    pub color_type: c_uint,
    pub bit_depth: c_uint,
}

impl ImageInfo {
    pub fn from_path(path: &CStr) -> Result<Self, ImageInfoError> {
        let path = path.to_str()?;
        let path = Path::new(path);

        let image = image::open(path)?;

        let (color_type, bit_depth) = match image {
            DynamicImage::ImageLuma8(_) => (ColorType::Grayscale, BitDepth::Depth8),
            DynamicImage::ImageLumaA8(_) => (ColorType::GrayscaleAlpha, BitDepth::Depth8),
            DynamicImage::ImageRgb8(_) => (ColorType::Rgb, BitDepth::Depth8),
            DynamicImage::ImageRgba8(_) => (ColorType::RgbAlpha, BitDepth::Depth8),
            DynamicImage::ImageLuma16(_) => (ColorType::Grayscale, BitDepth::Depth16),
            DynamicImage::ImageLumaA16(_) => (ColorType::GrayscaleAlpha, BitDepth::Depth16),
            DynamicImage::ImageRgb16(_) => (ColorType::Rgb, BitDepth::Depth16),
            DynamicImage::ImageRgba16(_) => (ColorType::RgbAlpha, BitDepth::Depth16),
            _ => return Err(ImageInfoError::UnsupportedPixelType),
        };

        Ok(Self {
            width: image.width(),
            height: image.height(),
            color_type: color_type.into(),
            bit_depth: bit_depth.into(),
        })
    }
}


mod ffi {
    use super::*;

    #[no_mangle]
    pub unsafe extern "C" fn image_info(path: *const c_char, info: *mut ImageInfo) -> c_int {
        if path.is_null() || info.is_null() {
            return -1;
        }

        let path = unsafe { CStr::from_ptr(path) };

        let result = ImageInfo::from_path(path)
            .map(|image_info| unsafe { *info = image_info });

        match result {
            Ok(_) => 0,
            Err(e) => {
                eprintln!("Error: {:?}", e);
                -1
            }
        }
    }

    #[no_mangle]
    pub extern "C" fn image_buf_size(info: ImageInfo) -> c_uint {
        info.height * image_row_size(info)
    }

    #[no_mangle]
    pub extern "C" fn image_row_size(info: ImageInfo) -> c_uint {
        info.width * 4
    }
}

#[allow(dead_code)]
#[derive(Debug)]
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
        value as u8 as c_uint
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
        value as u8 as c_uint
    }
}
