// Basic stack(data structure) implementation
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

// Representing article
int stackTopIndex = -1;
int stack[MAX_STACK_SIZE];

// Is the current stack empty
bool isStackEmpty() {
    return stackTopIndex == -1;
}

// Is the current stack full
bool isStackFull() {
    return (stackTopIndex == MAX_STACK_SIZE - 1);
}

// Push an element to the stack
void stackPush(int data) {
    if (isStackFull()) {
        fprintf(stderr, "Stack is full\n");
        exit(-1);
    }
    stackTopIndex += 1;
    stack[stackTopIndex] = data;
}

// Pop an element from the stack
int stackPop() {
    if (isStackEmpty()) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }
    int data = stack[stackTopIndex];
    stackTopIndex -= 1;
    return data;
}

// Peek the top element of the stack
// It does not remove the element from the stack, but just returns the top element
int stackPeek() {
    if (isStackEmpty()) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }
    return stack[stackTopIndex];
}

int main(void) {
    for (int i = 0; i < 4; i++) {
        printf("Pushing: %d\n", i);
        stackPush(i);
    }

    for (int i = 0; i < 5; i++) {
        printf("Peeking: %d\n", stackPeek());
        printf("Popping: %d\n", stackPop());
        // Because this pops one more time than the number of elements pushed,
        // The stack will emit an error through stderr
    }

    return 0;
}
