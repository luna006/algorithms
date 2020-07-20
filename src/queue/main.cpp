//
// Created by hammer on 7/17/20.
//
#include <iostream>
#include <memory>
#include "queue.h"

template<typename T>
void printQueue(std::shared_ptr<Queue<T>>& queue);

int main() {
    std::shared_ptr<Queue<int>> queue = std::make_shared<QueueOnArray<int>>();
    for (int i = 0; i < 10; i++) {
        queue->enqueue(i);
    }
    std::cout << queue->dequeue() << std::endl;
    queue->enqueue(99);
    queue->enqueue(47);

    printQueue(queue);
    std::cout << std::endl;

    std::cout << "Queue on linked list\n";
    queue.reset(new QueueOnList<int>());
    for (int i = 76; i > 69; --i) {
        queue->enqueue(i);
    }
    printQueue(queue);
    std::cout << std::endl;
    return 0;
}

template<typename T>
void printQueue(std::shared_ptr<Queue<T>>& queue) {
    while (!queue->isEmpty()) {
        std::cout << queue->dequeue() << " ";
    }
}

