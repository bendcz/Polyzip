#ifndef RLE_H
#define RLE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int compress_rle(const char *filePath);
int decompress_rle(const char *filePath);

#endif