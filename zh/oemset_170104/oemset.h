#ifndef OEMSET_H_INCLUDED
#define OEMSET_H_INCLUDED

#include <vector>
#include <set>
#include <algorithm>
#include <functional>

template<class T, class Compare, class Equality = std::equal_to<T> >
class optional_equality_multiset {
    std::vector<T> elements;

    struct MyEquality : std::binary_function<T, T, bool> {
        Compare less;
        Equality equality;
        bool useEquality;

        bool operator()(const T& first, const T& second) const {
            if(useEquality) {
                return equality(first, second);
            } else {
                return !less(first, second) && !less(second, first);
            }
        }
    } eq;

public:
    optional_equality_multiset() {
        eq.useEquality = false;
    }

    void insert(const T& elem) {
        elements.insert(
            std::upper_bound(elements.begin(), elements.end(), elem, Compare()), elem);
    }

    void use_equality() {
        eq.useEquality = true;
    }

    int count(const T& elem) const {
        return std::count_if(elements.begin(), elements.end(), std::bind1st(eq, elem));
    }

    void use_equivalence() {
        eq.useEquality = false;
    }

    void erase(const T& elem) {
        elements.erase(std::remove_if(elements.begin(), elements.end(), std::bind1st(eq, elem)), elements.end());
    }

    typedef typename std::vector<T>::const_iterator const_iterator;

    const_iterator find(const T& elem) const {
        return std::find_if(elements.begin(), elements.end(), std::bind1st(eq, elem));
    }

    const_iterator begin() const {
        return elements.begin();
    }

    const_iterator end() const {
        return elements.end();
    }

    template<class Cmp>
    operator std::multiset<T, Cmp>() const {
        return std::multiset<T, Cmp>(elements.begin(), elements.end());
    }
};

#endif // OEMSET_H_INCLUDED

