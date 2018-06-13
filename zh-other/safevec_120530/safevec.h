#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/


/*
    A feladat egy olyan biztonságos vector létrehozása, melytől ha egy olyan indexedik elemet kérünk le, 
    amelyik nem létezik, akkor megnöveli a struktúrát akkorára, hogy létezzen az az elem, majd visszatér vele
*/

#include <vector>

// 1 template paraméter, az elemek típusa
// származunk a std::vectorból
template <typename T>
class safe_vector : public std::vector<T>
{
    // typedefeljük el a típusokat
    typedef std::vector<T> Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::reference reference;
public:
    // ha egy lekérés történik, akkor meg kell nézni, hogy létezik-e az az elem
    // ha nem létezik, akkor újraméretezzük a vectort úgy, hogy létezzen 
    // (default értékekkel, amit paraméterül kapunk, hogy mi legyen)
    // majd visszatérünk vele
    reference at( size_type pos , const T& e )
    {
        if( Inher::size() <= pos )
            Inher::resize( pos + 1 , e );
        return Inher::at( pos );
    }

    // ha egy lekérés történik, akkor meg kell nézni, hogy létezik-e az az elem
    // ha nem létezik, akkor újraméretezzük a vectort úgy, hogy létezzen 
    // visszatérünk
    reference operator[]( size_type pos )
    {
        if( Inher::size() <= pos )
            Inher::resize( pos + 1 );
        return Inher::operator[]( pos );
    }
};

#endif // HEADER_INCLUDED
