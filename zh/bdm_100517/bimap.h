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
    A feladat egy olyan map struktúra megvalósítása, melynek a kulcs-érték típsusa ugyan az,
    és ha keresünk a mapban, akkor az értékek szerint is kereshetünk
    Ha kulcs helyen találunk egyezést, a hozzá tartozó értéket kell visszaadni, fordított esetben a kulcsot
    
*/

#include <map>

// egy! template paraméter, az indexelésnek a típusa
// származunk egy map-nyi < T , T > ből
template <typename T>
class BidirectionalMap : std::map < T , T >
{
    // nevezzük el a típusokat
    typedef std::map < T , T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;
public :
    // egyszerűség kedvvéért használjuk az ősosztály ezen függvényeit
    using Inher::begin;
    using Inher::end;
    using Inher::size;

    // behelyezünk egy elemet (a map az a kulcs-értékeket 
    //   egy párban tárolja, így kell behelyeznünk nekünk)
    void insert( const T& k , const T& v )
    {
        Inher::insert( std::make_pair( k ,v ) );
    }

    // ha lekérjük egy elemhez tartozó értéket, akkor 
    //  végig kell mennünk a map-en, és az első kulcs, vagy érték egyezést
    //  vissza kell adnunk (nem elég egyértelmű a kódból, de így működik jól)
    T at( const T& k ) const
    {
        for( const_iterator it = begin() ; it != end() ; ++it )
            if( it->first == k ) return it->second;
            else if( it->second == k ) return it->first;
        // ha nem volt, akkor egy üres, invalid elemmel térünk vissza
        return T();
    }

    // megszámoljuk, hogy egy értékből mennyi van a map-ben
    size_type count( const T& k ) const
    {
        // megszámlálás tételét alkalmazzuk
        size_type res = 0;
    
        // végig megyünk az intervallumon, és ha bármelyik egyezik, elszámoljuk
        for( const_iterator it = begin() ; it != end() ; ++it )
            if( it->first == k || it->second == k ) ++res;

        // visszatérünk ^^
        return res;
    }
    
    // kitöröljük az összes előfordulását a paraméternek
    // (akár bal, akár jobb oldalon találjuk meg)
    void erase( const T& k )
    {
        for( iterator it = begin() ; it != end() ; ++it )
            if( it->first == k || it->second == k ) Inher::erase( it-- );
    }

    // default konstruktor
    BidirectionalMap(){}

    // iterátoros konstruktor. Adjuk tovább az ősosztálynak
    template <typename It>
    BidirectionalMap( It begin , It end ):Inher( begin , end ){}
};


#endif // HEADER_INCLUDED
