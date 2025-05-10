#include "../include/huffman.h"

const char *compress_huffman(const char *inputPath, const char *outputPath)
{
    // File to compress.
    FILE *inputFile = fopen(inputPath, "rb");

    // Check that the file to be compressed has been opened successfully.
    if (inputFile == NULL)
    {
        perror("/!\\ Error during file reading.\n");
        return NULL;
    }

    Tree *tree = initialize_tree();

    if (tree = NULL)
    {
        perror("/!\\ Error during tree initialization.\n");
        return NULL;
    }

    int byte;
    while (fread(&byte, sizeof(int), 1, inputFile) == 1)
    {
        if (search_by_symbol(tree->root, byte) == NULL)
        {

        }
        else
        {

        }
    }
}

const char *decompress_huffman(const char *inputPath, const char *outputPath)
{

}