//
// Created by hammer on 7/23/20.
//

#ifndef ALGORITHMS_STL_LIST_H
#define ALGORITHMS_STL_LIST_H

#include <stdexcept>

namespace mystl {
    template<typename T>
    class List;

    template<typename T>
    class ListIter;

    template<typename T>
    class ConstListIter;

    template<typename T>
    class ListNode {
        friend class List<T>;
        friend class ListIter<T>;
        friend class ConstListIter<T>;

    private:
        T data;
        ListNode<T>* prev;
        ListNode<T>* next;

        explicit ListNode(const T& data = {}, ListNode<T>* prev = nullptr, ListNode<T>* next = nullptr)
        : data(data), prev(prev), next(next) {}
    };

    template<typename T>
    class List {
        template<typename TT>
        friend void swap(List<TT>&, List<TT>&);
        friend class ListIter<T>;
        friend class ConstListIter<T>;
    public:
        using iterator=ListIter<T>;
        using const_iterator=ConstListIter<T>;

        List();
        List(const List& otherList);
        List& operator=(List otherList);
        ~List();

        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;

        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

        std::size_t size() const;
        bool empty() const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        void push_front(const T& itemData);
        void push_back(const T& itemData);
        void pop_front();
        void pop_back();

        iterator insert(iterator iter, const T& itemData);
        iterator erase(iterator iter);
        iterator erase(iterator start, iterator end);
    private:
        using Node=ListNode<T>;
        std::size_t theSize = 0;
        Node* head = new Node();
        Node* tail = new Node();

        void init();
        //void clean();
    };

    template<typename T>
    class ConstListIter {
        friend class List<T>;

    public:
        ConstListIter() = default;
        virtual ~ConstListIter() = default;

        const T& operator*() const;
        ConstListIter& operator++();
        ConstListIter operator++(int);
        ConstListIter& operator--();
        ConstListIter operator--(int);

        bool operator==(const ConstListIter& rightOperand) const;
        bool operator!=(const ConstListIter& rightOperand) const;

    protected:
        using Node = ListNode<T>;

        Node* head = nullptr;
        Node* current = nullptr;

        explicit ConstListIter(const List<T>& source, Node* current) : head(source.head), current(current) {}

        void assertIsInitialized() const;
        void assertIsValid() const;
        void assertCanAdvance() const;
        void assertCanRetreat() const;

        T& retrieve() const;
    };

    template<typename T>
    class ListIter : public ConstListIter<T> {
        friend class List<T>;

    public:
        ListIter() = default;

        using ConstListIter<T>::operator*;
        T& operator*();
        ListIter& operator++();
        ListIter operator++(int);
        ListIter& operator--();
        ListIter operator--(int);

    protected:
        using Node = ListNode<T>;

        explicit ListIter(const List<T>& source, Node* current) : ConstListIter<T>(source, current) {}
    };

    template<typename T>
    void ConstListIter<T>::assertIsInitialized() const {
        if (head == nullptr || current == nullptr) {
            throw std::invalid_argument("Iterator is not initialized");
        }
    }

    template<typename T>
    void ConstListIter<T>::assertIsValid() const {
        assertIsInitialized();
        if (current == head) {
            throw std::invalid_argument("Iterator is not valid");
        }
    }

    template<typename T>
    void ConstListIter<T>::assertCanAdvance() const {
        assertIsInitialized();
        if (current->next == nullptr) {
            throw std::invalid_argument("Iterator can not be advanced");
        }
    }

    template<typename T>
    void ConstListIter<T>::assertCanRetreat() const {
        assertIsValid();
        if (current->prev == head) {
            throw std::invalid_argument("Iterator can not be retreated");
        }
    }

    template<typename T>
    T& ConstListIter<T>::retrieve() const {
        assertIsValid();
        assertCanAdvance();
        return current->data;
    }

    template<typename T>
    const T& ConstListIter<T>::operator*() const {
        return retrieve();
    }

    template<typename T>
    T& ListIter<T>::operator*() {
        return ConstListIter<T>::retrieve();
    }

    template<typename T>
    ConstListIter<T>& ConstListIter<T>::operator++() {
        assertCanAdvance();
        current = current->next;
        return *this;
    }

    template<typename T>
    ConstListIter<T> ConstListIter<T>::operator++(int) {
        ConstListIter oldIterator = *this;
        ++(*this);
        return oldIterator;
    }

    template<typename T>
    ListIter<T>& ListIter<T>::operator++() {
        ConstListIter<T>::assertCanAdvance();
        ConstListIter<T>::current = ConstListIter<T>::current->next;
        return *this;
    }

    template<typename T>
    ListIter<T> ListIter<T>::operator++(int) {
        ListIter oldIterator = *this;
        ++(*this);
        return oldIterator;
    }

    template<typename T>
    ConstListIter<T>& ConstListIter<T>::operator--() {
        assertCanRetreat();
        current = current->prev;
        return *this;
    }

    template<typename T>
    ConstListIter<T> ConstListIter<T>::operator--(int) {
        ConstListIter oldIterator = *this;
        --(*this);
        return oldIterator;
    }

    template<typename T>
    ListIter<T>& ListIter<T>::operator--() {
        ConstListIter<T>::assertCanRetreat();
        ConstListIter<T>::current = ConstListIter<T>::current->prev;
        return *this;
    }

    template<typename T>
    ListIter<T> ListIter<T>::operator--(int) {
        ListIter oldIterator = *this;
        --(*this);
        return oldIterator;
    }

    template<typename T>
    bool ConstListIter<T>::operator==(const ConstListIter<T> &rightOperand) const {
        return current == rightOperand.current;
    }

    template<typename T>
    bool ConstListIter<T>::operator!=(const ConstListIter<T> &rightOperand) const {
        return !(*this == rightOperand);
    }

    template<typename T>
    void List<T>::init() {
        head->next = tail;
        tail->prev = head;
    }

    template<typename T>
    List<T>::List() {
        init();
    }

    template<typename T>
    void swap(List<T>& first, List<T>& second) {
        using std::swap;
        swap(first.head, second.head);
        swap(first.tail, second.tail);
        swap(first.theSize, second.theSize);
    }

    template<typename T>
    List<T>::List(const List<T> &otherList) {
        init();
        if (!otherList.empty()) {
            for (auto iterator = otherList.cbegin(); iterator != otherList.cend(); ++iterator) {
                push_back(*iterator);
            }
        }
    }

    template<typename T>
    List<T>& List<T>::operator=(List<T> otherList) {
        swap(*this, otherList);
        return *this;
    }

    template<typename T>
    List<T>::~List() {
        while (!empty()) {
            pop_front();
        }
        delete head;
        delete tail;
    }

    template<typename T>
    typename List<T>::iterator List<T>::begin() {
        iterator iter(*this, head);
        return ++iter;
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::cbegin() const {
        const_iterator iter(*this, head);
        return ++iter;
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::begin() const {
        return cbegin();
    }

    template<typename T>
    typename List<T>::iterator List<T>::end() {
        return iterator(*this, tail);
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::cend() const {
        return const_iterator(*this, tail);
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::end() const {
        return cend();
    }

    template<typename T>
    std::size_t List<T>::size() const {
        return theSize;
    }

    template<typename T>
    bool List<T>::empty() const {
        return size() == 0;
    }

    template<typename T>
    T& List<T>::front() {
        return *begin();
    }

    template<typename T>
    const T& List<T>::front() const {
        return *begin();
    }

    template<typename T>
    T& List<T>::back() {
        return *--end();
    }

    template<typename T>
    const T& List<T>::back() const {
        return *--end();
    }

    template<typename T>
    void List<T>::push_back(const T &itemData) {
        insert(end(), itemData);
    }

    template<typename T>
    void List<T>::push_front(const T &itemData) {
        insert(begin(), itemData);
    }

    template<typename T>
    void List<T>::pop_front() {
        erase(begin());
    }

    template<typename T>
    void List<T>::pop_back() {
        erase(--end());
    }

    template<typename T>
    typename List<T>::iterator List<T>::insert(iterator iter, const T &itemData) {
        iter.assertIsValid();
        if (iter.head != head) {
            throw std::invalid_argument("<<< Insert >>> Iterator beings to other list");
        }

        Node* current = iter.current;
        current->prev->next = new Node(itemData, current->prev, current);
        current->prev = current->prev->next;
        theSize++;
        return iterator(*this, current->prev);
    }

    template<typename T>
    typename List<T>::iterator List<T>::erase(iterator iter) {
        iter.assertIsValid();
        if (iter.head != head) {
            throw std::invalid_argument("<<< erase >>> Iterator beings to other list");
        }
        if (iter == end()) {
            throw std::invalid_argument("<<< erase >>> Iterator points to past end of the list");
        }

        Node* nodeForDelete = iter.current;
        iterator nextPastDeleted(*this, nodeForDelete->next);
        nodeForDelete->prev->next = nodeForDelete->next;
        nodeForDelete->next->prev = nodeForDelete->prev;
        delete nodeForDelete;
        --theSize;
        return nextPastDeleted;
    }

    template<typename T>
    typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
        for (auto iter = start; iter != end; ) {
            iter = erase(iter);
        }
        return end;
    }
}
#endif //ALGORITHMS_STL_LIST_H
