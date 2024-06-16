/**
 * @file red_black_tree_insertion_only.c
 * @brief A red-black tree implementation with C language (insertion only for simplicity)
 */
//

#include <stdio.h>
#include <stdlib.h>

// Enum for color of node
typedef enum { RED, BLACK } Color;

// Struct for node
typedef struct RedBlackTreeNode {
    int data;
    Color color;
    struct RedBlackTreeNode *left;
    struct RedBlackTreeNode *right;
    struct RedBlackTreeNode *parent;      // maintain parent node for easy rotation
} RedBlackTreeNode;

// Struct for red-black tree
// (The tree itself will have a pointer to the root node and a pointer to a sentinel node representing NIL (null leaves))
typedef struct RedBlackTree {
    RedBlackTreeNode *root;
    RedBlackTreeNode *nil;
} RedBlackTree;

// List of functions
RedBlackTreeNode *createRedBlackTreeNode(int data, Color nodeColor, RedBlackTreeNode *nil);
RedBlackTree *createRedBlackTree();
void leftRotate(RedBlackTree *redBlackTree, RedBlackTreeNode *x);
void rightRotate(RedBlackTree *redBlackTree, RedBlackTreeNode *y);
void redBlackTreeInsert(RedBlackTree *redBlackTree, int key);
void redBlackTreeInsertFixup(RedBlackTree *redBlackTree, RedBlackTreeNode *newNode);
void printRedBlackTreeInOrder(RedBlackTreeNode *node, RedBlackTreeNode *nil);

// Function to initialize a red-black tree node
RedBlackTreeNode *createRedBlackTreeNode(int data, Color nodeColor, RedBlackTreeNode *nil) {
    RedBlackTreeNode *newNode = (RedBlackTreeNode *)calloc(1, sizeof(RedBlackTreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->color = nodeColor;
    newNode->left = nil;
    newNode->right = nil;
    newNode->parent = nil;
    return newNode;
}

// Function to initialize a red-black tree
RedBlackTree *createRedBlackTree() {
    RedBlackTree *newTree = (RedBlackTree *)calloc(1, sizeof(RedBlackTree));
    if (newTree == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newTree->nil = createRedBlackTreeNode(0, BLACK, NULL);
    newTree->root = newTree->nil;
    return newTree;
}


// Function to left rotate a node in the given tree
// (It's the mirror of rightRotate)
void leftRotate(RedBlackTree *redBlackTree, RedBlackTreeNode *x) {
    RedBlackTreeNode *y = x->right;
    x->right = y->left;

    if (y->left != redBlackTree->nil)
        // If y has a left child, set that child's parent to x
        y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == redBlackTree->nil) {
        // If x is the root, set y as the new root
        redBlackTree->root = y;
    } else if (x == x->parent->left) {
        // If x is a left child of its parent, set y as the new left child
        x->parent->left = y;
    } else {
        // If x is a right child of its parent, set y as the new right child
        x->parent->right = y;
    }

    // Finally, set x as the left child of y
    y->left = x;
    x->parent = y;
}

// Function to right rotate a node in the given tree
// (It's the mirror of leftRotate)
void rightRotate(RedBlackTree *redBlackTree, RedBlackTreeNode *y) {
    RedBlackTreeNode *x = y->left;
    y->left = x->right;

    if (x->right != redBlackTree->nil)
        // If x has a right child, set that child's parent to y
        x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == redBlackTree->nil) {
        // If y is the root, set x as the new root
        redBlackTree->root = x;
    } else if (y == y->parent->left) {
        // If y is a left child of its parent, set x as the new left child
        y->parent->left = x;
    } else {
        // If y is a right child of its parent, set x as the new right child
        y->parent->right = x;
    }

    // Finally, set y as the right child of x
    x->right = y;
    y->parent = x;
}

// Function to insert a node in the given tree
// (It's the same as the binary search tree insertion with some additional steps to maintain the red-black tree properties)
void redBlackTreeInsert(RedBlackTree *redBlackTree, int key) {
    // New leaf node is created red at first
    RedBlackTreeNode *newNode = createRedBlackTreeNode(key, RED, redBlackTree->nil);
    RedBlackTreeNode *currentNode = redBlackTree->root;
    RedBlackTreeNode *parentNode = redBlackTree->nil;

    // Find the parent of the new node in the binary search tree
    while (currentNode != redBlackTree->nil) {
        parentNode = currentNode;
        if (key < currentNode->data) {
            currentNode = currentNode->left;
        } else if (key > currentNode->data){
            currentNode = currentNode->right;
        } else {
            // If the key already exists, return
            free(newNode);
            fprintf(stderr, "The key %d already exists in the tree\n", key);
            return;
        }
    }

    // Set the parent of the new node
    newNode->parent = parentNode;

    // If the parent is NIL, it means the tree was empty so the new node is the root
    if (parentNode == redBlackTree->nil) {
        redBlackTree->root = newNode;
    } else if (key < parentNode->data) {
        // If the new node is less than the parent, set it as the left child
        parentNode->left = newNode;
    } else {
        // If the new node is greater than the parent, set it as the right child
        parentNode->right = newNode;
    }

    // Fix the red-black tree properties
    redBlackTreeInsertFixup(redBlackTree, newNode);
}

// Function to fix the red-black tree properties after insertion
void redBlackTreeInsertFixup(RedBlackTree *redBlackTree, RedBlackTreeNode *newNode) {
    RedBlackTreeNode *parentNode;           // newNode->parent
    RedBlackTreeNode *grandParentNode;      // newNode->parent->parent
    RedBlackTreeNode *uncleNode;            // newNode->parent->parent->left or newNode->parent->parent->right

    while (newNode->parent->color == RED) {
        // If the parent node's color is red, it indicates that the tree properties are violated
        // because the newNode is red thus there are two consecutive red nodes
        parentNode = newNode->parent;
        grandParentNode = parentNode->parent;

        if (parentNode == grandParentNode->left) {
            // If the parent is the left child of the grandparent
            uncleNode = grandParentNode->right;

            if (uncleNode->color == RED) {
                // Case 1: The uncle is red (recoloring required)
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandParentNode->color = RED;
                newNode = grandParentNode;      // Move up the tree to fix the properties
            } else {
                // Case 2: The uncle is black (restructuring required)
                //         and the new node is the right child of the parent (left-right case)
                if (newNode == parentNode->right) {
                    // First, left rotate the parent
                    newNode = parentNode;
                    leftRotate(redBlackTree, newNode);
                    // Now, the new node is the left child of the parent
                }

                // Case 3: The uncle is black (restructuring required)
                //         and the new node is the left child of the parent (left-left case)
                parentNode = newNode->parent;
                grandParentNode = parentNode->parent;
                parentNode->color = BLACK;
                grandParentNode->color = RED;
                rightRotate(redBlackTree, grandParentNode);
            }
        } else {
            // If the parent is the right child of the grandparnet
            uncleNode = grandParentNode->left;

            if (uncleNode->color == RED) {
                // Case 1: The uncle is red (recoloring required)
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandParentNode->color = RED;
                newNode = grandParentNode;      // Move up the tree to fix the properties
            } else {
                // Case 2: The uncle is black (restructuring required)
                //         and the new node is the left child of the parent (right-left case)
                if (newNode == parentNode->left) {
                    // First, right rotate the parent
                    newNode = parentNode;
                    rightRotate(redBlackTree, newNode);
                    // Now, the new node is the right child of the parent
                }

                // Case 3: The uncle is black (restructuring required)
                //         and the new node is the right child of the parent (right-right case)
                parentNode = newNode->parent;
                grandParentNode = parentNode->parent;
                parentNode->color = BLACK;
                grandParentNode->color = RED;
                leftRotate(redBlackTree, grandParentNode);
            }
        }
    }

    // The root should always be black to satisfy the red-black tree properties
    redBlackTree->root->color = BLACK;
}

// Function to print the red-black tree in-order, without NIL nodes
void printRedBlackTreeInOrder(RedBlackTreeNode *node, RedBlackTreeNode *nil) {
    if (node != nil) {
        printRedBlackTreeInOrder(node->left, nil);
        printf("%d ", node->data);
        printRedBlackTreeInOrder(node->right, nil);
    }
}

int main(void) {
    RedBlackTree *redBlackTreee = createRedBlackTree();

    redBlackTreeInsert(redBlackTreee, 10);
    redBlackTreeInsert(redBlackTreee, 20);
    redBlackTreeInsert(redBlackTreee, 30);
    redBlackTreeInsert(redBlackTreee, 40);
    redBlackTreeInsert(redBlackTreee, 50);
    redBlackTreeInsert(redBlackTreee, 25);

    printf("In-order traversal of the red-black tree: ");
    printRedBlackTreeInOrder(redBlackTreee->root, redBlackTreee->nil);

    return 0;
}