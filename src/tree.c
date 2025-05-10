#include "../include/tree.h"

Tree *initialize_tree()
{
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    Node *nytNode = create_node(-1, 0);

    if (tree == NULL || nytNode == NULL)
    {
        perror("/!\\ Error during tree memory allocation.\n");
        return NULL;
    }

    tree->nytNode = nytNode;
    tree->root = tree->nytNode;

    return tree;
}

Tree *add_symbol(Tree *tree, int symbol)
{

}
