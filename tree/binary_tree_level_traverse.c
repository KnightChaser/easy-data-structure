/**
 * @file binary_tree_level_traverse.c
 * @brief A basic binary tree level traversal implementation with using struct and pointers.
 *        The level traverse strategy uses a queue to traverse the tree level by level.
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

// Define a queue structure, it will be used for level traversal
struct Queue {
    struct BinaryTreeNode** array;
    int front;
    int rear;
    int capacity;
} Queue;

// Create a queue with the given capacity
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->array = (struct BinaryTreeNode**)malloc(queue->capacity * sizeof(struct BinaryTreeNode*));

    // Don't forget free this queue after using it >_<
    return queue;
}

// Check if the queue is full
bool isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Check if the queue is empty
bool isEmpty(struct Queue* queue) {
    return queue->front == queue->rear;
}

// Enqueue an item to the queue
void enqueue(struct Queue* queue, struct BinaryTreeNode* item) {
    if (isFull(queue)) {
        fprintf(stderr, "Queue is full, can't continue the program.\n");
        exit(-1);
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
}

// Dequeue an item from the queue
// Note that the front pointer is pointing to the previous item that was dequeued previously
struct BinaryTreeNode* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }
    queue->front = (queue->front + 1) % queue->capacity;
    return queue->array[queue->front];
}

// Level traversal
void levelTraverse(struct BinaryTreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue with the capacity of 100
    struct Queue* queue = createQueue(100);

    // Enqueue the root node
    enqueue(queue, root);

    // Traverse the tree level by level
    while (!isEmpty(queue)) {
        struct BinaryTreeNode* node = dequeue(queue);
        printf("%c ", node->data);

        // Enqueue the left child
        if (node->left != NULL) {
            enqueue(queue, node->left);
        }

        // Enqueue the right child
        if (node->right != NULL) {
            enqueue(queue, node->right);
        }
    }

    // Don't forget to free the queue after using it >_<
    free(queue);
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

    // Level traversal
    printf("Level traversal : ");
    levelTraverse(root);

    // Free the entire tree
    freeTree(root);

    return 0;
}

// Level traversal : A B C D E F G