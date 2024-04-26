use crate::ffi::bridge::ImageRGBABuf;

use self::bridge::ImageRGBA;
use cxx as _;
use image::{GrayAlphaImage, ImageBuffer, Rgba, RgbaImage};

fn create_image<'b>(buf: &'b [u8], width: u32, height: u32) -> bridge::ImageRGBA<'b> {
    ImageRGBA {
        data: buf.as_ptr(),
        data_len: buf.len(),
        width,
        height,
        _marker: &buf[0],
    }
}

fn image_make_greyscale<'bi>(img: &ImageRGBA<'bi>) -> ImageRGBABuf {
    use image::buffer::ConvertBuffer;
    let buffer = unsafe { std::slice::from_raw_parts(img.data, img.data_len) };
    let image: ImageBuffer<Rgba<u8>, _> =
        ImageBuffer::from_raw(img.width, img.height, buffer).unwrap();

    let image: GrayAlphaImage = image.convert();
    let image: RgbaImage = image.convert();

    let data = image.into_raw();
    ImageRGBABuf {
        data,
        width: img.width,
        height: img.height,
    }
}

#[cxx::bridge]
mod bridge {

    pub struct ImageRGBA<'b> {
        data: *const u8,
        data_len: usize,
        width: u32,
        height: u32,
        _marker: &'b u8,
    }

    pub struct ImageRGBABuf {
        data: Vec<u8>,
        width: u32,
        height: u32,
    }

    extern "Rust" {
        #[cxx_name = "rb_create_image_rgba"]
        unsafe fn create_image<'b>(buf: &'b [u8], width: u32, height: u32) -> ImageRGBA<'b>;

        #[cxx_name = "rb_image_rgba_make_greyscale"]
        unsafe fn image_make_greyscale<'bi, 'bo>(img: &ImageRGBA<'bi>) -> ImageRGBABuf;
    }

}
