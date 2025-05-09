#include "../include/utils.h"

const char *get_file_extension(const char *filePath)
{
    if (filePath == NULL) { return ""; }

    const char *lastPathSeparator = strrchr(filePath, *PATH_SEPARATOR);
    const char *firstDot = NULL;
    const char *tmp = NULL;

    firstDot = (lastPathSeparator != NULL) ? strchr(lastPathSeparator, '.') : strchr(filePath, '.');
    tmp = firstDot - 1;

    if (firstDot == NULL || firstDot == filePath || (tmp != NULL && strncmp(tmp, PATH_SEPARATOR, 1) == 0))
    {
        return "";
    }

    return firstDot + 1;
}

const char *get_file_name(const char *filePath)
{
    if (filePath == NULL) { return ""; }

    const char *extension = get_file_extension(filePath);
    const char *lastPathSeparator = strrchr(filePath, *PATH_SEPARATOR);
    size_t charsToCopy = strlen(lastPathSeparator) - strlen(extension) - 2;

    char *result = (char *) malloc(sizeof(char) * charsToCopy + 1);

    if (result == NULL)
    {
        perror("/!\\ Error during memory allocation.");
        exit(EXIT_FAILURE);
    }

    strncpy(result, lastPathSeparator + 1, charsToCopy);
    result[charsToCopy] = '\0';
    return result;
}

const char *get_path_without_extension(const char *filePath)
{
    if (filePath == NULL) { return ""; }

    const char *extension = get_file_extension(filePath);
    
    if (strncmp(extension, "\0", 1) == 0)
    {
        return filePath;
    }

    size_t charsToCopy = strlen(filePath) - strlen(extension) - 1;
    char *result = (char *)malloc(sizeof(char) * (charsToCopy + 1));

    if (result == NULL)
    {
        return NULL; 
    }

    memcpy(result, filePath, charsToCopy);
    result[charsToCopy] = '\0';

    return result;
}

const char *get_path_with_custom_extension(const char *filePath, const char *extension)
{
    if (filePath == NULL || extension == NULL || strlen(filePath) == 0 || strlen(extension) == 0) { return filePath; }

    const char * filePathWithoutExtension = get_path_without_extension(filePath);

    size_t filePathLength = strlen(filePathWithoutExtension);
    size_t extensionLength = strlen(extension);
    size_t finalLength = filePathLength + extensionLength + 1;
    bool addADot = false;

    if (strchr(extension, '.') != &extension[0])
    {
        addADot = true;
        finalLength += 1;
    }

    char *result = (char *) malloc(sizeof(char) * finalLength);

    if (result != NULL)
    {
        result[0] = '\0';

        strncat(result, filePathWithoutExtension, filePathLength);

        if (addADot)
        {
            strcat(result, ".");
        }

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