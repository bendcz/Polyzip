#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #define PATH_SEPARATOR "\\"
#elif __unix__
    #define PATH_SEPARATOR "/"
#endif

const char *get_file_extension(const char *filePath);
const char *get_file_name(const char *filePath);
const char *get_path_without_extension(const char *filePath);
const char *get_path_with_custom_extension(const char *filePath, const char *extension);

char *check_and_realloc(char *buffer, size_t *bufferSize, size_t requiredSize, size_t increment);

#endif