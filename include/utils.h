#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "errors.h"

#ifdef _WIN32
    #define PATH_SEPARATOR '\\'
#elif __unix__
    #define PATH_SEPARATOR '/'
#endif

struct Files
{
    FILE *inputFile;
    FILE *outputFile;
};

char *get_file_extension(const char *filePath);
char *get_file_name(const char *filePath);
char *get_path_without_extension(const char *filePath);
char *get_path_with_custom_extension(const char *filePath, const char *extension);

char *check_and_realloc(char *buffer, size_t *bufferSize, size_t requiredSize, size_t increment);

struct Files *get_files(const char *inputPath, const char *outputPath, const char *outputExtension);

bool write_bit(FILE *outputFile, uint8_t *buffer, int *count, int bit);
bool read_bit(FILE *inputFile, uint8_t *buffer, int *count, int *bit);
void flush_buffer(FILE *inputFile, uint8_t *buffer, int *count);

#endif