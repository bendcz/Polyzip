#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node
{
    Node *leftChild;
    Node *rightChild;
    int value;
} Node;

Node *create_node(int value);
void insert_node(Node **root, int value);

#endif