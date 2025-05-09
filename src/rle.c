#include "../include/rle.h"

// IN: Path to the file to be compressed and path to the compressed file.
// OUT: 0 (success) or 1 (failure).
/*
  This function opens the file passed as an argument, allocates memory
  blocks and manages whether they are too small, and uses these same blocks
  during compression using the RLE algorithm. The compressed string is saved
  in a file with the same name, but with a '.rle' extension.
*/
int compress_rle(const char *inputPath, const char *outputPath)
{
    // File to compress.
    FILE *inputFile = fopen(inputPath, "rb");

    // Contains output content.
    size_t resultSize = RESULT_SIZE_INCREMENT;
    char *result = (char *) malloc(resultSize);
    
    // Contains the content to be concatenated with the result as the file
    // is read during the compression phase.
    size_t tmpSize = TMP_SIZE_INCREMENT;
    char *tmp = (char *) malloc(tmpSize);

    // Check that the file to be compressed has been opened successfully.
    if (inputFile == NULL)
    {
        perror("/!\\ Error during file reading.\n");
        return EXIT_FAILURE;
    }

    // Check the results of memory allocation.
    if (result == NULL || tmp == NULL)
    {
        perror("/!\\ Error during memory allocation.\n");
        return EXIT_FAILURE;
    }

    // The termination character is added at the start, before concatenations
    // in the rest of the code.
    result[0] = '\0';
    tmp[0] = '\0';

    // Obtain the first character of the file.
    char oldChar = fgetc(inputFile);

    // This variable will be used to store the current char in the file read loop.
    char currentChar;

    // This variable stores the number of occurences of the current character.
    unsigned int occurences = 1;
    
    // Loop over the file, character by character.
    while (fread(&currentChar, sizeof(char), 1, inputFile) == 1)
    {
        // If the current character is not equal to the old one, we should remember
        // the number of occurences and the old character.
        // ex: "aaab"
        // -> When we reach the 'b' character, we need to store "3a".
        // Otherwise, it's the same characters and you just increment the occurences counter.
        if (currentChar != oldChar)
        {
            // Reallocation if we need more space.
            tmp = check_and_realloc(tmp, &tmpSize, tmpSize + 2, TMP_SIZE_INCREMENT);
            if (tmp == NULL) { return EXIT_FAILURE; }
            
            int nbCharsWritten = snprintf(tmp, tmpSize, "%d%c", occurences, oldChar);

            if (nbCharsWritten <= 0)
            {
                perror("/!\\ Error during compression.");
                return EXIT_FAILURE;
            }

            // Reallocation if we need more space.
            result = check_and_realloc(result, &resultSize, strlen(result) + strlen(tmp) + 1, RESULT_SIZE_INCREMENT);
            if (result == NULL) { return EXIT_FAILURE; }
    
            strncat(result, tmp, nbCharsWritten);

            oldChar = currentChar;
            occurences = 1;
        }
        else
        {
            occurences += 1;
        }
    }

    // This variable is used in oder to store the length of tmp.
    int tmpLength = snprintf(NULL, 0, "%d", occurences);
    tmp = check_and_realloc(tmp, &tmpSize, tmpLength + 2, TMP_SIZE_INCREMENT);

    if (tmp == NULL) { return EXIT_FAILURE; }

    snprintf(tmp, tmpSize, "%d%c", occurences, oldChar);

    // Reallocation if we need more space.
    result = check_and_realloc(result, &resultSize, strlen(result) + strlen(tmp) + 1, RESULT_SIZE_INCREMENT);
    if (result == NULL) { return EXIT_FAILURE; }

    strncat(result, tmp, strlen(tmp));

    // The role of these lines is to manage the compressed file path.
    const char *fileName = get_file_name(inputPath);
    char *newPath = (char *) malloc(sizeof(char) * strlen(outputPath) + strlen(fileName) + 3 + 1);
    if (newPath == NULL) { return EXIT_FAILURE; }

    strncpy(newPath, outputPath, strlen(outputPath));
    strncat(newPath, fileName, strlen(fileName));

    FILE *outputFile = fopen(get_path_with_custom_extension(newPath, "rle"), "wb");

    if (outputFile == NULL)
    {
        printf("/!\\ Error during file writing.\n");
        free(result);
        free(tmp);
        return EXIT_FAILURE;
    }

    fwrite(result, sizeof(char), strlen(result), outputFile);
    
    fclose(inputFile);
    fclose(outputFile);
    free(result);
    free(tmp);
    free((char *) newPath);

    return EXIT_SUCCESS;
}

// IN: Path to the file to be compressed and path to the compressed file.
// OUT: 0 (success) or 1 (failure).
/*
  This function opens the file passed as an argument, allocates memory
  blocks and manages whether they are too small, and uses these same blocks
  during decompression using the RLE algorithm. The decompressed string is saved
  in a file with the same name, but with a '.txt' extension.
*/
int decompress_rle(const char *inputPath, const char *outputPath)
{
    // File to decompress.
    FILE *inputFile = fopen(inputPath, "rb");

    if (inputFile == NULL)
    {
        perror("/!\\ Error during file reading.\n");
        return EXIT_FAILURE;
    }

    // Contains the decompressed content.
    size_t resultSize = RESULT_SIZE_INCREMENT;
    char *result = (char *) malloc(resultSize);

    size_t tmpSize = TMP_SIZE_INCREMENT;
    char *tmp = (char *) malloc(tmpSize);

    if (result == NULL || tmp == NULL)
    {
        perror("/!\\ Error during memory allocation.\n");
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

    // The role of these lines is to manage the compressed file path.
    const char *fileName = get_file_name(inputPath);
    char *newPath = (char *) malloc(sizeof(char) * strlen(outputPath) + strlen(fileName) + 3 + 1);
    if (newPath == NULL) { return EXIT_FAILURE; }

    strncpy(newPath, outputPath, strlen(outputPath));
    strncat(newPath, fileName, strlen(fileName));

    FILE *outputFile = fopen(get_path_with_custom_extension(newPath, "txt"), "wb");
    fprintf(outputFile, result);

    free((char *) newPath);
    free(result);
    fclose(outputFile);

    return EXIT_SUCCESS;
}