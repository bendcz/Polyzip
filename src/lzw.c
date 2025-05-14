#include "../include/lzw.h"

int compress_lzw(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "lzw");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("compress_huffman", ERROR_FILE_ALLOCATION);
    }

    // TODO

    return EXIT_SUCCESS;
}

int decompress_lzw(const char *inputPath, const char *outputPath)
{
    printf("Input path: %s\n", inputPath);
    printf("Output path: %s\n", outputPath);
    return EXIT_SUCCESS;
}