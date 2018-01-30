#ifndef PREDMSET_H_INCLUDED
#define PREDMSET_H_INCLUDED

#include <map>
#include <set>
#include <deque>

template<class T, class Pred, class Comp = std::less<T> >
class predicate_multiset
{
    std::map< T, std::deque<T>, Comp > _data;
    int _size;
public:
    predicate_multiset():_size(0){}

    void insert(const T& elem)
    {
        if(Pred()(elem))
        {
            _data[elem].push_front(elem);
        }
        else
        {
            _data[elem].push_back(elem);
        }
        ++_size;
    }

    int count(const T& elem) const
    {
        if(!_data.count(elem))
            return 0;

        return _data.find(elem)->second.size();
    }

    const T& at(const T& elem, int db) const
    {
        return _data.find(elem)->second.at(db);
    }

    void erase(const T& elem)
    {
        _size -= _data[elem].size();
        _data.erase(elem);
    }

    int size() const
    {
        return _size;
    }

    operator std::multiset< T, Comp >() const
    {
        std::multiset< T, Comp > res;
        for(typename std::map< T, std::deque<T>, Comp >::const_iterator it = _data.begin(); it != _data.end(); ++it)
        {
            res.insert(it->second.begin(), it->second.end());
        }
        return res;
    }
};
#endif // PREDMSET_H_INCLUDED
