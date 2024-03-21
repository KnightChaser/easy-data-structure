/**
 * @file stack_with_realloc.cpp
 * @brief An implementation of stack with realloc(stack_with_realloc.c) in C++, an integer stack.
 */

#include <iostream>
#include <string>
#include <stdexcept>

typedef std::string StackElement;

class Stack {
private:
    int stackTopIndex;
    int stackSize;
    StackElement *stack;
public:
    // Constructor, initializes the stack
    Stack() {
        this->stackTopIndex = -1;
        this->stackSize = 1;
        this->stack = new StackElement[this->stackSize];
        std::cout << "Stack initialized with starting size " << this->stackSize << std::endl;
    }

    // Destructor, deallocates the memory
    ~Stack() {
        delete[] this->stack;
    }

    // Methods
    bool isStackEmpty();
    bool isStackFull();
    void push(StackElement data);
    StackElement pop();
    StackElement peek();
};

// Check if the stack is empty
bool Stack::isStackEmpty() {
    if (this->stackTopIndex == -1)
        return true;
    else
        return false;
}

// Check if the stack is full
bool Stack::isStackFull() {
    if (this->stackTopIndex == (this->stackSize - 1))
        return true;
    else
        return false;
}

// Push data into the stack
// If the stack is full, then double the size of the stack automatically
void Stack::push(StackElement data) {
    if (this->isStackFull()) {
        this->stackSize *= 2;
        // To reallocate the memory with double space, we need to create a new array and 
        // copy the elements from the old array to the new array
        // (Realloc() is not memory safe actually.)
        StackElement *temp = new StackElement[this->stackSize];
        for (int index = 0; index < this->stackSize / 2; index++) {
            *(temp + index) = *(this->stack + index);
        }
        delete[] this->stack;
        this->stack = temp;
        std::cout << "Stack size doubled from " << this->stackSize / 2 << " to " << this->stackSize << std::endl;
    }
    this->stackTopIndex += 1;
    this->stack[this->stackTopIndex] = data;
}

// Pop data from the stack
// If the stack is empty, then throw an exception
StackElement Stack::pop() {
    if (this->isStackEmpty()) {
        throw std::underflow_error("Stack is empty, so can't pop data from it.");
    }
    StackElement poppedData = this->stack[this->stackTopIndex];
    this->stackTopIndex -= 1;
    return poppedData;
}

// Peek the top of the stack, without removing it
// If the stack is empty, then throw an exception
StackElement Stack::peek() {
    if (this->isStackEmpty()) {
        throw std::underflow_error("Stack is empty, so can't peek data from it.");
    }
    return this->stack[this->stackTopIndex];
}

int main(void) {
    Stack stack;

    // Pushing
    for (int index = 0; index < 10; index++) {
        std::string data = "Data " + std::to_string(index);
        std::cout << "Pushing " << data << " into the stack" << std::endl;
        stack.push(data);
    }

    // Peeking and popping data from the stack
    try {
        for (int index = 0; index < 11; index++) {
            std::cout << "Peeking: " << stack.peek() << std::endl;
            std::cout << "Popping: " << stack.pop() << std::endl;
        }
    } catch (std::exception& exception) {
        // Because we are popping one more times than the stack would have, exception will be triggered.
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}