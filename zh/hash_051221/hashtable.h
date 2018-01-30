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
#include <set>

// meg kellett valósítani egy másik hash függvényt, mint ami a cpp-ben van.
// template paraméterként kaptunk egy típust (hogy milyen típust kell hashelni)
// constructorba megkapjuk, hogy 0-tól meddig kell hashelni
// az operator() meg visszaadja a T típusra a hash értékét
template <class T>
class Func2 {
  const int n;
public:
  Func2(int i): n(i) { }
  int operator()(const T& x) const { return n - 1 - x%n; }
};

// van 2 template paraméterünk, az első, hogy milyen elemeket fogunk eltárolni
// a második, hogy milyen hash fügvénnyel dolgozzunk
template <typename Elem , typename Func>
class HashTable
{
    // legyen egy Bucket az egy vectornyi Elem
    // legyen a Table az egy vectornyi Bucket
    // plusz legyenek még elnevezve osztályok, amik aliasok
    typedef std::vector < Elem > Bucket;
    typedef std::vector < Bucket > Table;
    typedef typename Bucket::size_type size_type;
    typedef typename Bucket::iterator iterator;

    // csináljunk egy táblát meg egy funktor példányt
    Table table;
    Func f;
public:
    // amikor constructorba megkapjuk a bucket méretet, létrehozzuk a táblát n db üres Buckettel
    // és a funktornak is átadjuk, hogy eddig hash-eljen
    HashTable( size_type n ):table( n , Bucket() ),f(n)
    {}
    
    // az insert hash-eli a bejövő elemet, majd megnézi, hogy volt-e már az eddigiek között.
    // ha nem volt, akkor beleteszi a megfelelő Bucket végére
    void insert( const Elem& e )
    {
        size_type n = f( e );
        if ( std::find( table[n].begin() , table[n].end() , n ) == table[n].end() )
        {
            table[n].insert( table[n].end() , e );
        }
    }

    // az n. bucket méretét kérhetjük le
    size_type size( size_type n ) const
    {
        return table[n].size();
    }

    // a bucketek összméretét is le lehet kérdezni. Számoljuk meg
    size_type size() const
    {
        size_type res = 0;
        for( size_type i = 0 ; i < table.size() ; ++i )
        {
            res += table[i].size();
        }
        return res;
    }
    
    // benne van-e egy bizonyos elem
    // hívjuk meg a hash függvényt, és nézzük meg, hogy benne van-e az n. Bucketbe.
    bool has( const Elem& e ) const
    {
        size_type n = f( e );
        return std::find( table[n].begin() , table[n].end() , n ) != table[n].end();
    }

    // keressük meg hasheléssel, majd az n. bucketbe.
    // ha létezik, akkor a megkeresésnél visszzakapott iterátorával tudjuk törölni
    void erase( const Elem& e ) 
    {
        size_type n = f( e );
        iterator it = std::find( table[n].begin() , table[n].end() , n );
        if( it != table[n].end() )
        {
            table[n].erase( it );
        }
    }
};

#endif // HEADER_INCLUDED
