#ifndef INDOPS_H_INCLUDED
#define INDOPS_H_INCLUDED


struct Eater {
    bool b;
    Eater(int jegy) : b(true) {
        std::cout << jegy <<". ert: ";
    }
    Eater& operator&&(bool n) {
        std::cout << n;
        b &= n;
        return *this;
    }
    
    operator bool() const {
        return b;
    }
    
    ~Eater() {
        int a = -5;
        a %= 3;
        std::cout << " TEST: " << a  << std::endl;
        
    }
};

template<class Cont>
struct element_type_getter {
    typedef typename Cont::value_type value_type;
};

template<class T>
struct element_type_getter<T*> {
    typedef T value_type;
};

template<class Cont, class Elem = typename element_type_getter<Cont>::value_type>
class index_operations;

template<class Cont>
class index_operations<Cont, typename Cont::value_type> {
    Cont& cont;
    int shift;
    bool rev;
public:
    index_operations(Cont& cont) : cont(cont), shift(0), rev(false) {}
    
    void shift_left(int with = 1) {
        shift -= with;
    }
    
    typename Cont::reference at(int index) const {
        index += shift % (int)cont.size();
        index %= (int)cont.size();
        if(index < 0)
            index += cont.size();
        return cont[rev ? cont.size() - 1 - index : index];
    }
    
    void shift_right(int with = 1) {
        shift += with;
    }
    
    void operator>>(int with) {
        shift_right(with);
    }
    
    void operator<<(int with) {
        shift_left(with);
    }
    
    typename Cont::reference operator[](int index) const {
        return at(index);
    }
    
    void reverse() {
        rev = !rev;
    }
};

template<class T>
class index_operations<T*, T> {
    T* arr;
    int size;
    
    int shift;
    bool rev;
public:
    index_operations(T* arr, int size) : arr(arr), size(size), shift(0), rev(false) {}
    T& operator[](int index) const {
        index += shift % size;
        index %= size;
        if(index < 0)
            index += size;
        return arr[rev ? size - 1 - index : index];
    }
    
    void operator>>(int with) {
        shift += with;
    }
    
    void operator<<(int with) {
        shift -= with;
    }
    
    void operator~() {
        rev = !rev;
    }
};

#endif // INDOPS_H_INCLUDED
