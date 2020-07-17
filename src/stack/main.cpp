//
// Created by hammer on 7/17/20.
//
#include <memory>
#include <iostream>
#include "stack.h"

int main() {
    std::shared_ptr<Stack<int>> stack = std::make_shared<StackOnArray<int>>();
    stack->push(4);
    stack->push(7);
    stack->push(90);
    stack->push(0);
    while (!stack->isEmpty()) {
        std::cout << stack->topAndPop() << std::endl;
    }
    return 0;
}
