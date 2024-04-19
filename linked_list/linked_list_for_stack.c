/**
 * @file linked_list_for_stack.c
 * @brief A stack implementation using linked list, written in C language.
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

typedef struct LinkedListStack {
    LinkedListNode *top;
    unsigned int size;
} LinkedListStack;

// Create a new linked list stack
LinkedListStack* createLinkedListStack(Element data) {
    LinkedListStack *stack = (LinkedListStack *)malloc(sizeof(LinkedListStack));
    memset(stack, 0, sizeof(LinkedListStack));
    stack->top = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    stack->top->data = data;
    stack->top->next = NULL;
    stack->size = 1;

    return stack;
    // Don't forget to free the memory after using the stack >_<
}

// Check if the stack is empty
// (We don't need to check if the stack is full because the linked list stack is dynamic)
bool isLinkedListStackEmpty(LinkedListStack *stack) {
    if (stack->size == 0)
        return true;
    else
        return false;
}

// Push a new element to the linked list stack
void pushElementToLinkedListStack(LinkedListStack *stack, Element data) {
    // (top) -> (newNode) -> (old top) -> ...
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->next = stack->top;     // The new node will point to the old top node, thus (newNode) -> (old top)
    stack->top = newNode;           // The new node will be the top node, thus (top) -> (newNode)
    stack->size++;
}

// Peek the top element of the liniked list stack
Element peekElementOfLinkedListStack(LinkedListStack *stack) {
    return stack->top->data;
}

// Pop the top element of the linked list stack
Element popElementFromLinkedListStack(LinkedListStack *stack) {
    // (top) -> (old top) -> (old top->next(that will be the new top)) -> ...
    LinkedListNode *oldTop = stack->top;
    Element data = oldTop->data;
    stack->top = oldTop->next;      // The old top node will be removed, and the next node will be the new top node
    free(oldTop);
    stack->size--;

    return data;
}

// Print the linked list stack
void printLinkedListStack(LinkedListStack *stack) {
    if (isLinkedListStackEmpty(stack)) {
        printf("The linked list stack is empty.\n");
        return;
    }

    // Pretty print
    // Such as ...
    // --------------------
    // | 4 -> 3 -> 2 -> 1
    // --------------------
    unsigned int size = stack->size;
    unsigned int stackWallLength = size * 4 + 1;    // 4 = 1 space + 1 arrow + 1 space + 1 data
    char *stackWall = (char *)malloc(sizeof(char) * (stackWallLength + 1));

    // Print the upper wall
    memset(stackWall, '-', stackWallLength);
    stackWall[stackWallLength] = '\0';
    printf("%s\n", stackWall);

    // Print the data
    LinkedListNode *currentNode = stack->top;
    for (unsigned int i = 0; i < size; i++) {
        printf("| %c ", currentNode->data);
        currentNode = currentNode->next;
    }

    // Print the lower wall
    printf("\n%s\n", stackWall);
}

// Destroy the linked list stack
void destroyLinkedListStack(LinkedListStack *stack) {
    LinkedListNode *currentNode = stack->top;
    while (currentNode != NULL) {
        free(currentNode);
        currentNode = currentNode->next;
    }

    free(stack);
    printf("The linked list stack has been destroyed.\n");
}

int main(void) {
    LinkedListStack *stack = createLinkedListStack('A');
    printLinkedListStack(stack);

    pushElementToLinkedListStack(stack, 'B');
    printLinkedListStack(stack);

    pushElementToLinkedListStack(stack, 'C');
    printLinkedListStack(stack);

    pushElementToLinkedListStack(stack, 'D');
    printLinkedListStack(stack);

    pushElementToLinkedListStack(stack, 'E');
    printLinkedListStack(stack);

    printf("The top element of the linked list stack is %c.\n", peekElementOfLinkedListStack(stack));

    printf("The top element %c has been popped from the linked list stack.\n", popElementFromLinkedListStack(stack));
    printLinkedListStack(stack);

    printf("The top element %c has been popped from the linked list stack.\n", popElementFromLinkedListStack(stack));
    printLinkedListStack(stack);

    printf("The top element %c has been popped from the linked list stack.\n", popElementFromLinkedListStack(stack));
    printLinkedListStack(stack);

    printf("The top element %c has been popped from the linked list stack.\n", popElementFromLinkedListStack(stack));
    printLinkedListStack(stack);

    printf("The top element %c has been popped from the linked list stack.\n", popElementFromLinkedListStack(stack));
    printLinkedListStack(stack);

    destroyLinkedListStack(stack);

    return 0;
}

// -----
// | A
// -----
// ---------
// | B | A
// ---------
// -------------
// | C | B | A
// -------------
// -----------------
// | D | C | B | A
// -----------------
// ---------------------
// | E | D | C | B | A
// ---------------------
// The top element of the linked list stack is E.
// The top element E has been popped from the linked list stack.
// -----------------
// | D | C | B | A
// -----------------
// The top element D has been popped from the linked list stack.
// -------------
// | C | B | A
// -------------
// The top element C has been popped from the linked list stack.
// ---------
// | B | A 
// ---------
// The top element B has been popped from the linked list stack.
// -----
// | A
// -----
// The top element A has been popped from the linked list stack.
// The linked list stack is empty.
// The linked list stack has been destroyed.