#include "../include/node.h"

Node *create_node(int value)
{
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL)
    {
        perror("/!\\ Error during node memory allocation.\n");
        return NULL;
    }

    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}

void insert_node(Node **root, int value)
{
    
}