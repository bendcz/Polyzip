#include "../include/tree.h"

Tree *initialize_tree()
{
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    Node *nytNode = create_node('\0', 0);

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
    }
    else
    {
        Node *internalNode = create_node('\0', 1);
        Node *newNode = create_node(symbol, 1);

        internalNode->leftChild = tree->nytNode;
        internalNode->rightChild = newNode;

        if (tree->root == tree->nytNode)
        {
            tree->root = internalNode;
        }
        else
        {
            Node *nytParent = find_nyt_parent(tree->root, tree->nytNode);

            if (nytParent != NULL)
            {
                if (nytParent->leftChild == tree->nytNode)
                {
                    nytParent->leftChild = internalNode;
                }
                else
                {
                    nytParent->rightChild = internalNode;
                }
            }
        }

        tree->nytNode = create_node('\0', 0);
    }

    return tree;
}

void free_tree(Node *root)
{
    if (root == NULL) { return; }

    free_tree(root->leftChild);
    free_tree(root->rightChild);
    free(root);
}