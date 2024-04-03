/**
 * @file linked_list_basic.cpp
 * @brief C++ implementation of a single linked list
 *        C++ version of linked_list_basic.c 
 */
//

#include <iostream>
#include <stdexcept>

template <typename LinkedListType>
class LinkedList {
private:
    struct Node {
        LinkedListType data;
        Node *next;
    };
    Node *headNodePointer;  // Pointer to the head node of the linked list
    Node *tailNodePointer;  // Pointer to the tail node of the linked list
    unsigned int size;
public:
    // Constructor of the linked list class, initializes the linked list with a single node
    LinkedList(LinkedListType data) {
        this->headNodePointer = new Node();
        this->headNodePointer->data = data;
        this->headNodePointer->next = nullptr;
        this->tailNodePointer = this->headNodePointer;
        this->size = 0;
    }

    // Destructor of the linked list class, deletes the linked list
    ~LinkedList() {
        Node *currentNode = this->headNodePointer;
        Node *nextNode;
        while (currentNode != nullptr) {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
        std::cout << "Linked List deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    void insertFront(LinkedListType data);
    void insertBack(LinkedListType data);
    void insertAfter(LinkedListType data, const unsigned int targetIndex);
    LinkedListType deleteFront();
    LinkedListType deleteBack();
    LinkedListType deleteAfter(const unsigned int targetIndex);
    void display();
};

// Method to check if the linked list is empty
template <typename LinkedListType>
bool LinkedList<LinkedListType>::isEmpty() {
    if (this->headNodePointer == nullptr)
        return true;
    else
        return false;
}

// Method to insert a node at the front of the linked list
template <typename LinkedListType>
void LinkedList<LinkedListType>::insertFront(LinkedListType data) {
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = this->headNodePointer;
    this->headNodePointer = newNode;    // Update the head node pointer
    this->size += 1;
}

// Method to insert a node at the back of the linked list
template <typename LinkedListType>
void LinkedList<LinkedListType>::insertBack(LinkedListType data) {
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    this->tailNodePointer->next = newNode;  // Update the tail node pointer
    this->size += 1;
}

// Method to insert a node after a specific index in the linked list
template <typename LinkedListType>
void LinkedList<LinkedListType>::insertAfter(LinkedListType data, const unsigned int targetIndex) {
    // Range check. At least targetIndex will be 0 or greater than 0
    if (targetIndex > this->size) {
        throw std::range_error("Index out of range");
    } 

    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    // Traverse the linked list to the target index'th node
    Node *currentNode = this->headNodePointer;
    for (size_t index = 0; index < targetIndex; index++) {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
    this->size += 1;
}

// Method to delete the front node of the linked list
template <typename LinkedListType>
LinkedListType LinkedList<LinkedListType>::deleteFront() {
    // Check if the linked list is empty
    if (this->isEmpty()) {
        throw std::underflow_error("Linked list is empty, can't delete more elements");
    }

    // Delete the front node after capturing the value of the node
    Node *nodeToDelete = this->headNodePointer;
    LinkedListType data = nodeToDelete->data;
    this->headNodePointer = nodeToDelete->next;
    delete nodeToDelete;
    this->size -= 1;

    return data;
}

// Method to delete the back node of the linked list
template <typename LinkedListType>
LinkedListType LinkedList<LinkedListType>::deleteBack() {
    // Check if the linked list is empty
    if (this->isEmpty()) {
        throw std::underflow_error("Linked list is empty, can't delete more elements");
    }

    // Traverse the linked list to the second last node
    // Can't directly traverse to the last node as we need to update the tail node pointer
    // and this is not a doubly linked list
    Node *currentNode = this->headNodePointer;
    while (currentNode->next->next != nullptr) {
        currentNode = currentNode->next;
    }

    // Delete the last node after capturing the value of the node
    Node *nodeToDelete = currentNode->next;
    LinkedListType data = nodeToDelete->data;
    currentNode->next = nullptr;            // It is now the last node
    this->tailNodePointer = currentNode;    // Update the tail node pointer
    delete nodeToDelete;
    this->size -= 1;

    return data;
}

// Method to delete a node after a specific index in the linked list
template <typename LinkedListType>
LinkedListType LinkedList<LinkedListType>::deleteAfter(const unsigned int targetIndex) {
    // Range check. At least targetIndex will be 0 or greater than 0
    if (targetIndex >= this->size) {
        throw std::range_error("Index out of range, so can't delete the node");
    }

    // Traverse the linked list to the target index'th node
    Node *currentNode = this->headNodePointer;
    for (size_t index = 0; index < targetIndex; index++) {
        currentNode = currentNode->next;
    }

    // Delete the node after the target index after capturing the value of the node
    Node *nodeToDelete = currentNode->next;
    LinkedListType data = nodeToDelete->data;
    currentNode->next = nodeToDelete->next;
    delete nodeToDelete;
    this->size -= 1;

    return data;
}

// Method to display the linked list
template <typename LinkedListType>
void LinkedList<LinkedListType>::display() {
    
    Node *currentNode = this->headNodePointer;
    std::cout << "[# of nodes: " << this->size + 1 << "] ";
    while (currentNode != nullptr) {
        std::cout << currentNode->data << " -> ";
        currentNode = currentNode->next;
    }
    std::cout << "(nullptr)" << std::endl;
}

int main(void) {
    
    LinkedList<std::string> linkedList("alpha");
    linkedList.display();

    linkedList.insertFront("bravo");
    linkedList.display();

    linkedList.insertBack("charlie");
    linkedList.display();

    // Of course, the index starts from 0
    linkedList.insertAfter("delta", 1);
    linkedList.display();
    
    linkedList.deleteFront();
    linkedList.display();

    linkedList.deleteBack();
    linkedList.display();

    linkedList.deleteAfter(0);
    linkedList.display();

    return 0;
}

// [# of nodes: 1] alpha -> (nullptr)
// [# of nodes: 2] bravo -> alpha -> (nullptr)
// [# of nodes: 3] bravo -> alpha -> charlie -> (nullptr)
// [# of nodes: 4] bravo -> alpha -> delta -> charlie -> (nullptr)
// [# of nodes: 3] alpha -> delta -> charlie -> (nullptr)
// [# of nodes: 2] alpha -> delta -> (nullptr)
// [# of nodes: 1] alpha -> (nullptr)
// Linked List deleted