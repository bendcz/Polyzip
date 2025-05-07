#include "../include/utils.h"

const char *get_file_extension(const char *filePath)
{
    const char *dot = strrchr(filePath, '.');
    
    if (!dot || dot == filePath)
    {
        return "";
    }

    return dot + 1;
}

const char *get_path_whitout_extension(const char *filePath)
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
    const char * filePathWithoutExtension = get_path_whitout_extension(filePath);

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