#ifndef PACONT_H_INCLUDED
#define PACONT_H_INCLUDED


#include <deque>

template<class T, class Fun>
struct predicate_alternating_container : std::deque<T>
{
    typedef std::deque<T> Inher;

    void insert(const T& e)
    {
        if(Fun()(*this))
        {
            Inher::push_front(e);
        }
        else
        {
            Inher::push_back(e);
        }
    } 

    void erase(int i)
    {
        Inher::erase(Inher::begin() + i);
    } 

    predicate_alternating_container(){}

    template<class Oth>
    predicate_alternating_container(const predicate_alternating_container<T, Oth>& oth)
    {
        for(int i = 0; i < oth.size(); ++i)
        {
            insert(oth[i]);
        }
    }
};


#endif // PACONT_H_INCLUDED
