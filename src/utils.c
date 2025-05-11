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

struct Files *get_files(const char *inputPath, const char *outputPath, const char *outputExtension)
{
    FILE *inputFile = fopen(inputPath, "rb");

    if (inputFile == NULL)
    {
        perror("/!\\ Error opening input file.\n");
        return NULL;
    }

    const char *fileName = get_file_name(inputPath);
    if (fileName == NULL)
    {
        perror("/!\\ Error getting file name.\n");
        fclose(inputFile);
        return NULL;
    }

    char *newPath = (char *) malloc(strlen(outputPath) + strlen(fileName) + 3 + 1);
    if (newPath == NULL)
    {
        perror("/!\\ Error allocating memory for new path.\n");
        fclose(inputFile);
        return NULL;
    }

    strncpy(newPath, outputPath, strlen(outputPath));
    strncat(newPath, fileName, strlen(fileName));

    const char *finalPath = get_path_with_custom_extension(newPath, outputExtension);
    if (finalPath == NULL)
    {
        perror("/!\\ Error getting final path.\n");
        free(newPath);
        fclose(inputFile);
        return NULL;
    }

    FILE *outputFile = fopen(finalPath, "wb");
    if (outputFile == NULL)
    {
        perror("/!\\ Error opening output file.\n");
        free(newPath);
        fclose(inputFile);
        return NULL;
    }

    struct Files *result = (struct Files *)malloc(sizeof(struct Files));
    if (result == NULL)
    {
        perror("/!\\ Error allocating memory for result.\n");
        free(newPath);
        fclose(inputFile);
        fclose(outputFile);
        return NULL;
    }

    result->inputFile = inputFile;
    result->outputFile = outputFile;

    free(newPath);
    return result;
}