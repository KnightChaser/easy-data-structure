/*
 * @file dequeue_basic.cpp
 * @brief An implementation of dequeue using C++ STL, C++ version of dequeue_basic.c
 *        To provide more availability, we use circular queue to implement dequeue.
 */
//

#include <cstddef>
#include <iostream>
#include <cstring>
#include <stdexcept>

template <typename DequeueElement>
class Dequeue {
private:
    unsigned int frontIndex;
    unsigned int rearIndex;
    unsigned int dequeueSize;
    DequeueElement* dequeueArray;
public:
    // Constructor of the dequeue class, initializes the dequeue
    Dequeue(unsigned int size) {
        this->frontIndex = 0;
        this->rearIndex = 0;
        this->dequeueSize = size;
        this->dequeueArray = new DequeueElement[size]();   // Initialize the dequeue with 0
    }

    // Destructor of the dequeue class, deletes the dequeue
    ~Dequeue() {
        delete[] this->dequeueArray;
        std::cout << "Dequeue deleted" << std::endl;
    }

    // Methods
    bool isEmpty();
    bool isFull();
    void enqueueFront(DequeueElement data);
    void enqueueRear(DequeueElement data);
    DequeueElement dequeueFront();
    DequeueElement dequeueRear();
    DequeueElement peekFront();
    DequeueElement peekRear();
    void display();
};

// Check if the dequeue is empty
template <typename DequeueElement>
bool Dequeue<DequeueElement>::isEmpty() {
    if (this->frontIndex == this->rearIndex)
        return true;
    else
        return false;
}

// Check if the dequeue is full
template <typename DequeueElement>
bool Dequeue<DequeueElement>::isFull() {
    if ((this->rearIndex + 1) % this->dequeueSize == this->frontIndex)
        return true;
    else
        return false;
}

// Insert an element at the front of the dequeue (enqueue at front)
template <typename DequeueElement>
void Dequeue<DequeueElement>::enqueueFront(DequeueElement data) {
    if (this->isFull()) {
        throw std::overflow_error("Dequeue is full, can't enqueue more elements");
    }
    this->frontIndex = (this->frontIndex - 1 + this->dequeueSize) % this->dequeueSize;
    this->dequeueArray[this->frontIndex] = data;
}

// Insert an element at the rear of the dequeue (enqueue at rear)
template <typename DequeueElement>
void Dequeue<DequeueElement>::enqueueRear(DequeueElement data) {
    if (this->isFull()) {
        throw std::overflow_error("Dequeue is full, can't enqueue more elements");
    }
    this->rearIndex = (this->rearIndex + 1) % this->dequeueSize;
    this->dequeueArray[this->rearIndex] = data;
}

// Remove an element from the front of the dequeue (dequeue from front)
template <typename DequeueElement>
DequeueElement Dequeue<DequeueElement>::dequeueFront() {
    if (this->isEmpty()) {
        throw std::underflow_error("Dequeue is empty, can't dequeue more elements");
    }
   DequeueElement data = this->dequeueArray[this->frontIndex];
    memset(&this->dequeueArray[this->frontIndex], 0, sizeof(DequeueElement));    // Invalidate the dequeued data
    this->frontIndex = (this->frontIndex + 1) % this->dequeueSize;
    return data;
}

// Remove an element from the rear of the dequeue (dequeue from rear)
template <typename DequeueElement>
DequeueElement Dequeue<DequeueElement>::dequeueRear() {
    if (this->isEmpty()) {
        throw std::underflow_error("Dequeue is empty, can't dequeue more elements");
    }
    DequeueElement data = this->dequeueArray[this->rearIndex];
    memset(&this->dequeueArray[this->rearIndex], 0, sizeof(DequeueElement));    // Invalidate the dequeued data
    this->rearIndex = (this->rearIndex - 1 + this->dequeueSize) % this->dequeueSize;
    return data;
}

// Get the front element of the dequeue (peek from front)
template <typename DequeueElement>
DequeueElement Dequeue<DequeueElement>::peekFront() {
    if (this->isEmpty()) {
        throw std::underflow_error("Dequeue is empty, can't peek more elements");
    }
    return this->dequeueArray[this->frontIndex];
}

// Get the rear element of the dequeue (peek from rear)
template <typename DequeueElement>
DequeueElement Dequeue<DequeueElement>::peekRear() {
    if (this->isEmpty()) {
        throw std::underflow_error("Dequeue is empty, can't peek more elements");
    }
    return this->dequeueArray[(this->rearIndex - 1 + this->dequeueSize) % this->dequeueSize];
}

// Display the dequeue
template <typename DequeueElement>
void Dequeue<DequeueElement>::display() {
    std::cout << "... -> |";
    for (size_t index = 0; index < this->dequeueSize; index++) {
        // If the element is not 0(NULL = empty), print it, else print empty space
        if (this->dequeueArray[index] != 0) {
            std::cout << " " << this->dequeueArray[index] << " |";
        } else {
            std::cout << "   |";
        }
    }
    std::cout << " -> ..." << std::endl;
}

int main(void) {
    Dequeue<char> dequeue(10);
    dequeue.display();
    
    try {

        // Enqueuing data to the dequeue from front and rear alternatively
        dequeue.enqueueFront('A');
        dequeue.display();
        dequeue.enqueueRear('B');
        dequeue.display();
        dequeue.enqueueFront('C');
        dequeue.display();
        dequeue.enqueueRear('D');
        dequeue.display();
        dequeue.enqueueFront('E');
        dequeue.display();
        dequeue.enqueueRear('F');
        dequeue.display();
        dequeue.enqueueFront('G');
        dequeue.display();
        dequeue.enqueueRear('H');
        dequeue.display();

        // Dequeuing data from the dequeue from front and rear alternatively
        for (size_t index = 0; index < 4; index++) {
            dequeue.dequeueFront();
            dequeue.display();
            dequeue.dequeueRear();
            dequeue.display();
        }
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}

// ... -> |   |   |   |   |   |   |   |   |   |   | -> ...
// ... -> |   |   |   |   |   |   |   |   |   | A | -> ...
// ... -> |   | B |   |   |   |   |   |   |   | A | -> ...
// ... -> |   | B |   |   |   |   |   |   | C | A | -> ...
// ... -> |   | B | D |   |   |   |   |   | C | A | -> ...
// ... -> |   | B | D |   |   |   |   | E | C | A | -> ...
// ... -> |   | B | D | F |   |   |   | E | C | A | -> ...
// ... -> |   | B | D | F |   |   | G | E | C | A | -> ...
// ... -> |   | B | D | F | H |   | G | E | C | A | -> ...
// ... -> |   | B | D | F | H |   |   | E | C | A | -> ...
// ... -> |   | B | D | F |   |   |   | E | C | A | -> ...
// ... -> |   | B | D | F |   |   |   |   | C | A | -> ...
// ... -> |   | B | D |   |   |   |   |   | C | A | -> ...
// ... -> |   | B | D |   |   |   |   |   |   | A | -> ...
// ... -> |   | B |   |   |   |   |   |   |   | A | -> ...
// ... -> |   | B |   |   |   |   |   |   |   |   | -> ...
// ... -> |   |   |   |   |   |   |   |   |   |   | -> ...
// Dequeue deleted