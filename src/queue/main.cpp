//
// Created by hammer on 7/17/20.
//
#include <iostream>
#include <memory>
#include "queue.h"

int main() {
    std::shared_ptr<Queue<int>> queue = std::make_shared<QueueOnArray<int>>();
    for (int i = 0; i < 10; i++) {
        queue->enqueue(i);
    }
    std::cout << queue->dequeue() << std::endl;
    queue->enqueue(99);
    queue->enqueue(47);

    while (!queue->isEmpty()) {
        std::cout << queue->dequeue() << " ";
    }
    std::cout << std::endl;
    return 0;
}

