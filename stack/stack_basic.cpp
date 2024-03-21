/**
 * @file stack_basic.cpp
 * @brief An implementation of basic stack(stack_basic.c) in C++, an integer stack.
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#define MAX_STACK_SIZE 5

class Stack {
private:
    int stackTopIndex;
    int stack[MAX_STACK_SIZE];
public:
    void initialization();
    bool isStackEmpty();
    bool isStackFull();
    void push(int data);
    int pop();
    int peek();
};

// Stack initialization
void Stack::initialization() {
    this->stackTopIndex = -1;
    memset(this->stack, 0, sizeof(this->stack));
}

// Check if the stack is empty
bool Stack::isStackEmpty() {
    if (this->stackTopIndex == -1)
        return true;
    else
        return false;
}

// Check if the stack is full
bool Stack::isStackFull() {
    if (this->stackTopIndex == (MAX_STACK_SIZE - 1))
        return true;
    else
        return false;
}

// Push data into the stack
void Stack::push(int data) {
    if (this->isStackFull()) {
        std::cout << "Stack is full" << std::endl;
        throw std::overflow_error("Stack is full, so can't push data into it.");
    }
    this->stackTopIndex += 1;
    this->stack[this->stackTopIndex] = data;
}

// Pop data from the stack
int Stack::pop() {
    if (this->isStackEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        throw std::underflow_error("Stack is empty, so can't pop data from it.");
    } 
    int data = this->stack[this->stackTopIndex];
    this->stackTopIndex -= 1;
    return data;
}

// Peek the top of the stack, without removing it
int Stack::peek() {
    if (this->isStackEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        throw std::underflow_error("Stack is empty, so can't peek data from it.");
    }
    return this->stack[this->stackTopIndex];
}

int main(void) {

    // Stack intialization and pushing
    Stack stack;
    stack.initialization();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    // Peeking and popping data from the stack.
    try {
        for (int i = 0; i < MAX_STACK_SIZE + 1; i++) {
            std::cout << "peeking: " << stack.peek() << std::endl;
            std::cout << "popping: " << stack.pop() << std::endl;
        }
    } catch (std::exception& exception) {
        std::cout << "Exception during handling the stack: " << exception.what() << std::endl;
    }

    return 0;
}