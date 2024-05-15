# file: binary_tree_traversal_recursive.py
# brief: Binary tree traversal using recursive methods

class Node:
    def __init__(self, key) -> None:
        self.left = None
        self.right = None
        self.value = key

# In order traversal
# Left -> Root -> Right
def inorder_traversal(node) -> None:
    if node:
        inorder_traversal(node.left)
        print(node.value, end=" ")
        inorder_traversal(node.right)

# Pre order traversal
# Root -> Left -> Right
def preorder_traversal(node) -> None:
    if node:
        print(node.value, end=" ")
        preorder_traversal(node.left)
        preorder_traversal(node.right)

# Post order traversal
# Left -> Right -> Root
def postorder_traversal(node) -> None:
    if node:
        postorder_traversal(node.left)
        postorder_traversal(node.right)
        print(node.value, end=" ")

# Create a binary tree
#         A
#      -----
#      |   |
#      B   C
#     --- ---
#     | | | |
#     D E F G
root = Node('A')
root.left = Node('B')
root.right = Node('C')
root.left.left = Node('D')
root.left.right = Node('E')
root.right.left = Node('F')
root.right.right = Node('G')

print("Inorder traversal:   ", end=" ") 
inorder_traversal(root)
print("\nPreorder traversal:  ", end=" ")
preorder_traversal(root)
print("\nPostorder traversal: ", end=" ")
postorder_traversal(root)

# Inorder traversal:    D B E A F C G 
# Preorder traversal:   A B D E C F G
# Postorder traversal:  D E B F G C A