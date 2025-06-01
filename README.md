<a name="top"></a>

![icon](resources/icon.svg)

[![language](https://img.shields.io/badge/language-c-9128bf?style=for-the-badge)]()
[![standard](https://img.shields.io/badge/c_standard-c11-9128bf?style=for-the-badge)]()
[![Dynamic Regex Badge](https://img.shields.io/badge/dynamic/regex?url=https%3A%2F%2Fgithub.com%2Fbendcz%2FPolyzip%2Factions%2Fworkflows%2Fgithub-code-scanning%2Fcodeql%2Fbadge.svg&search=%3Ctitle%3E%5B%5E%3C%5D*%20-%20(%5B%5E%3C%5D%2B)%3C%5C%2Ftitle%3E&replace=%241&style=for-the-badge&logo=github&label=CodeQL&color=brightbreen)
]()
[![license](https://img.shields.io/badge/license-Unlicense-brightbreen?style=for-the-badge)]()

## :bookmark: Table of Contents
- [About](#-about)
- [How to Build](#-how-to-build)
- [Documentation](#-documentation)
    - [How it works?](#how-it-works)
    - [Usage](#usage)
- [Security](#-security)
- [To-Do List](#-to-do-list)
- [License](#-license)
- [Contacts](#-contacts)

## 🚀 About

Polyzip is a program written in C11 for **compressing and decompressing files** using the following algorithms:

- RLE (Run-Length Encoding),
- Adaptive Huffman (Faller-Gallager-Knuth),
- LZW (Lempel-Ziv-Welch).

Polyzip tries to adhere to **simple**, **secure** and **tested** code.

## 🔨 How to Build

**Dependencies:**

- CMake (3.30 >=),
- OpenSSL (3 >=),
- Criterion (for tests only).

Compiling the project is very easy. Follow the steps below!  
In your CLI:

1. `git clone git@github.com:bendcz/Polyzip.git`
2. `cd Polyzip`
3. `mkdir build && cd build`

Then, you have three choices.
1. **Compile in Release mode (with optimizations and without debug possibilities):**
    - `cmake .. && make`
2. **Compile in Debug mode (without optimizations and with debug possibilities):**
    - `cmake .. -DDEBUG=ON && make`
3. **Compile unit tests:**
    - `cmake -DBUILD_TESTS=ON .. & make`

## 📚 Documentation

### How it works?
- #### Understand Polyzip's code

![icon](resources/how-it-works.svg)

- #### Understand the algorithms behind Polyzip
    - RLE (Run-Length Encoding):
        - [Wikipedia](https://en.wikipedia.org/wiki/Run-length_encoding)
    - Adaptive Huffman (Faller-Gallager-Knuth):
        - [Wikipedia](https://en.wikipedia.org/wiki/Adaptive_Huffman_coding)
        - [Ben Tanen — Visualizing Adaptive Huffman Coding](https://ben-tanen.com/adaptive-huffman/)
    - LZW (Lempel-Ziv-Welch):
        - [Wikipedia](https://en.wikipedia.org/wiki/Lempel-Ziv-Welch)
        - [GeeksforGeeks — LZW (Lempel–Ziv–Welch) Compression technique](https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/)
### Usage

In CLI: `./polyzip -<c|d> -<ALGORITHM> <INPUT_PATH> <OUTPUT_PATH>`,

* `-c`: compression,<br>

* `-d`: decompression,
* `-rle`: using the RLE algorithm,
* `-huffman`: using the Huffman algorithm,
* `-lzw`: using the LZW algorithm,
* `<INPUT_PATH>`: path to the file to compress/decompress,
* `<OUTPUT_PATH>`: directory where the result should be written.


## 🛡️ Security

I tried to produce secure code, in particular by using functions with more safeguards (such as the buffer size in `snprintf`)  
and by checking the various use cases with Valgrind. The pattern of the command is:

```
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./polyzip -<c|d> -<ALGORITHM> <INPUT_PATH> <OUTPUT_PATH>
```

⚠️ **Make sure you've compiled in debug mode before you expect to see anything!**

I have also set up a CodeQL analysis for the repository. However, if you ever find a flaw in this code, you can contact me  
by clicking on [this link](#-contacts).


## 💡 To-Do List

- Implement the DEFLATE algorithm,
- Store *magic codes* in files to remember the original format,
- Compile the executable for the main operating systems,
- Make unit tests more robust and improve code coverage,
- Creating a graphical interface with the SDL.

## 📃 License

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

* **Email**:
* **Website**:

[Back to top](#top)