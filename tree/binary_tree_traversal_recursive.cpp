/**
 * @file binary_tree_traversal_recursive.cpp
 * @brief A basic binary tree traversal demonstration via recursive approach for BFS, and DFS.
 *        (Preorder, Inorder, Postorder in DFS, and Level order(BFS))
 */
//

#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>

// Tree structure
template <typename BinaryTreeElementType>
class BinaryTree {
private:
    struct BinaryTreeNode {
        BinaryTreeElementType data;
        std::shared_ptr<BinaryTreeNode> left;
        std::shared_ptr<BinaryTreeNode> right;
    };
public:
    std::shared_ptr<BinaryTreeNode> root;

    // Constructor, create a root node
    BinaryTree(BinaryTreeElementType data) {
        this->root = std::make_shared<BinaryTreeNode>();
        this->root->data = data;
        this->root->left = nullptr;
        this->root->right = nullptr;
    }

    // Because we use shared_ptr, we don't need to free the nodes manually

    // methods (boilerplate code)
    // Unnecessary methods are omitted
    bool isThisAppendable(std::shared_ptr<BinaryTreeNode> node, bool isLeft);
    void createLeftChild(std::shared_ptr<BinaryTreeNode> parent, BinaryTreeElementType data);
    void createRightChild(std::shared_ptr<BinaryTreeNode> parent, BinaryTreeElementType data);

    // Recursive traversal implementations
    void preorderTraversal(std::shared_ptr<BinaryTreeNode> node);
    void inorderTraversal(std::shared_ptr<BinaryTreeNode> node);
    void postorderTraversal(std::shared_ptr<BinaryTreeNode> node);
    void levelOrderTraversal(std::shared_ptr<BinaryTreeNode> node);  // Also known as BFS(Breadth First Search)
                                                                            // Unfortunately, we can't use queue in recursive approach
};

// Check if the node is appendable
template <typename BinaryTreeElementType>
bool BinaryTree<BinaryTreeElementType>::isThisAppendable(std::shared_ptr<BinaryTreeNode> node, bool isLeft) {
    if (isLeft) {
        return node->left == nullptr;
    } else {
        return node->right == nullptr;
    }
}

// Create a left child node
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::createLeftChild(std::shared_ptr<BinaryTreeNode> parent, BinaryTreeElementType data) {
    if (isThisAppendable(parent, true)) {
        parent->left = std::make_shared<BinaryTreeNode>();
        parent->left->data = data;
        parent->left->left = nullptr;
        parent->left->right = nullptr;
    } else {
        throw std::runtime_error("This node already has a left child node.");
    }
}

// Create a right child node
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::createRightChild(std::shared_ptr<BinaryTreeNode> parent, BinaryTreeElementType data) {
    if (isThisAppendable(parent, false)) {
        parent->right = std::make_shared<BinaryTreeNode>();
        parent->right->data = data;
        parent->right->left = nullptr;
        parent->right->right = nullptr;
    } else {
        throw std::runtime_error("This node already has a right child node.");
    }
}

// Preorder traversal
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::preorderTraversal(std::shared_ptr<BinaryTreeNode> node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->data << " ";
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

// Inorder traversal
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::inorderTraversal(std::shared_ptr<BinaryTreeNode> node) {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    std::cout << node->data << " ";
    inorderTraversal(node->right);
}

// Postorder traversal
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::postorderTraversal(std::shared_ptr<BinaryTreeNode> node) {
    if (node == nullptr) {
        return;
    }

    postorderTraversal(node->left);
    postorderTraversal(node->right);
    std::cout << node->data << " ";
}

// Level order traversal (also known as BFS(Breadth First Search))
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::levelOrderTraversal(std::shared_ptr<BinaryTreeNode> node) {
    if (node == nullptr) {
        // It's safe to raise an exception because it's not a recursive function.
        throw std::invalid_argument("The tree is empty.");
    }

    std::queue<std::shared_ptr<BinaryTreeNode>> levelOrderQueue;

    // Initially, push the root node
    levelOrderQueue.push(node);

    while (!levelOrderQueue.empty()) {
        std::shared_ptr<BinaryTreeNode> currentNode = levelOrderQueue.front();
        levelOrderQueue.pop();
        std::cout << currentNode->data << " ";

        // If the left child exists, push it to the queue
        if (currentNode->left != nullptr) {
            levelOrderQueue.push(currentNode->left);
        }

        // If the right child exists, push it to the queue
        if (currentNode->right != nullptr) {
            levelOrderQueue.push(currentNode->right);
        }

        // Continue until the queue is empty
    }
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

    // Create a binary tree
    BinaryTree<char> tree('A');
    tree.createLeftChild(tree.root, 'B');
    tree.createRightChild(tree.root, 'C');
    tree.createLeftChild(tree.root->left, 'D');
    tree.createRightChild(tree.root->left, 'E');
    tree.createLeftChild(tree.root->right, 'F');
    tree.createRightChild(tree.root->right, 'G');

    // Preorder traversal
    std::cout << "Preorder traversal    : ";
    tree.preorderTraversal(tree.root);
    std::cout << std::endl;

    // Inorder traversal
    std::cout << "Inorder traversal     : ";
    tree.inorderTraversal(tree.root);
    std::cout << std::endl;

    // Postorder traversal
    std::cout << "Postorder traversal   : ";
    tree.postorderTraversal(tree.root);
    std::cout << std::endl;

    // Level order traversal
    std::cout << "Level order traversal : ";
    tree.levelOrderTraversal(tree.root);
    std::cout << std::endl;

    return 0;
}

// Preorder traversal    : A B D E C F G 
// Inorder traversal     : D B E A F C G 
// Postorder traversal   : D E B F G C A 
// Level order traversal : A B C D E F G