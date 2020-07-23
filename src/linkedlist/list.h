//
// Created by hammer on 7/21/20.
//

#ifndef ALGORITHMS_LIST_H
#define ALGORITHMS_LIST_H

template<typename T>
class List;

template<typename T>
class ListIterator;

template<typename T>
class ListNode {
    friend class List<T>;
    friend class ListIterator<T>;

    explicit ListNode(const T& element = T(), ListNode<T>* next = nullptr) : element(element), next(next) {}

    T element;
    ListNode* next = nullptr;
};

template<typename T>
class ListIterator {
    friend class List<T>;
public:
    ListIterator() = default;
    bool isValid() const {
        return currentNode != nullptr;
    }
    ListIterator<T>& operator++() {
        currentNode = currentNode->next;
        return *this;
    }

    const T& operator*() const {
        return currentNode->element;
    }

    T& operator*() {
        return currentNode->element;
    }

private:
    ListNode<T>* currentNode = nullptr;

    explicit ListIterator(ListNode<T>* node) : currentNode(node) {}
};

template<typename T>
class List {
    template<typename Object>
    friend void swap(List<Object>&, List<Object>&);
public:
    List() = default;
    List(const List<T>& otherList);
    List<T>& operator=(List<T> otherList);
    ~List();

    bool isEmpty() const;

    void clean();
    ListIterator<T> getHead() const;
    ListIterator<T> getFirst() const;
    void insert(const T& element, const ListIterator<T>& iterator);
    void remove(const T& element);
    ListIterator<T> find(const T& element) const;
    ListIterator<T> findPrevious(const T& element) const;

private:
    ListNode<T>* header = new ListNode<T>();
};

template<typename Object>
void swap(List<Object>& firstList, List<Object>& secondList) {
    using std::swap;
    swap(firstList.header, secondList.header);
}

template<typename T>
List<T>::List(const List<T>& otherList) {
    ListIterator<T> thisIterator = getHead();
    ListIterator<T> otherListIterator = otherList.getFirst();
    for (; otherListIterator.isValid(); ++otherListIterator, ++thisIterator) {
        insert(*otherListIterator, thisIterator);
    }
}

template<typename T>
List<T>& List<T>::operator=(List<T> otherList) {
    swap(*this, otherList);
    return *this;
}

template<typename T>
bool List<T>::isEmpty() const {
    return header->next == nullptr;
}

template<typename T>
ListIterator<T> List<T>::getHead() const {
    return ListIterator<T>(header);
}

template<typename T>
ListIterator<T> List<T>::getFirst() const {
    return ListIterator<T>(header->next);
}

template<typename T>
ListIterator<T> List<T>::find(const T &element) const {
    ListNode<T>* currentNode = header->next;
    while (currentNode != nullptr && currentNode->element != element) {
        currentNode = currentNode->next;
    }
    return ListIterator<T>(currentNode);
}

template<typename T>
ListIterator<T> List<T>::findPrevious(const T &element) const {
    ListNode<T>* currentNode = header;
    while (currentNode->next != nullptr && currentNode->next->element != element) {
        currentNode = currentNode->next;
    }
    return ListIterator<T>(currentNode);
}

template<typename T>
void List<T>::remove(const T &element) {
    ListNode<T>* previousElement = findPrevious(element).currentNode;
    if (previousElement->next != nullptr) {
        ListNode<T>* oldElement = previousElement->next;
        previousElement->next = oldElement->next;
        delete oldElement;
    }
}

template<typename T>
void List<T>::insert(const T &element, const ListIterator<T> &iterator) {
    if (iterator.isValid()) {
        iterator.currentNode->next = new ListNode<T>(element, iterator.currentNode->next);
    }
}

template<typename T>
void List<T>::clean() {
    while (!isEmpty()) {
        remove(*(getFirst()));
    }
}

template<typename T>
List<T>::~List() {
    clean();
    delete header;
}

#endif //ALGORITHMS_LIST_H
