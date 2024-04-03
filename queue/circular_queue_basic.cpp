/**
 * @file circular_queue_basic.cpp
 * @brief A basic implementation of circular queue, written in C++.
 *        C++ version of circular_queue_basic.c
 *        To strictly follow that the queue size is fixed, we use a constant to define the queue size rather than std::vector.
 */
//

#include <iostream>
#include <cstring>
#include <stdexcept>

template <typename CircularQueueType>
class CircularQueue {
private:
    unsigned int queueFrontIndex;
    unsigned int queueRearIndex;
    unsigned int queueSize;
    CircularQueueType *circularQueueArray;
public:
    // Constructor of the circular queue class, initializes the circular queue
    CircularQueue(unsigned int size) {
        this->queueFrontIndex = 0;
        this->queueRearIndex = 0;
        this->queueSize = size;
        this->circularQueueArray = new CircularQueueType[size]();   // Initialize the circular queue with 0
    }

    // Destructor of the circular queue class, deletes the circular queue
    ~CircularQueue() {
        delete[] this->circularQueueArray;
        std::cout << "Circular Queue deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    bool isFull();
    void enqueue(CircularQueueType data);
    CircularQueueType dequeue();
    CircularQueueType peek();
    void display();
};

// Method to check if the circular queue is empty
template <typename CircularQueueType>
bool CircularQueue<CircularQueueType>::isEmpty() {
    if (this->queueFrontIndex == this->queueRearIndex)
        return true;
    else
        return false;
}

// Method to check if the circular queue is full
template <typename CircularQueueType>
bool CircularQueue<CircularQueueType>::isFull() {
    if ((this->queueRearIndex + 1) % this->queueSize == this->queueFrontIndex)
        return true;
    else
        return false;
}

// Method to insert an element into the circular queue (enqueue operation)
template <typename CircularQueueType>
void CircularQueue<CircularQueueType>::enqueue(CircularQueueType data) {
    if (this->isFull()) {
        throw std::overflow_error("Queue is full, can't enqueue more elements");
    } else {
        this->queueRearIndex = (this->queueRearIndex + 1) % this->queueSize;
        this->circularQueueArray[this->queueRearIndex] = data;
    }
}

// Method to remove an element from the circular queue (dequeue operation)
template <typename CircularQueueType>
CircularQueueType CircularQueue<CircularQueueType>::dequeue() {
    CircularQueueType data = 0;
    if (this->isEmpty()) {
        throw std::overflow_error("Queue is empty, can't dequeue more elements");
    } else {
        this->queueFrontIndex = (this->queueFrontIndex + 1) % this->queueSize;
        data = this->circularQueueArray[this->queueFrontIndex];
        memset(&this->circularQueueArray[this->queueFrontIndex], 0, sizeof(CircularQueueType));    // Clear the data to make it empty clearly
    }

    return data;
}

// Method to get the front element of the circular queue (peek operation)
template <typename CircularQueueType>
CircularQueueType CircularQueue<CircularQueueType>::peek() {
    if (this->isEmpty()) {
        throw std::underflow_error("Queue is empty, can't peek more elements");
    } else {
        return this->circularQueueArray[(this->queueFrontIndex + 1) % this->queueSize];
    }
}

// Method to display the circular queue
template <typename CircularQueueType>
void CircularQueue<CircularQueueType>::display() {
    std::cout << "... -> |";
    for (size_t index = 0; index < this->queueSize; index++) {
        CircularQueueType data = this->circularQueueArray[index];
        if (data != 0) {
            std::cout << " " << data << " |";
        } else {
            std::cout << "   |";
        }
    }
    std::cout << " -> ..." << std::endl;
}

int main(void) {
    try {
        CircularQueue<char> circularQueue(10);

        // Enqueue some elements into the circular queue
        char elements[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        for (size_t index = 0; index < sizeof(elements) / sizeof(elements[0]); index++) {
            circularQueue.enqueue(elements[index]);
            circularQueue.display();
        }

        // Now enqueue and dequeue some elements alternatively
        char newElements[] = {'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q'};
        for (size_t index = 0; index < sizeof(newElements) / sizeof(newElements[0]); index++) {
            circularQueue.enqueue(newElements[index]);
            circularQueue.display();
            circularQueue.dequeue();
            circularQueue.display();
        }

        // Peek the front element of the circular queue
        std::cout << "Front element of the circular queue: " << circularQueue.peek() << std::endl;
    } catch (const std::exception &exception) {
        std::cerr << "Got an exception during playing with a circular queue: " <<  exception.what() << std::endl;
    }

    return 0;
}

// ... -> |   | A |   |   |   |   |   |   |   |   | -> ...
// ... -> |   | A | B |   |   |   |   |   |   |   | -> ...
// ... -> |   | A | B | C |   |   |   |   |   |   | -> ...
// ... -> |   | A | B | C | D |   |   |   |   |   | -> ...
// ... -> |   | A | B | C | D | E |   |   |   |   | -> ...
// ... -> |   | A | B | C | D | E | F |   |   |   | -> ...
// ... -> |   | A | B | C | D | E | F | G |   |   | -> ...
// ... -> |   | A | B | C | D | E | F | G | H |   | -> ...
// ... -> |   | A | B | C | D | E | F | G | H | J | -> ...
// ... -> |   |   | B | C | D | E | F | G | H | J | -> ...
// ... -> | K |   | B | C | D | E | F | G | H | J | -> ...
// ... -> | K |   |   | C | D | E | F | G | H | J | -> ...
// ... -> | K | L |   | C | D | E | F | G | H | J | -> ...
// ... -> | K | L |   |   | D | E | F | G | H | J | -> ...
// ... -> | K | L | M |   | D | E | F | G | H | J | -> ...
// ... -> | K | L | M |   |   | E | F | G | H | J | -> ...
// ... -> | K | L | M | N |   | E | F | G | H | J | -> ...
// ... -> | K | L | M | N |   |   | F | G | H | J | -> ...
// ... -> | K | L | M | N | O |   | F | G | H | J | -> ...
// ... -> | K | L | M | N | O |   |   | G | H | J | -> ...
// ... -> | K | L | M | N | O | P |   | G | H | J | -> ...
// ... -> | K | L | M | N | O | P |   |   | H | J | -> ...
// ... -> | K | L | M | N | O | P | Q |   | H | J | -> ...
// ... -> | K | L | M | N | O | P | Q |   |   | J | -> ...
// Front element of the circular queue: J
// Circular Queue deleted