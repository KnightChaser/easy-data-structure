/**
 * @file priority_queue_via_max_heap_array.c
 * @brief A C implementation of a priority queue using a max heap array
 */
//

#include <stdio.h>
#include <stdbool.h>

#define MAX_HEAP_ARRAY_SIZE 1024

typedef int PriorityQueueElementType;
typedef struct PriorityQueueViaMaxHeapArray {
    PriorityQueueElementType maxHeapArray[MAX_HEAP_ARRAY_SIZE];
    unsigned int size;
} PriorityQueueViaMaxHeapArray;

// Helper method to maintain the heap property after insertion
void heapifyUp(PriorityQueueViaMaxHeapArray *priorityQueue, unsigned int index) {
    while (index > 0) {
        // Note that the max heap is implemented as an array, so the parent index can be calculated as (index - 1) / 2
        unsigned int parentIndex = (index - 1) / 2;
        if (priorityQueue->maxHeapArray[parentIndex] < priorityQueue->maxHeapArray[index]) {
            // If the parent node is less than the current node, swap them to maintain the max heap
            PriorityQueueElementType temp = priorityQueue->maxHeapArray[parentIndex];
            priorityQueue->maxHeapArray[parentIndex] = priorityQueue->maxHeapArray[index];
            priorityQueue->maxHeapArray[index] = temp;
            index = parentIndex;
        } else {
            // Break the loop if the parent node is greater than or equal to the current node
            break;
        }
    }
}

// Method to insert an element into the priority queue
void insertPriorityQueueViaMaxHeapArray(PriorityQueueViaMaxHeapArray *priorityQueue, PriorityQueueElementType data) {
    if (priorityQueue->size >= MAX_HEAP_ARRAY_SIZE) {
        fprintf(stderr, "Error: Priority Queue is full\n");
        return;
    }

    priorityQueue->maxHeapArray[priorityQueue->size] = data;
    priorityQueue->size++;
    heapifyUp(priorityQueue, priorityQueue->size - 1);
}

// Helper method to maintain the heap property after removal
void heapifyDown(PriorityQueueViaMaxHeapArray *priorityQueue, unsigned int index) {
    while (true) {
        // Note that the max heap is implemented as an array, so the left child index can be calculated as 2 * index + 1
        unsigned int leftChildIndex = 2 * index + 1;
        unsigned int rightChildIndex = 2 * index + 2;
        unsigned int maxIndex = index;                      // Assume the current node is the largest

        if (leftChildIndex < priorityQueue->size &&
            priorityQueue->maxHeapArray[leftChildIndex] > priorityQueue->maxHeapArray[maxIndex]) {
            // If the left child is greater than the current node, update the max index
            maxIndex = leftChildIndex;
        }

        if (rightChildIndex < priorityQueue->size &&
            priorityQueue->maxHeapArray[rightChildIndex] > priorityQueue->maxHeapArray[maxIndex]) {
            // If the right child is greater than the current node or left child, update the max index
            maxIndex = rightChildIndex;
        }

        if (maxIndex == index) {
            // If the current node is the largest, break the loop
            // Why? Because the current node is already greater than its children
            break;
        }

        // Otherwise, swap the current node with the largest child
        // Why? To maintain the max heap property
        PriorityQueueElementType temp = priorityQueue->maxHeapArray[index];
        priorityQueue->maxHeapArray[index] = priorityQueue->maxHeapArray[maxIndex];
        priorityQueue->maxHeapArray[maxIndex] = temp;
        index = maxIndex;
    }
}

// Method to remove the element with the highest priority (highest value) from the priority queue
PriorityQueueElementType removePriorityQueueViaMaxHeapArray(PriorityQueueViaMaxHeapArray *priorityQueue) {
    if (priorityQueue->size == 0) {
        fprintf(stderr, "Error: Priority Queue is empty\n");
        return -1;
    }

    // The element with the highest priority is always the root of the max heap
    // So, removing the root element will be removing the first element of the array
    PriorityQueueElementType removedElement = priorityQueue->maxHeapArray[0];
    priorityQueue->maxHeapArray[0] = priorityQueue->maxHeapArray[priorityQueue->size - 1]; // Replace the root with the last element of the array
    priorityQueue->size--;

    // Maintain the heap property after removal
    // Note that the root element is replaced with the last element of the array (which was the last element of the max heap)
    heapifyDown(priorityQueue, 0);
    return removedElement;
}

// Method to get the maximum element from the priority queue
// Because of the max heap, the biggest value always resides at the root(first in the array)
PriorityQueueElementType getMaxPriorityQueueViaMaxHeapArray(PriorityQueueViaMaxHeapArray *priorityQueue) {
    if (priorityQueue->size == 0) {
        fprintf(stderr, "Error: Priority Queue is empty\n");
        return -1;
    }

    return priorityQueue->maxHeapArray[0];
}

// Method to get the minimum element from the priority queue
// Simply iterate through the array to find the smallest value
PriorityQueueElementType getMinPriorityQueueViaMaxHeapArray(PriorityQueueViaMaxHeapArray *priorityQueue) {
    if (priorityQueue->size == 0) {
        fprintf(stderr, "Error: Priority Queue is empty\n");
        return -1;
    }

    PriorityQueueElementType minElement = priorityQueue->maxHeapArray[0];
    for (unsigned int index = 1; index < priorityQueue->size; index++) {
        if (priorityQueue->maxHeapArray[index] < minElement) {
            minElement = priorityQueue->maxHeapArray[index];
        }
    }

    return minElement;
}

// Method to print the elements of the priority queue
void printPriorityQueueViaMaxHeapArray(PriorityQueueViaMaxHeapArray *priorityQueue) {
    if (priorityQueue->size == 0) {
        printf("Priority Queue is empty\n");
        return;
    }

    printf("Priority Queue (Max Heap Array): ");
    for (unsigned int index = 0; index < priorityQueue->size; index++) {
        printf("%d ", priorityQueue->maxHeapArray[index]);
    }
    printf("\n");
}

//Main function
int main(void) {
    PriorityQueueViaMaxHeapArray priorityQueue = { .size = 0 };

    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 10);
    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 20);
    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 15);
    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 40);
    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 50);
    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 100);
    insertPriorityQueueViaMaxHeapArray(&priorityQueue, 25);

    printPriorityQueueViaMaxHeapArray(&priorityQueue);

    printf("Max Element: %d\n", getMaxPriorityQueueViaMaxHeapArray(&priorityQueue));
    printf("Min Element: %d\n", getMinPriorityQueueViaMaxHeapArray(&priorityQueue));

    printf("Removed Element: %d\n", removePriorityQueueViaMaxHeapArray(&priorityQueue));
    printPriorityQueueViaMaxHeapArray(&priorityQueue);

    printf("Max Element: %d\n", getMaxPriorityQueueViaMaxHeapArray(&priorityQueue));
    printf("Min Element: %d\n", getMinPriorityQueueViaMaxHeapArray(&priorityQueue));

    return 0;
}

// Priority Queue (Max Heap Array): 100 40 50 10 20 15 25 
// Max Element: 100
// Min Element: 10
// Removed Element: 100
// Priority Queue (Max Heap Array): 50 40 25 10 20 15 
// Max Element: 50
// Min Element: 10