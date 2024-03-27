/*
 * @file queue_basic.c
 * @brief Basic queue implementation in C
 */
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

typedef char QueueElement;
typedef struct {
    int queueFrontIndex;
    int queueRearIndex;
    int queueSize;
    QueueElement* queueElements;
} Queue;

// Initialize the queue
void initializeQueue(Queue *queue, const int queueSize) {
    queue->queueFrontIndex = -1;
    queue->queueRearIndex = -1;
    queue->queueSize = queueSize;

    // Allocate memory for the queue elements
    queue->queueElements = (QueueElement*)malloc(queueSize * sizeof(QueueElement));
    memset(queue->queueElements, 0, queueSize * sizeof(QueueElement));
}

// Check if the queue is empty
bool isQueueEmpty(Queue *queue) {
    if (queue->queueFrontIndex == queue->queueRearIndex)
        return true;
    else
        return false;
}

// Check if the queue is full
bool isQueueFull(Queue *queue) {
    if (queue->queueRearIndex == queue->queueSize - 1)
        return true;
    else
        return false;
}

// Enqueue an element (add an element to the queue)
void enqueue(Queue *queue, const QueueElement data) {
    if (isQueueFull(queue)) {
        fprintf(stderr, "Queue is full, so can't enqueue\n");
        exit(-1);
    }
    queue->queueRearIndex++;
    queue->queueElements[queue->queueRearIndex] = data;
}

// Dequeue an element (remove an element from the queue)
QueueElement dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty, so can't dequeue\n");
        exit(-1);
    }

    queue->queueFrontIndex++;
    QueueElement data = queue->queueElements[queue->queueFrontIndex];
    memset(&queue->queueElements[queue->queueFrontIndex], 0, sizeof(QueueElement));     // Invalidate the dequeued element
    return data;
}


// Peek the front element of the queue
QueueElement peek(Queue *queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty, so can't peek\n");
        exit(-1);
    }
    // +1 because the front element is at the next index of the front index
    return queue->queueElements[queue->queueFrontIndex + 1];
}

// Display the queue elements on the console
void displayQueue(Queue *queue) {
    printf("| ");
    for (int index = 0; index <= queue->queueSize - 1; index++) {
        // Print the queue element if it is in the valid range
        if (index >= queue->queueFrontIndex && index <= queue->queueRearIndex) {
            printf("%c | ", queue->queueElements[index] ? queue->queueElements[index] : ' ');
        } else {
            printf("  | ");
        }
    }
    printf("\n");
}

int main(void) {
    Queue queue;
    initializeQueue(&queue, 10);

    // Enqueue elements
    enqueue(&queue, 'A');
    enqueue(&queue, 'B');
    enqueue(&queue, 'C');
    enqueue(&queue, 'D');
    enqueue(&queue, 'E');
    displayQueue(&queue);

    // Dequeue and enqueue elements
    dequeue(&queue);
    displayQueue(&queue);

    enqueue(&queue, 'F');
    displayQueue(&queue);

    dequeue(&queue);
    displayQueue(&queue);

    enqueue(&queue, 'G');
    displayQueue(&queue);

    // Peek the front element
    printf("Peek: %c\n", peek(&queue));

    return 0;
}