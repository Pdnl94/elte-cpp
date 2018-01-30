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
    A feladat egy olyan map (kulcs-érték) típus létrehozása, amely az érték-alapján is vissza tudja keresni a kulcsokat
    le lehet kérdezni, hogy melyik érték melyik kulcshoz van rendelve, illetve hogy hányszor szerepel a map struktúrában 

    specializáljuk arra az esetre, hogy a kulcs és az érték megegyezik.
*/

#include <map>

// 2 template, a kulcs, és a hozzá rendelt érték típusai, származunk a map < Key, Val >-ból
template < typename Key , typename Val >
class BidirectionalMap : public std::map < Key , Val >
{
    // típuselnevezések
    typedef std::map < Key , Val > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator const_iterator;
public:
    // használjuk a beépített [] operátort is, mert elfedtük a megvalósítottal
    using Inher::operator[];
    // a többivel nincs probléma, mivel publikusan származunk

    // insert - behelyez egy párat a map-be
    void insert( const Key& k ,const Val& v )
    {
        Inher::insert( std::make_pair( k , v ) );
    }

    // egy value-ról megállapítjuk, hogy melyik kulcshoz tartozik
    Key at( const Val& v ) const
    {
        // végigmegyünk, és ha a second megegyezik, akkor a first-el visszatérünk
        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second == v ) return it->first;
        // ha nem találtuk, akkor egy invalid elemmel
        return Key();
    }

    // számoljuk meg, hogy egy value hányszor van benne a struktúrában
    size_type count( const Val& v ) const
    {
        size_type ret = 0;
        // megszámlálás tétel, ha second == aktuális érték, akkor növeljünk
        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second == v ) ++ret;

        return ret;
    }

    // ugyan az mint az at()
    Key operator[]( const Val& v ) const
    {
        return at(v);
    }
};

// specializáljuk az osztályt úgy, hogy ugyan az a kulcs és az érték - származzunk a map-ból
template <typename T>
class BidirectionalMap<T,T> : public std::map < T , T >
{
    // elnevezések
    typedef std::map < T , T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator const_iterator;
public:
    // insert, semmi változás
    void insert( const T& k ,const T& v )
    {
        Inher::insert( std::make_pair( k , v ) );
    }

    // az első, amire megtaláljuk azt, hogy ő most a kulcs, vagy az érték volt, a másikat visszaadjuk
    T at( const T& v ) const
    {
        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
        {
            if( it->first == v ) return it->second; // kulcs volt, értéket adunk vissza
            if( it->second == v ) return it->first; // érték volt, kulcsot adunk vissza
        }
        return T();
    }

    // megszámolja, hogy hányszor szerepel a párokban legalább egyszer
    size_type count( const T& v ) const
    {
        size_type ret = 0;
        // bármelyik (kulcs, érték) megegyezik, növeljük a számlálót
        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second == v || it->first == v ) ++ret;

        return ret;
    }

    // ugyan az, mint az at()
    T operator[]( const T& v ) const
    {
        return at( v );
    }
};



#endif // HEADER_INCLUDED
