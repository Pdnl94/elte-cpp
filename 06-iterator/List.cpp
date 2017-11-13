#include "List.h"

template<typename T>
List<T>::~List() {
    delete next;
}

template<typename T>
void List<T>::add(T _data) {
    add(_data, count);
}

template<typename T>
void List<T>::add(T _data, int currentCount) {
    if (next == nullptr) {
        next = new List<T>(_data, currentCount + 1);
    } else {
        next->add(_data, currentCount + 1);
    }
}

template<typename T>
List<T> *List<T>::getLastNode() {
    if (next == nullptr) {
        return this;
    } else next->getLastNode();
}

template<typename T>
int List<T>::size() {
    return getLastNode()->count;
}

template<typename T>
T List<T>::get() {
    return data;
}

template<typename T>
T List<T>::get(int i) {
    if (count == i) {
        return data;
    } else {
        next->get(i);
    }
}

template<typename T>
List<T> *List<T>::getNext() {
    return next;
}