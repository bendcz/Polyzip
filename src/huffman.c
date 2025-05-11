#include "../include/huffman.h"

int compress_huffman(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "hfm");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("compress_huffman", ERROR_FILE_ALLOCATION);
    }

    Tree *tree = initialize_tree();

    if (tree == NULL)
    {
        return print_error_message("compress_huffman", ERROR_MEMORY_ALLOCATION);
    }

    int byte;
    while (fread(&byte, sizeof(int), 1, files->inputFile) == 1)
    {
        tree = add_symbol(tree, byte);
    }

    char *codes = (char *) malloc(sizeof(char) * CODES_SIZE);

    if (codes == NULL)
    {
        return print_error_message("compress_huffman", ERROR_MEMORY_ALLOCATION);
    }
    
    get_huffman_codes(tree, codes);
    
    rewind(files->inputFile);

    while (fread(&byte, sizeof(int), 1, files->inputFile) == 1)
    {
        char *code = codes[(unsigned char) byte];
        fputs(code, files->outputFile);
    }

    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);

    free_tree(tree->root);
    free(tree);

    return SUCCESS;
}

int decompress_huffman(const char *inputPath, const char *outputPath)
{
    return SUCCESS;
}

int generate_huffman_codes(Node *node, char **codes, char *code, int depth)
{
    if (codes == NULL || code == NULL)
    {
        return print_error_message("generate_huffman_codes", ERROR_MEMORY_ALLOCATION);
    }

    if (node == NULL)
    {
        return;
    }

    if (node->symbol != '\0')
    {
        code[depth] = '\0';
        codes[(unsigned char) node->symbol] = strdup(code);
    }

    if (node->leftChild != NULL)
    {
        code[depth] = '0';
        generate_huffman_codes(node->leftChild, codes, code, depth + 1);
    }

    if (node->rightChild != NULL)
    {
        code[depth] = '1';
        generate_huffman_codes(node->rightChild, codes, code, depth + 1);
    }
}