#ifndef PREDCONT_H_INCLUDED
#define PREDCONT_H_INCLUDED

#include <algorithm>

struct AlwaysFalse
{
    template<class T>
    bool operator()(const T&) const
    {
        return false;
    }
};

template<class Cont, class Pred = AlwaysFalse, class Elem = typename Cont::value_type>
class predicate_container
{
    Cont c;
    Pred p;
public:
    predicate_container& insert(const Elem& val)
    {
        if(p(*this))
        {
            c.insert(c.begin(), val);
        }
        else
        {
            c.insert(c.end(), val);
        }
        return *this;
    }

    int size() const
    {
        return c.size();
    }

    const Elem& at(int index) const
    {
        typename Cont::const_iterator it = c.begin();
        std::advance(it, index);
        return *it;
    }

    const Elem& operator[](int index) const
    {
        return at(index);
    }

    void erase(const Elem& val)
    {
        c.erase(std::remove(c.begin(), c.end(), val), c.end());
    }

    predicate_container(){}

    template<class It>
    predicate_container(It begin, It end): c(begin, end){}
};

#endif // PREDCONT_H_INCLUDED
