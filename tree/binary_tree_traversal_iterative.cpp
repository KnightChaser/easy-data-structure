/**
 * @file binary_tree_traversal_iterative.cpp
 * @brief A basic binary tree traversal implementation with using struct and pointers.
 *        By using iterative approach, it will traverse the tree in three ways (a little bit complex way).
 *        (Preorder, Inorder, Postorder, Level order(BFS))
 *        Because we are using C++, we can use standard library features :)
 */

#include <iostream>
#include <memory>
#include <stack>
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

    // Iterative traversal implementations
    std::string preorderTraversal();
    std::string inorderTraversal();
    std::string postorderTraversal();
    std::string levelOrderTraversal();  // Also known as BFS(Breadth First Search)
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
    if (this->isThisAppendable(parent, true)) {
        std::shared_ptr<BinaryTreeNode> leftChild = std::make_shared<BinaryTreeNode>();
        leftChild->data = data;
        leftChild->left = nullptr;
        leftChild->right = nullptr;
        parent->left = leftChild;
    } else {
        throw std::runtime_error("The left child already exists.");
    }
}

// Create a right child node
template <typename BinaryTreeElementType>
void BinaryTree<BinaryTreeElementType>::createRightChild(std::shared_ptr<BinaryTreeNode> parent, BinaryTreeElementType data) {
    if (this->isThisAppendable(parent, false)) {
        std::shared_ptr<BinaryTreeNode> rightChild = std::make_shared<BinaryTreeNode>();
        rightChild->data = data;
        rightChild->left = nullptr;
        rightChild->right = nullptr;
        parent->right = rightChild;
    } else {
        throw std::runtime_error("The right child already exists.");
    }
}

// Preorder traversal
template <typename BinaryTreeElementType>
std::string BinaryTree<BinaryTreeElementType>::preorderTraversal() {
    if (this->root == nullptr) {
        throw std::invalid_argument("The tree is empty.");
    }

    std::stack<std::shared_ptr<BinaryTreeNode>> stack;
    stack.push(this->root);
    std::string result;

    while (!stack.empty()) {
        std::shared_ptr<BinaryTreeNode> node = stack.top();
        stack.pop();

        result += node->data;
        result += " ";

        // Push the right child first, because we want to process the left child first
        if (node->right != nullptr) {
            stack.push(node->right);
        }

        // Push the left child later, because we want to process the left child first
        if (node->left != nullptr) {
            stack.push(node->left);
        }
    }

    return result;
}

// Inorder traversal
template <typename BinaryTreeElementType>
std::string BinaryTree<BinaryTreeElementType>::inorderTraversal() {
    if (this->root == nullptr) {
        throw std::invalid_argument("The tree is empty.");
    }

    // Create a stack and pick the root node as the current node
    std::stack<std::shared_ptr<BinaryTreeNode>> stack;
    std::shared_ptr<BinaryTreeNode> current = this->root;
    std::string result;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();
        result += current->data;
        result += " ";

        current = current->right; // We reached the leftmost node, now go to the right child
    }

    return result;
}

// Postorder traversal
template <typename BinaryTreeElementType>
std::string BinaryTree<BinaryTreeElementType>::postorderTraversal() {
    if (this->root == nullptr) {
        throw std::invalid_argument("The tree is empty.");
    }

    std::stack<std::shared_ptr<BinaryTreeNode>> stack;
    stack.push(this->root);

    std::stack<std::shared_ptr<BinaryTreeNode>> outputStack;
    std::string result;

    while (!stack.empty()) {
        std::shared_ptr<BinaryTreeNode> node = stack.top();
        stack.pop();
        outputStack.push(node);

        // Push the left child first, because we want to process the right child first
        if (node->left != nullptr) {
            stack.push(node->left);
        }

        // Push the right child later, because we want to process the right child first
        if (node->right != nullptr) {
            stack.push(node->right);
        }
    }

    while (!outputStack.empty()) {
        std::shared_ptr<BinaryTreeNode> node = outputStack.top();
        outputStack.pop();
        result += node->data;
        result += " ";
    }

    return result;
}

// Level order traversal
template <typename BinaryTreeElementType>
std::string BinaryTree<BinaryTreeElementType>::levelOrderTraversal() {
    if (this->root == nullptr) {
        throw std::invalid_argument("The tree is empty.");
    }

    std::queue<std::shared_ptr<BinaryTreeNode>> queue;
    queue.push(this->root);
    std::string result;

    while (!queue.empty()) {
        std::shared_ptr<BinaryTreeNode> node = queue.front();
        queue.pop();

        result += node->data;
        result += " ";

        if (node->left != nullptr) {
            queue.push(node->left);
        }

        if (node->right != nullptr) {
            queue.push(node->right);
        }
    }

    return result;
}

int main() {
    // Diagram
    //                  A
    //                -----
    //                |   |
    //                B   C
    //           -----    -----
    //           |   |    |   |
    //           D   E    F   G
    
    // Create a binary tree
    BinaryTree<char> tree('A');
    tree.createLeftChild(tree.root, 'B');
    tree.createRightChild(tree.root, 'C');
    tree.createLeftChild(tree.root->left, 'D');
    tree.createRightChild(tree.root->left, 'E');
    tree.createLeftChild(tree.root->right, 'F');
    tree.createRightChild(tree.root->right, 'G');

    // Preorder traversal
    std::cout << "Preorder traversal    : " << tree.preorderTraversal() << std::endl;

    // Inorder traversal
    std::cout << "Inorder traversal     : " << tree.inorderTraversal() << std::endl;

    // Postorder traversal
    std::cout << "Postorder traversal   : " << tree.postorderTraversal() << std::endl;

    // Level order traversal
    std::cout << "Level order traversal : " << tree.levelOrderTraversal() << std::endl;

    return 0;
}

// Preorder traversal    : A B D E C F G 
// Inorder traversal     : D B E A F C G
// Postorder traversal   : D E B F G C A
// Level order traversal : A B C D E F G