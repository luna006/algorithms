//
// Created by hammer on 7/17/20.
//

#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include <vector>
#include <stdexcept>

template<typename T>
class Queue {
public:
    virtual bool isEmpty() const = 0;
    virtual const T& getFront() const = 0;

    virtual void clear() = 0;
    virtual void enqueue(const T& item) = 0;
    virtual T dequeue() = 0;
};

template<typename T>
class QueueOnArray : public Queue<T> {
public:
    QueueOnArray() : array(INITIAL_QUEUE_SIZE) {}

    bool isEmpty() const override {
        return size == 0;
    }
    const T& getFront() const override;

    void clear() override;
    void enqueue(const T& item) override;
    T dequeue() override;

private:
    static constexpr int INITIAL_QUEUE_SIZE = 10;

    std::vector<T> array;
    std::size_t size = 0;
    std::size_t front = 0;
    std::size_t back = 0;

    void inc(std::size_t& index) const;
    bool isFull() const;
    void resizeQueue();
};

template<typename T>
class QueueOnList : public Queue<T> {
    template<typename Object>
    friend void swap(QueueOnList<Object>&, QueueOnList<Object>&);
public:
    QueueOnList() = default;
    QueueOnList(const QueueOnList<T>& otherQueue);
    QueueOnList<T>& operator=(QueueOnList<T> otherQueue);
    ~QueueOnList() {
        clear();
    }

    bool isEmpty() const override {
        return first == nullptr;
    }
    const T& getFront() const override;
    void clear() override;
    void enqueue(const T& item) override;
    T dequeue() override;
private:
    struct ListNode {
        T element;
        ListNode* next;

        explicit ListNode(const T& element, ListNode* next = nullptr) : element(element), next(next) {}
    };

    ListNode* first = nullptr;
    ListNode* back = nullptr;
};

template<typename T>
void QueueOnArray<T>::clear() {
    size = front = back = 0;
}

template<typename T>
void QueueOnArray<T>::inc(std::size_t &index) const {
    if (++index == array.size()) {
        index = 0;
    }
}

template<typename T>
bool QueueOnArray<T>::isFull() const {
    return size == array.size();
}

template<typename T>
void QueueOnArray<T>::enqueue(const T &item) {
    if (isFull()) {
        resizeQueue();
    }
    array[back] = item;
    inc(back);
    size++;
}

template<typename T>
void QueueOnArray<T>::resizeQueue() {
    array.resize(array.size() * 2 + 1);
    if (front != 0) {
        for (std::size_t i = 0; i < front; i++) {
            array[size + i] = array[i];
        }
        back += size;
    }
}

template<typename T>
T QueueOnArray<T>::dequeue() {
    if (isEmpty()) {
        throw std::invalid_argument("<<< dequeue >> Queue is empty");
    }
    T tmp = array[front];
    inc(front);
    size--;
    return tmp;
}

template<typename T>
const T& QueueOnArray<T>::getFront() const {
    if (isEmpty()) {
        throw std::invalid_argument("<<< getFront >> Queue is empty");
    }
    return array[front];
}

template<typename T>
QueueOnList<T>::QueueOnList(const QueueOnList<T>& otherQueue) {
    if (!otherQueue.isEmpty()) {
        ListNode* currNodeOther = otherQueue.first;
        ListNode* currNodeThis = new ListNode(currNodeOther->element);
        first = currNodeThis;
        for (currNodeOther = currNodeOther->next; currNodeOther != nullptr; currNodeOther = currNodeOther->next) {
            currNodeThis->next = new ListNode(currNodeOther->element);
            currNodeThis = currNodeThis->next;
        }
        back = currNodeThis;
    }
}

template<typename T>
inline void swap(QueueOnList<T>& first, QueueOnList<T>& second) {
    using std::swap;
    std::swap(first.first, second.first);
    std::swap(first.back, second.back);
}

template<typename T>
QueueOnList<T>& QueueOnList<T>::operator=(QueueOnList<T> otherQueue) {
    swap(*this, otherQueue);
    return *this;
}

template<typename T>
const T& QueueOnList<T>::getFront() const {
    if (isEmpty()) {
        throw std::invalid_argument("<<< getFront >>> Queue is empty");
    }
    return first->element;
}

template<typename T>
void QueueOnList<T>::enqueue(const T &item) {
    if (isEmpty()) {
        first = back = new ListNode(item);
    } else {
        back->next = new ListNode(item);
        back = back->next;
    }
}

template<typename T>
T QueueOnList<T>::dequeue() {
    T result = getFront();
    ListNode* oldFirstNode = first;
    first = first->next;
    delete oldFirstNode;
    return result;
}

template<typename T>
void QueueOnList<T>::clear() {
    ListNode* oldFirstNode = nullptr;
    while (!isEmpty()) {
        oldFirstNode = first;
        first = first->next;
        delete oldFirstNode;
    }
    back = nullptr;
}

#endif //ALGORITHMS_QUEUE_H
