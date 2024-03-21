/**
 * @file stack_with_realloc.c
 * @brief This file contains the implementation of a program that deals with stacks.
 *        To make more flexibility on the stack, realloc() will be used to expand the stack's memory space when it's full.
 *        So you can push more data into the stack without worrying about the stack's memory space.
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

typedef char StackElement[1024];
typedef struct {
    int stackTopIndex;
    int stackSize;
    StackElement *stack;
} Stack;

// Initializing stack, even resetting its memory space
void stackInitialization(Stack *stack) {
    stack->stackTopIndex = -1;
    stack->stackSize = 1;
    stack->stack = (StackElement *)malloc(sizeof(StackElement) * stack->stackSize);
}

// Check if the stack is empty
bool isStackEmpty(Stack *stack) {
    return stack->stackTopIndex == -1;
}

// Check if the stack is full
bool isStackFull(Stack *stack) {
    return stack->stackTopIndex == (stack->stackSize - 1);
}

// Pushing an element to the stack
void stackPush(Stack *stack, const StackElement data) {
    if (isStackFull(stack)) {
        // Expand the stack's memory space twice
        stack->stackSize *= 2;
        stack->stack = (StackElement *)realloc(stack->stack, sizeof(StackElement) * stack->stackSize);
        printf("Stack is full, expanded the stack's memory space from %d to %d.\n",(stack->stackSize)/2, stack->stackSize);
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
    StackElement* poppedData = (StackElement *)malloc(sizeof(StackElement));
    memcpy(poppedData, stack->stack[stack->stackTopIndex], sizeof(StackElement));
    stack->stackTopIndex -= 1;
    return poppedData;
}

// Peeking an element from the stack, not removing it
StackElement* stackPeek(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty, can't peek more data from the stack.\n");
        exit(-1);
    }
    StackElement* peekedData = (StackElement *)malloc(sizeof(StackElement));
    memcpy(peekedData, stack->stack[stack->stackTopIndex], sizeof(StackElement));
    return peekedData;
}

int main(void) {
    Stack stack;
    stackInitialization(&stack);

    // Pushing data into the stack
    StackElement stackElementArray[5] = {
        "First element",
        "Second element",
        "Third element",
        "Fourth element",
        "Fifth element"
    };
    for (int index = 0; index < 5; index++) {
        printf("Pushing: %s\n", stackElementArray[index]);
        stackPush(&stack, stackElementArray[index]);
    }

    // Peeking and popping data from the stack
    for (int index = 0; index < 6; index++) {
        StackElement *peekedData = stackPeek(&stack);
        printf("Peeking: %s\n", *peekedData);
        free(peekedData);

        StackElement *poppedData = stackPop(&stack);
        printf("Popping: %s\n", *poppedData);
        free(poppedData);
        // Because this tries to pop one more element than the stack would have, 
        // It will raise an error message that the stack is empty and exit the program.
    }

    return 0;
}