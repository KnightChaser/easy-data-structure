/*
 * @file circular_queue_basic.c
 * @brief A basic implementation of circular queue, written in C language
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

typedef char CircularQueueElement;
typedef struct {
    unsigned int queueFrontIndex;
    unsigned int queueRearIndex;
    unsigned int queueSize;
    CircularQueueElement* queueElements;
} CircularQueue;

// Initialize the circular queue
void initializeCircularQueue(CircularQueue *circularQueue, const unsigned int queueSize) {
    circularQueue->queueFrontIndex = 0;
    circularQueue->queueRearIndex = 0;
    circularQueue->queueSize = queueSize;

    // Allocate memory for the circular queue elements and rsset the memory
    circularQueue->queueElements = (CircularQueueElement *)malloc(queueSize * sizeof(CircularQueueElement));
    memset(circularQueue->queueElements, 0, queueSize * sizeof(CircularQueueElement));
}

// Check if the circular queue is empty
bool isCircularQueueEmpty(CircularQueue *circularQueue) {
    if (circularQueue->queueFrontIndex == circularQueue->queueRearIndex)
        return true;
    else
        return false;
}

// Check if the circular queue is full
// To distiniguish between empty and full, we need to keep one slot empty.
// (If the front and rear indices are equal, the queue might be empty or full, so we need to keep one slot empty to distinguish between them.)
bool isCircularQueueFull(CircularQueue *circularQueue) {
    if ((circularQueue->queueRearIndex + 1) % circularQueue->queueSize == circularQueue->queueFrontIndex)
        return true;
    else
        return false;
}

// Enqueue an element (add an element to the circular queue)
void enqueueCircularQueue(CircularQueue *circularQueue, const CircularQueueElement data) {
    if (isCircularQueueFull(circularQueue)) {
        fprintf(stderr, "Circular queue is full, so can't enqueue\n");
        exit(-1);
    }

    circularQueue->queueRearIndex = (circularQueue->queueRearIndex + 1) % circularQueue->queueSize;     // Because it's a circular queue
    circularQueue->queueElements[circularQueue->queueRearIndex] = data;
}

// Dequeue an element (remove an element from the circular queue)
CircularQueueElement dequeueCircularQueue(CircularQueue *circularQueue) {
    if (isCircularQueueEmpty(circularQueue)) {
        fprintf(stderr, "Circular queue is empty, so can't dequeue\n");
        exit(-1);
    }

    circularQueue->queueFrontIndex = (circularQueue->queueFrontIndex + 1) % circularQueue->queueSize;   // Because it's a circular queue
    CircularQueueElement data = circularQueue->queueElements[circularQueue->queueFrontIndex];
    memset(circularQueue->queueElements + circularQueue->queueFrontIndex, 0, sizeof(CircularQueueElement)); // Reset the memory to make it empty
    return data;
}

// Peek the front element of the circular queue, not popping it actually
CircularQueueElement peekCircularQueue(CircularQueue *circularQueue) {
    if (isCircularQueueEmpty(circularQueue)) {
        fprintf(stderr, "Circular queue is empty, so can't peek\n");
        exit(-1);
    }

    return circularQueue->queueElements[(circularQueue->queueFrontIndex + 1) % circularQueue->queueSize];
}

// Clear the circular queue
void clearCircularQueue(CircularQueue *circularQueue) {
    printf("Clearing the circular queue(address: 0x%p)\n", (void *)circularQueue);
    free(circularQueue->queueElements);
    circularQueue->queueElements = NULL;
    circularQueue->queueFrontIndex = 0;
    circularQueue->queueRearIndex = 0;
    circularQueue->queueSize = 0;
}

// Print the entire circular queue elements in pretty format
void displayCircularQueue(CircularQueue *circularQueue) {
    printf("... -> |");
    for (size_t index = 0; index < circularQueue->queueSize; index++) {
        printf(" %c |", circularQueue->queueElements[index] ? circularQueue->queueElements[index] : ' ');
    }
    printf(" -> ...\n");
}

int main(void) {
    CircularQueue circularQueue;
    initializeCircularQueue(&circularQueue, 10);

    // Enqueue elements
    char elements[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    for (size_t index = 0; index < sizeof(elements) / sizeof(elements[0]); index++) {
        enqueueCircularQueue(&circularQueue, elements[index]);
        displayCircularQueue(&circularQueue);
    }

    // Dequeue and enqueue elements
    char newElements[] = {'J', 'K', 'L', 'M', 'N', 'O'};

    for (size_t index = 0; index < sizeof(newElements) / sizeof(newElements[0]); index++) {
        dequeueCircularQueue(&circularQueue);
        displayCircularQueue(&circularQueue);

        enqueueCircularQueue(&circularQueue, newElements[index]);
        displayCircularQueue(&circularQueue);
    }

    clearCircularQueue(&circularQueue);
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
// ... -> |   | A | B | C | D | E | F | G | H | I | -> ...
// ... -> |   |   | B | C | D | E | F | G | H | I | -> ...
// ... -> | J |   | B | C | D | E | F | G | H | I | -> ...
// ... -> | J |   |   | C | D | E | F | G | H | I | -> ...
// ... -> | J | K |   | C | D | E | F | G | H | I | -> ...
// ... -> | J | K |   |   | D | E | F | G | H | I | -> ...
// ... -> | J | K | L |   | D | E | F | G | H | I | -> ...
// ... -> | J | K | L |   |   | E | F | G | H | I | -> ...
// ... -> | J | K | L | M |   | E | F | G | H | I | -> ...
// ... -> | J | K | L | M |   |   | F | G | H | I | -> ...
// ... -> | J | K | L | M | N |   | F | G | H | I | -> ...
// ... -> | J | K | L | M | N |   |   | G | H | I | -> ...
// ... -> | J | K | L | M | N | O |   | G | H | I | -> ...
// Clearing the circular queue(address: 0x00000094c8fff980)