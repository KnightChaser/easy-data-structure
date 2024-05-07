/**
 * @file binary_tree_basic.c
 * @brief A basic binary tree implementation with using struct and pointers.
 */
//

#include <stdio.h>
#include <stdlib.h>

// Define a node structure
typedef char BinaryTreeElementType;

struct BinaryTreeNode {
    BinaryTreeElementType data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

int main(void) {

    // Diagram
    //       A
    //     -----
    //     |   |
    //     B   C

    // Create a root node
    struct BinaryTreeNode* root = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    root->data = 'A';

    // Create left and right child nodes
    struct BinaryTreeNode* leftChild = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    leftChild->data = 'B';
    leftChild->left = NULL;
    leftChild->right = NULL;
    root->left = leftChild;

    struct BinaryTreeNode* rightChild = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    rightChild->data = 'C';
    rightChild->left = NULL;
    rightChild->right = NULL;
    root->right = rightChild;

    // Free
    free(root);
    free(leftChild);
    free(rightChild);

    return 0;
}