#include "../include/utils.h"

const char *get_file_extension(const char *filePath)
{
    const char *firstDot = strchr(filePath, '.');
    const char *tmp = firstDot - 1;

    if (firstDot == NULL || firstDot == filePath || (tmp != NULL && strncmp(tmp, PATH_SEPARATOR, 1) == 0))
    {
        return "";
    }

    return firstDot + 1;
}

const char *get_path_without_extension(const char *filePath)
{
    const char *extension = get_file_extension(filePath);

    char *p, *q, *r;

    if (*extension && (q = r = strstr(filePath, extension)) != NULL)
    {
        size_t len = strlen(extension);
        while ((r = strstr(p = r + len, extension)) != NULL)
        {
            while (p < r)
                *q++ = *p++;
        }

        while ((*q++ = *p++) != '\0')
            continue;
    }

    return filePath;
}

char *get_path_with_custom_extension(const char *filePath, const char *extension)
{
    const char * filePathWithoutExtension = get_path_without_extension(filePath);

    size_t filePathLength = strlen(filePathWithoutExtension);
    size_t extensionLength = strlen(extension);
    size_t finalLength = filePathLength + extensionLength + 1;

    char *result = (char *) malloc(sizeof(char) * finalLength);

    if (result != NULL)
    {
        result[0] = '\0';
        strncat(result, filePathWithoutExtension, filePathLength);
        strncat(result, extension, extensionLength);
    }

    return result;
}

char *check_and_realloc(char *buffer, size_t *bufferSize, size_t requiredSize, size_t increment)
{
    if (requiredSize >= *bufferSize)
    {
        *bufferSize += increment;
        char *newBuffer = (char *) realloc(buffer, *bufferSize);

        if (newBuffer == NULL)
        {
            printf("/!\\ Error during memory reallocation.\n");
            free(buffer);
            return NULL;
        }

        return newBuffer;
    }
    
    return buffer;
}