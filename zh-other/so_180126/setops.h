#ifndef SETOPS_H_INCLUDED
#define SETOPS_H_INCLUDED

#include <set>

template<class Type>
class set_operations {
    std::set<Type> set;
    bool inverse;
public:
    template<class OthComp>
    set_operations(const std::set<Type, OthComp>& set) : set(set.begin(), set.end()), inverse(false) {}
    
    void complement() {
        inverse = !inverse;
    }
    
    bool contains(const Type& elem) const {
        return set.count(elem) ^ inverse;
    }
    
    void set_union(const set_operations<Type>& other) {
        if (inverse) {
            for (typename std::set<Type>::const_iterator it = other.set.begin();
                    it != other.set.end(); ++it) {
                set.erase(*it);
            }
        } else {
            set.insert(other.set.begin(), other.set.end());
        }
    }
    
    bool subset(const set_operations<Type>& other) const {
        for (typename std::set<Type>::const_iterator it = other.set.begin();
                it != other.set.end(); ++it) {
            if (set.count(*it) == inverse)
                return false;
        }
        return true;
    }
    
    void operator+=(const set_operations<Type>& other) {
        set_union(other);
    }
};

#endif // SETOPS_H_INCLUDED
