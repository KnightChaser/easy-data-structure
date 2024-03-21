/**
 * @file stack_for_parenthesis_mathcing_check.c
 * @brief Check if the given expression has balanced parenthesis or not, with the help of stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

// Becaus the stack will be used for storing the parenthesis, so the stack will be of char type.
typedef char StackElement;
typedef struct {
    int stackTopIndex;
    StackElement stack[MAX_STACK_SIZE];
} Stack;

// Initializing stack, even resetting its memory space
void stackInitialization(Stack *stack) {
    memset(stack, 0, sizeof(Stack));
    stack->stackTopIndex = -1;
}

// Check if the stack is empty
int isStackEmpty(Stack *stack) {
    return stack->stackTopIndex == -1;
}

// Check if the stack is full
int isStackFull(Stack *stack) {
    return stack->stackTopIndex == MAX_STACK_SIZE - 1;
}

// Pushing an element to the stack
void stackPush(Stack *stack, StackElement data) {
    if (isStackFull(stack)) {
        fprintf(stderr, "Stack is full, can't push more data into the stack.\n");
        exit(-1);
    }
    stack->stackTopIndex += 1;
    stack->stack[stack->stackTopIndex] = data;
}

// Popping an element from the stack
StackElement stackPop(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty, can't pop more data from the stack.\n");
        exit(-1);
    }
    StackElement data = stack->stack[stack->stackTopIndex];
    stack->stackTopIndex -= 1;
    return data;
}

// Check if the given expression has balanced parenthesis or not
bool parenthesisMatchingCheck(const char *expression) {
    Stack stack;
    stackInitialization(&stack);

    // Loop through the expression, and push '(' to the stack, and pop ')' from the stack
    for (size_t index = 0; index < strlen(expression); index++) {
        char currentCharacter = expression[index];
        if (currentCharacter == '(') {
            stackPush(&stack, currentCharacter);
        } else if (currentCharacter == ')') {
            if (isStackEmpty(&stack)) {
                // Unbalanced parenthesis
                return false;
            }
            stackPop(&stack);
        }
    }

    // After the loop, the stack should be empty if the expression has correct parenthesis matching
    if (isStackEmpty(&stack))
        return true;
    else
        return false;
}

int main(void) {
    const char *expressionCorrect = "((a + b) * ((c - d) / (e + f)))";
    const char *expressionIncorrect = "((a + b) * ((c - d)) / (e + f))))";
    printf("The expression %s has %sbalanced parenthesis.\n\n", expressionCorrect, parenthesisMatchingCheck(expressionCorrect) ? "" : "un");
    printf("The expression %s has %sbalanced parenthesis.\n\n", expressionIncorrect, parenthesisMatchingCheck(expressionIncorrect) ? "" : "un");

    return 0;
}