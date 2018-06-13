#ifndef AECONT_H_INCLUDED
#define AECONT_H_INCLUDED

#include <deque>

template<class T>
class alternating_endpoint_container : public std::deque<T>
{
    typedef std::deque<T> Inher;

    bool b;
public:
    alternating_endpoint_container():b(true){}

    template<class It>
    alternating_endpoint_container(It begin, It end):b(true)
    {
        while(begin != end)
        {
            insert(*begin++);
        }
    }

    void insert(const T& t)
    {
        if(b = !b)
        {
            Inher::push_back(t);
        }
        else
        {
            Inher::push_front(t);
        }
    }

    void erase()
    {
        if(b = !b)
        {
            Inher::pop_back();
        }
        else
        {
            Inher::pop_front();
        }
    }
};

#endif // AECONT_H_INCLUDED
