# binary_tree_full.py
# A basic binary tree implementation using Python class with insert, search, and traversal functions

# A node structure for binary tree
class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.value = key

# A binary tree implementation using Python class
# Note that binary tree insertion is aligned with the binary search tree property
# (i.e. left child is less than parent and right child is greater than parent)
class BinaryTree:
    def __init__(self):
        self.root = None

    # Insert a node into the binary tree
    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        else:
            self._insert(self.root, key)

    # Recursive insert function (private function)
    def _insert(self, root, key):
        if key < root.value:
            if root.left is None:
                root.left = Node(key)
            else:
                self._insert(root.left, key)
        else:
            if root.right is None:
                root.right = Node(key)
            else:
                self._insert(root.right, key)

    # Search for a node in the binary tree    
    def search(self, key):
        return self._search(self.root, key)

    # Recursive search function (private function)
    def _search(self, root, key):
        if root is None or root.value == key:
            return root
        if key < root.value:
            return self._search(root.left, key)
        return self._search(root.right, key)

    # In-order traversal of the binary tree
    def inorder_traversal(self):
        return self._inorder_traversal(self.root, [])

    # Recursive in-order traversal function (private function)
    def _inorder_traversal(self, root, result):
        if root:
            self._inorder_traversal(root.left, result)
            result.append(root.value)
            self._inorder_traversal(root.right, result)
        return result

    # Pre-order traversal of the binary tree
    def preorder_traversal(self):
        return self._preorder_traversal(self.root, [])

    # Recursive pre-order traversal function (private function)
    def _preorder_traversal(self, root, result):
        if root:
            result.append(root.value)
            self._preorder_traversal(root.left, result)
            self._preorder_traversal(root.right, result)
        return result

    # Post-order traversal of the binary tree
    def postorder_traversal(self):
        return self._postorder_traversal(self.root, [])

    # Recursive post-order traversal function (private function)
    def _postorder_traversal(self, root, result):
        if root:
            self._postorder_traversal(root.left, result)
            self._postorder_traversal(root.right, result)
            result.append(root.value)
        return result

    # Print the binary tree structure on the console (not important for the binary tree implementation, just for visualization)
    def print_tree(self):
        if not self.root:
            print("Tree is empty")
            return
        self._print_tree(self.root, 0, False, "")
        
    def _print_tree(self, node, level, is_right, indent):
        if node:
            self._print_tree(node.right, level + 1, True, indent + ("        " if is_right else " |      "))
            print(indent + (" /------ " if is_right else " \\------ ") + str(node.value))
            self._print_tree(node.left, level + 1, False, indent + (" |      " if is_right else "        "))

# Example usage
if __name__ == "__main__":
    binary_tree = BinaryTree()
    binary_tree.insert(30)
    binary_tree.insert(20)
    binary_tree.insert(10)
    binary_tree.insert(40)
    binary_tree.insert(50)
    binary_tree.insert(60)


    print(f"In-order traversal   : {binary_tree.inorder_traversal()}")
    print(f"Pre-order traversal  : {binary_tree.preorder_traversal()}")
    print(f"Post-order traversal : {binary_tree.postorder_traversal()}")

    print("\nBinary Tree Structure:")
    binary_tree.print_tree()

    print(f"Search for 10: {'Found' if binary_tree.search(10) else 'Not Found'}")
    print(f"Search for 99: {'Found' if binary_tree.search(99) else 'Not Found'}")

# In-order traversal   : [10, 20, 30, 40, 50, 60]
# Pre-order traversal  : [30, 20, 10, 40, 50, 60]
# Post-order traversal : [10, 20, 60, 50, 40, 30]
# 
# Binary Tree Structure:
#  |                       /------ 60
#  |               /------ 50
#  |       /------ 40
#  \------ 30
#          \------ 20
#                  \------ 10
# Search for 10: Found
# Search for 99: Not Found