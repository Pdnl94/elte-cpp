#ifndef INC_06_ITERATOR_LIST_H
#define INC_06_ITERATOR_LIST_H

template <class T>
class List {
private:
public:
    T data{};
    List<T>* next = nullptr;
    int count = 1;


    List(T data) : data(data), next(nullptr) {}
    List(T data, int count) : data(data), count(count), next(nullptr) {}

    ~List();

    void add(T _data);

    void add(T _data, int currentCount);

    List<T>* getLastNode();

    int size();

    T get();

    T get(int i);

    List<T>* getNext();

};

#endif //INC_06_ITERATOR_LIST_H