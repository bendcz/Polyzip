#ifndef RLE_H
#define RLE_H

#define RESULT_SIZE_INCREMENT 64
#define TMP_SIZE_INCREMENT 8

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

const char *compress_rle(const char *inputPath, const char *outputPath);
const char *decompress_rle(const char *inputPath, const char *outputPath);

#endif