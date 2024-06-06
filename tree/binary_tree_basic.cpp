/**
 * @file binary_tree_basic.cpp
 * @brief A basic binary tree implementation with using struct and pointers.
 *        CPP version of tree/binary_tree_basic.c
 */
//

#include <iostream>
#include <stdexcept>

template <typename BinaryTreeElementType>
class BinaryTree {
private:
    struct BinaryTreeNode {
        BinaryTreeElementType data;
        BinaryTreeNode* left;
        BinaryTreeNode* right;
    };
public:
    BinaryTreeNode* root;

    // Constructor, create a root node
    BinaryTree(BinaryTreeElementType data) {
        this->root = new BinaryTreeNode();
        this->root->data = data;
        this->root->left = nullptr;
        this->root->right = nullptr;
        std::cout << "Root node is created." << std::endl;
    };

    // Destructor, it will free all nodes iteratively
    ~BinaryTree() {
        this->freeNode(this->root);
        std::cout << "All nodes are freed(by destructor)." << std::endl;
    };

    // methods
    bool isThisAppendable(BinaryTreeNode* node, bool isLeft);
    void createLeftChild(BinaryTreeNode* parent, BinaryTreeElementType data);
    void createRightChild(BinaryTreeNode* parent, BinaryTreeElementType data);
    void printAllNodes();
    void printNode(BinaryTreeNode* node);
    void freeAllNodes();
    void freeNode(BinaryTreeNode* node);
};

// Check if the node is appendable
template <typename BinaryTreeElementType>
bool BinaryTree<BinaryTreeElementType>::isThisAppendable(BinaryTreeNode* node, bool isLeft) {
    if (isLeft) {
        return node->left == nullptr;
    } else {
        return node->right == nullptr;
    }
}

// Create a left child node
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::createLeftChild(BinaryTreeNode* parent, BinaryTreeElementType data) {
    if (this->isThisAppendable(parent, true)) {
        BinaryTreeNode* leftChild = new BinaryTreeNode();
        leftChild->data = data;
        leftChild->left = nullptr;
        leftChild->right = nullptr;
        parent->left = leftChild;
    } else {
        throw std::invalid_argument("The left child is already exist.");
    }
}

// Create a right child node
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::createRightChild(BinaryTreeNode* parent, BinaryTreeElementType data) {
    if (this->isThisAppendable(parent, false)) {
        BinaryTreeNode* rightChild = new BinaryTreeNode();
        rightChild->data = data;
        rightChild->left = nullptr;
        rightChild->right = nullptr;
        parent->right = rightChild;
    } else {
        throw std::invalid_argument("The right child is already exist.");
    }
}

// Print all nodes
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::printAllNodes() {
    // Print all nodes starting from the root
    this->printNode(this->root);
}

// Print a node
// Actually, this is an in-order traversal
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::printNode(BinaryTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    // By recursive approach, print all nodes
    this->printNode(node->left);
    std::cout << node->data << std::endl;
    this->printNode(node->right);
}

// Free all nodes
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::freeAllNodes() {
    // Delete all nodes starting from the root
    this->freeNode(this->root);
    std::cout << "All nodes are freed(by manually)." << std::endl;
}

// Free a node
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::freeNode(BinaryTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    // By recursive approach, free all nodes
    this->freeNode(node->left);
    this->freeNode(node->right);
    delete node;
}

int main(void) {
    // Diagram
    //       A
    //     -----
    //     |   |
    //     B   C

    // Create a binary tree
    BinaryTree<char> binaryTree('A');

    // Create left and right child nodes
    binaryTree.createLeftChild(binaryTree.root, 'B');
    binaryTree.createRightChild(binaryTree.root, 'C');

    // Print all nodes
    binaryTree.printAllNodes();

    // Free all nodes
    binaryTree.freeAllNodes();

    return 0;
}