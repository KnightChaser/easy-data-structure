/**
 * @file queue_basic.cpp
 * @brief Basic queue implementation in C++ (queue_basic.c)
 */
//

#include <iostream>
#include <cstring>

template <typename QueueType>
class Queue {
private:
    int queueFrontIndex;
    int queueRearIndex;
    int queueSize;
    QueueType *queueArray;
public:
    // Constructor of the queue class, initializes the queue
    Queue(int size) {
        this->queueFrontIndex = -1;
        this->queueRearIndex = -1;
        this->queueSize = size;
        this->queueArray = new QueueType[size]();   // Initialize the queue with 0
    }

    // Destructor of the queue class, deletes the queue
    ~Queue() {
        delete[] this->queueArray;
        std::cout << "Queue deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    bool isFull();
    void enqueue(QueueType data);
    QueueType dequeue();
    QueueType peek();
    void display();
};

// Method to check if the queue is empty
template <typename QueueType>
bool Queue<QueueType>::isEmpty() {
    if (this->queueFrontIndex == this->queueRearIndex)
        return true;
    else
        return false;
}

// Method to check if the queue is full
template <typename QueueType>
bool Queue<QueueType>::isFull() {
    if (this->queueRearIndex == this->queueSize - 1)
        return true;
    else
        return false;
}

// Method to enquque an element into the queue
template <typename QueueType>
void Queue<QueueType>::enqueue(QueueType data) {
    if (this->isFull())
        throw std::overflow_error("Queue is full, can't enqueue more.");

    this->queueRearIndex += 1;
    this->queueArray[this->queueRearIndex] = data;
}

// Method to dequeue an element from the queue
template <typename QueueType>
QueueType Queue<QueueType>::dequeue() {
    if (this->isEmpty())
        throw std::underflow_error("Queue is empty, can't dequeue more.");

    this->queueFrontIndex += 1;
    QueueType data = this->queueArray[this->queueFrontIndex];
    memset(&this->queueArray[this->queueFrontIndex], 0, sizeof(QueueType));     // Invalidate the dequeued element
    return data;
}

// Method to peek the front element of the queue
template <typename QueueType>
QueueType Queue<QueueType>::peek() {
    if (this->isEmpty())
        throw std::underflow_error("Queue is empty, can't peek.");

    return this->queueArray[this->queueFrontIndex + 1];
}

// Method to display the queue
template <typename QueueType>
void Queue<QueueType>::display() {
    std::cout << "| ";
    for (int index = 0; index < this->queueSize; index++) {
        // Print the queue element if it is in the valid range. If not, print empty space
        if (index >= this->queueFrontIndex && index <= this->queueRearIndex)
            if (this->queueArray[index])
                std::cout << this->queueArray[index] << " | ";
            else
                std::cout << "  | ";
        else
            std::cout << "  | ";
    }
    std::cout << std::endl;
}

int main(void) {
    Queue<char> queue(10);

    // Enqueue elements
    queue.enqueue('A');
    queue.enqueue('B');
    queue.enqueue('C');
    queue.enqueue('D');
    queue.enqueue('E');
    queue.display();

    // Dequeue and enqueue elements
    queue.dequeue();
    queue.display();

    queue.enqueue('F');
    queue.display();

    queue.dequeue();
    queue.display();

    queue.enqueue('G');
    queue.display();

    // Peek the front element
    std::cout << "Front element: " << queue.peek() << std::endl;

    // Queue will be automatically deleted by its destructor
    return 0;
}

// | A | B | C | D | E |   |   |   |   |   | 
// |   | B | C | D | E |   |   |   |   |   |
// |   | B | C | D | E | F |   |   |   |   |
// |   |   | C | D | E | F |   |   |   |   |
// |   |   | C | D | E | F | G |   |   |   |
// Front element: C
// Queue deleted