#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include "node.h"

typedef struct Tree Tree;

struct Tree {
    Node *root;
    Node *nytNode;
};

Tree *initialize_tree();
Tree *add_symbol(Tree *tree, int symbol);

#endif