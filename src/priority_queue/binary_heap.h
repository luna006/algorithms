//
// Created by hammer on 7/14/20.
//

#ifndef ALGORITHMS_BINARY_HEAP_H
#define ALGORITHMS_BINARY_HEAP_H


#include <vector>
#include <stdexcept>

template<typename Comparable>
class BinaryHeap {
public:
    BinaryHeap() = default;
    explicit BinaryHeap(const std::vector<Comparable>& initVector);
    bool isEmpty() const {
        return size == 0;
    }
    const Comparable& findMin() const;
    void insert(const Comparable& item);
    void deleteMin();
    void deleteMin(Comparable& item);
    void clear() {
        size = 0;
    }

private:
    static constexpr std::size_t NUMBER_NOT_USED_ELEMENTS = 1;
    std::size_t size = 0;
    std::vector<Comparable> array{NUMBER_NOT_USED_ELEMENTS};

    void buildHeap();
    void percolateDown(std::size_t hole);
    std::size_t getLeftChild(std::size_t itemIndex) const {
        return itemIndex << 1;
    }
    std::size_t getRightChild(std::size_t itemIndex) const {
        return (itemIndex << 1) + 1;
    }

    std::size_t getParent(std::size_t itemIndex) const {
        return itemIndex >> 1;
    }
};

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable>& initVector) : size(initVector.size()) {
    std::copy(initVector.cbegin(), initVector.cend(), std::back_inserter(array));
    buildHeap();
}

template<typename Comparable>
const Comparable & BinaryHeap<Comparable>::findMin() const {
    if (isEmpty()) {
        throw std::invalid_argument("PQueue is empty");
    }
    return array[1];
}

template<typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable &item) {
    array[0] = item;
    if (size + 1 == array.size()) {
        array.resize(array.size() * 2 + 1);
    }
    std::size_t hole = ++size;
    for (; item < array[hole / 2]; hole /= 2) {
        array[hole] = array[hole / 2];
    }
    array[hole] = item;
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin() {
    if (isEmpty()) {
        throw std::invalid_argument("PQueue is empty");
    }
    array[1] = array[size--];
    percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable &item) {
    item = findMin();
    array[1] = array[size--];
    percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::percolateDown(std::size_t hole) {
    std::size_t indexSmallestItem = hole;
    Comparable tmp = array[hole];
    for (; getLeftChild(hole) <= size; hole = indexSmallestItem) {
        indexSmallestItem = getLeftChild(hole);
        if (getRightChild(hole) <= size && array[getRightChild(hole)] < array[getLeftChild(hole)]) {
            indexSmallestItem = getRightChild(hole);
        }
        if (array[indexSmallestItem] < tmp) {
            array[hole] = array[indexSmallestItem];
        } else {
            break;
        }
    }
    array[hole] = tmp;
}

template<typename Comparable>
void BinaryHeap<Comparable>::buildHeap() {
    for (std::size_t i = size / 2; i > 0; --i) {
        percolateDown(i);
    }
}

#endif //ALGORITHMS_BINARY_HEAP_H
