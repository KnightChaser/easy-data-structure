/**
 * @file list_by_array.c
 * @brief C program to implement a linked list using array and perform various operations
 *        Linked lists are often implemented using nodes, but here we implement it using arrays for basic understanding.
 *        Implementing list structure via array is not efficient as it has fixed size and requires shifting of elements.
 *        In this code, you'll be able to recognize why "Node" structure is widely used in linked lists.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

typedef char ArrayListType;
typedef struct ArrayList {
    ArrayListType *array;
    unsigned int size;
    unsigned int capacity;
} ArrayList;

// Initialize the list
void initializeArrayList(ArrayList *list, unsigned int capacity) {
    list->array = (ArrayListType *)malloc(capacity * sizeof(ArrayListType));
    list->size = 0;
    list->capacity = capacity;
}

// Check if the array list is empty
bool isArrayListEmpty(ArrayList *list) {
    return list->size == 0;
}

// Check if the array list is full
bool isArrayListFull(ArrayList *list) {
    return list->size == list->capacity;
}

// Get data from the array list at the given index
ArrayListType getArrayListEntry(ArrayList *list, unsigned int targetIndex) {
    // Range check
    if (targetIndex >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
    }

    return list->array[targetIndex];
}

// Insert data into the array list, at the start
void addEntryToArrayListStart(ArrayList *list, ArrayListType data) {
    if (isArrayListFull(list)) {
        fprintf(stderr, "List is full\n");
        return;
    }

    // Shift all elements to the right
    for (size_t index = list->size; index > 0; index--) {
        list->array[index] = list->array[index - 1];
    }

    list->array[0] = data;
    list->size++;
}

// Insert data into the array list, at the end
void addEntryToArrayListEnd(ArrayList *list, ArrayListType data) {
    if (isArrayListFull(list)) {
        fprintf(stderr, "List is full\n");
        return;
    }

    list->array[list->size] = data;
    list->size++;
}

// Pop data from the array list, from the start
ArrayListType popEntryFromArrayListStart(ArrayList *list) {
    if (isArrayListEmpty(list)) {
        fprintf(stderr, "List is empty\n");
    }

    ArrayListType data = list->array[0];

    // Shift all elements to the left
    for (size_t index = 0; index < list->size - 1; index++) {
        list->array[index] = list->array[index + 1];
    }

    list->size--;
    return data;
}

// Pop data from the array list, from the end
ArrayListType popEntryFromArrayListEnd(ArrayList *list) {
    if (isArrayListEmpty(list)) {
        fprintf(stderr, "List is empty\n");
    }

    ArrayListType data = list->array[list->size - 1];
    memset(&list->array[list->size - 1], 0, sizeof(ArrayListType));     // Invalidate the popped out data

    list->array[list->size - 1] = 0;     // Invalidate the popped out data
    list->size--;
    return data;
}

// Display the array list
void displayArrayList(ArrayList *list) {

    for (size_t index = 0; index < list->size; index++)
        printf("%c -> ", list->array[index]);

    printf("NULL\n");
}

int main(void) {
    ArrayList list;
    initializeArrayList(&list, 5);

    addEntryToArrayListStart(&list, 'A');
    addEntryToArrayListStart(&list, 'B');
    addEntryToArrayListStart(&list, 'C');
    addEntryToArrayListEnd(&list, 'D');
    addEntryToArrayListEnd(&list, 'E');

    displayArrayList(&list);

    printf("Popped from start: %c\n", popEntryFromArrayListStart(&list));
    displayArrayList(&list);

    printf("Popped from end: %c\n", popEntryFromArrayListEnd(&list));

    displayArrayList(&list);

    return 0;
}

// C -> B -> A -> D -> E -> NULL
// Popped from start: C
// B -> A -> D -> E -> NULL
// Popped from end: E
// B -> A -> D -> NULL