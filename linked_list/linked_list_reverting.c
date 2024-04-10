/**
 * @file linked_list_reverting.c
 * @brief A simple demonstration of reverting a linked list.
 *        If a linked list is 1->2->3->4->5, after reverting it will be 5->4->3->2->1.
 *        To enjoy more fun with pointers, this linked list is for string(char *)
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct LinkedListNode {
    char*  data;
    struct LinkedListNode *next;
} LinkedListNode;

// Linked list utility function will be defined in minimum

// Insert a linked list node at the end
LinkedListNode* insertLinkedListNodeAtEnd(LinkedListNode *headNode, const char* data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    size_t dataLengthInByte = strlen(data) + 1;
    newNode->data = (char *)malloc(dataLengthInByte);
    strcpy_s(newNode->data, dataLengthInByte, data);

    newNode->next = NULL;

    if (headNode == NULL) {
        // The linked list is empty, so the new node will be the head node
        headNode = newNode;
    } else {
        LinkedListNode *currentNode = headNode;
        // To find the last node, traverse the linked list
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

    return headNode;
}


// Revert the linked list
// Given a linked list, this function will revert it
LinkedListNode* revertLinkedList(LinkedListNode *headNode) {
    LinkedListNode *previousNode = NULL;
    LinkedListNode *currentNode = headNode;
    LinkedListNode *nextNode = NULL;

    while (currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }

    return previousNode;
}

// Print the linked list
void printLinkedList(LinkedListNode *headNode) {
    LinkedListNode *currentNode = headNode;
    while (currentNode != NULL) {
        printf("%s -> ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("NULL\n");
}

// Deallocate the linked list (deletion)
void deleteLinkedList(LinkedListNode *headNode) {
    LinkedListNode *currentNode = headNode;
    LinkedListNode *nextNode = NULL;

    while (currentNode->next != NULL) {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }

    // Deallocate the last node
    free(currentNode->data);
    free(currentNode);

    printf("Linked list is deallocated\n");
}

int main(void) {
    LinkedListNode *linkedList = NULL;

    linkedList = insertLinkedListNodeAtEnd(linkedList, "Alpha");
    linkedList = insertLinkedListNodeAtEnd(linkedList, "Bravo");
    linkedList = insertLinkedListNodeAtEnd(linkedList, "Charlie");
    linkedList = insertLinkedListNodeAtEnd(linkedList, "Delta");
    linkedList = insertLinkedListNodeAtEnd(linkedList, "Echo");

    printf("Original linked list: ");
    printLinkedList(linkedList);

    // Revert the linked list
    linkedList = revertLinkedList(linkedList);

    printf("Reverted linked list: ");
    printLinkedList(linkedList);

    deleteLinkedList(linkedList);

    return 0;
}