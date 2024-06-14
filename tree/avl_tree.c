/**
 * @file avl_tree.c
 * @brief AVL(Adelson-Velsky and Landis) tree implementation in C language
 *        AVL tree is a self-balancing binary search tree in which the difference of heights of left and right subtrees of any node is less than or equal to one.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#undef max                              // Invalidating the previous definition of max macro(stdlib.h)
#define max(a, b) ((a > b) ? a : b)

typedef struct AVLTreeNode {
    int data;
    int height;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
} AVLTreeNode;  

// A utility function to calculate the height of the tree
int getAVLTreeHeight(AVLTreeNode *avlTreeNode) {
    if (avlTreeNode == NULL)
        return 0;
    return avlTreeNode->height;
}

// A utility function to create a new AVL tree node
AVLTreeNode* createAVLTree(int data) {
    AVLTreeNode *newNode = (AVLTreeNode *)calloc(1, sizeof(AVLTreeNode));
    newNode->data   = data;
    newNode->height = 1;
    newNode->left   = NULL;
    newNode->right  = NULL;

    // Don't forget to free the memory allocated to this node >_<
    return newNode;
}

// Right rotation
// In case of left-left imbalance, we perform right rotation
AVLTreeNode* rightRotate(AVLTreeNode *avlTreeNode) {
    AVLTreeNode *y  = avlTreeNode->left;
    AVLTreeNode *T2 = y->right;

    // Rotation
    y->right = avlTreeNode;
    avlTreeNode->left = T2;

    // Update heights
    avlTreeNode->height = 1 + max(getAVLTreeHeight(avlTreeNode->left), getAVLTreeHeight(avlTreeNode->right));
    y->height           = 1 + max(getAVLTreeHeight(y->left), getAVLTreeHeight(y->right));

    return y;
}

// Left rotation
// In case of right-right imbalance, we perform left rotation
AVLTreeNode* leftRotate(AVLTreeNode *avlTreeNode) {
    AVLTreeNode *y  = avlTreeNode->right;
    AVLTreeNode *T2 = y->left;

    // Rotation
    y->left = avlTreeNode;
    avlTreeNode->right = T2;

    // Update heights
    avlTreeNode->height = 1 + max(getAVLTreeHeight(avlTreeNode->left), getAVLTreeHeight(avlTreeNode->right));
    y->height           = 1 + max(getAVLTreeHeight(y->left), getAVLTreeHeight(y->right));

    return y;
}

// Get the balance factor of a node
int getBalanceFactor(AVLTreeNode *avlTreeNode) {
    if (avlTreeNode == NULL) {
        fprintf(stderr, "Error: NULL node passed to getBalanceFactor()\n");
        return 0;
    }

    // height of left subtree - height of right subtree
    // if the value is greater than 1,      the tree is left heavy
    // if the value is less than -1,        the tree is right heavy
    // if the value is between -1 and 1,    the tree is balanced
    return getAVLTreeHeight(avlTreeNode->left) - getAVLTreeHeight(avlTreeNode->right);
}

// Insert a new node in the AVL tree considering the balance factor
AVLTreeNode* insert(AVLTreeNode* avlTreeNode, int data) {
    if (avlTreeNode == NULL) {
        return createAVLTree(data);
    }

    // Perform the normal binary search tree insertion
    if (data < avlTreeNode->data)
        avlTreeNode->left = insert(avlTreeNode->left, data);
    else if (data > avlTreeNode->data)
        avlTreeNode->right = insert(avlTreeNode->right, data);
    else {
        fprintf(stderr, "Error: Duplicate data %d not allowed in AVL tree\n", data);
        return avlTreeNode;
    }

    // Update the height of this ancestor node
    avlTreeNode->height = 1 + max(getAVLTreeHeight(avlTreeNode->left), getAVLTreeHeight(avlTreeNode->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalanceFactor(avlTreeNode);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case (This case occurs when the balance factor is greater than 1 and the data is inserted in the left subtree of the left child)
    if (balance > 1 && data < avlTreeNode->left->data)
        return rightRotate(avlTreeNode);

    // Right Right Case (This case occurs when the balance factor is less than -1 and the data is inserted in the right subtree of the right child)
    if (balance < -1 && data > avlTreeNode->right->data)
        return leftRotate(avlTreeNode);

    // Left Right Case (This case occurs when the balance factor is greater than 1 and the data is inserted in the right subtree of the left child)
    if (balance > 1 && data > avlTreeNode->left->data) {
        avlTreeNode->left = leftRotate(avlTreeNode->left);
        return rightRotate(avlTreeNode);
    }

    // Right Left Case (This case occurs when the balance factor is less than -1 and the data is inserted in the left subtree of the right child)
    if (balance < -1 && data < avlTreeNode->right->data) {
        avlTreeNode->right = rightRotate(avlTreeNode->right);
        return leftRotate(avlTreeNode);
    }

    return avlTreeNode;
}

// An inorder traversal of the AVL tree
void inorderTraversal(AVLTreeNode *avlTreeNode) {
    if (avlTreeNode == NULL)
        return;

    inorderTraversal(avlTreeNode->left);
    printf("%d ", avlTreeNode->data);
    inorderTraversal(avlTreeNode->right);
}

int main(void) {
    AVLTreeNode *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    // The AVL tree after insertion of the above nodes will be:
    //                   30
    //             -------------
    //             |           |
    //            20          40
    //          -------      -------
    //          |     |      |     |
    //         10    25     NULL  50    

    printf("Inorder traversal of the AVL tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

// Inorder traversal of the AVL tree: 10 20 25 30 40 50 