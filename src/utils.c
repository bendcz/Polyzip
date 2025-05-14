#include "../include/utils.h"

char *get_file_extension(const char *filePath)
{
    if (filePath == NULL) { return NULL; }

    char *lastPathSeparator = strrchr(filePath, PATH_SEPARATOR);
    char *dot =(lastPathSeparator != NULL) ? strchr(lastPathSeparator, '.') : strchr(filePath, '.');

    if (dot == NULL || dot == filePath || strchr(dot, PATH_SEPARATOR))
    {
        return NULL;
    }

    return strdup(dot + 1);
}

char *get_file_name(const char *filePath)
{
    if (filePath == NULL) { return NULL; }

    char *extension = get_file_extension(filePath);
    const char *lastPathSeparator = strrchr(filePath, PATH_SEPARATOR);

    size_t extensionOffset = extension && *extension ? strlen(extension) + 1 : 0;
    size_t charsToCopy = strlen(lastPathSeparator + 1) - extensionOffset;

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

char *get_path_without_extension(const char *filePath)
{
    if (filePath == NULL) { return NULL; }

    const char *extension = get_file_extension(filePath);
    
    if (extension == NULL || *extension == '\0')
    {
        return strdup(filePath);
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

char *get_path_with_custom_extension(const char *filePath, const char *extension)
{
    if (filePath == NULL || extension == NULL || strlen(filePath) == 0 || strlen(extension) == 0) { return strdup(filePath); }

    char * filePathWithoutExtension = get_path_without_extension(filePath);

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

    free(filePathWithoutExtension);
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

    char *fileName = get_file_name(inputPath);
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
        free(fileName);
        fclose(inputFile);
        return NULL;
    }

    snprintf(newPath, strlen(outputPath) + strlen(fileName) + 4, "%s/%s", outputPath, fileName);

    char *finalPath = get_path_with_custom_extension(newPath, outputExtension);

    if (finalPath == NULL)
    {
        perror("/!\\ Error getting final path.\n");
        free(fileName);
        free(newPath);
        fclose(inputFile);
        return NULL;
    }

    FILE *outputFile = fopen(finalPath, "wb");
    
    if (outputFile == NULL)
    {
        perror("/!\\ Error opening output file.\n");
        free(fileName);
        free(newPath);
        fclose(inputFile);
        return NULL;
    }

    struct Files *result = (struct Files *)malloc(sizeof(struct Files));

    if (result == NULL)
    {
        perror("/!\\ Error allocating memory for result.\n");
        free(fileName);
        free(newPath);
        fclose(inputFile);
        fclose(outputFile);
        return NULL;
    }

    result->inputFile = inputFile;
    result->outputFile = outputFile;

    free(fileName);
    free(newPath);
    free((char *) finalPath);
    return result;
}

bool write_bit(FILE *outputFile, uint8_t *buffer, int *count, int bit)
{
    if (outputFile == NULL || buffer == NULL || count == NULL)
    {
        print_error_message("write_bit", ERROR_MEMORY_ALLOCATION);
    }

    *buffer = (*buffer << 1) | (bit & 1);
    (*count)++;

    if (*count == 8)
    {
        fwrite(buffer, sizeof(uint8_t), 1, outputFile);
        *buffer = 0;
        *count = 0;
    }

    return true;
}

bool read_bit(FILE *inputFile, uint8_t *buffer, int *count, int *bit)
{
    if (inputFile == NULL || buffer == NULL || count == NULL || bit == NULL)
    {
        print_error_message("read_bit", ERROR_MEMORY_ALLOCATION);
    }

    if (*count == 0)
    {
        if (fread(buffer, sizeof(uint8_t), 1, inputFile) != 1)
        {
            return false;
        }

        *count = 8;
    }

    *count -= 1;
    *bit = (*buffer >> *count) & 1;

    return true;
}

void flush_buffer(FILE *inputFile, uint8_t *buffer, int *count)
{
    if (*count > 0)
    {
        *buffer <<= (8 - *count);
        fwrite(buffer, sizeof(uint8_t), 1, inputFile);
        *count = 0;
        *buffer = 0;
    }
}