fn main() {
    cxx_build::bridge("src/ffi.rs") // returns a cc::Build
        .std("c++11")
        .file("src/imagergba.cc")
        .file("src/imagergba.h")
        .compile("rembrandt");

    println!("cargo:rerun-if-changed=src/lib.rs");
}
