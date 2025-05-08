#include "../include/rle.h"

// IN: Path to the file to be compressed.
// OUT: 0 (success) or 1 (failure).
/*
  This function opens the file passed as an argument, allocates memory
  blocks and manages whether they are too small, and uses these same blocks
  during compression using the RLE algorithm. The compressed string is saved
  in a file with the same name, in the same directory but with a '.rle' extension.
*/
int compress_rle(const char *filePath)
{
    FILE *inputFile = fopen(filePath, "rb");

    if (inputFile == NULL)
    {
        printf("/!\\ Error during file reading.\n");
        return EXIT_FAILURE;
    }

    size_t resultSize = RESULT_SIZE_INCREMENT;
    char *result = (char *) malloc(resultSize);
    size_t tmpSize = TMP_SIZE_INCREMENT;
    char *tmp = (char *) malloc(tmpSize);

    if (result == NULL || tmp == NULL)
    {
        printf("/!\\ Error during memory allocation.\n");
        return EXIT_FAILURE;
    }

    result[0] = '\0';
    tmp[0] = '\0';

    char oldChar = fgetc(inputFile);
    char currentChar;
    unsigned int occurences = isprint(oldChar) ? 1 : 0;
    int tmpLength = 0;
    
    while (fread(&currentChar, sizeof(char), 1, inputFile) == 1)
    {
        if (currentChar != oldChar)
        {
            tmpLength = snprintf(NULL, 0, "%d", occurences);
            tmp = check_and_realloc(tmp, &tmpSize, tmpSize + 2, TMP_SIZE_INCREMENT);

            if (tmp == NULL)
            {
                return EXIT_FAILURE;
            }
            
            int nbCharsWritten = snprintf(tmp, tmpSize, "%d%c", occurences, oldChar);

            if (nbCharsWritten <= 0)
            {
                printf("/!\\ Error during compression.");
                return EXIT_FAILURE;
            }

            result = check_and_realloc(result, &resultSize, strlen(result) + strlen(tmp) + 1, RESULT_SIZE_INCREMENT);

            if (result == NULL)
            {
                return EXIT_FAILURE;
            }
    
            strncat(result, tmp, nbCharsWritten);

            oldChar = currentChar;
            occurences = 1;
        }
        else
        {
            occurences += 1;
        }
    }


    tmpLength = snprintf(NULL, 0, "%d", occurences);
    tmp = check_and_realloc(tmp, &tmpSize, tmpLength + 2, TMP_SIZE_INCREMENT);

    if (tmp == NULL)
    {
        return EXIT_FAILURE;
    }

    snprintf(tmp, tmpSize, "%d%c", occurences, oldChar);

    result = check_and_realloc(result, &resultSize, strlen(result) + strlen(tmp) + 1, RESULT_SIZE_INCREMENT);

    if (result == NULL)
    {
        return EXIT_FAILURE;
    }
    
    strncat(result, tmp, strlen(tmp));

    fclose(inputFile);

    
    const char *newPath = get_path_with_custom_extension(filePath, "rle");
    FILE *outputFile = fopen(newPath, "wb");

    if (outputFile == NULL)
    {
        printf("/!\\ Error during file writing.\n");
        free(result);
        free(tmp);
        return EXIT_FAILURE;
    }

    fwrite(result, sizeof(char), strlen(result), outputFile);
    fclose(outputFile);

    free(result);
    free(tmp);
    free((char *) newPath);

    return EXIT_SUCCESS;
}

int decompress_rle(const char *filePath)
{
    FILE *inputFile = fopen(filePath, "rb");

    if (inputFile == NULL)
    {
        printf("/!\\ Error during file reading.\n");
        return EXIT_FAILURE;
    }

    size_t resultSize = RESULT_SIZE_INCREMENT;
    char *result = (char *) malloc(resultSize);

    size_t tmpSize = TMP_SIZE_INCREMENT;
    char *tmp = (char *) malloc(tmpSize);

    if (result == NULL || tmp == NULL)
    {
        printf("/!\\ Error during memory allocation.\n");
        return EXIT_FAILURE;
    }

    char currentChar;
    int currentSize;
    
    while (fread(&currentChar, sizeof(char), 1, inputFile) == 1)
    {
        if (isdigit(currentChar))
        {
            tmp = check_and_realloc(tmp, &tmpSize, tmpSize + 2, TMP_SIZE_INCREMENT);

            if (tmp == NULL)
            {
                free(result);
                return EXIT_FAILURE;
            }

            strncat(tmp, &currentChar, 1);
        }
        else
        {
            currentSize = atoi(tmp);

            result = check_and_realloc(result, &resultSize, resultSize + currentSize + 1, RESULT_SIZE_INCREMENT);

            if (result == NULL)
            {
                free(tmp);
                return EXIT_FAILURE;
            }

            for (int i = 0; i != currentSize; i++)
            {
                strncat(result, &currentChar, 1);
            }

            currentSize = 0;
            tmp[0] = '\0';
        }
    }

    free(tmp);
    fclose(inputFile);

    const char *newPath = get_path_with_custom_extension(filePath, "txt");
    FILE *outputFile = fopen(newPath, "wb");
    fprintf(outputFile, result);

    free((char *) newPath);
    free(result);
    fclose(outputFile);

    return EXIT_SUCCESS;
}