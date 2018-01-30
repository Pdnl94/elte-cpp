#ifndef SETFILTER_H_INCLUDED
#define SETFILTER_H_INCLUDED

#include <set>

template<class T, class C = std::less<T> >
class set_filtering {
    std::set<T, C>& orig;
    std::set<T, C> filt;
public:
    set_filtering(std::set<T, C>& orig) : orig(orig) {}
    
    void filter(const T& elem) {
        if(orig.count(elem)) {
            filt.insert(*orig.find(elem));
            orig.erase(elem);
        }
    }
    
    void unfilter(const T& elem) {
        if(filt.count(elem)) {
            orig.insert(*filt.find(elem));
            filt.erase(elem);
        }
    }
    
    void inverse() {
        std::swap(filt, orig);
    }
    
    ~set_filtering() {
        orig.insert(filt.begin(), filt.end());
    }
    
    void operator~() {
        inverse();
    }

    template<class Cmp>
    void operator+=(Cmp comp) {
        typename std::set<T, C>::iterator it = orig.begin();
        while(it != orig.end()) {
            T cp = *it++;
            if(comp(cp)) {
                filter(cp);
            }
        }
    }
    
    template<class Cmp>
    void operator-=(Cmp comp) {
        typename std::set<T, C>::iterator it = filt.begin();
        while(it != filt.end()) {
            T cp = *it++;
            if(comp(cp)) {
                unfilter(cp);
            }
        }
    }
};

#endif // SETFILTER_H_INCLUDED
