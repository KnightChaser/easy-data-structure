/**
 * @file binary_search_tree_insertion_deletion.cpp
 * @brief Binary Search Tree Insertion and Deletion demonstration via C++.
 *        Because the tree is for searching, all values in the left subtree of a node are less than the node's value,
 *        and all values in the right subtree are greater than the node's value.
 */

#include <iostream>
#include <memory>

// Binary search tree class structure
template <typename BinarySearchTreeType>
class BinarySearchTree {
private:
    // Node structure
    struct BinarySearchTreeNode {
        BinarySearchTreeType data;
        std::shared_ptr<BinarySearchTreeNode> left;
        std::shared_ptr<BinarySearchTreeNode> right;
    };

    // Root node
    std::shared_ptr<BinarySearchTreeNode> root;

    // Find the minimum node
    std::shared_ptr<BinarySearchTreeNode> findMinimumValueNode(std::shared_ptr<BinarySearchTreeNode> node);

public:
    // Constructor (create a root node with a value)
    BinarySearchTree(BinarySearchTreeType root_data) {
        root = std::make_shared<BinarySearchTreeNode>();
        root->data = root_data;
        root->left = nullptr;
        root->right = nullptr;
    }

    // Methods
    bool isExist(BinarySearchTreeType data);   // Check if a node exists
    void insert(BinarySearchTreeType data);    // Insert a new node
    void remove(BinarySearchTreeType data);    // Remove a node
    void print();                              // Print the tree

    // Helper functions
    std::shared_ptr<BinarySearchTreeNode> insertNode(std::shared_ptr<BinarySearchTreeNode> node, BinarySearchTreeType data);
    std::shared_ptr<BinarySearchTreeNode> removeNode(std::shared_ptr<BinarySearchTreeNode> node, BinarySearchTreeType data);
    void printInOrder(std::shared_ptr<BinarySearchTreeNode> node);
};

// Check if a node exists
template <typename BinarySearchTreeType>
bool BinarySearchTree<BinarySearchTreeType>::isExist(BinarySearchTreeType data) {
    std::shared_ptr<BinarySearchTreeNode> current = root;
    while (current != nullptr) {
        if (current->data == data)
            return true;
        else if (data < current->data)
            // Meaning the data is in the left subtree
            current = current->left;
        else
            // Meaning the data is in the right subtree
            current = current->right;
    }
    return false;
}

// Find the minimum node
// Due to the order of the binary search tree, the minimum node is the leftmost node
template <typename BinarySearchTreeType>
std::shared_ptr<typename BinarySearchTree<BinarySearchTreeType>::BinarySearchTreeNode> 
BinarySearchTree<BinarySearchTreeType>::findMinimumValueNode(std::shared_ptr<BinarySearchTreeNode> node) {
    std::shared_ptr<BinarySearchTreeNode> current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Insert a new node
template <typename BinarySearchTreeType>
void BinarySearchTree<BinarySearchTreeType>::insert(BinarySearchTreeType data) {
    root = insertNode(root, data);
}

template <typename BinarySearchTreeType>
std::shared_ptr<typename BinarySearchTree<BinarySearchTreeType>::BinarySearchTreeNode> 
BinarySearchTree<BinarySearchTreeType>::insertNode(std::shared_ptr<BinarySearchTreeNode> node, BinarySearchTreeType data) {

    // If the tree is empty, meaning the data can be inserted because it's unique
    if (node == nullptr) {
        node = std::make_shared<BinarySearchTreeNode>();
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    if (data < node->data)
        // Insert to the left subtree
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        // Insert to the right subtree
        node->right = insertNode(node->right, data);

    return node;
}

// Remove a node
template <typename BinarySearchTreeType>
void BinarySearchTree<BinarySearchTreeType>::remove(BinarySearchTreeType data) {
    root = removeNode(root, data);
}

template <typename BinarySearchTreeType>
std::shared_ptr<typename BinarySearchTree<BinarySearchTreeType>::BinarySearchTreeNode> 
BinarySearchTree<BinarySearchTreeType>::removeNode(std::shared_ptr<BinarySearchTreeNode> node, BinarySearchTreeType data) {
    if (node == nullptr)
        return node;

    // Find the node to be removed
    if (data < node->data)
        node->left = removeNode(node->left, data);
    else if (data > node->data)
        node->right = removeNode(node->right, data);
    else {
        // Found the node to be removed
        // Case 1: Node has no child
        if (node->left == nullptr && node->right == nullptr) {
            node = nullptr;
        }

        // Case 2: Node has one child
        else if (node->left == nullptr && node->right != nullptr) {
            return node->right;
        } else if (node->right == nullptr && node->left != nullptr) {
            return node->left;
        }

        // Case 3: Node has two children
        else {
            std::shared_ptr<BinarySearchTreeNode> temp = findMinimumValueNode(node->right);
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
    }

    return node;
}

// Print the tree in an inorder (and recursive) way
template <typename BinarySearchTreeType>
void BinarySearchTree<BinarySearchTreeType>::print() {
    printInOrder(root);
    std::cout << std::endl;
}

template <typename BinarySearchTreeType>
void BinarySearchTree<BinarySearchTreeType>::printInOrder(std::shared_ptr<BinarySearchTreeNode> node) {
    if (node == nullptr)
        return;

    printInOrder(node->left);
    std::cout << node->data << " ";
    printInOrder(node->right);
}

// Main function
int main(void) {
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

    BinarySearchTree<int> tree(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);

    std::cout << "Binary Search Tree                  : ";
    tree.print();

    tree.remove(10);
    std::cout << "Binary Search Tree after removing 10: ";
    tree.print();

    tree.remove(20);
    std::cout << "Binary Search Tree after removing 20: ";
    tree.print();

    tree.remove(30);
    std::cout << "Binary Search Tree after removing 30: ";
    tree.print();

    return 0;
}

// Binary Search Tree                  : 10 20 30 40 50 60 
// Binary Search Tree after removing 10: 20 30 40 50 60
// Binary Search Tree after removing 20: 30 40 50 60
// Binary Search Tree after removing 30: 40 50 60