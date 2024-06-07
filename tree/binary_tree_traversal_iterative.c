/**
 * @file binary_tree_traversal_iterative.c
 * @brief A basic binary tree traversal implementation with using struct and pointers.
 *        By using iterative approach, it will traverse the tree in three ways (a little bit complex way).
 *        (Preorder, Inorder, Postorder, Level order(BFS))
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

// Define a stack structure, it will be used for iterative traversals
// (In recursive approach, we don't need to use stack explicitly, because of the function call stack)
struct Stack {
    struct BinaryTreeNode** array;
    int top;
    int capacity;
} Stack;

// Create a stack with the given capacity
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct BinaryTreeNode**)malloc(stack->capacity * sizeof(struct BinaryTreeNode*));
    return stack;
}

// Check if the stack is full
bool isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Check if the stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an item to the stack
void push(struct Stack* stack, struct BinaryTreeNode* item) {
    if (isFull(stack)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
}

// Pop an item from the stack
struct BinaryTreeNode* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        return NULL;
    }
    return stack->array[stack->top--];
}

// Preorder traversal
// Root -> Left -> Right
void preorder(struct BinaryTreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a stack with the capacity of 100
    struct Stack* stack = createStack(100);

    // Push the root node to the stack
    push(stack, root);

    // Traverse the tree iteratively
    while (!isEmpty(stack)) {
        // Pop the top item from the stack
        struct BinaryTreeNode* node = pop(stack);
        printf("%c ", node->data);

        // Push the right child first, because we want to process the left child first
        if (node->right != NULL) {
            push(stack, node->right);
        }

        // Push the left child later, because we want to process the left child first
        if (node->left != NULL) {
            push(stack, node->left);
        }
    }

    // Free the stack
    free(stack);
}

// Inorder traversal
// Left -> Root -> Right
void inorder(struct BinaryTreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a stack with the capacity of 100
    struct Stack* stack = createStack(100);

    // Start from the root node
    struct BinaryTreeNode* current = root;

    // Traverse the tree iteratively
    while (current != NULL || !isEmpty(stack)) {

        // Reach the leftmost node of the current node
        // Push all left nodes to the stack
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        // Pop the root node from the stack (we popped the leftmost node before, so it's the root node now)
        current = pop(stack);
        printf("%c ", current->data);

        // Move to the right child
        current = current->right;
    }

    // Free the stack
    free(stack);
}

// Postorder traversal
// Left -> Right -> Root
void postorder(struct BinaryTreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create two stacks with the capacity of 100
    struct Stack* stack1 = createStack(100);
    struct Stack* stack2 = createStack(100);

    // Push the root node to the first stack
    push(stack1, root);

    // Traverse the tree iteratively
    while (!isEmpty(stack1)) {
        // Pop the top item from the first stack
        struct BinaryTreeNode* node = pop(stack1);

        // Push the node to the second stack
        push(stack2, node);
        
        // Push the left child first, because we want to process the right child first
        if (node->left != NULL) {
            push(stack1, node->left);
        }

        // Push the right child later, because we want to process the right child first
        if (node->right != NULL) {
            push(stack1, node->right);
        }
    }

    // Print the nodes in the second stack
    while (!isEmpty(stack2)) {
        struct BinaryTreeNode* node = pop(stack2);
        printf("%c ", node->data);
    }

    // Free the stacks
    free(stack1);
    free(stack2);
}

// Level order traversal (BFS; Breadth First Search)
void levelOrder(struct BinaryTreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Level order(BFS) requires a queue structure
    // For now, we will use just an array to simulate a queue
    struct BinaryTreeNode* queue[100];
    unsigned int front = 0;
    unsigned int rear = 0;

    // Enqueue the root node
    queue[rear] = root;
    rear++;

    // Traverse the tree iteratively
    while (front < rear) {
        // Dequeue the front node
        struct BinaryTreeNode* node = queue[front];
        front++;

        printf("%c ", node->data);

        // Enqueue the left child
        if (node->left != NULL) {
            queue[rear] = node->left;
            rear++;
        }

        // Enqueue the right child
        if (node->right != NULL) {
            queue[rear] = node->right;
            rear++;
        }
    }
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

    // Free the current node
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
    printf("Preorder traversal        : ");
    preorder(root);

    // Inorder traversal
    printf("\nInorder traversal         : ");
    inorder(root);

    // Postorder traversal
    printf("\nPostorder traversal       : ");
    postorder(root);

    // Level order traversal(BFS)
    printf("\nLevel order traversal(BFS): ");
    levelOrder(root);

    // Free
    freeTree(root);

    return 0;
}

// Preorder traversal        : A B D E C F G 
// Inorder traversal         : D B E A F C G
// Postorder traversal       : D E B F G C A
// Level order traversal(BFS): A B C D E F G