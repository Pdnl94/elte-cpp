#ifndef SETHELP_H_INCLUDED
#define SETHELP_H_INCLUDED

#include <set>
#include <algorithm>


template<class Type, class Comp = std::less<Type> >
class set_helper {
    std::set<Type, Comp>& set;
public:
    set_helper(std::set<Type, Comp>& set) : set(set) {}
    
    /* kettesert
    void update(const Type& from, const Type& to) {
        set.erase(from);
        set.insert(to);
    }
    */

    void update(const Type& from, const Type& to) {
        for (typename std::set<Type, Comp>::const_iterator it = set.begin();
                it != set.end(); ++it) {
            if (*it == from) {
                set.erase(it);
                break;            
            }
        }
        set.insert(to);
    }
    
    template<class OthType, class OthComp>
    friend class set_helper; 
    
    template<class OthComp>
    void operator+=(const set_helper<Type, OthComp>& other) {
        for (typename std::set<Type, OthComp>::const_iterator it = other.set.begin();
                it != other.set.end(); ++it) {
            update(*it, *it);
        }
    }
    
    template<class OthComp>
    void operator<<(set_helper<Type, OthComp>& other) {
        for (typename std::set<Type, OthComp>::const_iterator it = other.set.begin();
                it != other.set.end(); ) {
            typename std::set<Type, Comp>::const_iterator it2 = 
                    std::find(set.begin(), set.end(), *it);
            if (it2 == set.end()) {
                set.insert(*it);
                other.set.erase(*it++);
            } else {
                ++it;
            }
        }
    }

    template<class OthComp>
    void operator>>(set_helper<Type, OthComp>& other) {
        other << *this;
    }
};

template<class Type, class Comp>
set_helper<Type, Comp> make_set_helper(std::set<Type, Comp>& set) {
    return set_helper<Type, Comp>(set);
}

#endif // SETHELP_H_INCLUDED
