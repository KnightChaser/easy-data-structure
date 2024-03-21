/**
 * @file stack_for_postfix_calculation.c
 * @brief Evaluate the given postfix expression with the help of stack.
 *        The postfix expression is the expression in which the operator comes after the operands, such as "23+5*".
 */
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

// Stack
typedef double StackElement;
typedef struct {
    int stackTopIndex;
    StackElement items[MAX_STACK_SIZE];
} Stack;

// Initialize the stack
void stackInitialization(Stack *stack) {
    stack->stackTopIndex = -1;
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

// Evaluate the given postfix expression, such as "10 3 5 * 16 4 - / +".
StackElement evaluatePostfixExpression(const char* postfixExpression) {
    Stack stack;
    stackInitialization(&stack);

    while(*postfixExpression) {
        const char currentCharacter = (char)*postfixExpression;
        if (isdigit(currentCharacter)) {
            // If the current character is a digit, then it is an operand.
            // Conver the string to a number(may have 2 or more digits) and push it to the stack.
            StackElement operand = 0;
            while (isdigit(*postfixExpression)) {
                operand = operand * 10 + (*postfixExpression - '0');
                postfixExpression++;
            }
            stackPush(&stack, operand);
        } else if (
            currentCharacter == '+' || currentCharacter == '-' ||
            currentCharacter == '*' || currentCharacter == '/'
        ) {
            // If the current character is an operator, then pop two operands from the stack,
            // perform the arithmetic operation and push the result back to the stack.
            StackElement operand1 = stackPop(&stack);
            StackElement operand2 = stackPop(&stack);
            switch (currentCharacter) {
                case '+':
                    stackPush(&stack, operand1 + operand2);
                    break;
                case '-':
                    stackPush(&stack, operand2 - operand1);
                    break;
                case '*':
                    stackPush(&stack, operand1 * operand2);
                    break;
                case '/':
                    stackPush(&stack, operand2 / operand1);
                    break;
                default:
                    fprintf(stderr, "Invalid operator, only +, -, *, / are allowed but %c received\n", currentCharacter);
                    exit(-1);
            }
        }

        // Move to the next character
        // If the current character is a space(works as seperators), then move to the next character
        postfixExpression++;
    }
    // The result of the postfix expression is the only element in the stack
    StackElement result = stackPop(&stack);
    return result;
}

int main(void) {
    const char* postfixExpression = "10 3 5 * 16 4 - / +";
    printf("The result of the postfix expression \"%s\" is %f\n", postfixExpression, evaluatePostfixExpression(postfixExpression));

    return 0;
}