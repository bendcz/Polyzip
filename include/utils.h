#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *get_file_extension(const char *filePath);
const char *get_path_whitout_extension(const char *filePath);
char *get_path_with_custom_extension(const char *filePath, const char *extension);

#endif