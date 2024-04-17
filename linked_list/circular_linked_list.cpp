/**
 * @file circular_linked_list.cpp
 * @brief A simple demonstration of circular linked list.
 *        A C++ version of linked_list/circular_linked_list.c.
 */
//

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

template <typename CircularLinkedListType>
class CircularLinkedList {
private:
    struct Node {
        CircularLinkedListType data;
        std::shared_ptr<Node> next;
    };
    // Pointer to the head node of the circular linked list
    std::shared_ptr<Node> headNodePointer;
    unsigned int size;
public:
    // Constructor of the circular linked list class, initializes the circular linked list with a single node
    CircularLinkedList(CircularLinkedListType data) : headNodePointer(std::make_shared<Node>()), size(1) {
        this->headNodePointer->data = data;
        this->headNodePointer->next = headNodePointer;
    }

    // Destructor of the circular linked list class, deletes the circular linked list
    // Note that std::shared_ptr will automatically delete the memory when it goes out of scope
    ~CircularLinkedList() {
        if (this->headNodePointer != nullptr) {
            this->headNodePointer->next = nullptr; // Break the circular reference.
        }
        std::cout << "Circular Linked List deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    void insertNextToHead(CircularLinkedListType data);
    void insertNextToNodeValue(CircularLinkedListType data, CircularLinkedListType targetValue);
    void insertBeforeHead(CircularLinkedListType data);
    void display();
};

// Method to check if the circular linked list is empty
template <typename CircularLinkedListType>
bool CircularLinkedList<CircularLinkedListType>::isEmpty() {
    if (this->headNodePointer == nullptr)
        // Since there is an element in the circular linked list, it is not empty
        return true;
    else
        return false;
}

// Method to insert a new node next to the head node
template <typename CircularLinkedListType>
void CircularLinkedList<CircularLinkedListType>::insertNextToHead(CircularLinkedListType data) {
    std::shared_ptr<Node> newNode = std::make_unique<Node>();
    newNode->data = data;
    newNode->next = this->headNodePointer->next;
    this->headNodePointer->next = newNode;
    this->size++;
}

// Method to insert a new node before the head node
template <typename CircularLinkedListType>
void CircularLinkedList<CircularLinkedListType>::insertBeforeHead(CircularLinkedListType data) {
    // Create a new node
    std::shared_ptr<Node> newNode = std::make_unique<Node>();
    newNode->data = data;

    // Traverse the circular linked list to find the last node
    // Because it's a circular linked list, the last node points to the head node
    std::shared_ptr<Node> currentNode = this->headNodePointer;
    while (currentNode->next != this->headNodePointer)
        currentNode = currentNode->next;

    // Now currentNode is right before the head node
    currentNode->next = newNode;
    newNode->next = this->headNodePointer;
    this->headNodePointer = newNode;             // Refresh headNode to the newly created node
    this->size++;
}

// Method to insert a new node having "value" next to the specific node having "targetValue"
template <typename CircularLinkedListType>
void CircularLinkedList<CircularLinkedListType>::insertNextToNodeValue(CircularLinkedListType data, CircularLinkedListType targetValue) {
    // Create a new node
    std::shared_ptr<Node> newNode = std::make_unique<Node>();
    newNode->data = data;

    // Traverse the circular linked list to find the specific node
    std::shared_ptr<Node> currentNode = this->headNodePointer;
    while (currentNode->data != targetValue) {
        currentNode = currentNode->next;
        if (currentNode == this->headNodePointer) {
            // The logic couldn't find the specific node having the target value (non-existent target value)
            throw std::runtime_error("The specific node having the target value is not found.");
        }
    }

    // Now currentNode is the specific node having the target value
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    this->size++;
}

// Method to display the circular linked list
template <typename CircularLinkedListType>
void CircularLinkedList<CircularLinkedListType>::display() {

    // Actually, this won't happen in normal case because the head node is initialized in the constructor
    if (this->isEmpty()) {
        throw std::runtime_error("The circular linked list is empty.");
    }

    std::shared_ptr<Node> currentNode = this->headNodePointer;
    do {
        std::cout << currentNode->data << " -> ";
        currentNode = currentNode->next;
    } while (currentNode != this->headNodePointer);

    // To emphasize that it is a circular linked list, print the head node's data again
    std::cout << this->headNodePointer->data << std::endl;
}

// Main function
int main(void) {
    // Create a circular linked list with a single node
    CircularLinkedList<std::string> circularLinkedList("EE");

    // Insert a new node next to the head node
    std::string elementsFront[] = {"A0", "A1", "A2", "A3"};
    for (const std::string element : elementsFront) {
        circularLinkedList.insertNextToHead(element);
        circularLinkedList.display();
    }

    // Insert a new node having "XX" next to the specific node having "A1"
    circularLinkedList.insertNextToNodeValue("XX", "A1");

    // Insert a new node before the head node
    std::string elementsBack[] = {"Z0", "Z1", "Z2", "Z3"};
    for (const std::string element : elementsBack) {
        circularLinkedList.insertBeforeHead(element);
        circularLinkedList.display();
    }

    // Making an exception
    try {
        circularLinkedList.insertNextToNodeValue("YY", "A5");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

// EE -> A0 -> EE
// EE -> A1 -> A0 -> EE
// EE -> A2 -> A1 -> A0 -> EE
// EE -> A3 -> A2 -> A1 -> A0 -> EE
// Z0 -> EE -> A3 -> A2 -> A1 -> XX -> A0 -> Z0
// Z1 -> Z0 -> EE -> A3 -> A2 -> A1 -> XX -> A0 -> Z1
// Z2 -> Z1 -> Z0 -> EE -> A3 -> A2 -> A1 -> XX -> A0 -> Z2
// Z3 -> Z2 -> Z1 -> Z0 -> EE -> A3 -> A2 -> A1 -> XX -> A0 -> Z3
// The specific node having the target value is not found.
// Circular Linked List deleted