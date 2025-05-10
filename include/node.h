#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node *leftChild;
    Node *rightChild;
    int value;
};

Node *create_node(int value);
Node *insert_node(Node *root, int value);
bool search(Node *root, int value);

#endif