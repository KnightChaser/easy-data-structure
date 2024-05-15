/**
 * @file binary_tree_for_expressions_1.c
 * @brief A basic binary tree implementation for expressions with using struct and pointers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a node structure 
typedef struct BinaryTreeNode {
    double data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

// Create a new node with a given value
// Can you guess which traversal we are going to use to evaluate the expression? Answer: Postorder traversal
double evalulateExpressionBinaryTree(BinaryTreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->data;
    }

    double leftValue = evalulateExpressionBinaryTree(root->left);
    double rightValue = evalulateExpressionBinaryTree(root->right);

    // (char)root->data is used to convert the ASCII value to the character, for arithmetic operations
    switch ((char)root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue;
        default:
            return 0;
    }

}

int main(void) {
    // We are going to evaluate the following expression: (3 * 2) + (16 + 25)
    //                 +
    //             --------
    //             |      |
    //             *      +
    //         -----      -----
    //        |    |      |   |
    //        3    2     16   25
    BinaryTreeNode level2Node1 = { 3, NULL, NULL };
    BinaryTreeNode level2Node2 = { 2, NULL, NULL };
    BinaryTreeNode level2Node3 = { 16, NULL, NULL };
    BinaryTreeNode level2Node4 = { 25, NULL, NULL };
    BinaryTreeNode level1Node1 = { '*', &level2Node1, &level2Node2 };
    BinaryTreeNode level1Node2 = { '+', &level2Node3, &level2Node4 };
    BinaryTreeNode root = { '+', &level1Node1, &level1Node2 };

    printf("The result of the expression is: %.2f\n", evalulateExpressionBinaryTree(&root));

    return 0;
}

// The result of the expression is: 47.00