#include <iostream>

#include <sort.h>

int main(int argc, const char** argv) {
    const int N = 10;
    int array[N] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    mergeSort(array, N);
    std::cout << "After sort: ";
    for (auto el : array) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}