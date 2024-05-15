/**
 * @file binary_tree_for_expressions_2.c
 * @brief A basic binary tree implementation for expressions with using struct and pointers.
 *        By using the postorder traversal, we can get the result of the expression.
 *        It parses the given expression and builds a binary tree from it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a node structure
typedef struct BinaryTreeNode {
    float data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

// Create a new node with a given value
BinaryTreeNode* createNode(float value) {
    BinaryTreeNode* newNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Check if the given character is an operator
bool isOperator(char character) {
    return character == '+' || character == '-' || character == '*' || character == '/';
}

// Build a binary tree from the given expression
BinaryTreeNode* buildExpressionTree(const char* expression) {
    BinaryTreeNode* stack[100]; // Stack to hold nodes
    int top = -1;               // Stack top

    for (unsigned int index = 0; expression[index] != '\0'; index++) {
        if (isOperator(expression[index])) {
            // Create a new node for the operator
            BinaryTreeNode* node = createNode(expression[index]);

            // Pop two nodes from the stack and set them as children
            node->right = stack[top];       top--;
            node->left = stack[top];        top--;

            // Push the new node onto the stack
            
            stack[top] = node;
        } else if (expression[index] >= '0' && expression[index] <= '9') {
            // Create a new node for the operand
            BinaryTreeNode* node = createNode(expression[index] - '0');

            // Push the node onto the stack
            top++;
            stack[top] = node;
        } else {
            // Ignore invalid characters
            continue;
        }
    }
    // The root of the tree is the only node left on the stack
    return stack[top];
}

// Postorder traversal
void postorder(BinaryTreeNode* root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);

    if (isOperator((char)root->data))
        printf("%c ", (char)root->data);
    else
        printf("%.0f ", root->data);
}

// Calculate the result of the expression
float calculate(BinaryTreeNode* root) {
    if (root->left == NULL && root->right == NULL)
        return root->data;
    
    float left = calculate(root->left);
    float right = calculate(root->right);

    switch ((char)root->data) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        default:
            return 0;
    }
}

int main(void) {
    const char* expression = "53*2+";

    // How does this work?
    // 1. Build the expression tree. The given expression will be converted to the following tree:
    // 2. Traverse the tree in postorder and print the result.
    // 3. Calculate the result of the expression.
    BinaryTreeNode* root = buildExpressionTree(expression);
    printf("Postorder traversal: ");
    postorder(root);

    printf("\n");
    printf("Result: %.2f\n", calculate(root));

    return 0;
}
