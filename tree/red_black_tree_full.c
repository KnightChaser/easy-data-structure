/**
 * @file red_black_tree_full.c
 * @brief A red-black tree implementation with C language (insertion and deletion)
 */

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
void redBlackTreeDelete(RedBlackTree *redBlackTree, int key);
void redBlackTreeDeleteFixup(RedBlackTree *redBlackTree, RedBlackTreeNode *targetNode);
void redBlackTransplant(RedBlackTree *redBlackTree, RedBlackTreeNode *targetToBeReplaced, RedBlackTreeNode *replacement);
RedBlackTreeNode* treeMinimum(RedBlackTreeNode *node, RedBlackTreeNode *nil);
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

// Function to delete a node from the tree
void redBlackTreeDelete(RedBlackTree *redBlackTree, int key) {
    RedBlackTreeNode *targetNode = redBlackTree->root;
    RedBlackTreeNode *replacementNode;
    RedBlackTreeNode *fixupNode;

    // Find the node to delete
    while (targetNode != redBlackTree->nil) {
        if (key == targetNode->data) {
            break;
        } else if (key < targetNode->data) {
            targetNode = targetNode->left;
        } else {
            targetNode = targetNode->right;
        }
    }

    if (targetNode == redBlackTree->nil) {
        // Key not found
        fprintf(stderr, "The key %d does not exist in the tree\n", key);
        return;
    }

    replacementNode = targetNode;
    Color originalColor = replacementNode->color;

    if (targetNode->left == redBlackTree->nil) {
        fixupNode = targetNode->right;
        redBlackTransplant(redBlackTree, targetNode, targetNode->right);
    } else if (targetNode->right == redBlackTree->nil) {
        fixupNode = targetNode->left;
        redBlackTransplant(redBlackTree, targetNode, targetNode->left);
    } else {
        replacementNode = treeMinimum(targetNode->right, redBlackTree->nil);
        originalColor = replacementNode->color;
        fixupNode = replacementNode->right;
        if (replacementNode->parent == targetNode) {
            fixupNode->parent = replacementNode;
        } else {
            redBlackTransplant(redBlackTree, replacementNode, replacementNode->right);
            replacementNode->right = targetNode->right;
            replacementNode->right->parent = replacementNode;
        }
        redBlackTransplant(redBlackTree, targetNode, replacementNode);
        replacementNode->left = targetNode->left;
        replacementNode->left->parent = replacementNode;
        replacementNode->color = targetNode->color;
    }

    if (originalColor == BLACK) {
        redBlackTreeDeleteFixup(redBlackTree, fixupNode);
    }

    free(targetNode);
}

// Helper function to replace one subtree as a child of its parent with another subtree
void redBlackTransplant(RedBlackTree *redBlackTree, RedBlackTreeNode *targetToBeReplaced, RedBlackTreeNode *replacement) {
    if (targetToBeReplaced->parent == redBlackTree->nil) {
        redBlackTree->root = replacement;
    } else if (targetToBeReplaced == targetToBeReplaced->parent->left) {
        // If the target node is a left child, set the replacement as the new left child
        targetToBeReplaced->parent->left = replacement;
    } else {
        // If the target node is a right child, set the replacement as the new right child
        targetToBeReplaced->parent->right = replacement;
    }
    replacement->parent = targetToBeReplaced->parent;
}

// Helper function to find the node with the minimum key in a subtree (leftmost node)
RedBlackTreeNode* treeMinimum(RedBlackTreeNode *node, RedBlackTreeNode *nil) {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

// Function to fix up the tree after deletion to maintain Red-Black properties
void redBlackTreeDeleteFixup(RedBlackTree *redBlackTree, RedBlackTreeNode *targetNode) {
    RedBlackTreeNode *siblingNode;

    // if the deleted node is red, we don't need to fix anything because the number of black nodes on paths is the same
    while (targetNode != redBlackTree->root && targetNode->color == BLACK) {

        if (targetNode == targetNode->parent->left) {
            siblingNode = targetNode->parent->right;

            // Case 1: targetNode's sibling siblingNode is red
            if (siblingNode->color == RED) {
                siblingNode->color = BLACK;
                targetNode->parent->color = RED;
                leftRotate(redBlackTree, targetNode->parent);
                siblingNode = targetNode->parent->right;
            }

            // Case 2: targetNode's sibling siblingNode is black and both of siblingNode's children are black
            if (siblingNode->left->color == BLACK && siblingNode->right->color == BLACK) {
                siblingNode->color = RED;
                targetNode = targetNode->parent;
            } else {
                // Case 3: targetNode's sibling siblingNode is black, siblingNode's left child is red, and siblingNode's right child is black
                if (siblingNode->right->color == BLACK) {
                    siblingNode->left->color = BLACK;
                    siblingNode->color = RED;
                    rightRotate(redBlackTree, siblingNode);
                    siblingNode = targetNode->parent->right;
                }

                // Case 4: targetNode's sibling siblingNode is black and siblingNode's right child is red
                siblingNode->color = targetNode->parent->color;
                targetNode->parent->color = BLACK;
                siblingNode->right->color = BLACK;
                leftRotate(redBlackTree, targetNode->parent);
                targetNode = redBlackTree->root;
            }
        } else {
            siblingNode = targetNode->parent->left;

            // Case 1: targetNode's sibling siblingNode is red
            if (siblingNode->color == RED) {
                siblingNode->color = BLACK;
                targetNode->parent->color = RED;
                rightRotate(redBlackTree, targetNode->parent);
                siblingNode = targetNode->parent->left;
            }

            // Case 2: targetNode's sibling siblingNode is black and both of siblingNode's children are black
            if (siblingNode->right->color == BLACK && siblingNode->left->color == BLACK) {
                siblingNode->color = RED;
                targetNode = targetNode->parent;
            } else {
                // Case 3: targetNode's sibling siblingNode is black, siblingNode's right child is red, and siblingNode's left child is black
                if (siblingNode->left->color == BLACK) {
                    siblingNode->right->color = BLACK;
                    siblingNode->color = RED;
                    leftRotate(redBlackTree, siblingNode);
                    siblingNode = targetNode->parent->left;
                }

                // Case 4: targetNode's sibling siblingNode is black and siblingNode's left child is red
                siblingNode->color = targetNode->parent->color;
                targetNode->parent->color = BLACK;
                siblingNode->left->color = BLACK;
                rightRotate(redBlackTree, targetNode->parent);
                targetNode = redBlackTree->root;
            }
        }
    }
    targetNode->color = BLACK;
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
    RedBlackTree *redBlackTree = createRedBlackTree();

    redBlackTreeInsert(redBlackTree, 10);
    redBlackTreeInsert(redBlackTree, 20);
    redBlackTreeInsert(redBlackTree, 30);
    redBlackTreeInsert(redBlackTree, 40);
    redBlackTreeInsert(redBlackTree, 50);
    redBlackTreeInsert(redBlackTree, 25);

    printf("In-order traversal of the red-black tree after insertions: ");
    printRedBlackTreeInOrder(redBlackTree->root, redBlackTree->nil);
    printf("\n");

    redBlackTreeDelete(redBlackTree, 20);
    redBlackTreeDelete(redBlackTree, 30);

    printf("In-order traversal of the red-black tree after deletions: ");
    printRedBlackTreeInOrder(redBlackTree->root, redBlackTree->nil);
    printf("\n");

    return 0;
}
