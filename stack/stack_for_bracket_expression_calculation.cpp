/*
 * @file stack_for_bracket_expression_calculation.cpp
 * @brief Calculating arithmetic expressions with brackets using stack in C++.
 *        Because this task is divided by converting infix expression to postfix expression and then evaluating the postfix expression,
 *        Char and Double stack will be used. (-> To provide polymorphism in data type for the stack, used C++ instead)
 */
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

// stack
template <typename StackType>
class Stack {
private:
    int stackTopIndex;
    int stackSize;
    StackType *stack;
public:
    // Constructor, initializes the stack
    Stack() {
        this->stackTopIndex = -1;
        this->stackSize = 1;
        this->stack = new StackType[this->stackSize];
        // std::cout << "Stack initialized with starting size " << this->stackSize << std::endl;
    }

    // Destructor, deallocates the memory
    ~Stack() {
        delete[] this->stack;
    }

    // Methods
    bool isStackEmpty();
    bool isStackFull();
    void push(StackType data);
    int getStackSize();
    StackType pop();
    StackType peek();
};

// Check if the stack is empty
template <typename StackType>
bool Stack<StackType>::isStackEmpty() {
    if (this->stackTopIndex == -1)
        return true;
    else
        return false;
}

// Check if the stack is full
template <typename StackType>
bool Stack<StackType>::isStackFull() {
    if (this->stackTopIndex == (this->stackSize - 1))
        return true;
    else
        return false;
}

// Get the size of the stack (how many elements are in the stack)
template <typename StackType>
int Stack<StackType>::getStackSize() {
    // Because the index starts from 0, the size of the stack is the index + 1
    return this->stackTopIndex + 1;
}

// Push data into the stack.
// If the stack is full, then double the size of the stack automatically.
template <typename StackType>
void Stack<StackType>::push(StackType data) {
    if (this->isStackFull()) {
        this->stackSize *= 2;
        // To reallocate the memory with double space, we need to create a new array and 
        // copy the elements from the old array to the new array
        // (Realloc() is not memory safe actually.)
        StackType *temp = new StackType[this->stackSize];
        for (int index = 0; index < this->stackSize / 2; index++)
            *(temp + index) = *(this->stack + index);
        delete[] this->stack;
        this->stack = temp;
        // std::cout << "Stack size doubled from " << this->stackSize / 2 << " to " << this->stackSize << std::endl;
    }
    this->stackTopIndex += 1;
    this->stack[this->stackTopIndex] = data;
}

// Pop data from the stack
// If the stack is empty, then throw an exception
template <typename StackType>
StackType Stack<StackType>::pop() {
    if (this->isStackEmpty())
        throw std::out_of_range("Stack is empty, can't pop anymore.");
    StackType data = this->stack[this->stackTopIndex];
    this->stackTopIndex -= 1;
    return data;
}

// Peek the top element of the stack
// If the stack is empty, then throw an exception
template <typename StackType>
StackType Stack<StackType>::peek() {
    if (this->isStackEmpty())
        throw std::out_of_range("Stack is empty, can't peek anymore.");
    return this->stack[this->stackTopIndex];
}

// method functions for calculating arithmetic expressions with brackets
class BracketExpressionCalculator {
private:
    Stack<char> *stackForFixConversion;
    Stack<double> *stackForPostfixEvaluation;
    std::string expression;
public:
        void initialization();
        int operatorPrecedence(const char op);
        std::string convertInfixToPostfix(const std::string infixExpression);
        double evaluatePostfixExpression(const std::string postfixExpression);
};

// Function declarations
void BracketExpressionCalculator::initialization() {
    this->stackForFixConversion = new Stack<char>();
    this->stackForPostfixEvaluation = new Stack<double>();
}

// Get the precedence of the operator
// The higher the number, the higher the precedence
int BracketExpressionCalculator::operatorPrecedence(const char op) {
    switch (op) {
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

// Convert infix expression to postfix expression
// Receives infix expression as input and returns to postfix expression
std::string BracketExpressionCalculator::convertInfixToPostfix(const std::string infixExpression) {
    
    std::stringstream postfixExpression;

    for (size_t index = 0; index < infixExpression.length(); index++) {
        const char currentCharacter = infixExpression[index];

        // If the current character is a "character"(operators, parentheses)
        switch(currentCharacter) {
            case '+':
            case '-':
            case '*':
            case '/':
                // If the current character is an operator, pop all operators with higher or equal precedence from the stack
                while (!this->stackForFixConversion->isStackEmpty() &&
                        (this->operatorPrecedence(this->stackForFixConversion->peek()) >= this->operatorPrecedence(currentCharacter))) {
                    postfixExpression << this->stackForFixConversion->pop() << " ";
                }
                this->stackForFixConversion->push(currentCharacter);
                break;
            case '(':
                // If the current character is an opening parenthesis, push it to the stack
                this->stackForFixConversion->push(currentCharacter);
                break;
            case ')':
            {
                // If the current character is a closing parenthesis, pop all operators from the stack until an opening parenthesis is encountered
                char topOperator = this->stackForFixConversion->pop();
                while (topOperator != '(') {
                    postfixExpression << topOperator << " ";
                    topOperator = this->stackForFixConversion->pop();
                }
                break;
            }
            case ' ':
                // Ignore spaces
                break;
            default: 
            {
                // If the current character is a digit
                if (isdigit(currentCharacter)) {
                    // If the current character is a digit, then it is an operand.
                    // Convert the string to a number(may have 2 or more digits) and push it to the stack.
                    double operand = 0;
                    while (isdigit(infixExpression[index])) {
                        operand = operand * 10 + (infixExpression[index] - '0');
                        index++;
                    }

                    // Make sure that every tokenizied element (numbers, operators) is separated by one space
                    if (isdigit(infixExpression[index + 1]))
                        postfixExpression << operand;
                    else   
                        postfixExpression << operand << " ";
                    continue;
                }

                // Because the current character is not an operator, a parenthesis, or a digit, it is an invalid character.
                std::string exceptionMessage = "Invalid character in the infix expression: " + std::string(1, currentCharacter) + "\n";
                throw std::invalid_argument(exceptionMessage);
            }
        }
    }

    // Pop all remaining operators from the stack and append them to the postfix expression
    while (!this->stackForFixConversion->isStackEmpty()) {
        postfixExpression << this->stackForFixConversion->pop() << " ";
    }

    return postfixExpression.str();
}

// Evaluate the postfix expression and return the result as double (number)
double BracketExpressionCalculator::evaluatePostfixExpression(const std::string postfixExpression) {
    for (size_t index = 0; index < postfixExpression.length(); index++) {
        char currentCharacter = postfixExpression[index];
        if (isdigit(currentCharacter)) {
            // If the current character is a digit, then it is an operand.
            // Conver the string to a number(may have 2 or more digits) and push it to the stack.
            double operand = 0;
            while (isdigit(currentCharacter)) {
                operand = operand * 10 + (currentCharacter - '0');
                index++;
                currentCharacter = postfixExpression[index];
            }
            this->stackForPostfixEvaluation->push(operand);

            // Even when next current character is not a digit, the upper loop will increment the index.
            // So, decrement the index to point to the correct character.
            index -= 1;
        } else if (currentCharacter == '+' || currentCharacter == '-'
                || currentCharacter == '*' || currentCharacter == '/') {
            // Event when next character is not a space, it should be an operator.
            // If it's neither an operand nor a space, it's an invalid character.
            if (this->stackForPostfixEvaluation->getStackSize() < 2) {
                throw std::invalid_argument("Invalid postfix expression. Not enough operands.");
            }
            double operand1 = this->stackForPostfixEvaluation->pop();
            double operand2 = this->stackForPostfixEvaluation->pop();
            switch (currentCharacter) {
                case '+':
                    this->stackForPostfixEvaluation->push(operand2 + operand1);
                    break;
                case '-':
                    this->stackForPostfixEvaluation->push(operand2 - operand1);
                    break;
                case '*':
                    this->stackForPostfixEvaluation->push(operand2 * operand1);
                    break;
                case '/':
                    this->stackForPostfixEvaluation->push(operand2 / operand1);
                    break;
            }
        } else if (currentCharacter != ' ') {
            std::string exceptionMessage = "Invalid postfix expression. Invalid character: " + std::string(1, currentCharacter) + "\n";
            throw std::invalid_argument(exceptionMessage);
        }
    }

    // Check if the stack only has one element, which is the final result.
    if (this->stackForPostfixEvaluation->getStackSize() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }

    // The final result will be at the top of the stack.
    return this->stackForPostfixEvaluation->pop();
}

int main(void) {
    BracketExpressionCalculator calculator;
    calculator.initialization();

    // Please note that the expression should be separated by space for every tokenized element, (numbers, operators)

    std::string infixExpression = "( ( 20 * 9 ) + 8 ) - 20 + 3 - ( 5 + 9 )";
    std::string postfixExpression = calculator.convertInfixToPostfix(infixExpression);
    std::cout << "Infix expression: " << infixExpression << std::endl;
    std::cout << "Postfix expression: " << postfixExpression << std::endl;

    double result = calculator.evaluatePostfixExpression(postfixExpression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

// Example
// Infix expression: ( ( 20 * 9 ) + 8 ) - 20 + 3 - ( 5 + 9 )
// Postfix expression: 20 9 * 8 + 20 - 3 + 5 9 + -
// Result: 157