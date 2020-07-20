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
class StackOnList : public Stack<T> {
    template<typename Object>
    friend void swap(StackOnList<Object>&, StackOnList<Object>&);
public:
    StackOnList() = default;
    StackOnList(const StackOnList<T>& otherStack);
    StackOnList<T>& operator=(StackOnList<T> otherStack);
    ~StackOnList() {
        clear();
    }

    bool isEmpty() const override {
        return topOfStack == nullptr;
    }
    void clear() override;

    const T& top() const override;
    void push(const T& item) override;
    void pop() override;
    T topAndPop() override;

private:
    struct ListNode {
        T element;
        ListNode* next;

        explicit ListNode(const T& element, ListNode* next = nullptr) : element(element), next(next) {}
    };
    ListNode* topOfStack = nullptr;

    static void moveNext(ListNode*& node) {
        node = node->next;
    }
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

template<typename T>
StackOnList<T>::StackOnList(const StackOnList<T>& otherStack) {
    if (!otherStack.isEmpty()) {
        ListNode* currentNodeOfOtherStack = otherStack.topOfStack;
        ListNode* currentNodeOfThisStack = new ListNode(currentNodeOfOtherStack->element);
        topOfStack = currentNodeOfThisStack;
        for (moveNext(currentNodeOfOtherStack); currentNodeOfOtherStack != nullptr; moveNext(currentNodeOfOtherStack)) {
            currentNodeOfThisStack->next = new ListNode(currentNodeOfOtherStack->element);
            moveNext(currentNodeOfThisStack);
        }
    }
}

template<typename T>
inline void swap(StackOnList<T>& firstStack, StackOnList<T>& secondStack) {
    using std::swap;
    swap(firstStack.topOfStack, secondStack.topOfStack);
}

template<typename T>
StackOnList<T>& StackOnList<T>::operator=(StackOnList<T> otherStack) {
    swap(*this, otherStack);
    return *this;
}

template<typename T>
void StackOnList<T>::clear() {
    ListNode* currentNode = topOfStack;
    while (topOfStack) {
        currentNode = topOfStack;
        moveNext(topOfStack);
        delete currentNode;
    }
}

template<typename T>
void StackOnList<T>::push(const T& item) {
    topOfStack = new ListNode(item, topOfStack);
}

template<typename T>
void StackOnList<T>::pop() {
    if (isEmpty()) {
        throw std::invalid_argument("<<< pop >> Stack is empty");
    }
    ListNode* oldTopOfStack = topOfStack;
    moveNext(topOfStack);
    delete oldTopOfStack;
}

template<typename T>
const T& StackOnList<T>::top() const {
    return topOfStack->element;
}

template<typename T>
T StackOnList<T>::topAndPop() {
    if (isEmpty()) {
        throw std::invalid_argument("<<< pop >> Stack is empty");
    }
    T result = topOfStack->element;
    ListNode* oldTopOfStack = topOfStack;
    moveNext(topOfStack);
    delete oldTopOfStack;
    return result;
}

#endif //ALGORITHMS_STACK_H
