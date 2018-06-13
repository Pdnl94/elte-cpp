#ifndef STRINGIMPL_H_INCLUDED
#define STRINGIMPL_H_INCLUDED

#include <string>
#include <algorithm>

template<class Container, class Type = typename Container::value_type>
class string_implemented_with : public Container
{

public:
    typedef typename Container::const_iterator const_iterator;
    using Container::begin;
    using Container::end;
    using Container::size;

    string_implemented_with(Type* ptr): Container(ptr, ptr + std::char_traits<Type>::length( ptr )){ *ptr = '\0'; }

    string_implemented_with& erase(int tol, int db)
    {
        const_iterator from = begin();
        std::advance(from, tol);

        const_iterator to = from;
        std::advance(to, db);

        Container::erase(from, to);
        return *this;
    }

    const Type& at(int pos) const
    {
        const_iterator it = begin();
        std::advance(it, pos);
        return *it;
    }

    int length() const
    {
        return size();
    }

    const Type& operator[](int pos) const
    {
        return at(pos);
    }

    Type& operator[](int pos)
    {
        typename Container::iterator it = begin();
        std::advance(it, pos);
        return *it;
    }

    static const int npos;

    template<class C2>
    int find_first_not_of(const string_implemented_with<C2, Type>& oth) const
    {
        const_iterator it = begin();
        while(it != end())
        {
            if(std::find(oth.begin(), oth.end(), *it) == oth.end())
                return std::distance(begin(), it);

            ++it;
        }
        return npos;
    }
};

template<class Container, class Type>
const int string_implemented_with<Container, Type>::npos = -1;

#endif // STRINGIMPL_H_INCLUDED
