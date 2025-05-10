#include "../include/node.h"

Node *create_node(int symbol, int weight)
{
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL)
    {
        perror("/!\\ Error during node memory allocation.\n");
        return NULL;
    }

    node->symbol = symbol;
    node->weight = weight;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}

Node *insert_node(Node *root, int symbol, int weight)
{
    if (root == NULL)
    {
        root = create_node(symbol, weight);
    }
    else if (weight <= root->weight)
    {
        insert_node(root->leftChild, symbol, weight);
    }
    else
    {
        insert_node(root->rightChild, symbol, weight);
    }

    return root;
}

Node *delete_node(Node *root, int symbol)
{
    if (root == NULL)
    {
        return NULL;
    }

    //todo

}

Node *find_minimum(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->leftChild == NULL)
    {
        return root;
    }

    return find_minimum(root->leftChild);
}

Node *search_by_symbol(Node *root, int symbol)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->symbol == symbol)
    {
        return root;
    }
    else if (root->leftChild != NULL)
    {
        return search_by_symbol(root->leftChild, symbol);
    }
    else if (root->rightChild != NULL)
    {
        return search_by_symbol(root->rightChild, symbol);
    }
}

Node* search_by_weight(Node *root, int weight)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->weight == weight)
    {
        return root;
    }
    else if (weight <= root->weight)
    {
        return search(root->leftChild, weight);
    }
    else
    {
        return search(root->rightChild, weight);
    }
}

bool is_leaf(Node *root)
{
    return (root->leftChild == NULL && root->rightChild == NULL);
}