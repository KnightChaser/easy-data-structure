/**
 * @file doubly_linked_list.cpp
 * @brief A simple implementation of doubly linked list, written in C++ language.
 *        A C++ version of linked_list/doubly_linked_list.c.
 */
//

#include <iostream>
#include <memory>
#include <stdexcept>

template <typename DoublyLinkedListElementType>
class DoublyLinkedList {
private:
    struct Node {
        DoublyLinkedListElementType data;
        std::shared_ptr<Node> next;         // Pointer to the next node
        std::shared_ptr<Node> previous;     // Pointer to the previous node
    };

    // Pointer to the head node of the doubly linked list
    std::shared_ptr<Node> headNodePointer;
    unsigned int size;
public:
    // Constructor of the doubly linked list class, initializes the doubly linked list with a single node
    DoublyLinkedList(DoublyLinkedListElementType data) : headNodePointer(std::make_shared<Node>()), size(1) {
        // At first, the head node points to itself
        this->headNodePointer->data = data;
        this->headNodePointer->next = this->headNodePointer;
        this->headNodePointer->previous = this->headNodePointer;
    }

    // Destructor of the doubly linked list class, deletes the doubly linked list
    // Note that std::shared_ptr will automatically delete the memory when it goes out of scope
    ~DoublyLinkedList() {
        if (this->headNodePointer != nullptr) {
            this->headNodePointer->next = nullptr;     // Break the circular reference.
            this->headNodePointer->previous = nullptr; // Break the circular reference.
        }
        std::cout << "Doubly Linked List deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    void insertNextToHead(DoublyLinkedListElementType data);
    void insertNextToNodeValue(DoublyLinkedListElementType data, DoublyLinkedListElementType targetValue);
    void insertBeforeHead(DoublyLinkedListElementType data);
    void removeNodeByValue(DoublyLinkedListElementType data);
    void display();
};

// Method to check if the doubly linked list is empty
template <typename DoublyLinkedListElementType>
bool DoublyLinkedList<DoublyLinkedListElementType>::isEmpty() {
    if (this->headNodePointer == nullptr)
        // Since there is an element in the doubly linked list, it is not empty
        return true;
    else
        return false;
}

// Method to insert a new node next to the head node
template <typename DoublyLinkedListElementType>
void DoublyLinkedList<DoublyLinkedListElementType>::insertNextToHead(DoublyLinkedListElementType data) {
    // ... <-> headNode <-> newNode <-> ...
    std::shared_ptr<Node> newNode = std::make_unique<Node>();
    newNode->data = data;

    newNode->next = this->headNodePointer->next;            // The new node points to the node after the head node (forward)
    newNode->previous = this->headNodePointer;              // The new node points to the head node (backward)
    this->headNodePointer->next->previous = newNode;        // The node after the head node now points to the new node (backward)
    this->headNodePointer->next = newNode;                  // The head node now points to the new node (forward)
                                                            // Now, the new node is inserted next to the head node
    this->size++;
}

// Method to insert a new node next to a node that has a specific data
template <typename DoublyLinkedListElementType>
void DoublyLinkedList<DoublyLinkedListElementType>::insertNextToNodeValue(DoublyLinkedListElementType data, DoublyLinkedListElementType targetValue) {
    std::shared_ptr<Node> currentNode = this->headNodePointer;

    do {
        if (currentNode->data == targetValue) {
            // ... <-> currentNode <-> newNode <-> ...
            std::shared_ptr<Node> newNode = std::make_unique<Node>();
            newNode->data = data;

            newNode->next = currentNode->next;         // The new node points to the node that was next to the given node (forward)
            newNode->previous = currentNode;           // The new node points to the given node (backward)
            currentNode->next->previous = newNode;     // The node that was next to the given node now points to the newNode backward
            currentNode->next = newNode;               // The given node now points to the newNode forward
                                                        // Now, the new node is inserted next to the given node
            this->size++;
            return;
        }
    // Repeat traversing the doubly linked list until the end of the list
    } while ((currentNode = currentNode->next) != this->headNodePointer);

    throw std::invalid_argument("The data does not exist in the doubly linked list.");
}

// Method to insert a new node before the head node
template <typename DoublyLinkedListElementType>
void DoublyLinkedList<DoublyLinkedListElementType>::insertBeforeHead(DoublyLinkedListElementType data) {
    // ... <-> newNode <-> headNode <-> ...
    std::shared_ptr<Node> newNode = std::make_unique<Node>();
    newNode->data = data;

    newNode->next = this->headNodePointer;                  // The new node points to the head node (forward)
    newNode->previous = this->headNodePointer->previous;    // The new node points to the node before the head node (backward)
    this->headNodePointer->previous->next = newNode;        // The node before the head node now points to the new node (forward)
    this->headNodePointer->previous = newNode;              // The head node now points to the new node (backward)
                                                            // Now, the new node is inserted before the head node
    this->size++;
}

// Method to remove a node from the doubly linked list
template <typename DoublyLinkedListElementType>
void DoublyLinkedList<DoublyLinkedListElementType>::removeNodeByValue(DoublyLinkedListElementType data) {
    std::shared_ptr<Node> currentNode = this->headNodePointer;

    do {
        if (currentNode->data == data) {
            // ... <-> previousNode <-> currentNode <-> nextNode <-> ...
            currentNode->previous->next = currentNode->next;       // The node before the given node now points to the node after the given node
            currentNode->next->previous = currentNode->previous;   // The node after the given node now points to the node before the given node
            this->size--;
            return;
            // Now, the current node has been removed from the doubly linked list
        }
    // Repeat traversing the doubly linked list until the end of the list
    } while ((currentNode = currentNode->next) != this->headNodePointer);

    throw std::invalid_argument("The data does not exist in the doubly linked list.");
}

// Method to display the doubly linked list
template <typename DoublyLinkedListElementType>
void DoublyLinkedList<DoublyLinkedListElementType>::display() {
    if (this->isEmpty()) {
        throw std::invalid_argument("The doubly linked list is empty.");
        return;
    }

    std::shared_ptr<Node> currentNode = this->headNodePointer;
    std::cout << "(Size: " << this->size << ") => ";
    do {
        std::cout << currentNode->data << " <-> ";
        currentNode = currentNode->next;
    } while (currentNode != this->headNodePointer);

    // Emphasize the circularity of the doubly linked list
    std::cout << this->headNodePointer->data << std::endl;
}

// Main function
int main() {
    // Create a doubly linked list with a single node
    DoublyLinkedList<char> doublyLinkedList('A');

    // Insert a new node next to the head node
    doublyLinkedList.insertNextToHead('B');
    doublyLinkedList.display();

    // Insert a new node next to a node that has a specific data
    doublyLinkedList.insertNextToNodeValue('C', 'B');
    doublyLinkedList.insertNextToNodeValue('X', 'C');
    doublyLinkedList.display();

    // Insert a new node before the head node
    doublyLinkedList.insertBeforeHead('D');
    doublyLinkedList.display();

    // Remove a node from the doubly linked list
    doublyLinkedList.removeNodeByValue('B');
    doublyLinkedList.display();

    return 0;
}

// (Size: 2) => A <-> B <-> A
// (Size: 4) => A <-> B <-> C <-> X <-> A
// (Size: 5) => A <-> B <-> C <-> X <-> D <-> A
// (Size: 4) => A <-> C <-> X <-> D <-> A
// Doubly Linked List deleted