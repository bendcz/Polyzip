#ifndef NODE_H
#define NODE_H

#define NULL_VALUE '\0'

#include <stdbool.h>
#include <stdlib.h>
#include "errors.h"

typedef struct Node Node;

struct Node
{
    int symbol;
    int weight;
    int order;

    Node *parent;
    Node *leftChild;
    Node *rightChild;

    bool isNYT;
    bool isLeaf;
};

Node *create_node(int symbol, bool isNYT);
Node *initialize_tree();
Node *find_nyt_node(Node *root);
Node *find_node_by_symbol(Node *root, int symbol);
Node *find_highest_order_node_with_same_weight(Node *root, int weight);
void swap_nodes(Node *firstNode, Node *secondNode);
void rebalance(Node *node);
Node *update_tree(Node *root, int symbol);
void free_node(Node* node);

#endif