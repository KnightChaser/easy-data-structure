/**
 * @file linked_list_for_queue.cpp
 * @brief A queue implementation using linked list, written in C++.
 */
//

#include <iostream>
#include <stdexcept>

// Node structure for the linked list queue
template<typename LinkedListType>
struct LinkedListNode {
    LinkedListType data;
    LinkedListNode *next;
    LinkedListNode(LinkedListType data) : data(data), next(nullptr) {}
};

// Linked list queue class
template<typename LinkedListType>
class LinkedListQueue {
private:
    LinkedListNode<LinkedListType> *front;
    LinkedListNode<LinkedListType> *rear;
    unsigned int size;

public:
    explicit LinkedListQueue(LinkedListType data);
    ~LinkedListQueue();

    void enqueue(LinkedListType data);
    LinkedListType dequeue();
    LinkedListType peekFront() const;
    LinkedListType peekRear() const;
    unsigned int getSize() const;
    bool isEmpty() const;
    void print() const;
};

// Constructor of the linked list queue class
template<typename LinkedListType>
LinkedListQueue<LinkedListType>::LinkedListQueue(LinkedListType data) 
    : front(new LinkedListNode<LinkedListType>(data)), rear(front), size(1) {}

// Destructor of the linked list queue class
template<typename LinkedListType>
LinkedListQueue<LinkedListType>::~LinkedListQueue() {
    LinkedListNode<LinkedListType> *current = front;
    while (current != nullptr) {
        LinkedListNode<LinkedListType> *temp = current;
        current = current->next;
        delete temp;
    }
    std::cout << "The linked list queue is destroyed.\n";
}

// Check if the linked list queue is empty
template<typename LinkedListType>
bool LinkedListQueue<LinkedListType>::isEmpty() const {
    return size == 0;
}

// Add an element to the linked list queue
template<typename LinkedListType>
void LinkedListQueue<LinkedListType>::enqueue(LinkedListType data) {
    LinkedListNode<LinkedListType> *newNode = new LinkedListNode<LinkedListType>(data);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

// Get the front element of the linked list queue
template<typename LinkedListType>
LinkedListType LinkedListQueue<LinkedListType>::peekFront() const {
    if (isEmpty()) {
        throw std::runtime_error("The linked list queue is empty.");
    }
    return front->data;
}

// Get the last element of the linked list queue
template<typename LinkedListType>
LinkedListType LinkedListQueue<LinkedListType>::peekRear() const {
    if (isEmpty()) {
        throw std::runtime_error("The linked list queue is empty.");
    }
    return rear->data;
}

// Get the size of the linked list queue
template<typename LinkedListType>
unsigned int LinkedListQueue<LinkedListType>::getSize() const {
    return size;
}

// Remove an element from the linked list queue
template<typename LinkedListType>
LinkedListType LinkedListQueue<LinkedListType>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("The linked list queue is empty.");
    }
    LinkedListNode<LinkedListType> *oldFront = front;
    LinkedListType data = oldFront->data;
    front = front->next;
    delete oldFront;
    if (front == nullptr) {
        rear = nullptr;
    }
    size--;
    return data;
}

// Display the linked list queue
template<typename LinkedListType>
void LinkedListQueue<LinkedListType>::print() const {
    if (isEmpty()) {
        std::cerr << "The linked list queue is empty.\n";
    } else {
        LinkedListNode<LinkedListType> *current = front;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }
}

int main(void) {
    LinkedListQueue<char> queue('A');
    queue.print();

    queue.enqueue('B');
    queue.print();

    queue.enqueue('C');
    queue.print();

    queue.enqueue('D');
    queue.print();

    queue.enqueue('E');
    queue.print();

    std::cout << "The front element of the linked list queue is " << queue.peekFront() << ".\n";
    std::cout << "The last element of the linked list queue is " << queue.peekRear() << ".\n";
    std::cout << "The size of the linked list queue is " << queue.getSize() << ".\n";

    std::cout << "The front element " << queue.dequeue() << " has been dequeued from the linked list queue.\n";
    queue.print();

    std::cout << "The front element " << queue.dequeue() << " has been dequeued from the linked list queue.\n";
    queue.print();

    std::cout << "The front element " << queue.dequeue() << " has been dequeued from the linked list queue.\n";
    queue.print();

    std::cout << "The front element " << queue.dequeue() << " has been dequeued from the linked list queue.\n";
    queue.print();

    std::cout << "The front element " << queue.dequeue() << " has been dequeued from the linked list queue.\n";
    queue.print();

    return 0;
}

// A -> B -> NULL
// A -> B -> C -> NULL
// A -> B -> C -> D -> NULL
// A -> B -> C -> D -> E -> NULL
// The front element of the linked list queue is A.
// The last element of the linked list queue is E.
// The size of the linked list queue is 5.
// The front element A has been dequeued from the linked list queue.
// B -> C -> D -> E -> NULL
// The front element B has been dequeued from the linked list queue.
// C -> D -> E -> NULL
// The front element C has been dequeued from the linked list queue.
// D -> E -> NULL
// The front element D has been dequeued from the linked list queue.
// E -> NULL
// The front element E has been dequeued from the linked list queue.
// The linked list queue is empty.
// The linked list queue is destroyed.