fn main() {
    cxx_build::bridge("src/lib.rs")  // returns a cc::Build
        .std("c++11")
        .compile("rembrandt");

    println!("cargo:rerun-if-changed=src/lib.rs");
}