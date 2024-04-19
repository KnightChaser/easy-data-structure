/**
 * @file linked_list_for_queue.c
 * @brief A simple demonstration of linked list for queue.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

// Define the structure of a node in the linked list
typedef char Element;

typedef struct LinkedListNode {
    Element data;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedListQueue {
    LinkedListNode *front;          // The front node of the queue
    LinkedListNode *rear;           // The rear node of the queue
    unsigned int size;
} LinkedListQueue;

// Create a new linked list queue
LinkedListQueue* createLinkedListQueue(Element data) {
    LinkedListQueue *queue = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
    memset(queue, 0, sizeof(LinkedListQueue));
    queue->front = (LinkedListNode *)malloc(sizeof(LinkedListNode));

    // At the first time, the front and rear nodes are the same.
    queue->front->data = data;
    queue->front->next = NULL;
    queue->rear = queue->front;
    queue->size = 1;

    return queue;
    // Don't forget to free the memory after using the queue >_<
}

// Check if the queue is empty
bool isLinkedListQueueEmpty(LinkedListQueue *queue) {
    if (queue->size == 0)
        return true;
    else
        return false;
}

// Enqueue a new element 
void enqueueElementToLinkedListQueue(LinkedListQueue *queue, Element data) {
    // Enqueue the new element next to the rear node
    // ... -> (rear) -> (newNode: becomes the new rear) -> NULL
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->next = NULL;

    if (isLinkedListQueueEmpty(queue)) {
        // If the queue is empty, the front and rear nodes are the same.
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // If the queue is not empty, the rear node will point to the new node.
        queue->rear->next = newNode;
        queue->rear = newNode;
        
        // If newNode->next is not NULL, use the following code instead
        // queue->rear->next = NULL;       // Unless the rear node points to NULL, the queue will not be terminated.
    }
}

// Peek the front element of the linked list queue
Element peekElementOfLinkedListQueue(LinkedListQueue *queue) {
    if (isLinkedListQueueEmpty(queue)) {
        fprintf(stderr, "The linked list queue is empty.\n");
    }
    return queue->front->data;
}

// Peek the last element of the linked list queue
Element peekLastElementOfLinkedListQueue(LinkedListQueue *queue) {
    if (isLinkedListQueueEmpty(queue)) {
        fprintf(stderr, "The linked list queue is empty.\n");
    }
    return queue->rear->data;
}

// Get the size of the linked list queue
unsigned int sizeOfLinkedListQueue(LinkedListQueue *queue) {
    return queue->size;
}

// Dequeue the front element of the linked list queue
Element dequeueElementFromLinkedListQueue(LinkedListQueue *queue) {
    // Dequeue the front element, becuase queue is FIFO(First Input First Output)
    // (front: popped out) -> (new front: this will be the new front) -> ...
    if (isLinkedListQueueEmpty(queue)) {
        fprintf(stderr, "The linked list queue is empty.\n");
    }

    // Get the front node
    LinkedListNode *oldFront = queue->front;
    Element data = oldFront->data;

    // Move the front node to the next node
    queue->front = oldFront->next;
    free(oldFront);
    if (queue->front == NULL) {
        // If the front node is NULL, the queue is empty.
        queue->rear = NULL;
    }
    queue->size--;

    return data;
}

// Print the elements of the linked list queue
void printLinkedListQueue(LinkedListQueue *queue) {
    if (isLinkedListQueueEmpty(queue)) {
        fprintf(stderr, "The linked list queue is empty.\n");
    }

    LinkedListNode *current = queue->front;
    while (current != NULL) {
        printf("%c -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

// Destroy the linked list queue
void destroyLinkedListQueue(LinkedListQueue *queue) {
    LinkedListNode *current = queue->front;

    // Freeing the memory of each node associated with the linked list queue
    while (current != NULL) {
        LinkedListNode *temp = current;
        current = current->next;
        free(temp);
    }

    // Free the queue structure itself
    free(queue);
    printf("The linked list queue is destroyed.\n");
}

int main(void) {
    LinkedListQueue *queue = createLinkedListQueue('A');
    printLinkedListQueue(queue);

    enqueueElementToLinkedListQueue(queue, 'B');
    printLinkedListQueue(queue);

    enqueueElementToLinkedListQueue(queue, 'C');
    printLinkedListQueue(queue);

    enqueueElementToLinkedListQueue(queue, 'D');
    printLinkedListQueue(queue);

    enqueueElementToLinkedListQueue(queue, 'E');
    printLinkedListQueue(queue);

    printf("The front element of the linked list queue is %c.\n", peekElementOfLinkedListQueue(queue));
    printf("The last element of the linked list queue is %c.\n", peekLastElementOfLinkedListQueue(queue));
    printf("The size of the linked list queue is %u.\n", sizeOfLinkedListQueue(queue));

    printf("The front element %c has been dequeued from the linked list queue.\n", dequeueElementFromLinkedListQueue(queue));
    printLinkedListQueue(queue);

    printf("The front element %c has been dequeued from the linked list queue.\n", dequeueElementFromLinkedListQueue(queue));
    printLinkedListQueue(queue);

    printf("The front element %c has been dequeued from the linked list queue.\n", dequeueElementFromLinkedListQueue(queue));
    printLinkedListQueue(queue);

    printf("The front element %c has been dequeued from the linked list queue.\n", dequeueElementFromLinkedListQueue(queue));
    printLinkedListQueue(queue);

    printf("The front element %c has been dequeued from the linked list queue.\n", dequeueElementFromLinkedListQueue(queue));
    printLinkedListQueue(queue);

    destroyLinkedListQueue(queue);

    return 0;
}

// A -> NULL
// A -> B -> NULL
// A -> B -> C -> NULL
// A -> B -> C -> D -> NULL
// A -> B -> C -> D -> E -> NULL
// The front element of the linked list queue is A.
// The last element of the linked list queue is E.
// The size of the linked list queue is 1.
// The front element A has been dequeued from the linked list queue.
// The linked list queue is empty.
// B -> C -> D -> E -> NULL
// The linked list queue is empty.
// The front element B has been dequeued from the linked list queue.
// C -> D -> E -> NULL
// The front element C has been dequeued from the linked list queue.
// D -> E -> NULL
// The front element D has been dequeued from the linked list queue.
// E -> NULL
// The front element E has been dequeued from the linked list queue.
// NULL
// The linked list queue is destroyed.