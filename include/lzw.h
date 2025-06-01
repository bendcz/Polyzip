#ifndef LZW_H
#define LZW_H

#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "utils.h"
#include "errors.h"

int compress_lzw(const char *inputPath, const char *outputPath);
int decompress_lzw(const char *inputPath, const char *outputPath);

#endif