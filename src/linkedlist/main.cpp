//
// Created by hammer on 7/21/20.
//
#include <iostream>
#include <string>
#include "list.h"
#include "stl_list.h"

template<typename T>
void printList(ListIterator<T> begin, const std::string& separator = " ");

template<typename T>
void printSublist(ListIterator<T> begin, const ListIterator<T>& end, const std::string& separator = " ");

int main() {
    mystl::List<double> l;
    for (std::size_t i = 0; i < 10; i++) {
        l.push_back(0.1 + i * 0.1);
    }

    for (mystl::List<double>::const_iterator iter = l.begin(); iter != l.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;


    List<int> list;
    ListIterator<int> iterator = list.getHead();
    list.insert(5, iterator);
    list.insert(4, iterator);
    list.insert(3, iterator);
    list.insert(2, iterator);
    list.insert(1, iterator);
    printList(list.getFirst());
    std::cout << std::endl;

    list.remove(3);
    printList(list.getFirst());
    std::cout << std::endl;

    iterator = list.getFirst();
    *iterator = 99;
    printList(list.getFirst());
    std::cout << std::endl;

    List<int> secondList = list;
    printList(secondList.getFirst());
    std::cout << std::endl;

    list.remove(4);
    list.remove(5);
    secondList = list;
    printList(secondList.getFirst());
    std::cout << std::endl;
    return 0;
}

template<typename T>
void printList(ListIterator<T> begin, const std::string& separator) {
    for (; begin.isValid(); ++begin) {
        std::cout << *begin << separator;
    }
}

template<typename T>
void printSublist(ListIterator<T> begin, const ListIterator<T>& end, const std::string& separator) {
    for (; begin != end; ++begin) {
        std::cout << *begin << separator;
    }
}
