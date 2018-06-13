#ifndef FFVEC_H_INCLUDED
#define FFVEC_H_INCLUDED

#include <vector>
#include <algorithm>

template<class T>
class full_fledged_vector : public std::vector<T>
{
    typedef std::vector<T> Inher;
public:
    full_fledged_vector(){}
    full_fledged_vector(const T* ptr, int db):Inher(ptr, ptr + db){}

    full_fledged_vector<T> subvec(int from, int db) const
    {
        return full_fledged_vector<T>(this->data()+from, db);
    }

    void append(const T* ptr, int db)
    {
        this->insert(this->end(), ptr, ptr + db);
    }

    int find_first_of(const full_fledged_vector& ptr) const
    {
        typename Inher::const_iterator it = std::find_first_of(this->begin(), this->end(), ptr.begin(), ptr.end());
        return it != this->end() ? it - this->begin() : npos;
    }

    void operator+=(const full_fledged_vector& ptr)
    {
        append(ptr.data(), ptr.size());
    }

    template<class T1, class T2>
    void replace(T1 from, T1 to, T2 rfrom, T2 rto)
    {
        int hova = from - this->begin();
        this->erase(from, to);
        this->insert(this->begin() + hova, rfrom, rto);
    }

    operator std::basic_string<T>()
    {
        return std::basic_string<T>(this->begin(), this->end());
    }

    static const int npos;
};

template<class T>
const int full_fledged_vector<T>::npos = -1;

#endif // FFVEC_H_INCLUDED
