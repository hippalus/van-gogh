# Resources

[Interop crates listed on blessed.rs](https://blessed.rs/crates#section-ffi)
[UniFFI](https://mozilla.github.io/uniffi-rs/)
    [UniFFI-bindgen-go](https://github.com/NordSecurity/uniffi-bindgen-go)
    [uniffi-kotlin-multiplatform-bindings](https://gitlab.com/trixnity/uniffi-kotlin-multiplatform-bindings)
    [uniffi-bindgen-cs](https://github.com/NordSecurity/uniffi-bindgen-cs)
[Crust of Rust on FFI](https://youtu.be/pePqWoTnSmQ)

https://tgrep.nl/tweedegolf/non-commercial/-/issues/19#note_89871

---
# How-to posts

To be completed over time

## C

### Tools
- mozilla/cbindgen — generates C header files from Rust source files. Used in Gecko for WebRender
- rust-lang/rust-bindgen — A Rust bindings generator
- Diplomat: https://github.com/rust-diplomat/diplomat

### Use cases

## C++

### Tools
- dtolnay/cxx — Safe interop between Rust and C++
- rust-cpp - Embed C++ code directly in Rust
- Crubit: https://github.com/google/crubit
- https://github.com/google/autocxx
- https://github.com/rust-qt/ritual

### Resources
- https://medium.com/@aidagetoeva/async-c-rust-interoperability-39ece4cd3dcf
    - https://www.youtube.com/watch?v=tsEuA9S5q9Q

### Use cases
- Rust-module/extension for Qt-based application
- Point Cloud Library (PCL)
- 
## Python

### Tools
- getsentry/milksnake — extension for python setuptools that allows you to distribute dynamic linked libraries in Python wheel
- PyO3/PyO3 — Rust bindings for the Python interpreter
- https://rustpython.github.io/



### Use cases
- Speed up ML/AI/scientific computation
- Rust is a better contender than C for speeding up python scripts

## Node.js

### Tools'
- napi
- infinyon/node-bindgen - Easy way to generate nodejs module using Rust
- neon-bindings/neon — Rust bindings for writing safe and fast native Node.js modules

### Use cases
- Rust is a better contender than C for speeding up JS (vgl node-gyp-based stuff) (hoewel V8 best goed is)
- Making sure calculations is correct (link to post office scandal?)

## Java/JVM

### Tools
- https://docs.rs/jni/latest/jni/ type definitions for jni stuff
### Use cases
- type system (zelfdocumenterende code)
- android

## C#/.NET

### Tools
- https://github.com/Cysharp/csbindgen

### Use cases
- unity

## Swift

### Tools
https://github.com/chinedufn/swift-bridge?tab=readme-ov-file

### Use cases

- iOS

## Web Assembly

### Tools
- rustwasm/wasm-bindgen — A project for facilitating high-level interactions between wasm modules and JS
- rustwasm/wasm-pack — pack up the wasm and publish it to npm
- trunk - build, bundle & ship your Rust WASM application to the web
- https://extism.org/

### Use cases
- Rust WASM stuff is relatively mature

## Elixir

### Tools
- Rustler: https://www.lambdafunctions.com/articles/elixir-and-rust

# General tools
https://github.com/getditto/safer_ffi

---

## Other sources
- The nomicon on FFI https://doc.rust-lang.org/nomicon/ffi.html
- https://kmdouglass.github.io/posts/complex-data-types-and-the-rust-ffi/