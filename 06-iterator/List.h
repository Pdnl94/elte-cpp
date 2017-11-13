//
// Created by alexa on 2017-11-13.
//

#ifndef INC_06_ITERATOR_LIST_H
#define INC_06_ITERATOR_LIST_H
#include <iostream>

template <class T>
class List {
private:

    T data{};
    List<T>* next = nullptr;
    int count = 1;

public:

    List(T data) : data(data), next(nullptr) {}
    List(T data, int count) : data(data), count(count), next(nullptr) {}

    ~List() {
        delete next;
    }

    void add(T _data) {
        add(_data, count);
    }

    void add(T _data, int currentCount) {
        if(next == nullptr) {
            next = new List<T>(_data, currentCount + 1);
        } else {
            next->add(_data, currentCount + 1);
        }
    }

    List<T>* getLastNode() {
        if(next == nullptr) {
            return this;
        } else next->getLastNode();
    }

    int size() {
        return getLastNode()->count;
    }

    T get() {
        return data;
    }

    T get(int i) {
        if(count == i) {
            return data;
        } else {
            next->get(i);
        }
    }

    List<T>* getNext() {
        return next;
    }

};

#endif //INC_06_ITERATOR_LIST_H