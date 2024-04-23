pub fn rb_add(left: usize, right: usize) -> usize {
    left + right
}

#[cxx::bridge]
mod bridge {
    extern "Rust" {
        fn rb_add(left: usize, right: usize) -> usize;
    }
}

