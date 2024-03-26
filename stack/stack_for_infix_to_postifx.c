/*
 * @file stack_for_infix_to_postfix.c
 * @brief Convert the given infix expression to postfix expression with the help of stack.
 */
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

// Stack
typedef char StackElement;
typedef struct {
    int stackTopIndex;
    StackElement items[MAX_STACK_SIZE];
} Stack;

// Initialize the stack
void stackInitialization(Stack *stack) {
    stack->stackTopIndex = -1;
    memset(stack->items, 0, sizeof(stack->items));
}

// Is the current stack empty
bool isStackEmpty(Stack *stack) {
    return stack->stackTopIndex == -1;
}

// Is the current stack full
bool isStackFull(Stack *stack) {
    return (stack->stackTopIndex == MAX_STACK_SIZE - 1);
}

// Push an element to the stack
void stackPush(Stack *stack, StackElement data) {
    if (isStackFull(stack)) {
        fprintf(stderr, "Stack is full\n");
        exit(-1);
    }
    stack->stackTopIndex += 1;
    stack->items[stack->stackTopIndex] = data;
}

// Pop an element from the stack
StackElement stackPop(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }
    StackElement data = stack->items[stack->stackTopIndex];
    stack->stackTopIndex -= 1;
    return data;
}

// Peek the top element of the stack
StackElement stackPeek(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }
    return stack->items[stack->stackTopIndex];
}

// Decide the precedence of the operator
// The higher the number, the higher the precedence
int operatorPrecedence(const char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Convert the given infix expression to postfix expression
void convertInfixToPostfix(const char* infixExpression, char *postfixExpression) {
    Stack stack;
    stackInitialization(&stack);
    while (*infixExpression) {
        const char currentCharacter = *infixExpression;
        // If the current character is a digit
        if (isdigit(currentCharacter)) {
            // If the current character is a digit, then it is an operand.
            // Convert the string to a number(may have 2 or more digits) and push it to the stack.
            StackElement operand = 0;
            while (isdigit(*infixExpression)) {
                operand = operand * 10 + (*infixExpression - '0');
                infixExpression++;
            }

            // Make sure that every tokenized element(numbers, operators) is separated by one space(' ').
            if (isdigit(*(infixExpression + 1)))
                sprintf(postfixExpression, "%s%d ", postfixExpression, operand);
            else
                sprintf(postfixExpression, "%s%d", postfixExpression, operand);
            continue;
        }

        // If the current character is a "character"(operators, parentheses)
        switch (currentCharacter) {
            case '+':
            case '-':
            case '*':
            case '/':
                // If the current character is an operator, pop all operators with higher or equal precedence from the stack.
                while (!isStackEmpty(&stack) && operatorPrecedence(stackPeek(&stack)) >= operatorPrecedence(currentCharacter)) {
                    sprintf(postfixExpression, "%s %c ", postfixExpression, stackPop(&stack));
                }
                stackPush(&stack, currentCharacter);
                break;
            case '(':
                // If the current character is '(', push it to the stack.
                stackPush(&stack, currentCharacter);
                break;
            case ')': {
                // If the current character is ')', pop all operators until '(' is popped from the stack.
                StackElement topOperator = stackPop(&stack);
                while (topOperator != '(') {
                    sprintf(postfixExpression, "%s %c", postfixExpression, topOperator);
                    topOperator = stackPop(&stack);
                }
                break;
            }
            case ' ':
                // Ignore space
                continue;
            default:
                fprintf(stderr, "Invalid character %c\n", currentCharacter);
        }
        infixExpression++;
    }

    // Print every operator in the stack
    while (!isStackEmpty(&stack)) {
        sprintf(postfixExpression, "%s %c", postfixExpression, stackPop(&stack));
    }
}

int main(void) {
    const char* infixExpression = "13+20/2*(10-3+(8*15))";
    char postfixExpression[100] = {0, };
    convertInfixToPostfix(infixExpression, postfixExpression);

    printf("  Infix expression: %s\n", infixExpression);
    printf("Postfix expression: %s\n", postfixExpression);

    return 0;
}

// == Example Output ==
//   Infix expression: 13+20/2*(10-3+(8*15))
// Postfix expression: 13 20 2 / 10 3 - 8 15 * + * +

// Because the stack for infix to postfix is based on char,
// and the stack for postfix calculation is based on float or double,
// the stack for infix to postfix is not compatible with the stack for postfix calculation.
// To make it compatible, you need to change the StackElement type to float or double. -> polymorphism (You will be need to use C++!)