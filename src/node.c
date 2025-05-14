#include "../include/node.h"
static unsigned int ORDER = 512;

Node *create_node(int symbol, bool isNYT)
{
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL)
    {
        print_error_message("create_node", ERROR_MEMORY_ALLOCATION);
        return NULL;
    }

    node->symbol = symbol;
    node->weight = 0;
    
    node->parent = NULL;
    node->leftChild = NULL;
    node->rightChild = NULL;

    node->order = ORDER--;
    node->isNYT = isNYT;
    node->isLeaf = isNYT || symbol != NULL_VALUE;

    return node;
}

Node *initialize_tree()
{
    return create_node(NULL_VALUE, true);
}

Node *find_nyt_node(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->isNYT)
    {
        return root;
    }

    Node *leftResult = find_nyt_node(root->leftChild);
    if (leftResult != NULL)
    {
        return leftResult;
    }

    return find_nyt_node(root->rightChild);
}

Node *find_node_by_symbol(Node *root, int symbol)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->isLeaf && root->symbol == symbol)
    {
        return root;
    }

    Node *leftResult = find_node_by_symbol(root->leftChild, symbol);
    if (leftResult != NULL)
    {
        return leftResult; 
    }

    return find_node_by_symbol(root->rightChild, symbol);
}

Node *find_highest_order_node_with_same_weight(Node *root, int weight)
{
    if (root == NULL)
    {
        return NULL;
    }

    Node *highestNode = NULL;

    if (root->weight == weight)
    {
        highestNode = root;
    }

    Node *leftResult = find_highest_order_node_with_same_weight(root->leftChild, weight);
    Node *rightResult = find_highest_order_node_with_same_weight(root->rightChild, weight);

    if (leftResult && (highestNode == NULL || leftResult->order > highestNode->order))
    {
        highestNode = leftResult;
    }
    else if (rightResult && (highestNode == NULL || rightResult->order > highestNode->order))
    {
        highestNode = rightResult;
    }

    return highestNode;
}

void swap_nodes(Node *firstNode, Node *secondNode)
{
    if (firstNode == NULL || secondNode == NULL)
    {
        print_error_message("swap_nodes", ERROR_MEMORY_ALLOCATION);
        return;
    }

    int tmpSymbol = firstNode->symbol;
    int tmpWeight = firstNode->weight;
    int tmpOrder = firstNode->order;
    bool tmpNYT = firstNode->isNYT;

    firstNode->symbol = secondNode->symbol;
    firstNode->weight = secondNode->weight;
    firstNode->order = secondNode->order;
    firstNode->isNYT = secondNode->isNYT;

    secondNode->symbol = tmpSymbol;
    secondNode->weight = tmpWeight;
    secondNode->order = tmpOrder;
    secondNode->isNYT = tmpNYT;
}

void rebalance(Node *node)
{
    while (node != NULL)
    {
        Node *highestNode = find_highest_order_node_with_same_weight(node, node->weight);

        if (highestNode != NULL && highestNode != node && highestNode != node->parent)
        {
            swap_nodes(node, highestNode);
        }

        node->weight += 1;
        node = node->parent;
    }
}

Node *update_tree(Node *root, int symbol)
{
    if (root == NULL)
    {
        return NULL;
    }

    Node *node = find_node_by_symbol(root, symbol);
    
    if (node == NULL)
    {
        Node *nullNode = find_nyt_node(root);

        if (nullNode == NULL)
        {
            print_error_message("update_tree", ERROR_MEMORY_ALLOCATION);
            return NULL;
        }

        Node *internalNode = create_node(NULL_VALUE, false);
        Node *currentNode = create_node(symbol, false);

        if (internalNode == NULL || currentNode == NULL)
        {
            print_error_message("update_tree", ERROR_MEMORY_ALLOCATION);
            return NULL;
        }

        internalNode->weight = 1;
        currentNode->weight = 1;

        internalNode->leftChild = nullNode;
        internalNode->rightChild = currentNode;
        internalNode->parent = nullNode->parent;

        if (nullNode->parent != NULL)
        {
            if (nullNode->parent->leftChild == nullNode)
            {
                nullNode->parent->leftChild = internalNode;
            }
            else
            {
                nullNode->parent->rightChild = internalNode;
            }
        }
        else
        {
            root = internalNode;
        }
        
        nullNode->parent = internalNode;
        currentNode->parent = internalNode;
        rebalance(internalNode);
    }
    else
    {
        node->weight += 1;
        rebalance(node);
    }

    return root;
}

void free_node(Node *node)
{
    if (node != NULL)
    {
        free_node(node->leftChild);
        free_node(node->rightChild);
        free(node);
    }
}