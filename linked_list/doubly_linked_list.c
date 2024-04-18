/**
 * @file doubly_linked_list.c
 * @brief A simple implementation of doubly linked list, written in C langauge.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>

typedef char DoublyLinkedListElement;
typedef struct DoublyLinkedListNode {
    DoublyLinkedListElement data;
    struct DoublyLinkedListNode *next;
    struct DoublyLinkedListNode *previous;
} DoublyLinkedListNode;

// Initialize a new doubly linked list node
void initializeDoublyLinkedListNode(DoublyLinkedListNode *node, 
                                    DoublyLinkedListElement data) {
    // // Fill the memory with 0 (initialize the node with 0 to ensure safety
    memset(node, 0, sizeof(DoublyLinkedListNode));
    node->data = data;
    node->next = node;
    node->previous = node;
}

// Insert a new node next to the given node
void insertDoublyLinkedListNodeNextTo(DoublyLinkedListNode *node, 
                                      DoublyLinkedListElement data) {
    DoublyLinkedListNode *newNode = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
    initializeDoublyLinkedListNode(newNode, data);

    // ... <-> node <-> newNode <-> ...
    newNode->next = node->next;         // newNode->next points to the node that was next to the given node (forward)
    newNode->previous = node;           // newNode->previous points to the given node (backward)
    node->next->previous = newNode;     // The node that was next to the given node now points to the newNode backward
    node->next = newNode;               // The given node now points to the newNode forward
}

// Insert a new node next to a node that has a specific data
void insertDoublyLinkedListNodeNextToData(DoublyLinkedListNode *headNode,
                                          DoublyLinkedListElement data,
                                          DoublyLinkedListElement newData) {
    DoublyLinkedListNode *currentNode = headNode;

    do {
        if (currentNode->data == data) {
            insertDoublyLinkedListNodeNextTo(currentNode, newData);
            return;
        }
    } while ((currentNode = currentNode->next) != headNode);

    fprintf(stderr, "The data %c does not exist in the doubly linked list.\n", data);
}

// Remove a node from the doubly linked list
void removeDoublyLinkedListNode(DoublyLinkedListNode *node) {
    // ... <-> previousNode <-> node <-> nextNode <-> ...
    node->previous->next = node->next;               // The node before the given node now points to the node after the given node
    node->next->previous = node->previous;           // The node after the given node now points to the node before the given node
    free(node);                               // Free the memory of the given node
}

// Print the doubly linked list
void printDoublyLinkedList(DoublyLinkedListNode *headNode) {
    if (headNode == NULL) {
        printf("The doubly linked list is empty.\n");
        return;
    }

    DoublyLinkedListNode *currentNode = headNode;
    do {
        printf("%c <-> ", currentNode->data);
        currentNode = currentNode->next;
    } while (currentNode != headNode);

    // Emphasize the circularity of the doubly linked list
    printf("%c\n", headNode->data);
}

// Free the memory of the doubly linked list
void freeDoublyLinkedList(DoublyLinkedListNode *headNode) {
    if (headNode == NULL) {
        printf("The doubly linked list is empty.\n");
        return;
    }

    DoublyLinkedListNode *currentNode = headNode;
    do {
        DoublyLinkedListNode *tempNode = currentNode;
        currentNode = currentNode->next;
        free(tempNode);
    } while (currentNode != headNode);

    free(headNode);
    printf("The doubly linked list has been freed.\n");
}

int main(void) {
    // Initialize a new doubly linked list
    DoublyLinkedListNode *doublyLinkedList = (DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));

    // Initialize the head node of the doubly linked list
    initializeDoublyLinkedListNode(doublyLinkedList, 'A');
    printDoublyLinkedList(doublyLinkedList);

    // Inserting
    insertDoublyLinkedListNodeNextTo(doublyLinkedList, 'B');
    printDoublyLinkedList(doublyLinkedList);
    insertDoublyLinkedListNodeNextTo(doublyLinkedList->next, 'C');
    printDoublyLinkedList(doublyLinkedList);
    insertDoublyLinkedListNodeNextTo(doublyLinkedList->next->next, 'D');
    printDoublyLinkedList(doublyLinkedList);
    insertDoublyLinkedListNodeNextTo(doublyLinkedList->next->next->next, 'E');
    printDoublyLinkedList(doublyLinkedList);

    // Inserting next to a node that has a specific data
    insertDoublyLinkedListNodeNextToData(doublyLinkedList, 'B', 'X');
    printDoublyLinkedList(doublyLinkedList);
    insertDoublyLinkedListNodeNextToData(doublyLinkedList, 'C', 'Y');
    printDoublyLinkedList(doublyLinkedList);

    // Removing
    removeDoublyLinkedListNode(doublyLinkedList->next->next);
    printDoublyLinkedList(doublyLinkedList);
    removeDoublyLinkedListNode(doublyLinkedList->next);
    printDoublyLinkedList(doublyLinkedList);

    freeDoublyLinkedList(doublyLinkedList);

    return 0;
}

// A <-> A
// A <-> B <-> A
// A <-> B <-> C <-> A
// A <-> B <-> C <-> D <-> A
// A <-> B <-> C <-> D <-> E <-> A
// A <-> B <-> X <-> C <-> D <-> E <-> A
// A <-> B <-> X <-> C <-> Y <-> D <-> E <-> A
// A <-> B <-> C <-> Y <-> D <-> E <-> A
// A <-> C <-> Y <-> D <-> E <-> A