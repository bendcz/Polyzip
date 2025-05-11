#include "../include/rle.h"

// IN: Path to the file to be compressed and path to the compressed file.
// OUT: Error/success code, more details in include/errors.h.
/*
  This function opens the file passed as an argument, allocates memory
  blocks and manages whether they are too small, and uses these same blocks
  during compression using the RLE algorithm. The compressed string is saved
  in a file with the same name, but with a '.rle' extension.
*/
int compress_rle(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "rle");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("compress_rle", ERROR_FILE_ALLOCATION);
    }

    char oldByte = 0;
    char currentByte = 0;
    unsigned int occurences = 1;
    
    if (fread(&oldByte, sizeof(char), 1, files->inputFile) != 1)
    {
        fclose(files->inputFile);
        fclose(files->outputFile);
        free(files);
        return print_error_message("compress_rle", ERROR_FILE_READ);
    }
    
    // Loop over the file, character by character.
    while (fread(&currentByte, sizeof(char), 1, files->inputFile) == 1)
    {
        // If the current character is not equal to the old one, we should remember
        // the number of occurences and the old character.
        // ex: "aaab"
        // -> When we reach the 'b' character, we need to store "3a".
        // Otherwise, it's the same characters and you just increment the occurences counter.
        if (currentByte != oldByte)
        {   
            if (fprintf(files->outputFile, "%d%c", occurences, oldByte) < 0)
            {
                fclose(files->inputFile);
                fclose(files->outputFile);
                free(files);
                return print_error_message("compress_rle", ERROR_FILE_WRITE);
            }

            oldByte = currentByte;
            occurences = 1;
        }
        else
        {
            occurences += 1;
        }
    }

    if (fprintf(files->outputFile, "%d%c", occurences, oldByte) < 0)
    {
        fclose(files->inputFile);
        fclose(files->outputFile);
        free(files);
        return print_error_message("compress_rle", ERROR_FILE_WRITE);
    }

    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);

    return SUCCESS;
}

// IN: Path to the file to be compressed and path to the compressed file.
// OUT: Error/success code, more details in include/errors.h.
/*
  This function opens the file passed as an argument, allocates memory
  blocks and manages whether they are too small, and uses these same blocks
  during decompression using the RLE algorithm. The decompressed string is saved
  in a file with the same name, but with a '.txt' extension.
*/
int decompress_rle(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "txt");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("decompress_rle", ERROR_FILE_ALLOCATION);
    }

    size_t tmpSize = TMP_SIZE_INCREMENT;
    char *tmp = (char *) malloc(tmpSize);

    if (tmp == NULL)
    {
        fclose(files->inputFile);
        fclose(files->outputFile);
        free(files);
        return print_error_message("decompress_rle", ERROR_MEMORY_ALLOCATION);
    }

    char currentByte;
    int currentSize;
    
    while (fread(&currentByte, sizeof(char), 1, files->inputFile) == 1)
    {
        if (isdigit(currentByte))
        {
            tmp = check_and_realloc(tmp, &tmpSize, tmpSize + 2, TMP_SIZE_INCREMENT);

            if (tmp == NULL)
            {
                fclose(files->inputFile);
                fclose(files->outputFile);
                free(files);
                return print_error_message("decompress_rle", ERROR_MEMORY_ALLOCATION);
            }

            strncat(tmp, &currentByte, 1);
        }
        else
        {
            currentSize = atoi(tmp);

            for (int i = 0; i != currentSize; i++)
            {
                if (fwrite(&currentByte, sizeof(char), 1, files->outputFile) != 1)
                {
                    free(tmp);
                    fclose(files->inputFile);
                    fclose(files->outputFile);
                    free(files);
                    return print_error_message("decompress_rle", ERROR_FILE_WRITE);
                }
            }

            currentSize = 0;
            tmp[0] = '\0';
        }
    }

    free(tmp);
    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);

    return SUCCESS;
}