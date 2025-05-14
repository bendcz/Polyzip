#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"
#include "../include/huffman.h"
#include "../include/lzw.h"

int main(int argc, char *argv[])
{
    printf("▗▄▄▖  ▄▄▄  █ ▄   ▄ ▄▄▄▄▄ ▄ ▄▄▄▄\n");
    printf("▐▌ ▐▌█   █ █ █   █  ▄▄▄▀ ▄ █   █\n");
    printf("▐▛▀▘ ▀▄▄▄▀ █  ▀▀▀█ █▄▄▄▄ █ █▄▄▄▀\n");
    printf("▐▌         █ ▄   █       █ █     \n");
    printf("              ▀▀▀          ▀    \n");
    printf("lets you compress and decompress files using various algorithms.\n");

    if (argc < 5)
    {
        printf("\n/!\\ Error during program call.\n");
        printf("Usage: ./polyzip -<c|d> -rle <INPUT_PATH> <OUTPUT_PATH> <CUSTOM_NAME>?\n");
        return EXIT_FAILURE;
    }

    if (strncmp(argv[1], "-c", 2) == 0)
    {
        if (strncmp(argv[2], "-rle", 4) == 0)
        {
            compress_rle(argv[3], argv[4]);
        }
        else if (strncmp(argv[2], "-huffman", 8) == 0)
        {
            compress_huffman(argv[3], argv[4]);
        }
        else if (strncmp(argv[2], "-lzw", 4) == 0)
        {
            compress_lzw(argv[3], argv[4]);
        }
    }
    else if (strncmp(argv[1], "-d", 2) == 0)
    {
        if (strncmp(argv[2], "-rle", 4) == 0)
        {
            decompress_rle(argv[3], argv[4]);
        }
        else if (strncmp(argv[2], "-huffman", 8) == 0)
        {
            decompress_huffman(argv[3], argv[4]);
        }
        else if (strncmp(argv[2], "-lzw", 4) == 0)
        {
            decompress_lzw(argv[3], argv[4]);
        }
    }

    return EXIT_SUCCESS;
}