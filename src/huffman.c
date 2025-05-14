#include "../include/huffman.h"

int compress_huffman(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "hfm");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("compress_huffman", ERROR_FILE_ALLOCATION);
    }

    Node *root = initialize_tree();

    if (root == NULL)
    {
        fclose(files->inputFile);
        fclose(files->outputFile);
        free(files);
        return print_error_message("compress_huffman", ERROR_MEMORY_ALLOCATION);
    }

    uint8_t buffer = 0;
    int count = 0;
    int symbol = 0;

    fseek(files->inputFile, 0, SEEK_END);
    uint32_t originalSize = ftell(files->inputFile);
    fseek(files->inputFile, 0, SEEK_SET);
    fwrite(&originalSize, sizeof(uint32_t), 1, files->outputFile);

    while ((symbol = fgetc(files->inputFile)) != EOF)
    {
        Node *node = find_node_by_symbol(root, symbol);

        if (node == NULL)
        {
            Node *nytNode = find_nyt_node(root);
            write_code(files->outputFile, root, nytNode, &buffer, &count);

            for (int i = 7; i >= 0; i--)
            {
                write_bit(files->outputFile, &buffer, &count, (symbol >> i) & 1);
            }
        }
        else
        {
            write_code(files->outputFile, root, node,  &buffer, &count);
        }

        root = update_tree(root, symbol);
    }

    if (count > 0)
    {
        buffer <<= (8 - count);
        fwrite(&buffer, sizeof(uint8_t), 1, files->outputFile);
    }

    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);

    free_node(root);
    
    return SUCCESS;
}


int decompress_huffman(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "txt");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("decompress_huffman", ERROR_FILE_ALLOCATION);
    }

    Node *root = initialize_tree();

    if (root == NULL)
    {
        fclose(files->inputFile);
        fclose(files->outputFile);
        free(files);
        return print_error_message("decompress_huffman", ERROR_FILE_ALLOCATION);
    }

    uint32_t originalSize;
    fread(&originalSize, sizeof(uint32_t), 1, files->inputFile);
    uint32_t decodedCount = 0;

    uint8_t buffer = 0;
    int count = 0;
    int bit = 0;

    Node *currentNode = root;
    bool isEOF = false;

    while(decodedCount < originalSize)
    {
        currentNode = root;

        while (currentNode->leftChild != NULL && currentNode->rightChild != NULL)
        {
            if (!read_bit(files->inputFile, &buffer, &count, &bit))
            {
                isEOF = true;
                break;
            }

            currentNode = (bit == 0) ? currentNode->leftChild : currentNode->rightChild;
        }
        
        if (isEOF)
        {
            isEOF = true;
            break;
        }

        int symbol;

        if (currentNode->isNYT)
        {
            symbol = 0;

            for (int i = 0; i != 8; i++)
            {
                if (!read_bit(files->inputFile, &buffer, &count, &bit))
                {
                    isEOF = true;
                    break;
                }

                symbol = (symbol << 1) | bit;
            }

            if (isEOF) { break; }
        }
        else
        {
            symbol = currentNode->symbol;
        }

        fputc(symbol, files->outputFile);
        decodedCount++;
        root = update_tree(root, symbol);
    }

    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);
    free_node(root);

    return SUCCESS;
}

bool write_code(FILE *inputFile, Node *root, Node *targetNode, uint8_t *buffer, int *count)
{
    char path[CODES_SIZE];
    int depth = 0;

    Node *currentNode = targetNode;

    while (currentNode != root)
    {
        if (currentNode->parent->leftChild == currentNode)
        {
            path[depth++] = 0;
        }
        else
        {
            path[depth++] = 1;
        }

        currentNode = currentNode->parent;
    }

    for (int i = depth - 1; i >= 0; i--)
    {
        write_bit(inputFile, buffer, count, path[i]);
    }

    return true;
}