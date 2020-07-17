//
// Created by hammer on 7/17/20.
//

#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
public:
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;

    virtual const T& top() const = 0;
    virtual void push(const T& item) = 0;
    virtual void pop() = 0;
    virtual T topAndPop() = 0;
};

template<typename T>
class StackOnArray : public Stack<T> {
public:
    StackOnArray() : array(INITIAL_STACK_SIZE) {}

    bool isEmpty() const override {
        return tos == TOP_OF_EMPTY_STACK;
    }
    void clear() override {
        tos = TOP_OF_EMPTY_STACK;
    }

    const T& top() const override;
    void push(const T& item) override;
    void pop() override;
    T topAndPop() override;
private:
    static constexpr int TOP_OF_EMPTY_STACK = -1;
    static constexpr std::size_t INITIAL_STACK_SIZE = 10;
    int tos = TOP_OF_EMPTY_STACK;
    std::vector<T> array;
};

template<typename T>
const T& StackOnArray<T>::top() const {
    if (isEmpty()) {
        throw std::invalid_argument("<<< top() >>> Stack is empty");
    }
    return array[tos];
}

template<typename T>
void StackOnArray<T>::push(const T &item) {
    if (static_cast<typename std::vector<T>::size_type>(tos + 1) == array.size()) {
        array.resize(array.size() * 2 + 1);
    }
    array[++tos] = item;
}

template<typename T>
void StackOnArray<T>::pop() {
    if (isEmpty()) {
        throw std::invalid_argument("<<< pop >>> Stack is empty");
    }
    tos--;
}

template<typename T>
T StackOnArray<T>::topAndPop() {
    if (isEmpty()) {
        throw std::invalid_argument("<<< topAndPop >>> Stack is empty");
    }
    return array[tos--];
}

#endif //ALGORITHMS_STACK_H
