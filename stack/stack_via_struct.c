// Stack(data structure) implementation via struct
// Each stack element(typedef char StackElement[1024]) can handle up to 1,024 bytes long characters(including NULL terminator).
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char StackElement[1024];
typedef struct {
    int stackTopIndex;
    StackElement stack[MAX_STACK_SIZE];
} Stack;

// Initializing stack, even resetting its memory space
void stackInit(Stack *stack) {
    memset(stack, 0, sizeof(Stack));
    stack->stackTopIndex = -1;
}

// Check if the stack is empty
bool isStackEmpty(Stack *stack) {
    return stack->stackTopIndex == -1;
}

// Check if the stack is full
bool isStackFull(Stack *stack) {
    return stack->stackTopIndex == MAX_STACK_SIZE - 1;
}

// Pushing an element to the stack
void stackPush(Stack *stack, StackElement data) {
    if (isStackFull(stack)) {
        fprintf(stderr, "Stack is full, can't push more data into the stack.\n");
        exit(-1);
    }
    stack->stackTopIndex += 1;
    memcpy(stack->stack[stack->stackTopIndex], data, sizeof(StackElement));
}

// Popping an element from the stack
StackElement* stackPop(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty, can't pop more data from the stack.\n");
        exit(-1);
    }
    StackElement* data = malloc(sizeof(StackElement));
    memcpy(data, stack->stack[stack->stackTopIndex], sizeof(StackElement));
    stack->stackTopIndex -= 1;
    return data;
}

// Seeking an element from the stack, not removing it
StackElement* stackPeek(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty, can't peek more data from the stack.\n");
        exit(-1);
    }
    StackElement* data = malloc(sizeof(StackElement));
    memcpy(data, stack->stack[stack->stackTopIndex], sizeof(StackElement));
    return data;
}

int main(void) {
    Stack stack;
    stackInit(&stack);

    // Pushing elements to the stack
    StackElement stackElementArray[3] = {"Hello World", "It's me, stack", "Stack is fun"};
    for (int i = 0; i < 3; i++) {
        printf("Pushing: %s\n",stackElementArray[i]);
        stackPush(&stack, stackElementArray[i]);
    }

    // Peeking and popping elements from the stack
    for (int i = 0; i < 5; i++) {
        StackElement* peeked = stackPeek(&stack);
        printf("Peeking: %s\n", *peeked);
        free(peeked);
        // free() for stackPeek() and stackPop() is necessary to prevent memory leaks,
        // because they allocate memory for the return string values as char* type.

        StackElement* popped = stackPop(&stack);
        printf("Popping: %s\n", *popped);
        free(popped);
        // Because this pops one more time than the number of elements pushed,
        // The stack will emit an error through stderr.
    }

    return 0;
}
