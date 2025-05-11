#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node *leftChild;
    Node *rightChild;
    char symbol;
    int weight;
};

Node *create_node(char symbol, int weight);
Node *insert_node(Node *root, char symbol, int weight);
Node *delete_node(Node *root, int weight);
Node *find_minimum(Node *root);
Node *search_by_symbol(Node *root, char symbol);
Node *search_by_weight(Node *root, int weight);
Node *find_nyt_parent(Node *root, Node *nytNode);
bool is_leaf(Node *root);

#endif