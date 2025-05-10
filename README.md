<a name="top"></a>

<h1 style="color: #9128bfff; font-size: 8rem;">Polyzip</h1>

[![language](https://img.shields.io/badge/language-C-blue)]()
[![standard](https://img.shields.io/badge/C_Standard-C11-blue)]()
[![OS](https://img.shields.io/badge/OS-linux,_windows-blue)]()
[![license](https://img.shields.io/badge/license-Unlicense-brightbreen)]()
[![Free](https://img.shields.io/badge/free-brightgreen)](#-license)

## Table of Contents
- [About](#-about)
- [How to Build](#-how-to-build)
- [Download an already compiled version](#-download-an-already-compiled-version)
- [Documentation](#-documentation)
- [License](#-license)
- [Contacts](#-contacts)

## 🚀 About

Polyzip is a program written in C11 for **compressing and decompressing files** using the following algorithms:

- RLE (Run-Length Encoding),
- Huffman (adptative),
- LZW (Lempel-Ziv-Welch) (TODO),
- DEFLATE (TODO).

Polyzip tries to adhere to **simple**, **secure** and **tested** code.

## 🔨 How to Build

**Dependencies:**

- CMake (3.30 >=),
- Criterion (for tests only),
- OpenSSL (for tests only).

Compiling the project is very easy.  
In your CLI:

1. `git clone git@github.com:bendcz/Polyzip.git`
2. `cd Polyzip`
3. `mkdir build && cd build`
4. `cmake .. && make`

To active test compilation, `cmake ..` should be `cmake -DBUILD_TESTS=ON ..`.

## ⚡ Download an already-compiled version

| Operating System | CPU Architecture | Link | SHA-512 |
| ---------------- | ---------------- | ---- | ------- |
| Ubuntu 22.04 (LTS) | 32-bit         |      |         |
| Ubuntu 22.04 (LTS) | 64-bit         |      |         |
| Debian 11 (Bullseye) | 32-bit       |      |         |
| Debian 11 (Bullseye)  | 64-bit      |      |         |
| Windows 11       | 32-bit           |      |         |
| Windows 11       | 64-bit           |      |         |
| Windows 10       | 32-bit           |      |         |
| Windows 10       | 64-bit           |      |         |

## 📚 Documentation

## 📫 License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

## 📫 Contacts


[Back to top](#top)