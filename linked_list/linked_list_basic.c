/*
 * @file linked_list_basic.c
 * @brief A basic implementation of linked list using Node structure(data and the pointer to the next node)
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char LinkedListType;
typedef struct LinkedListNode {
    LinkedListType data;
    struct LinkedListNode *next;
} LinkedListNode;

// Insert a new node at the start
LinkedListNode* insertLinkedListNodeAtStart(LinkedListNode *headNode, 
                                            LinkedListType data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->next = headNode;
    headNode = newNode;
    return headNode;
}

// Insert a new node next to the given node
LinkedListNode* insertLinkedListNodeBehindGivenNode(LinkedListNode *headNode, 
                                                    LinkedListNode *givenNode, 
                                                    LinkedListType data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->next = givenNode->next;
    givenNode->next = newNode;
    return headNode;
}

// Insert a new node at the end
LinkedListNode* insertLinkedListNodeAtEnd(LinkedListNode *headNode,
                                          LinkedListType data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->next = NULL;

    // If the given linked list is empty
    if (headNode == NULL) {
        headNode = newNode;
        return headNode;
    }

    // Traverse to the end of the linked list,
    // and insert the new node at the end of the given linked list
    LinkedListNode *currentNode = headNode;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    
    currentNode->next = newNode;
    return headNode;

}

// Delete the first node
LinkedListNode* deleteLinkedListNodeAtStart(LinkedListNode *headNode) {
    if (headNode == NULL) {
        fprintf(stderr, "The linked list is empty, so can't delete a new node.\n");
        return NULL;
    }

    LinkedListNode *removedNode = headNode;
    headNode = headNode->next;                          // Move the head to the next(second) node
    free(removedNode);
    return headNode;
}

// Delete the node after the given node
LinkedListNode* deleteLinkedListNodeBehindGivenNode(LinkedListNode *headNode, 
                                                    LinkedListNode *givenNode) {

    // Range check, if the given node is NULL or the next node is NULL
    if (givenNode == NULL || givenNode->next == NULL) {
        fprintf(stderr, "The given node is NULL or the next node is NULL, so can't delete a new node.\n");
        return headNode;
    }

    LinkedListNode *removedNode = givenNode->next;
    givenNode->next = givenNode->next->next;            // Skip the next node that will be deleted
    free(removedNode);
    return headNode;
}

// Delete the last node
LinkedListNode* deleteLinkedListNodeAtEnd(LinkedListNode *headNode) {

    // If the linked list is empty
    if (headNode == NULL) {
        fprintf(stderr, "The linked list is empty, so can't delete a new node.\n");
        return NULL;
    }

    // If the linked list has only one node
    if (headNode->next == NULL) {
        free(headNode);
        return NULL;
    }

    // Traverse to the end of the linked list,
    // and delete the last node of the given linked list
    LinkedListNode *currentNode = headNode;
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
    }

    free(currentNode->next);
    currentNode->next = NULL;
    return headNode;
}

// Delete the linked list
void deleteLinkedList(LinkedListNode *headNode) {

    // Traverse the linked list, and delete all nodes sequentially
    LinkedListNode *currentNode = headNode;
    while (currentNode != NULL) {
        LinkedListNode *tempNode = currentNode;
        currentNode = currentNode->next;
        free(tempNode);
    }
}

// Print the linked list
void displayLinkedList(LinkedListNode *headNode) {
    for (LinkedListNode *currentNode = headNode; currentNode != NULL; currentNode = currentNode->next)
        printf("%c -> ", currentNode->data);
    printf("NULL\n");
}

int main(void) {
    LinkedListNode *linkedList = NULL;  // Initialize the linked list (only the head node)

    // Insert a new node at the last
    for (size_t index = 0; index < 5; index++) {
        linkedList = insertLinkedListNodeAtEnd(linkedList, 'A' + index);
        displayLinkedList(linkedList);
    }

    // Delete the first node repeatedly
    for (size_t index = 0; index < 5; index++) {
        linkedList = deleteLinkedListNodeAtStart(linkedList);
        displayLinkedList(linkedList);
    }

    deleteLinkedList(linkedList);

    return 0;
}

// A -> NULL
// A -> B -> NULL
// A -> B -> C -> NULL
// A -> B -> C -> D -> NULL
// A -> B -> C -> D -> E -> NULL
// B -> C -> D -> E -> NULL
// C -> D -> E -> NULL
// D -> E -> NULL
// E -> NULL 
// NULL