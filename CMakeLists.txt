cmake_minimum_required(VERSION 3.30)
project(Polyzip VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB INCLUDES
    "include/*.h"
)

file(GLOB SOURCES
    "src/*.c"
)

add_executable(Polyzip ${SOURCES} ${INCLUDES})
target_compile_options(Polyzip PRIVATE -g -O0 -Wall -Wextra)

option(BUILD_TESTS "Build tests" OFF)

if (BUILD_TESTS)
    find_package(Criterion REQUIRED)
    find_package(OpenSSL REQUIRED)
    add_executable(utils_test tests/utils_test.c src/utils.c include/utils.h
                              tests/rle_test.c src/rle.c include/rle.h)
    target_link_libraries(utils_test Criterion::Criterion OpenSSL::Crypto)

    add_custom_target(run_tests
    COMMAND utils_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
endif()