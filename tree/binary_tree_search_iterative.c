/**
 * @file binary_tree_search_iterative.c
 * @brief A basic binary tree implementation for searching with using struct and pointers.
 *        Suppose the member values in the given binary tree are unique, aligned from left to right.
 *        An iteration version of tree/binary_tree_search_recursive.c
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a node structure
typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

// Search for a value in the binary tree
bool searchInBinaryTree(BinaryTreeNode* root, int value) {
    if (root == NULL) {
        return false;
    }

    // We don't need any complex approach, since we have an assumption that the values are unique and aligned from left to right
    while (root != NULL) {
        if (root->data == value) {
            return true;
        }

        if (root->data < value) {
            root = root->right;
        } else {
            root = root->left;
        }
    }

    return false;
}

int main(void) {
    //               100
    //             ---------
    //             |       |
    //             40     200
    //           -----   -----
    //           |   |   |   |
    //           30  50 150 300

    // Building a tree
    BinaryTreeNode level2Node1 = { 30, NULL, NULL };
    BinaryTreeNode level2Node2 = { 50, NULL, NULL };
    BinaryTreeNode level2Node3 = { 150, NULL, NULL };
    BinaryTreeNode level2Node4 = { 300, NULL, NULL };
    BinaryTreeNode level1Node1 = { 40, &level2Node1, &level2Node2 };
    BinaryTreeNode level1Node2 = { 200, &level2Node3, &level2Node4 };
    BinaryTreeNode rootNode = { 100, &level1Node1, &level1Node2 };

    // Searching existing and non-existing values
    printf("Searching for 49: %s\n", searchInBinaryTree(&rootNode, 49) ? "Found" : "Not found");
    printf("Searching for 50: %s\n", searchInBinaryTree(&rootNode, 50) ? "Found" : "Not found");

    return 0;
}