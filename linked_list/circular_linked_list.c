/**
 * @file circular_linked_list.c
 * @brief A simple demonstration of circular linked list.
 *        If a linked list is 1->2->3->4->5, and 5 will point to 1, then it is a circular linked list.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char CircularLinkedListElement;
typedef struct CircularLinkedListNode {
    CircularLinkedListElement data;
    struct CircularLinkedListNode *next;
} CircularLinkedListNode;

// Insert a new node next to the head node
CircularLinkedListNode* insertCircularLinkedListNodeNextToHead(CircularLinkedListNode *headNode,
                                                               CircularLinkedListElement data) {
    CircularLinkedListNode *newNode = (CircularLinkedListNode *)malloc(sizeof(CircularLinkedListNode));
    memset(newNode, 0, sizeof(CircularLinkedListNode));

    newNode->data = data;

    if (headNode == NULL) {
        // The given circular linked list is empty, so the new node will be the head node
        headNode = newNode;
        headNode->next = headNode;
    } else {
        // The new node will be appended next to the head node
        newNode->next = headNode->next;
        headNode->next = newNode;
    }
    
    return headNode;
}

// Insert a new node before the head node
CircularLinkedListNode* insertCircularLinkedListNodeBeforeHead(CircularLinkedListNode *headNode,
                                                               CircularLinkedListElement data) {
    CircularLinkedListNode *newNode = (CircularLinkedListNode *)malloc(sizeof(CircularLinkedListNode));
    memset(newNode, 0, sizeof(CircularLinkedListNode));

    newNode->data = data;

    if (headNode == NULL) {
        // The given circular linked list is empty, so the new node will be the head node
        headNode = newNode;
        headNode->next = headNode;
    } else {
        // The new node will be appended before the head node (in front of the head node)
        CircularLinkedListNode *currentNode = headNode;
        while (currentNode->next != headNode) {
            currentNode = currentNode->next;
        }

        // Now currentNode is right before the head node
        currentNode->next = newNode;
        newNode->next = headNode;
    }
    
    return headNode;
}

// Print the circular linked list
void printCircularLinkedList(CircularLinkedListNode *headNode) {
    if (headNode == NULL) {
        printf("The circular linked list is empty.\n");
        return;
    }

    CircularLinkedListNode *currentNode = headNode;
    do {
        printf("%c -> ", currentNode->data);
        currentNode = currentNode->next;
        // If the current node is the head node(again)
        // It means the circular linked list has been traversed a full circle
    } while (currentNode != headNode);
    printf("%c\n", currentNode->data);
}

// Free the circular linked list
void freeCircularLinkedList(CircularLinkedListNode *headNode) {
    if (headNode == NULL) {
        printf("The circular linked list is empty.\n");
        return;
    }

    CircularLinkedListNode *currentNode = headNode;
    CircularLinkedListNode *nextNode = NULL;
    do {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
        // If the current node is the head node(again)
        // It means the circular linked list has been traversed a full circle
        // and all nodes in the circular linked list have been freed
    } while (currentNode != headNode);
    printf("The circular linked list has been freed.\n");
}

int main(void) {
    CircularLinkedListNode *headNode = NULL;

    // Insert a new node next to the head node
    char* elements = "ABCDEFGHIJK";
    for (size_t index = 0; index < strlen(elements); index++) {
        headNode = insertCircularLinkedListNodeNextToHead(headNode, elements[index]);
        printCircularLinkedList(headNode);
    }

    // Insert a new node before the head node
    elements = "LMNOPQR";
    for (size_t index = 0; index < strlen(elements); index++) {
        headNode = insertCircularLinkedListNodeBeforeHead(headNode, elements[index]);
        printCircularLinkedList(headNode);
    }

    // Free the circular linked list
    freeCircularLinkedList(headNode);

    return 0;
}