/**
 * @file queue_basic_with_node_polymorphism.c
 * @brief Basic queue implementation in C using a node (list) with polymorphism.
 *        Because the queue is implemented using a node, the queue can grow dynamically.
 *        To provide polymorphism, the data type of the queue is void* that can point to any kind of data.
 *        (Of course, the pointer handling should be done carefully to avoid memory leaks or segmentation faults. :D)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// An example structure to store XY coordinates
typedef struct XYCoordinate {
    double x;
    double y;
} XYCoordinate;

// QueueNode is a structure that contains any kind of data via void* and a pointer to the next node
typedef struct QueueNode {
    void *data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* frontQueueNode;
    QueueNode* rearQueueNode;
    unsigned int queueSize;
} Queue;

// Initialize the queue
void initializeQueue(Queue *queue) {
    queue->frontQueueNode = NULL;
    queue->rearQueueNode = NULL;
    queue->queueSize = 0;
}

// Check if the queue is empty
// No need to define isQueueFull() because the queue can grow dynamically via nodes
bool isQueueEmpty(Queue *queue) {
    return queue->queueSize == 0;
}

// Enqueue an element (add an element to the queue)
void enqueue(Queue *queue, void *data) {
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

    queue->queueSize++;
}

// Dequeue an element (remove an element from the queue)
void* dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty, so can't dequeue\n");
        return NULL;
    }

    // Because front node will be removed during dequeue, we need to keep the front node
    QueueNode* tempQueueNode = queue->frontQueueNode;

    void* data = tempQueueNode->data;
    queue->frontQueueNode = tempQueueNode->next;
    free(tempQueueNode);
    queue->queueSize--;

    return data;
}

// Peek an element (get the front element of the queue without removing it)
void* peek(Queue *queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty, so can't peek\n");
        return NULL;
    }

    return queue->frontQueueNode->data;
}

// Delete the queue while freeing all the nodes
void deleteQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);    // free the queue itself (not the nodes, because they are already freed in dequeue()

    printf("Queue deleted\n");
}

// Print the queue
// Because the data type is polymorphic, we need to pass a function pointer to print the data
void printQueue(Queue *queue, void (*printData)(void*)) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    QueueNode* tempQueueNode = queue->frontQueueNode;
    printf("Queue: ");
    while (tempQueueNode != NULL) {
        printData(tempQueueNode->data);
        tempQueueNode = tempQueueNode->next;
    }
    printf("(NULL)\n");
}

void printStringData(void* data) {
    printf("%s -> ", (char*)data);
}

// Print the XYCoordinate data
void printXYCoordinateData(void* data) {
    XYCoordinate* coordinate = (XYCoordinate*)data;     // type casting from void* to XYCoordinate*
    printf("{.x => %f, .y => %f} -> ", coordinate->x, coordinate->y);
}

int main(void) {
    Queue* queueForXYCoordinate = (Queue*)malloc(sizeof(Queue));
    initializeQueue(queueForXYCoordinate);

    XYCoordinate* coordinateData[] = {
        &(XYCoordinate){.x = 1.48, .y = 3.14},
        &(XYCoordinate){.x = -10.49, .y = 2.71},
        &(XYCoordinate){.x = 0.0, .y = 0.0},
        &(XYCoordinate){.x = 5.59, .y = -4.44}
    };
    for (size_t index = 0; index < sizeof(coordinateData) / sizeof(coordinateData[0]); index++) {
        enqueue(queueForXYCoordinate, coordinateData[index]);
        printQueue(queueForXYCoordinate, printXYCoordinateData);
    }
    for (size_t index = 0; index < sizeof(coordinateData) / sizeof(coordinateData[0]); index++) {
        dequeue(queueForXYCoordinate);
        printQueue(queueForXYCoordinate, printXYCoordinateData);
    }

    deleteQueue(queueForXYCoordinate);
    printf("\n\n");

    Queue* queueForString = (Queue*)malloc(sizeof(Queue));
    initializeQueue(queueForString);

    char* stringData[] = {
        "Void* pointer",
        "literally",
        "can",
        "point",
        "to",
        "any",
        "kind",
        "of",
        "data"
    };
    for (size_t index = 0; index < sizeof(stringData) / sizeof(stringData[0]); index++) {
        enqueue(queueForString, stringData[index]);
        printQueue(queueForString, printStringData);
    }
    for (size_t index = 0; index < sizeof(stringData) / sizeof(stringData[0]); index++) {
        dequeue(queueForString);
        printQueue(queueForString, printStringData);
    }

    deleteQueue(queueForString);

    return 0;
}

// Queue: {.x => 1.480000, .y => 3.140000} -> (NULL)
// Queue: {.x => 1.480000, .y => 3.140000} -> {.x => -10.490000, .y => 2.710000} -> (NULL)
// Queue: {.x => 1.480000, .y => 3.140000} -> {.x => -10.490000, .y => 2.710000} -> {.x => 0.000000, .y => 0.000000} -> (NULL)
// Queue: {.x => 1.480000, .y => 3.140000} -> {.x => -10.490000, .y => 2.710000} -> {.x => 0.000000, .y => 0.000000} -> {.x => 5.590000, .y => -4.440000} -> (NULL)
// Queue: {.x => -10.490000, .y => 2.710000} -> {.x => 0.000000, .y => 0.000000} -> {.x => 5.590000, .y => -4.440000} -> (NULL)
// Queue: {.x => 0.000000, .y => 0.000000} -> {.x => 5.590000, .y => -4.440000} -> (NULL)
// Queue: {.x => 5.590000, .y => -4.440000} -> (NULL)
// Queue is empty
// Queue deleted


// Queue: Void* pointer -> (NULL)
// Queue: Void* pointer -> literally -> (NULL)
// Queue: Void* pointer -> literally -> can -> (NULL)
// Queue: Void* pointer -> literally -> can -> point -> (NULL)
// Queue: Void* pointer -> literally -> can -> point -> to -> (NULL)
// Queue: Void* pointer -> literally -> can -> point -> to -> any -> (NULL)
// Queue: Void* pointer -> literally -> can -> point -> to -> any -> kind -> (NULL)
// Queue: Void* pointer -> literally -> can -> point -> to -> any -> kind -> of -> (NULL)
// Queue: Void* pointer -> literally -> can -> point -> to -> any -> kind -> of -> data -> (NULL)
// Queue: literally -> can -> point -> to -> any -> kind -> of -> data -> (NULL)
// Queue: can -> point -> to -> any -> kind -> of -> data -> (NULL)
// Queue: point -> to -> any -> kind -> of -> data -> (NULL)
// Queue: to -> any -> kind -> of -> data -> (NULL)
// Queue: any -> kind -> of -> data -> (NULL)
// Queue: kind -> of -> data -> (NULL)
// Queue: of -> data -> (NULL)
// Queue: data -> (NULL)
// Queue is empty
// Queue deleted