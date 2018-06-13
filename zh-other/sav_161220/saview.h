#ifndef SAVIEW_H_INCLUDED
#define SAVIEW_H_INCLUDED

#include <algorithm>
#include <vector>

template<class T, class Comparer = std::less<T> >
class sorted_array_view {
    std::vector<T> origin;
    T* array;
    const int array_size;
public:
    static const int npos;
    sorted_array_view(T* array, const int array_size) :
        origin(array, array + array_size),
        array(array), array_size(array_size)
    {
        std::sort(array, array + array_size, Comparer());
    }
    
    ~sorted_array_view() {
        std::copy(origin.begin(), origin.end(), array);
    }
    
    int size() const {
        return array_size;
    }
    
    int count(const T& elem) const {
        const std::pair<T*, T*>& range = std::equal_range(array, array + array_size, elem, Comparer());
        return range.second - range.first;
    }
    
    int index_of(const T& elem) const {
        const std::pair<T*, T*>& range = std::equal_range(array, array + array_size, elem, Comparer());
        return range.first != range.second ? range.first - array : npos;
    }
    
    template<class Cont>
    void copy(Cont& container) const {
        container.clear();
        std::copy(array, array + array_size, std::back_inserter(container));
    }
    
    const T* begin() const {
        return array;
    }
    
    const T* end() const {
        return array + array_size;
    }
};

template<class T, class Comparer>
const int sorted_array_view<T, Comparer>::npos = -1;

#endif // SAVIEW_H_INCLUDED

