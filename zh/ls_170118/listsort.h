#ifndef LISTSORT_H_INCLUDED
#define LISTSORT_H_INCLUDED

#include <list>

template<class T, class Comp = std::less<T> >
class list_sorter {
    int lists;
    std::list<T>& container;
    
    class equal_to_comp {
        const T& elem;
        Comp comparer;
    public:
        equal_to_comp(const T& elem) : elem(elem) {}
        
        bool operator()(const T& test) const {
            return !comparer(elem, test) && !comparer(test, elem);
        }
    };
public:
    list_sorter(std::list<T>& container) : lists(1), container(container) {
        container.sort(Comp());
    }
    
    list_sorter& add(std::list<T>& other) {
        container.splice(container.end(), other);
        container.sort(Comp());
        ++lists;
        return *this;
    }
    
    list_sorter& remove(const T& elem) {
        container.remove_if(equal_to_comp(elem));
        return *this;
    }
    
    int list_count() const {
        return lists;
    }
    
	template<class U, class Cmp>
    friend class list_sorter;
    
	template<class Cmp>
    list_sorter& operator+=(list_sorter<T, Cmp>& other) {
        return add(other.container);
    }
};

#endif // LISTSORT_H_INCLUDED