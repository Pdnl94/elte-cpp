#ifndef CHECKSUM_H_INCLUDED
#define CHECKSUM_H_INCLUDED

#include <numeric>

template<class Container, class Checksum, class Elem = typename Container::value_type, class Add = std::plus<int> >
class checksum {
    const Container& cont;
    
    struct MyAdder {
        int operator()(int was, const Elem& elem) const {
            return Add()(was, Checksum()(elem));
        }
    } add;
    
    int init;
    int savedChecksum;
public:
    checksum(const Container& cont, int init = 0) 
        : cont(cont), init(init),
        savedChecksum(get_checksum())
    {}
    
    int get_checksum() const {
        return std::accumulate(cont.begin(), cont.end(), init, add);
    }
    
    bool validate_checksum() const {
        return savedChecksum == get_checksum();
    }
    
    void update_checksum() {
        savedChecksum = get_checksum();
    }
};

#endif // CHECKSUM_H_INCLUDED

