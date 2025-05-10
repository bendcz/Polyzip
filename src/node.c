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

Node *insert_node(Node *root, int value)
{
    if (root == NULL)
    {
        root = create_node(value);
    }
    else if (value <= root->value)
    {
        insert_node(root->leftChild, value);
    }
    else
    {
        insert_node(root->rightChild, value);
    }

    return root;
}

bool search(Node *root, int value)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->value == value)
    {
        return true;
    }
    else if (value <= root->value)
    {
        return search(root->leftChild, value);
    }
    else
    {
        return search(root->rightChild, value);
    }
}

Node *find_minimum(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->leftChild == NULL)
    {
        return root->value;
    }

    return find_minimum(root->leftChild);
}

bool delete_node(Node *root, int value)
{
    if (root == NULL)
    {
        return false;
    }

    Node *node = search(root, value);
}