/*
 * @file stack_with_polymorphism.c
 * @brief This file contains the implementation of a program that deals with stacks.
 *        To make more flexibility on the stack, void* will be used to store any type of data.
 *        Even though it's quite complicated, it also can be called as polymorphism.
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// StackElement is a void pointer that can store any type of data
typedef struct {
    int stackTopIndex;
    int stackSize;
    void **stack;       // an array of void* data
} Stack;

// Initializing stack, even resetting its memory space
void stackInitialization(Stack *stack) {
    stack->stackTopIndex = -1;
    stack->stackSize = 1;
    stack->stack = (void **)malloc(sizeof(void *) * stack->stackSize);
    memset(stack->stack, 0, sizeof(void *) * stack->stackSize);             // for data safety
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
void stackPush(Stack *stack, void *data, size_t dataSize) {
    if (isStackFull(stack)) {
        // Expand the stack's memory space twice
        stack->stackSize *= 2;
        stack->stack = (void **)realloc(stack->stack, sizeof(void *) * stack->stackSize);
        printf("Stack is full, expanded the stack's memory space from %d to %d.\n", (stack->stackSize) / 2, stack->stackSize);
    }
    stack->stackTopIndex += 1;
    stack->stack[stack->stackTopIndex] = malloc(dataSize);
    memset(stack->stack[stack->stackTopIndex], 0, dataSize);                // for data safety
    memcpy(stack->stack[stack->stackTopIndex], data, dataSize);
}


// Popping an element from the stack
void* stackPop(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty, can't pop more data from the stack.\n");
        exit(-1);
    }
    void* poppedData = stack->stack[stack->stackTopIndex];
    stack->stackTopIndex -= 1;
    return poppedData;
}

// Peeking an element from the stack, not removing it
void* stackPeek(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty, can't peek more data from the stack.\n");
        exit(-1);
    }
    return stack->stack[stack->stackTopIndex];
}

// Example struct
typedef struct {
    float x;
    float y;
} XYCoordinate;

int main(void) {
    Stack stack;
    stackInitialization(&stack);

    // Pushing different types of data to the stack
    char charData = 'A';
    stackPush(&stack, &charData, sizeof(char));

    int intData = 123;
    stackPush(&stack, &intData, sizeof(int));

    float floatData = 3.14;
    stackPush(&stack, &floatData, sizeof(float));

    XYCoordinate xyData = {-10.49, 2.71};
    stackPush(&stack, &xyData, sizeof(XYCoordinate));

    char stringData[] = "void* han direct literally any type of data";
    stackPush(&stack, stringData, strlen(stringData) + 1);      // +1 for null-terminator


    // Popping and peeking data from the stack
    char *poppedStringData = (char *)stackPop(&stack);
    printf("Peeked data: %s\n", poppedStringData);
    free(poppedStringData);

    XYCoordinate *poppedXYData = (XYCoordinate *)stackPop(&stack);
    printf("Popped data: {this.x => %f, this.y => %f}\n", poppedXYData->x, poppedXYData->y);
    free(poppedXYData);

    float *poppedFloatData = (float *)stackPop(&stack);
    printf("Popped data: %f\n", *poppedFloatData);
    free(poppedFloatData);

    int *poppedIntData = (int *)stackPop(&stack);
    printf("Popped data: %d\n", *poppedIntData);
    free(poppedIntData);

    char *poppedCharData = (char *)stackPop(&stack);
    printf("Popped data: %c\n", *poppedCharData);
    free(poppedCharData);

    // Free the stack's memory space
    for (int index = 0; index <= stack.stackTopIndex; index++) {
        free(stack.stack[index]);
    }

    return 0;
}
