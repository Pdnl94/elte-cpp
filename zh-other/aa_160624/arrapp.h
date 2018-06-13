#ifndef ARRAPP_H_INCLUDED
#define ARRAPP_H_INCLUDED

#include <map>
#include <vector>
#include <iterator>

template<class T>
class array_appender {

    std::map<int, T*> container;
    int sumSize;
public:
    array_appender(T* arr, int arrSize) : sumSize(arrSize) {
        container[0] = arr;
    }

    void append(T* arr, int arrSize) {
        container[sumSize] = arr;
        sumSize += arrSize;
    }

    const T& at(int index) const {
        std::pair<const int, T*> elem = *--container.upper_bound(index);
        return elem.second[index - elem.first];
    }

    int size() const {
        return sumSize;
    }

    const T& operator[](int index) const {
        return at(index);
    }

    T& operator[](int index) {
        std::pair<const int, T*> elem = *--container.upper_bound(index);
        return elem.second[index - elem.first];
    }

    void append(std::vector<T>& vec) {
        append(&vec[0], vec.size());
    }

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        array_appender<T>* parent;
        int index;
    public:
        iterator(array_appender<T>* parent, int index) : parent(parent), index(index) {}

        bool operator==(const iterator& it) const {
            return parent == it.parent && index == it.index;
        }

        bool operator!=(const iterator& it) const {
            return !(*this == it);
        }

        iterator& operator++() {
            ++index;
            return *this;
        }

        T& operator*() {
            return (*parent)[index];
        }

        int operator-(const iterator& it) const {
            return index - it.index;
        }

        // ...
    };

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, size());
    }
};

#endif // ARRAPP_H_INCLUDED
