/**
 * @file stack_basic.cpp
 * @brief An implementation of basic stack(stack_basic.c) in C++, an integer stack.
*/

#include <iostream>
#include <stdexcept>

#define MAX_STACK_SIZE 5

class Stack {
private:
    int stackTopIndex;
    int stack[MAX_STACK_SIZE];
public:
    // Constructor, initializes the stack
    Stack() {
        std::cout << "Stack initialized with max size of " << MAX_STACK_SIZE << std::endl;
        this->stackTopIndex = -1;
    }

    bool isStackEmpty() const;
    bool isStackFull() const;
    void push(int data);
    int pop();
    int peek() const;
};

// Check if the stack is empty
bool Stack::isStackEmpty() const {
    if (this->stackTopIndex == -1)
        return true;
    else
        return false;
}

// Check if the stack is full
bool Stack::isStackFull() const {
    if (this->stackTopIndex == (MAX_STACK_SIZE - 1))
        return true;
    else
        return false;
}

// Push data into the stack
void Stack::push(int data) {
    if (isStackFull()) {
        std::cout << "Stack is full" << std::endl;
        throw std::overflow_error("Stack is full, so can't push data into it.");
    }
    this->stackTopIndex += 1;
    stack[this->stackTopIndex] = data;
}

// Pop data from the stack
int Stack::pop() {
    if (isStackEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        throw std::underflow_error("Stack is empty, so can't pop data from it.");
    } 
    int data = stack[stackTopIndex];
    this->stackTopIndex -= 1;
    return data;
}

// Peek data from the stack
int Stack::peek() const {
    if (isStackEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        throw std::underflow_error("Stack is empty, so can't peek data from it.");
    }
    return stack[stackTopIndex];
}

int main(void) {
    Stack stack;

    try {
        for (int index = 1; index <= MAX_STACK_SIZE; index++) {
            std::cout << "pushing: " << index << std::endl;
            stack.push(index);
        }

        for (int index = 0; index < MAX_STACK_SIZE + 1; index++) {
            std::cout << "peeking: " << stack.peek() << std::endl;
            std::cout << "popping: " << stack.pop() << std::endl;
        }
    } catch (const std::exception& exception) {
        std::cout << "Exception during handling the stack: " << exception.what() << std::endl;
    }

    return 0;
}
