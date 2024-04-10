/**
 * @file linked_list_for_string.c
 * @brief A linked list implementation for storing strings.
 *        A variation of linked_list_basic.c but handling string(set of characters), using char* pointers.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strcpy and strdup

typedef char* LinkedListType;
typedef struct LinkedListNode {
    LinkedListType data;
    struct LinkedListNode *next;
} LinkedListNode;

// Updated function to handle dynamic string allocation
LinkedListNode* insertLinkedListNodeAtStart(LinkedListNode *headNode, 
                                            LinkedListType data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = strdup(data); // Duplicate the string
    newNode->next = headNode;
    headNode = newNode;
    return headNode;
}

// Similarly update other insert functions
LinkedListNode* insertLinkedListNodeBehindGivenNode(LinkedListNode *headNode, 
                                                    LinkedListNode *givenNode, 
                                                    LinkedListType data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = strdup(data); // Duplicate the string
    newNode->next = givenNode->next;
    givenNode->next = newNode;
    return headNode;
}

LinkedListNode* insertLinkedListNodeAtEnd(LinkedListNode *headNode,
                                          LinkedListType data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = strdup(data); // Duplicate the string
    newNode->next = NULL;

    if (headNode == NULL) {
        headNode = newNode;
    } else {
        LinkedListNode *currentNode = headNode;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
    return headNode;
}

// Update delete functions to free string memory
LinkedListNode* deleteLinkedListNodeAtStart(LinkedListNode *headNode) {
    if (headNode == NULL) {
        fprintf(stderr, "The linked list is empty, so can't delete a new node.\n");
        return NULL;
    }

    LinkedListNode *removedNode = headNode;
    headNode = headNode->next;
    free(removedNode->data); // Free the string
    free(removedNode);
    return headNode;
}

// Similarly update other delete functions
LinkedListNode* deleteLinkedListNodeBehindGivenNode(LinkedListNode *headNode, 
                                                    LinkedListNode *givenNode) {
    if (givenNode == NULL || givenNode->next == NULL) {
        fprintf(stderr, "The given node is NULL or the next node is NULL, so can't delete a new node.\n");
        return headNode;
    }

    LinkedListNode *removedNode = givenNode->next;
    givenNode->next = givenNode->next->next;
    free(removedNode->data); // Free the string
    free(removedNode);
    return headNode;
}

LinkedListNode* deleteLinkedListNodeAtEnd(LinkedListNode *headNode) {
    if (headNode == NULL) {
        fprintf(stderr, "The linked list is empty, so can't delete a new node.\n");
        return NULL;
    }

    if (headNode->next == NULL) {
        free(headNode->data); // Free the string
        free(headNode);
        return NULL;
    }

    LinkedListNode *currentNode = headNode;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }

    free(currentNode->next->data); // Free the string
    free(currentNode->next);
    currentNode->next = NULL;
    return headNode;
}

void deleteLinkedList(LinkedListNode *headNode) {
    LinkedListNode *currentNode = headNode;
    while (currentNode != NULL) {
        LinkedListNode *tempNode = currentNode;
        currentNode = currentNode->next;
        free(tempNode->data); // Free the string
        free(tempNode);
    }
    printf("The linked list is deleted successfully.\n");
}

void displayLinkedList(LinkedListNode *headNode) {
    for (LinkedListNode *currentNode = headNode; currentNode != NULL; currentNode = currentNode->next)
        printf("%s -> ", currentNode->data);
    printf("NULL\n");
}

int main(void) {
    LinkedListNode *linkedList = NULL;  // Initialize the linked list (only the head node)

    // Insert nodes
    linkedList = insertLinkedListNodeAtEnd(linkedList, "Handling");
    displayLinkedList(linkedList);
    linkedList = insertLinkedListNodeAtEnd(linkedList, "char*");
    displayLinkedList(linkedList);
    linkedList = insertLinkedListNodeAtStart(linkedList, "pointers");
    displayLinkedList(linkedList);

    // Delete nodes
    for (size_t index = 0; index < 3; index++) {
        linkedList = deleteLinkedListNodeAtStart(linkedList);
        displayLinkedList(linkedList);
    }

    // Clean up
    deleteLinkedList(linkedList);

    return 0;
}

// Handling -> NULL
// Handling -> char* -> NULL
// pointers -> Handling -> char* -> NULL
// Handling -> char* -> NULL
// char* -> NULL
// NULL
// The linked list is deleted successfully.