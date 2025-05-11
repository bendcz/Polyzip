#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "tree.h"
#include "utils.h"
#include "errors.h"

int compress_huffman(const char *inputPath, const char *outputPath);
int decompress_huffman(const char *inputPath, const char *outputPath);

#endif