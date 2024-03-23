/** 
 * @file stack_for_postfix_calculation.cpp
 * @brief An implementation of stack(stack_for_postfix_calculation.c) in C++, a stack for postfix calculation.
 *        Because this code is written in C++, it will use std::stack instead of a custom stack implementation.
 *        (C++ implementation of stack_for_postfix_calculation.c)
 */
//

#include <iostream>
#include <stack>

double evaluatePostfixExpression(std::string expression) {
    std::stack<double> stack;
    for (size_t index = 0; index < expression.length(); index++) {
        char currentCharacter = expression[index];
        if (isdigit(currentCharacter)) {
            // If the current character is a digit, then it is an operand.
            // Convert the string to a number(may have 2 or more digits) and push it to the stack.
            double operand = 0;
            while (isdigit(currentCharacter)) {
                operand = operand * 10 + (currentCharacter - '0');
                index++;
                currentCharacter = expression[index];
            }
            stack.push(operand);

            // Even when next current character is not a digit, the upper loop will increment the index.
            // So, decrement the index to point to the correct character.
            index--;
        } else if (currentCharacter == '+' || currentCharacter == '-' 
                || currentCharacter == '*' || currentCharacter == '/') {
            // If the current character is not a space, it should be an operator.
            // If it's neither an operand nor a space, it's an invalid character.
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid postfix expression. Not enough operands.");
            }
            double operand1 = stack.top(); stack.pop();
            double operand2 = stack.top(); stack.pop();
            switch (currentCharacter) {
                case '+':
                    stack.push(operand2 + operand1);
                    break;
                case '-':
                    stack.push(operand2 - operand1);
                    break;
                case '*':
                    stack.push(operand2 * operand1);
                    break;
                case '/':
                    stack.push(operand2 / operand1);
                    break;
            }
        } else if (currentCharacter != ' ') {
            throw std::invalid_argument("Invalid postfix expression. Invalid character.");
        }
    }

    // Check if the stack only has one element, which is the final result.
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }

    // The final result will be at the top of the stack.
    return stack.top();
}


int main(void) {
    const std::string postfixExpression = "10 3 5 * 16 4 - / +";
    std::cout << "Postfix expression: " << postfixExpression << std::endl;
    std::cout << "Result: " << evaluatePostfixExpression(postfixExpression) << std::endl;

    return 0;
}