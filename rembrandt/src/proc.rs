use self::bridge::{ImageLumaBuf, ImageRGBA, ImageRgbaBuf};
use image::{GrayImage, ImageBuffer, Rgba};

fn create_image<'b>(buf: &'b [u8], width: u32, height: u32) -> bridge::ImageRGBA<'b> {
    ImageRGBA {
        data: buf.as_ptr(),
        data_len: buf.len(),
        width,
        height,
        _marker: &buf[0],
    }
}

fn image_make_greyscale<'bi>(img: &ImageRGBA<'bi>) -> ImageLumaBuf {
    use image::buffer::ConvertBuffer;
    let buffer = unsafe { std::slice::from_raw_parts(img.data, img.data_len) };
    let image: ImageBuffer<Rgba<u8>, _> =
        ImageBuffer::from_raw(img.width, img.height, buffer).unwrap();

    let image: GrayImage = image.convert();

    let data = image.into_raw();
    ImageLumaBuf {
        data,
        width: img.width,
        height: img.height,
    }
}

fn image_rotate_hue<'bi, 'bo>(img: &ImageRGBA<'bi>) -> ImageRgbaBuf {
    todo!()
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

    pub struct ImageRgbaBuf {
        data: Vec<u8>,
        width: u32,
        height: u32,
    }

    pub struct ImageLumaBuf {
        data: Vec<u8>,
        width: u32,
        height: u32,
    }

    extern "Rust" {
        #[cxx_name = "rb_create_image"]
        unsafe fn create_image<'b>(buf: &'b [u8], width: u32, height: u32) -> ImageRGBA<'b>;

        #[cxx_name = "rb_image_make_greyscale"]
        unsafe fn image_make_greyscale<'bi, 'bo>(img: &ImageRGBA<'bi>) -> ImageLumaBuf;

        #[cxx_name = "rb_image_rotate_hue"]
        unsafe fn image_rotate_hue<'bi, 'bo>(img: &ImageRGBA<'bi>) -> ImageRgbaBuf;
    }
}
