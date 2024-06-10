/**
 * @file binary_tree_insertion_deletion.c
 * @brief A binary tree implementation with insertion and deletion operations.
 *        Suppose all values in the given binary tree are unique and aligned from left to right.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Binary tree node structure
typedef int binaryTreeElement;
typedef struct BinaryTreeNode {
    binaryTreeElement data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

// Create a new node
BinaryTreeNode* createNewBinaryTreeNode(binaryTreeElement data) {
    BinaryTreeNode *newNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Search the given data in the given binary search tree recursively
bool searchBinaryTreeNodeRecursive(BinaryTreeNode *root, binaryTreeElement data) {
    // If the tree is empty, return false
    if (root == NULL)
        return false;

    // If the given data is found, return true
    if (root->data == data)
        return true;

    // Search the left subtree if the given data is less than the root's data
    // Search the right subtree if the given data is greater than the root's data
    if (data < root->data)
        return searchBinaryTreeNodeRecursive(root->left, data);
    else
        return searchBinaryTreeNodeRecursive(root->right, data);
}

// Search the given data in the given binary search tree iteratively
bool searchBinaryTreeNodeIterative(BinaryTreeNode* root, binaryTreeElement data) {
    while(root != NULL) {
        // If the given data is found, return true
        if (root->data == data)
            return true;

        // Search the left subtree if the given data is less than the root's data
        // Search the right subtree if the given data is greater than the root's data
        if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }

    // If the given data is not found, return false
    return false;
}

// Find the minimum value node in the given binary search tree
BinaryTreeNode* findMinimumValueNode(BinaryTreeNode *root) {
    BinaryTreeNode *current = root;

    // The minimum value node is the leftmost node
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Insert a new node to the given binary search tree recursively
BinaryTreeNode* insertBinaryTreeNodeRecursive(BinaryTreeNode *root, binaryTreeElement data) {

    // If the tree is empty, return a new node
    if (root == NULL)
        return createNewBinaryTreeNode(data);

    // Insert the new node to the left if the given data is less than the root's data
    // Insert the new node to the right if the given data is greater than the root's data
    if (data < root->data)
        root->left = insertBinaryTreeNodeRecursive(root->left, data);
    else if (data > root->data)
        root->right = insertBinaryTreeNodeRecursive(root->right, data);
    else
        return NULL;

    return root;
}

// Insert a new node to the given binary search tree iteratively
BinaryTreeNode* insertBinaryTreeNodeIterative(BinaryTreeNode *root, binaryTreeElement data) {
    // Create nodes to traverse the tree
    BinaryTreeNode *newNode     = createNewBinaryTreeNode(data);
    BinaryTreeNode *currentNode = root;
    BinaryTreeNode *parentNode  = NULL;

    // Traverse the tree to
    while (currentNode != NULL) {
        parentNode = currentNode;
        if (data < currentNode->data)
            // If the data want to insert is less than the current node's data, move to the left subtree
            currentNode = currentNode->left;
        else if (data > currentNode->data)
            // If the data want to insert is greater than the current node's data, move to the right subtree
            currentNode = currentNode->right;
        else
            // If the given data is already in the tree, return the root (we can't insert duplicates)
            return NULL;
    }

    // If there is no node with the desired data, insert the new node
    if (parentNode == NULL)
        return newNode;
    else if (data < parentNode->data)
        parentNode->left = newNode;
    else
        parentNode->right = newNode;

    return root;
}

// Delete the node with the given data from the given binary search tree recursively
BinaryTreeNode* deleteBinaryTreeNodeRecursive(BinaryTreeNode *root, binaryTreeElement data) {
    // If the tree is empty, return NULL
    if (root == NULL)
        return root;

    // Search for the node to be deleted
    if (data < root->data) {
        // Move to the left subtree
        root->left = deleteBinaryTreeNodeRecursive(root->left, data);
    } else if (data > root->data) {
        // Move to the right subtree
        root->right = deleteBinaryTreeNodeRecursive(root->right, data);
    } else {
        // Node with the matching data is found

        // Case 1: Node with no children (leaf node) => free the node itself right away
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: Node with one child => Copy the child to the node and free the child (thus, the node is deleted)
        else if (root->left == NULL) {
            BinaryTreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BinaryTreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node with two children => Replace the data of the node with the in-order successor's data
        // Then, delete the in-order successor node
        else {
            // Find the minimum value node in the right subtree(nearest successor)
            BinaryTreeNode *temp = findMinimumValueNode(root->right);
            // Replace the data of the node to be deleted with the in-order successor's data
            root->data = temp->data;
            // Recursively delete the in-order successor
            root->right = deleteBinaryTreeNodeRecursive(root->right, temp->data);
        }
    }
    return root;
}

// Delete the node with the given data from the given binary search tree iteratively
BinaryTreeNode* deleteBinaryTreeNodeIterative(BinaryTreeNode* root, binaryTreeElement data) {
    BinaryTreeNode* parentNode = NULL;      // Parent node of the node to be deleted
    BinaryTreeNode* currentNode = root;     // Node to be deleted
    
    // Find the node to be deleted
    while (currentNode != NULL && currentNode->data != data) {
        parentNode = currentNode;
        if (data < currentNode->data)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
    }

    // If the node to be deleted is not found, return the root
    if (currentNode == NULL)
        return root;

    // Case 1: Node with no children (leaf node)
    // Then, free the node itself immediately
    if (currentNode->left == NULL && currentNode->right == NULL) {
        if (currentNode != root) {
            // If the node to be deleted is not the root, set the parent's child to NULL
            if (parentNode->left == currentNode)
                parentNode->left = NULL;
            else
                parentNode->right = NULL;
        } else
            root = NULL;
        free(currentNode);
    }

    // Case 2: Node with one child
    // Copy the child to the node and free the child (thus, the node is deleted)
    else if (currentNode->left == NULL && currentNode->right != NULL) {
        // There is only a right child
        if (currentNode != root) {
            // If the node to be deleted is not the root, set the parent's child(current node) to the current node's right child
            if (parentNode->left == currentNode)
                parentNode->left = currentNode->right;
            else
                parentNode->right = currentNode->right;
        } else
            root = currentNode->right;
        free(currentNode);
    } else if (currentNode->left != NULL && currentNode->right == NULL) {
        // There is only a left child
        if (currentNode != root) {
            // If the node to be deleted is not the root, set the parent's child(current node) to the current node's left child
            if (parentNode->left == currentNode)
                parentNode->left = currentNode->left;
            else
                parentNode->right = currentNode->left;
        } else
            root = currentNode->left;
        free(currentNode);
    }

    // Case 3: Node with two children
    // Replace the data of the node with the in-order successor's data
    // Then, delete the in-order successor node
    else {
        // Find the minimum value node in the right subtree(nearest successor)
        BinaryTreeNode* temp = findMinimumValueNode(currentNode->right);

        // Replace the data of the node to be deleted with the in-order successor's data
        currentNode->data = temp->data;

        // Iteratively delete the in-order successor
        while (currentNode->right != temp)
            currentNode = currentNode->right;

        // If the in-order successor has a right child, set the parent's right child to the in-order successor's right child
        // By doing this, the between the in-order successor and its right child is removed
        if (temp->right != NULL)
            currentNode->right = temp->right;
        else
            currentNode->right = NULL;

        free(temp);
    }

    return root;
}

// Inorder traversal of the given binary search tree
void inorderTraversalBinaryTree(BinaryTreeNode *root) {
    if (root != NULL) {
        inorderTraversalBinaryTree(root->left);
        printf("%d ", root->data);
        inorderTraversalBinaryTree(root->right);
    }
}

// Main function to test the binary search tree operations
int main(void) {
    BinaryTreeNode* root = NULL;

    // Tree diagram
    //                30
    //         ----------------
    //         |              |
    //        20              40
    //      -----            -----
    //      |   |            |   |
    //     10  NULL         NULL 50
    //                          -----
    //                          |   |
    //                         NULL 60

    // Insert nodes
    root = insertBinaryTreeNodeRecursive(root, 30);
    root = insertBinaryTreeNodeRecursive(root, 20);
    root = insertBinaryTreeNodeRecursive(root, 10);
    root = insertBinaryTreeNodeIterative(root, 40);
    root = insertBinaryTreeNodeIterative(root, 50);
    root = insertBinaryTreeNodeIterative(root, 60);
    printf("Original binary tree          : ");
    inorderTraversalBinaryTree(root); // Output: 10 20 30 40 50 60
    printf("\n");

    // Search for 20 in the binary tree (recursively)
    printf("Search for 20 in the binary tree (recursively): %s\n", searchBinaryTreeNodeRecursive(root, 20) ? "Found" : "Not found");

    // Search for 41 in the binary tree (iteratively)
    printf("Search for 41 in the binary tree (iteratively): %s\n", searchBinaryTreeNodeIterative(root, 41) ? "Found" : "Not found");

    // Remove 10 from the binary tree
    root = deleteBinaryTreeNodeRecursive(root, 10);
    printf("Remove 10 from the binary tree: ");
    inorderTraversalBinaryTree(root); // Output: 20 30 40 50 60
    printf("\n");

    // Remove 20 from the binary tree
    root = deleteBinaryTreeNodeRecursive(root, 20);
    printf("Remove 20 from the binary tree: ");
    inorderTraversalBinaryTree(root); // Output: 30 40 50 60
    printf("\n");

    // Remove 30 from the binary tree
    root = deleteBinaryTreeNodeIterative(root, 30);
    printf("Remove 30 from the binary tree: ");
    inorderTraversalBinaryTree(root); // Output: 40 50 60
    printf("\n");

    return 0;
}

// Original binary tree          : 10 20 30 40 50 60 
// Search for 20 in the binary tree (recursively): Found
// Search for 41 in the binary tree (iteratively): Not found
// Remove 10 from the binary tree: 20 30 40 50 60
// Remove 20 from the binary tree: 30 40 50 60
// Remove 30 from the binary tree: 40 50 60