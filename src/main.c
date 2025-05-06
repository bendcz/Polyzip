#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("▗▄▄▖  ▄▄▄  █ ▄   ▄ ▄▄▄▄▄ ▄ ▄▄▄▄\n");
    printf("▐▌ ▐▌█   █ █ █   █  ▄▄▄▀ ▄ █   █\n");
    printf("▐▛▀▘ ▀▄▄▄▀ █  ▀▀▀█ █▄▄▄▄ █ █▄▄▄▀\n");
    printf("▐▌         █ ▄   █       █ █     \n");
    printf("              ▀▀▀          ▀    \n");
    printf("This program compresses files using RLE encoding.\n");

    if (argc < 3)
    {
        printf("\n/!\\ Error during program call.\n");
        printf("Usage: ./polyzip --rle <FILE_PATH>\n");
        return EXIT_FAILURE;
    }

    if (strncmp(argv[1], "--rle", 5) == 0)
    {

    }

    return EXIT_SUCCESS;
}