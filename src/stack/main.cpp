//
// Created by hammer on 7/17/20.
//
#include <memory>
#include <iostream>
#include "stack.h"

void printStack(const std::shared_ptr<Stack<int>>& stackPtr);

int main() {
    std::shared_ptr<Stack<int>> stack = std::make_shared<StackOnArray<int>>();
    stack->push(4);
    stack->push(7);
    stack->push(90);
    stack->push(0);
    printStack(stack);

    stack.reset(new StackOnList<int>());
    std::cout << "Stack on linked list" << std::endl;
    stack->push(2312);
    stack->push(19999);
    stack->push(20000);
    stack->push(6666666);
    printStack(stack);

    return 0;
}

void printStack(const std::shared_ptr<Stack<int>>& stackPtr) {
    while (!stackPtr->isEmpty()) {
        std::cout << stackPtr->topAndPop() << std::endl;
    }
}
