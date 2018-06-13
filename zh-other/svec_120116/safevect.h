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
    konstruktorban megkapja a default elemet, amivel feltöltse a túlindexelés esetén a vectort
    illetve kap még egy paramétert, amit akkor kell visszaadnia, ha const-on indexelünk túl
*/

#include <vector>

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

    // tároljunk el a két default értéket
    T def;  // ez akkor kell, ha túlindexelnénk a struktúrából, akkor ilyen default elemekkel töltsük fel
    T _not; // ez akkor kell, ha const -on indexelünk túl, és nem tudjuk megnövelni a méretet (ilyennel térünk vissza)
public:
    // konstruktor, melynek mindkét paramétere default értékkel is rendelkezik
    safe_vector( T def = T() , T _not = T() ):def(def),_not(_not){}
    
    // ha egy lekérés történik, akkor meg kell nézni, hogy létezik-e az az elem
    // ha nem létezik, akkor újraméretezzük a vectort úgy, hogy létezzen
    // (default értékekkel, amit paraméterül kapunk, hogy mi legyen)
    // majd visszatérünk vele
    reference at( size_type pos )
    {
        if( Inher::size() <= pos )
            Inher::resize( pos + 1 , def );
        return Inher::at( pos );
    }

    // ha egy lekérés történik, akkor meg kell nézni, hogy létezik-e az az elem
    // ha nem létezik, akkor újraméretezzük a vectort úgy, hogy létezzen
    // visszatérünk
    reference operator[]( size_type pos )
    {
        if( Inher::size() <= pos )
            Inher::resize( pos + 1 , def );
        return Inher::operator[]( pos );
    }

    // konstans lekérés esetén ha túlindexelünk, akkor visszatérünk egy _not elemmel
    // különben az annyiadik indexen lévő elemmel
    T at( size_type pos ) const
    {
        if( Inher::size() <= pos )
            return _not;
        return Inher::at( pos );
    }

    // konstans lekérés esetén ha túlindexelünk, akkor visszatérünk egy _not elemmel
    // különben az annyiadik indexen lévő elemmel
    T operator[]( size_type pos ) const
    {
        if( Inher::size() <= pos )
            return _not;
        return Inher::operator[]( pos );
    }

    // insert - kap egy pozíciót, meg egy intervallumot
    // az adott pozíciótól kezdve felülírja a struktúra elemeit
    // annyival, amennyi a bemenet
    template <typename It>
    void insert( size_type pos , It begin, It end )
    {
        // kiszámoljuk a behelyezendő elemek számát
        size_type dist = std::distance( begin , end );
        
        // ha nincs ennyi elem, akkor megnyújtjuk a vectort
        if( Inher::size() < pos + dist )
            Inher::resize( pos + dist , def );

        // átmásoljuk az elemeket az adott poícióra
        std::copy( begin , end , Inher::begin() + pos );
    }
};

#endif // HEADER_INCLUDED
