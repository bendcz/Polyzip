#include "../include/huffman.h"

int compress_huffman(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "hfm");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("compress_huffman", ERROR_FILE_ALLOCATION);
    }

    Tree *tree = initialize_tree();

    if (tree = NULL)
    {
        return print_error_message("compress_huffman", ERROR_MEMORY_ALLOCATION);
    }

    int byte;
    while (fread(&byte, sizeof(int), 1, files->inputFile) == 1)
    {
        tree = add_symbol(tree, byte);
    }

    return SUCCESS;
}

int decompress_huffman(const char *inputPath, const char *outputPath)
{
    return SUCCESS;
}