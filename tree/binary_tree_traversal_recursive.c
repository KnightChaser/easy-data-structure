/**
 * @file binary_tree_traversal_recursive.c
 * @brief A basic binary tree traversal implementation with using struct and pointers.
 *        By using recursive approach, it will traverse the tree in three ways in easy way.
 *        (Preorder, Inorder, Postorder)
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a node structure
typedef char BinaryTreeElementType;

struct BinaryTreeNode {
    BinaryTreeElementType data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

// Preorder traversal
// Root -> Left -> Right
void preorder(struct BinaryTreeNode* node) {
    if (node == NULL) {
        return;
    }
    printf("%c ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// Inorder traversal
// Left -> Root -> Right
void inorder(struct BinaryTreeNode* node) {
    if (node == NULL) {
        return;
    }
    inorder(node->left);
    printf("%c ", node->data);
    inorder(node->right);
}

// Postorder traversal
// Left -> Right -> Root
void postorder(struct BinaryTreeNode* node) {
    if (node == NULL) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    printf("%c ", node->data);
}

// Create a node with the given value
struct BinaryTreeNode* createNode(BinaryTreeElementType data) {
    struct BinaryTreeNode* newNode = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    // Don't forget to free this node after using it >_<
    return newNode;
}

// Free the entire tree
void freeTree(struct BinaryTreeNode* node) {
    if (node == NULL) {
        return;
    }

    // By recursive approach, free all nodes
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main(void) {
    // Diagram
    //       A
    //     -----
    //     |   |
    //     B   C
    //   ---  ---
    //   | |  | |
    //   D E  F G

    // Create a root node
    struct BinaryTreeNode* root = createNode('A');

    // Create left and right child nodes
    root->left = createNode('B');
    root->right = createNode('C');

    // Create left and right child nodes of the left child node
    root->left->left = createNode('D');
    root->left->right = createNode('E');

    // Create left and right child nodes of the right child node
    root->right->left = createNode('F');
    root->right->right = createNode('G');

    // Preorder traversal
    printf("Preorder traversal : ");
    preorder(root);

    // Inorder traversal
    printf("\nInorder traversal  : ");
    inorder(root);

    // Postorder traversal
    printf("\nPostorder traversal: ");
    postorder(root);

    // Free
    freeTree(root);

    return 0;

}

// Preorder traversal : A B D E C F G 
// Inorder traversal  : D B E A F C G
// Postorder traversal: D E B F G C A