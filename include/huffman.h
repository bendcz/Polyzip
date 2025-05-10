#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "tree.h"
#include "utils.h"

const char *compress_huffman(const char *inputPath, const char *outputPath);
const char *decompress_huffman(const char *inputPath, const char *outputPath);

#endif