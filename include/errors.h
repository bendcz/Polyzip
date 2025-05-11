#ifndef ERRORS_H
#define ERRORS_H

#define SUCCESS 0
#define ERROR_FILE_ALLOCATION 1
#define ERROR_MEMORY_ALLOCATION 2
#define ERROR_FILE_READ 3
#define ERROR_FILE_COMPRESSION 4
#define ERROR_FILE_WRITE 5

#include <stdio.h>
#include <string.h>

int print_error_message(const char *functionName, int errorCode);

#endif