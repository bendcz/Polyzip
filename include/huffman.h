#ifndef RLE_H
#define RLE_H

#define RESULT_SIZE_INCREMENT 64
#define TMP_SIZE_INCREMENT 8

const char *compress_huffman(const char *inputPath, const char *outputPath);
const char *decompress_huffman(const char *inputPath, const char *outputPath);

#endif