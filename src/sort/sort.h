#pragma once
#include <cstddef>
#include <utility>

template<typename T> void insertSort(T* array, const std::size_t n) {
    for (std::size_t i = 1; i < n; i++) {
        for (std::size_t j = i; j > 0 && array[j] < array[j - 1]; j--) {
            std::swap(array[j - 1], array[j]);
        }
    }
}

template<typename T> void selectSort(T* array, const std::size_t n) {
    std::size_t selectedIndex = 0;
    for (std::size_t i = 0; i < n - 1; i++) {
        selectedIndex = i;
        for (std::size_t j = i + 1; j < n; j++) {
            if (array[selectedIndex] > array[j]) {
                selectedIndex = j;
            }
        }
        if (selectedIndex > i) {
            std::swap(array[i], array[selectedIndex]);
        }
    }
}

void mergeSort(int* array, const std::size_t n);