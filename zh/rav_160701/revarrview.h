#ifndef REVARRVIEW_H_INCLUDED
#define REVARRVIEW_H_INCLUDED

#include <vector>
#include <map>

template<class T>
class reverse_array_view {
    std::map<int, T*> container;
    int sumSize;
public:
    reverse_array_view(T* arr, int arrSize) : sumSize(arrSize) {
        container[0] = arr;
    }

    void add(T* arr, int arrSize) {
        container[sumSize] = arr;
        sumSize += arrSize;
    }

    const T& at(int index) const {
        index = size() - index - 1;
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
        index = size() - index - 1;
        std::pair<const int, T*> elem = *--container.upper_bound(index);
        return elem.second[index - elem.first];
    }

    template<int size>
    void add(T (& arr)[size]) {
        add(arr, size);
    }

    void add(std::vector<T>& vec) {
        add(&vec[0], vec.size());
    }
};

#endif // REVARRVIEW_H_INCLUDED
