#include "../include/errors.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int print_error_message(const char *functionName, int errorCode)
{
    char *message = (char *) malloc(sizeof(char) * (strlen(functionName) + 37));

    if (message == NULL)
    {
        perror("/!\\ print_error_message/ERROR_MEMORY_ALLOCATION /!\\\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    message[0] = '\0';
    strncat(message, "/!\\ ", 5);
    strncat(message, functionName, strlen(functionName));
    strcat(message, "/");

    switch (errorCode)
    {
        case ERROR_FILE_ALLOCATION:
            strncat(message, "ERROR_FILE_ALLOCATION /!\\", 26);
            perror(message);
            free(message);
            return ERROR_FILE_ALLOCATION;
        case ERROR_MEMORY_ALLOCATION:
            strncat(message, "ERROR_MEMORY_ALLOCATION /!\\", 28);
            perror(message);
            free(message);
            return ERROR_MEMORY_ALLOCATION;
        case ERROR_FILE_READ:
            strncat(message, "ERROR_FILE_READ /!\\", 20);

            if (errno != 0)
            {
                perror(message);
            }

            free(message);
            return ERROR_FILE_READ;
        case ERROR_FILE_COMPRESSION:
            strncat(message, "ERROR_FILE_COMPRESSION /!\\", 27);
            perror(message);
            free(message);
            return ERROR_FILE_COMPRESSION;
        case ERROR_FILE_WRITE:
            strncat(message, "ERROR_FILE_WRITE /!\\", 21);
            perror(message);
            free(message);
            return ERROR_FILE_WRITE;
        default:
            strncat(message, "UNKNOWN_ERROR /!\\", 18);
            perror(message);
            free(message);
            return -1;
    }
}