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
#include <algorithm>

// 2 template paraméter, a Key, meg a Value (mint egy Map-nél)
template <typename Key, typename Value>
class OrderedMMap
{
    // tároljuk el a könyveket egy vector-nyi pair-be, kérjünk le egy pár típust
    typedef std::vector < std::pair < Key , Value > > Container;
    typedef typename Container::size_type size_type;
    typedef typename Container::const_iterator const_iterator;

    Container c;
public:
    // a behelyezés megkeresi a kulcsok szerint rendezett struktúrában
    // az utolsó kulcs szerinti egyezés utáni elemet, majd behelyezi
    void insert( const Key& k , const Value& v )
    {
        size_type i = 0 ;

        while( i < c.size() && c[i].first <= k ) ++i;

        c.insert( c.begin() + i , std::make_pair( k , v ) );
    }

    // lekérhetjük a k kulcsok közüli n. elem értékét
    Value at( const Key& k , size_type n = 0 ) const
    {
        size_type i = 0;

        // amíg kisebbek a kulcsok, lépkedünk
        while( i < c.size() && c[i].first < k ) ++i;

        // amíg nem nagyobbak a kulcsok, n-et csökkentjük, míg el nem éri
        // a 0-t, ekkor visszatérünk a megtalált értékkel
        for ( ; i < c.size() && ! ( k < c[i].first ) ; ++i )
            if( ! n-- )
                return c[i].second;

        // ha nem volt benne, akkor egy invalid elemmel térjünk vissza
        return Value();
    }

    // töröljük ki a k kulcsúak közül az n.et
    // hasonló működésű mint az at(), csak itt nem visszaadjuk, hanem kitöröljük
    void erase( const Key& k , size_type n = 0 )
    {
        size_type i = 0 ;

        while( i < c.size() && c[i].first < k ) ++i;

        for ( ; i < c.size() && ! ( k < c[i].first ) ; ++i )
            if( ! n-- )
            {
                c.erase( c.begin() + i );
                break;
            }
    }

    // megszámolhatjuk, hogy egy kulcsból hány elem van a struktúrában
    size_type count( const Key& k ) const
    {
        // i-vel megyünk az elemeken, n be számoljuk meg
        size_type n = 0, i = 0;

        // amíg kisebb, lépjünk
        while( i < c.size() && c[i].first < k ) ++i;

        // amíg megegyezik (nem nagyobb),  növeljünk, lépjünk
        while( i < c.size() && ! ( k < c[i].first ) )  ++n,++i;

        return n;
    }

    // hasonló az at()-hez, ha nem volt ilyen elem, dobjunk hibát
    Value& operator()( const Key& k , size_type n = 0 )
    {
        size_type i = 0 ;

        while( i < c.size() && c[i].first < k ) ++i;

        for ( ; i < c.size() && ! ( k < c[i].first ) ; ++i )
            if( ! n-- )
                return c[i].second;

        throw "";
    }

    // könnyedség kedvéért meghívjuk az at() fv-t
    Value operator()( const Key& k , size_type n = 0 ) const
    {
        return at( k , n );
    }

    // lekérhetjük a méretét, illetve az iterátorait
    size_type size() const
    {
        return c.size();
    }

    const_iterator begin() const
    {
        return c.begin();
    }

    const_iterator end() const
    {
        return c.end();
    }
};

#endif // HEADER_INCLUDED
