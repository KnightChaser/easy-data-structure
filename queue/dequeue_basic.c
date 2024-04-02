/*
 * @file dequeue_basic.c
 * @brief Basic dequeue implementation in C
 *        To provide more availability, this implementation is based on a circular queue
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

typedef char DequeueElement;
typedef struct {
    unsigned int dequeueFrontIndex;
    unsigned int dequeueRearIndex;
    unsigned int dequeueSize;
    DequeueElement* dequeueElements;
} Dequeue;

// Initialize the dequeue
void initializeDequeue(Dequeue *dequeue, const unsigned int dequeueSize) {
    dequeue->dequeueFrontIndex = 0;
    dequeue->dequeueRearIndex = 0;
    dequeue->dequeueSize = dequeueSize;

    // Allocate memory for the dequeue elements
    dequeue->dequeueElements = (DequeueElement*)malloc(dequeueSize * sizeof(DequeueElement));
    memset(dequeue->dequeueElements, 0, dequeueSize * sizeof(DequeueElement));
}

// Check if the dequeue is empty
bool isDequeueEmpty(Dequeue *dequeue) {
    if (dequeue->dequeueFrontIndex == dequeue->dequeueRearIndex)
        return true;
    else
        return false;
}

// Check if the dequeue is full
bool isDequeueFull(Dequeue *dequeue) {
    if ((dequeue->dequeueRearIndex + 1) % dequeue->dequeueSize == dequeue->dequeueFrontIndex)
        return true;
    else
        return false;
}

// Enqueue an element at the front of the dequeue
void enqueueFront(Dequeue *dequeue, const DequeueElement data) {
    if (isDequeueFull(dequeue)) {
        fprintf(stderr, "Dequeue is full, so can't enqueue at the front\n");
        exit(-1);
    }

    dequeue->dequeueFrontIndex = (dequeue->dequeueFrontIndex - 1 + dequeue->dequeueSize) % dequeue->dequeueSize;
    dequeue->dequeueElements[dequeue->dequeueFrontIndex] = data;
}

// Enqueue an element at the rear of the dequeue
void enqueueRear(Dequeue *dequeue, const DequeueElement data) {
    if (isDequeueFull(dequeue)) {
        fprintf(stderr, "Dequeue is full, so can't enqueue at the rear\n");
        exit(-1);
    }

    dequeue->dequeueElements[dequeue->dequeueRearIndex] = data;
    dequeue->dequeueRearIndex = (dequeue->dequeueRearIndex + 1) % dequeue->dequeueSize;
}

// Dequeue an element from the front of the dequeue
DequeueElement dequeueFront(Dequeue *dequeue) {
    if (isDequeueEmpty(dequeue)) {
        fprintf(stderr, "Dequeue is empty, so can't dequeue from the front\n");
        exit(-1);
    }

    DequeueElement data = dequeue->dequeueElements[dequeue->dequeueFrontIndex];
    memset(&dequeue->dequeueElements[dequeue->dequeueFrontIndex], 0, sizeof(DequeueElement));     // Invalidate the dequeued element
    dequeue->dequeueFrontIndex = (dequeue->dequeueFrontIndex + 1) % dequeue->dequeueSize;
    return data;
}

// Dequeue an element from the rear of the dequeue
DequeueElement dequeueRear(Dequeue *dequeue) {
    if (isDequeueEmpty(dequeue)) {
        fprintf(stderr, "Dequeue is empty, so can't dequeue from the rear\n");
        exit(-1);
    }

    dequeue->dequeueRearIndex = (dequeue->dequeueRearIndex - 1 + dequeue->dequeueSize) % dequeue->dequeueSize;
    memset(&dequeue->dequeueElements[dequeue->dequeueRearIndex], 0, sizeof(DequeueElement));     // Invalidate the dequeued element
    DequeueElement data = dequeue->dequeueElements[dequeue->dequeueRearIndex];
    return data;
}

// Peek the front element of the dequeue
DequeueElement peekFront(Dequeue *dequeue) {
    if (isDequeueEmpty(dequeue)) {
        fprintf(stderr, "Dequeue is empty, so can't peek the front element\n");
        exit(-1);
    }

    return dequeue->dequeueElements[(dequeue->dequeueFrontIndex + 1) % dequeue->dequeueSize];
}

// Peek the rear element of the dequeue
DequeueElement peekRear(Dequeue *dequeue) {
    if (isDequeueEmpty(dequeue)) {
        fprintf(stderr, "Dequeue is empty, so can't peek the rear element\n");
        exit(-1);
    }

    return dequeue->dequeueElements[(dequeue->dequeueRearIndex - 1 + dequeue->dequeueSize) % dequeue->dequeueSize];
}

// Display the dequeue
void displayDequeue(Dequeue *dequeue) {
    printf("... -> |");
    for (size_t index = 0; index < dequeue->dequeueSize; index++) {
        printf(" %c |", dequeue->dequeueElements[index] ? dequeue->dequeueElements[index] : ' ');
    }
    printf(" -> ...\n");
}

// Clear the dequeue
void clearDequeue(Dequeue *dequeue) {
    printf("Clearing the dequeue(address: 0x%p)\n", (void *)dequeue);
    free(dequeue->dequeueElements);
    dequeue->dequeueElements = NULL;
    dequeue->dequeueFrontIndex = 0;
    dequeue->dequeueRearIndex = 0;
    dequeue->dequeueSize = 0;
}

int main(void) {
    Dequeue dequeue;
    initializeDequeue(&dequeue, 10);

    displayDequeue(&dequeue);

    // Doing some operations...
    enqueueFront(&dequeue, 'A');
    displayDequeue(&dequeue);
    enqueueRear(&dequeue, 'B');
    displayDequeue(&dequeue);
    enqueueFront(&dequeue, 'C');
    displayDequeue(&dequeue);
    enqueueRear(&dequeue, 'D');
    displayDequeue(&dequeue);
    enqueueFront(&dequeue, 'E');
    displayDequeue(&dequeue);
    enqueueRear(&dequeue, 'F');
    displayDequeue(&dequeue);
    enqueueFront(&dequeue, 'G');
    displayDequeue(&dequeue);
    enqueueRear(&dequeue, 'H');
    displayDequeue(&dequeue);

    dequeueFront(&dequeue);
    displayDequeue(&dequeue);
    dequeueRear(&dequeue);
    displayDequeue(&dequeue);
    dequeueFront(&dequeue);
    displayDequeue(&dequeue);
    dequeueRear(&dequeue);
    displayDequeue(&dequeue);
    dequeueFront(&dequeue);
    displayDequeue(&dequeue);
    dequeueRear(&dequeue);
    displayDequeue(&dequeue);
    dequeueRear(&dequeue);
    displayDequeue(&dequeue);
    dequeueFront(&dequeue);
    displayDequeue(&dequeue);
    
    
    clearDequeue(&dequeue);

    return 0;
}

// ... -> |   |   |   |   |   |   |   |   |   |   | -> ...
// ... -> |   |   |   |   |   |   |   |   |   | A | -> ...
// ... -> | B |   |   |   |   |   |   |   |   | A | -> ...
// ... -> | B |   |   |   |   |   |   |   | C | A | -> ...
// ... -> | B | D |   |   |   |   |   |   | C | A | -> ...
// ... -> | B | D |   |   |   |   |   | E | C | A | -> ...
// ... -> | B | D | F |   |   |   |   | E | C | A | -> ...
// ... -> | B | D | F |   |   |   | G | E | C | A | -> ...
// ... -> | B | D | F | H |   |   | G | E | C | A | -> ...
// ... -> | B | D | F | H |   |   |   | E | C | A | -> ...
// ... -> | B | D | F |   |   |   |   | E | C | A | -> ...
// ... -> | B | D | F |   |   |   |   |   | C | A | -> ...
// ... -> | B | D |   |   |   |   |   |   | C | A | -> ...
// ... -> | B | D |   |   |   |   |   |   |   | A | -> ...
// ... -> | B |   |   |   |   |   |   |   |   | A | -> ...
// ... -> |   |   |   |   |   |   |   |   |   | A | -> ...
// ... -> |   |   |   |   |   |   |   |   |   |   | -> ...
// Clearing the dequeue(address: 0x00000005fa1ffb60)