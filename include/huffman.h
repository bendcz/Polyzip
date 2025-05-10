#ifndef RLE_H
#define RLE_H

#define RESULT_SIZE_INCREMENT 64
#define TMP_SIZE_INCREMENT 8
#define TABLE_SIZE_INCREMENT 256

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "tree.h"
#include "utils.h"

const char *compress_huffman(const char *inputPath, const char *outputPath);
const char *decompress_huffman(const char *inputPath, const char *outputPath);

#endif