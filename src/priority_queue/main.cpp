//
// Created by hammer on 7/16/20.
//

#include <iostream>
#include <vector>
#include "binary_heap.h"

int main() {
    std::vector<int> vector{61, 20, 47, 17, 12, 55, 37, 21, 64, 25, 45, 83, 73, 63, 92};
    BinaryHeap<int> binHeap;
    for (int i : vector) {
        binHeap.insert(i);
    }
    int minItem{0};
    while (!binHeap.isEmpty()) {
        binHeap.deleteMin(minItem);
        std::cout << minItem << " ";
    }
    std::cout << std::endl;

    BinaryHeap<int> binHeap2(vector);
    while (!binHeap2.isEmpty()) {
        binHeap2.deleteMin(minItem);
        std::cout << minItem << " ";
    }
    std::cout << std::endl;
    return 0;
}

