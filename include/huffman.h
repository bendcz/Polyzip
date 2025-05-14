#ifndef HUFFMAN_H
#define HUFFMAN_H

#define CODES_SIZE 512

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "utils.h"
#include "errors.h"

int compress_huffman(const char *inputPath, const char *outputPath);
int decompress_huffman(const char *inputPath, const char *outputPath);

bool write_code(FILE *inputFile, Node *currentNode, Node *targetNode, uint8_t *buffer, int *count);

#endif