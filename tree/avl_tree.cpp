/**
 * @file avl_tree.cpp
 * @brief AVL(Adelson-Velsky and Landis) tree implementation in C++ language
 *        AVL tree is a self-balancing binary search tree in which the difference of heights of left and right subtrees of any node is less than or equal to one.
 */
//

#include <iostream>
#include <algorithm>
#include <memory>

template <typename AVLTreeType>
class AVLTree {
private:
    struct node {
        AVLTreeType data;
        unsigned int height;
        std::shared_ptr<node> left;
        std::shared_ptr<node> right;

        node(AVLTreeType data) : data(data), height(1), left(nullptr), right(nullptr) {}
    };
    std::shared_ptr<node> root;

    // Private helper methods
    unsigned int height(const std::shared_ptr<node>& node) const;       
    int getBalanceFactor(const std::shared_ptr<node>& node) const;      
    void updateHeight(const std::shared_ptr<node>& node);                     
    void inorderTraversal(const std::shared_ptr<node>& node) const;     

    std::shared_ptr<node> rightRotate(std::shared_ptr<node> node);     
    std::shared_ptr<node> leftRotate(std::shared_ptr<node> node);      
    std::shared_ptr<node> insert(std::shared_ptr<node> node, AVLTreeType data); 

public:
    // Public methods
    AVLTree() : root(nullptr) {}
    ~AVLTree() = default;

    void insert(AVLTreeType data);  // Public insert method
    void inorderTraversal() const;  // Public inorder traversal method
};

// A utility function to calculate the height of the tree
template <typename AVLTreeType>
unsigned int AVLTree<AVLTreeType>::height(const std::shared_ptr<node>& node) const {
    return (node == nullptr) ? 0 : node->height;
}

// A utility function to get the balance factor of a node
// (balance factor = height of left subtree - height of right subtree)
// If the balance factor is greater than 1, then the tree is left heavy
// If the balance factor is less than -1, then the tree is right heavy
// If the balance factor is between -1 and 1, then the tree is balanced
template <typename AVLTreeType>
int AVLTree<AVLTreeType>::getBalanceFactor(const std::shared_ptr<node>& node) const {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

// A utility function to update the height of a node
template <typename AVLTreeType>
void AVLTree<AVLTreeType>::updateHeight(const std::shared_ptr<node>& node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
}

// A utility function to perform inorder traversal of the tree
template <typename AVLTreeType>
void AVLTree<AVLTreeType>::inorderTraversal(const std::shared_ptr<node>& node) const {
    if (node == nullptr)
        return;
    inorderTraversal(node->left);
    std::cout << node->data << " ";
    inorderTraversal(node->right);
}

// Right rotation
template <typename AVLTreeType>
std::shared_ptr<typename AVLTree<AVLTreeType>::node> AVLTree<AVLTreeType>::rightRotate(std::shared_ptr<node> y) {
    std::shared_ptr<node> x = y->left;
    std::shared_ptr<node> T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation
template <typename AVLTreeType>
std::shared_ptr<typename AVLTree<AVLTreeType>::node> AVLTree<AVLTreeType>::leftRotate(std::shared_ptr<node> x) {
    std::shared_ptr<node> y = x->right;
    std::shared_ptr<node> T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insert a new node in the AVL tree
template <typename AVLTreeType>
std::shared_ptr<typename AVLTree<AVLTreeType>::node> AVLTree<AVLTreeType>::insert(std::shared_ptr<node> node, AVLTreeType data) {
    if (node == nullptr) {
        std::cout << "A new node was created with data: " << data << std::endl;
        return std::make_shared<typename AVLTree<AVLTreeType>::node>(data);
    }

    // Perform the normal binary search tree insertion
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else {
        std::cerr << "Error: Duplicate data " << data << " not allowed in AVL tree" << std::endl;
        return node;
    }

    // Update the height of this ancestor node
    updateHeight(node);

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Public insert method
template <typename AVLTreeType>
void AVLTree<AVLTreeType>::insert(AVLTreeType data) {
    root = insert(root, data);
}

// Public inorder traversal method
template <typename AVLTreeType>
void AVLTree<AVLTreeType>::inorderTraversal() const {
    inorderTraversal(root);
    std::cout << std::endl;
}

int main(void) {
    AVLTree<int> avlTree;
    avlTree.insert(10);
    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(40);
    avlTree.insert(50);
    avlTree.insert(25);
    // The AVL tree after insertion of the above nodes will be:
    //                   30
    //             -------------
    //             |           |
    //            20          40
    //          -------      -------
    //          |     |      |     |
    //         10    25     NULL  50    

    std::cout << "Inorder traversal of the AVL tree: ";
    avlTree.inorderTraversal();

    return 0;
}

// A new node was created with data: 10
// A new node was created with data: 20
// A new node was created with data: 30
// A new node was created with data: 40
// A new node was created with data: 50
// A new node was created with data: 25
// Inorder traversal of the AVL tree: 10 20 25 30 40 50