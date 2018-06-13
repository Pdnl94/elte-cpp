#ifndef PRSTACK_H_INCLUDED
#define PRSTACK_H_INCLUDED

#include <vector>
#include <deque>
#include <stack>

struct AlwaysFalse
{
    template<class T>
    bool operator()(const T&) const{ return false; }
};

template<class T, class Pred = AlwaysFalse >
struct predicate_stack : std::deque<T>
{
    std::vector<bool> frb;

    void push(const T& e)
    {
        frb.push_back(Pred()(*this));
        if(frb.back())
        {
            this->push_front(e);
        }
        else
        {
            this->push_back(e);
        }
    }

    const T& top() const
    {
        if(frb.back())
        {
            return this->front();
        }
        else
        {
            return this->back();
        }
    }

    T& top()
    {
        if(frb.back())
        {
            return this->front();
        }
        else
        {
            return this->back();
        }
    } 
    
    void pop()
    {
        if(frb.back())
        {
            this->pop_front();
        }
        else
        {
            this->pop_back();
        }
        frb.pop_back();
    } 

    operator std::stack<T>() const
    {
        std::deque<T> cpy(*this);
        std::deque<T> res;
        for(int i = frb.size() - 1; i >= 0 ; --i)
        {
            if(frb[i])
            {
                res.push_front(cpy.front());
                cpy.pop_front();
            }
            else
            {
                res.push_front(cpy.back());
                cpy.pop_back();
            }
        }
        return std::stack<T>(res);
    }
};

#endif // PRSTACK_H_INCLUDED
