/**
 * @file linked_list_for_stack.cpp
 * @brief A stack implementation using linked list, written in C++.
 *        C++ rewritten version of linked_list/linked_list_for_stack.c.
 */                      
//

#include <iostream>
#include <stdexcept>

template <typename LinkedListType>
class LinkedListStack {
private:
    struct Node {
        LinkedListType data;
        Node *next;
    };
    Node *topNodePointer;  // Pointer to the top node of the linked list stack
    unsigned int size;
public:
    // Constructor of the linked list stack class
    // Initializes the linked list stack with a single node
    LinkedListStack(LinkedListType data) {
        this->topNodePointer = new Node();
        this->topNodePointer->data = data;
        this->topNodePointer->next = nullptr;
        this->size = 0;
    }

    // Destructor of the linked list stack class
    // Deallocates the memory of the linked list stack
    ~LinkedListStack() {
        Node *currentNode = this->topNodePointer;
        Node *nextNode = nullptr;
        while (currentNode != nullptr) {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    // Methods
    bool isEmpty();
    void pushElement(LinkedListType data);
    LinkedListType popElement();
    LinkedListType peekElement();
    void display();
};

// Check if the linked list stack is empty
// We don't need to check if the linked list stack is full because the linked list stack is dynamic
template <typename LinkedListType>
bool LinkedListStack<LinkedListType>::isEmpty() {
    if (this->size == 0)
        return true;
    else
        return false;
}

// Push an element into the linked list stack
template <typename LinkedListType>
void LinkedListStack<LinkedListType>::pushElement(LinkedListType data) {
    // (topNodePointer) -> (newNode) -> (old topNodePointer) -> ...
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = this->topNodePointer;
    this->topNodePointer = newNode;
    this->size++;
}

// Pop an element from the linked list stack
template <typename LinkedListType>
LinkedListType LinkedListStack<LinkedListType>::popElement() {
    // (topNodePointer) -> (old topNodePointer) -> (old topNodePointer->next(that will be the new topNodePointer)) -> ...
    if (this->isEmpty()) {
        throw std::underflow_error("The linked list stack is empty.");
    }

    Node *oldTopNode = this->topNodePointer;
    LinkedListType data = oldTopNode->data;
    this->topNodePointer = oldTopNode->next;
    delete oldTopNode;
    this->size--;

    return data;
}

// Peek the top element of the linked list stack
template <typename LinkedListType>
LinkedListType LinkedListStack<LinkedListType>::peekElement() {
    if (this->isEmpty()) {
        throw std::underflow_error("The linked list stack is empty.");
    }
    return this->topNodePointer->data;
}

// Display the linked list stack
template <typename LinkedListType>
void LinkedListStack<LinkedListType>::display() {
    if (this->isEmpty()) {
        std::cout << "The linked list stack is empty." << std::endl;
        return;
    }

    Node *currentNode = this->topNodePointer;
    while (currentNode != nullptr) {
        std::cout << currentNode->data << " -> ";
        currentNode = currentNode->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main(void) {
    LinkedListStack<int> stack = LinkedListStack<int>(10);
    stack.pushElement(10);
    stack.display();
    stack.pushElement(20);
    stack.display();
    stack.pushElement(30);
    stack.display();
    stack.pushElement(40);
    stack.display();
    stack.pushElement(50);
    stack.display();

    std::cout << "Peeked element: " << stack.peekElement() << std::endl;
    std::cout << "Popped element: " << stack.popElement() << std::endl;
    stack.display();
    std::cout << "Peeked element: " << stack.peekElement() << std::endl;
    std::cout << "Popped element: " << stack.popElement() << std::endl;
    stack.display();

    return 0;
}

// 10 -> 10 -> nullptr
// 20 -> 10 -> 10 -> nullptr
// 30 -> 20 -> 10 -> 10 -> nullptr
// 40 -> 30 -> 20 -> 10 -> 10 -> nullptr
// 50 -> 40 -> 30 -> 20 -> 10 -> 10 -> nullptr
// Peeked element: 50
// Popped element: 50
// 40 -> 30 -> 20 -> 10 -> 10 -> nullptr
// Peeked element: 40
// Popped element: 40
// 30 -> 20 -> 10 -> 10 -> nullptr