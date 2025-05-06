cmake_minimum_required(VERSION 3.30)
project(Polyzip VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(Polyzip src/main.c)

target_compile_options(Polyzip PRIVATE -Wall -Wextra)