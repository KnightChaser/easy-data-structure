/**
 * @file queue_basic_with_node.c
 * @brief Basic queue implementation in C using a node (list)
 *        Because the queue is implemented using a node, the queue can grow dynamically.
 *        Thus, there is no need to specify the queue size or consider the queue full condition.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

typedef char QueueElement;

typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* next;     // Pointer to the next node
} QueueNode;

typedef struct Queue {
    QueueNode* frontQueueNode;
    QueueNode* rearQueueNode;
    unsigned int queueSize;     // Number of elements in the queue
} Queue;


// Initialize the queue
void initializeQueue(Queue *queue) {
    queue->frontQueueNode = NULL;
    queue->rearQueueNode = NULL;
    queue->queueSize = 0;
}

// Check if the queue is empty
bool isQueueEmpty(Queue *queue) {
    if (queue->queueSize == 0)
        return true;
    else
        return false;
}

// Enqueue an element (add an element to the queue)
void enqueue(Queue *queue, const QueueElement data) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->data = data;
    newQueueNode->next = NULL;

    if (isQueueEmpty(queue)) {
        // If the queue is empty, the new node is both the front and rear node
        queue->frontQueueNode = newQueueNode;
        queue->rearQueueNode = newQueueNode;
    } else {
        // If the queue is not empty, add the new node to the rear of the queue
        queue->rearQueueNode->next = newQueueNode;
        queue->rearQueueNode = newQueueNode;
    }

    queue->queueSize += 1;
}

// Dequeue an element (remove an element from the queue)
QueueElement dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty, so can't dequeue\n");
        exit(-1);
    }

    // Because front node will be removed during dequeue, we need to keep the front node
    QueueNode* tempQueueNode = queue->frontQueueNode;
    
    QueueElement data;
    data = tempQueueNode->data;
    queue->frontQueueNode = tempQueueNode->next;
    free(tempQueueNode);
    queue->queueSize -= 1;

    return data;
}

// Peek the front element of the queue
QueueElement peek(Queue *queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty, so can't peek\n");
        exit(-1);
    }

    return queue->frontQueueNode->data;
}

// Print the queue
void printQueue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    QueueNode* tempQueueNode = queue->frontQueueNode;
    while (tempQueueNode != NULL) {
        printf("%c%s", tempQueueNode->data, (tempQueueNode->next != NULL) ? " -> " : " ");
        tempQueueNode = tempQueueNode->next;
    }
    printf("\n");
}

// Delete the queue
void deleteQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
    printf("The queue is completely deleted\n");
}

int main(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    initializeQueue(queue);

    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    printQueue(queue);

    dequeue(queue);
    printQueue(queue);

    enqueue(queue, 'D');
    printQueue(queue);

    dequeue(queue);
    printQueue(queue);

    enqueue(queue, 'E');
    printQueue(queue);

    enqueue(queue, 'F');
    printQueue(queue);

    printf("Peek: %c\n", peek(queue));

    deleteQueue(queue);

    return 0;
}

// A -> B -> C 
// B -> C
// B -> C -> D
// C -> D
// C -> D -> E
// C -> D -> E -> F
// Peek: C
// The queue is completely deleted