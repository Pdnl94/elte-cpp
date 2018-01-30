#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <vector>
#include <map>

// 2 template paraméter
// az egyik az elemek típusa
// a másik a zsákok száma
template <typename T , std::size_t N>
class NBag
{
    // legyen egy zsák egy map < T , std::size_t >
    // minden elemhez hozzárendeljük hogy hányszor van benne a zsákban
    typedef std::map < T , std::size_t > Bag;
    
    // típusok
    typedef typename Bag::const_iterator const_iterator;
    typedef typename Bag::size_type size_type;
    
    // vectornyi zsák legyen a struktúra
    typedef std::vector < Bag > Container;
    
    Container c;
public:
    // konstruktorba létrehozzuk az N darab zsákot
    NBag():c( N , Bag() ){}

    // behelyezünk az bagI. zsákba az e elemet n szer
    // visszatérünk az objektum referenciájával
    NBag& insert( size_type bagI , const T& e , size_type n = 1 )
    {
        c[bagI][e] += n;
        return *this;
    }

    // lekérjük a méretét. Ez az összes zsák mérete
    size_type size() const
    {
        size_type res = 0;
        for( size_type i = 0 ; i < N ; ++i )
            res += c[i].size();
        return res;
    }

    // no comment
    size_type getN() const
    {
        return N;
    }

    // megnézzük, hogy a bagI -ben az e elemből hány db van
    size_type mul( size_type bagI , const T& e ) const
    {
        const_iterator cit = c[bagI].find(e);
        return cit == c[bagI].end() ? 0 : cit->second;
    }

    // átvesszük érték szerint a második zsákot, 
    // majd abba belepakoljuk a saját struktúránk elemeit
    NBag operator+( NBag r ) const
    {
        for( size_type i = 0; i < N; ++i )
        {
            for( const_iterator cit = c[i].begin() ; cit != c[i].end() ; ++cit )
            {
                r.insert( i , cit->first , cit->second );
            }
        }
        return r;
    }
};

// ezt kimásoltam c++ reference-ről (C++11-es fv)
template <class InItType, class OuItType, class Pred>
OuItType copy_if (InItType first, InItType last, OuItType result, Pred pred)
{
    while (first!=last) {
        if (pred(*first)) {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

#endif // HEADER_INCLUDED
