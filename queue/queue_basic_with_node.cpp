/**
 * @file queue_basic_with_node.cpp
 * @brief Basic queue implementation in C++ using nodes (C++ version of queue_basic_with_node.c)
 */
//
#include <iostream>
#include <stdexcept>

template <typename QueueType>
struct QueueNode {
    QueueType data;
    struct QueueNode *next;
};

template <typename QueueType>
class Queue {
private:
    QueueNode<QueueType> *frontQueueNode;
    QueueNode<QueueType> *rearQueueNode;
    unsigned int queueSize;
public:
    // Constructor, initializes the queue
    Queue() {
        this->frontQueueNode = nullptr;
        this->rearQueueNode = nullptr;
        this->queueSize = 0;
    }

    // Destructor, deletes the queue
    ~Queue() {
        QueueNode<QueueType> *tempQueueNode = this->frontQueueNode;
        
        // Traverse each node and delete it
        while (tempQueueNode != nullptr) {
            QueueNode<QueueType> *nextQueueNode = tempQueueNode->next;
            delete tempQueueNode;
            tempQueueNode = nextQueueNode;
        }
        std::cout << "Queue deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    void enqueue(QueueType data);
    QueueType dequeue();
    QueueType peek();
    void display();
};

// Method to check if the queue is empty
template <typename QueueType>
bool Queue<QueueType>::isEmpty() {
    if (this->queueSize == 0)
        return true;
    else
        return false;
}

// Method to enqueue an element into the queue
template <typename QueueType>
void Queue<QueueType>::enqueue(QueueType data) {
    QueueNode<QueueType> *newQueueNode = new QueueNode<QueueType>;
    newQueueNode->data = data;
    newQueueNode->next = nullptr;

    if (this->isEmpty()) {
        // If the queue is empty, the new node is both the front and rear node
        this->frontQueueNode = newQueueNode;
        this->rearQueueNode = newQueueNode;
    } else {
        // If the queue is not empty, the new node is the new rear node
        this->rearQueueNode->next = newQueueNode;
        this->rearQueueNode = newQueueNode;
    }

    this->queueSize += 1;
}

// Method to dequeue an element from the queue
template <typename QueueType>
QueueType Queue<QueueType>::dequeue() {
    if (this->isEmpty())
        throw std::underflow_error("Queue is empty, so can't dequeue");

    // Because front node will be removed during dequeue, we need to keep the front node
    QueueNode<QueueType> *tempQueueNode = this->frontQueueNode;

    QueueType data = tempQueueNode->data;
    this->frontQueueNode = this->frontQueueNode->next;
    delete tempQueueNode;
    this->queueSize -= 1;

    return data;
}

// Method to peek the front element of the queue
template <typename QueueType>
QueueType Queue<QueueType>::peek() {
    if (this->isEmpty())
        throw std::underflow_error("Queue is empty, so can't peek");

    return this->frontQueueNode->data;
}

// Method to display the queue
template <typename QueueType>
void Queue<QueueType>::display() {
    if (this->isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }

    // From the first node, traverse each node until the last node in the given queue
    QueueNode<QueueType> *tempQueueNode = this->frontQueueNode;
    while (tempQueueNode != nullptr) {
        // case-by-case handlilng for "->" separator
        if (tempQueueNode->next == nullptr)
            std::cout << tempQueueNode->data;
        else
            std::cout << tempQueueNode->data << " -> ";
        tempQueueNode = tempQueueNode->next;
    }
    std::cout << std::endl;
}

int main(void) {
    Queue<std::string> queue;

    queue.enqueue("Alpha");
    queue.enqueue("Bravo");
    queue.enqueue("Charlie");
    queue.enqueue("Delta");
    queue.enqueue("Echo"); 
    queue.display();

    queue.dequeue();
    queue.display();

    queue.enqueue("Foxtrot");
    queue.display();

    queue.dequeue();
    queue.display();

    std::cout << "Front element: " << queue.peek() << std::endl;

    return 0;
}