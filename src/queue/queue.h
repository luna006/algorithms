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

#endif //ALGORITHMS_QUEUE_H
