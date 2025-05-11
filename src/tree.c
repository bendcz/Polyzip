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
    Node *symbolNode = search_by_symbol(tree->root, symbol);

    if (symbolNode != NULL)
    {
        symbolNode->weight += 1;

        // Should I re-balance the tree?
    }
    else
    {
        Node *internalNode = create_node(-1, 1);
        Node *newNode = create_node(symbol, 1);

        internalNode->leftChild = tree->nytNode;
        internalNode->rightChild = newNode;

        if (tree->root == tree->nytNode)
        {
            tree->root = internalNode;
        }
        else
        {
            // Find NYT node parent.
            // Edit links.
        }

        tree->nytNode = create_node(-1, 0);
    }

    return tree;
}
