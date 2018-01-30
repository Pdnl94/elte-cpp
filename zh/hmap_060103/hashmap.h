#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <numeric>
#include <string>
#include <vector>

// meg kellett valósítani egy másik hash függvényt, mint ami a cpp-ben van.
// constructorba megkapjuk, hogy 0-tól meddig kell hashelni
// az operator() meg visszaadja az std::string típusra a hash értékét
class Func2 {
  const int n;
public:
  Func2(int i):n(i) { }

  int operator()(const std::string& s) const {
    return ( n - 1 - (std::accumulate(s.begin(),s.end(),0)) % n );
  }
};


// van 3 template paraméterünk, az első, hogy milyen indexelésű legyen a map
// a második, hogy milyen elemeket fogunk eltárolni
// a harmadik, hogy milyen hash fügvénnyel dolgozzunk
template <typename Key , typename Value , typename Func>
class HashMap
{
    // legyen egy Bucket az egy vectornyi < Key , Value > pár
    // legyen a Table az egy vectornyi Bucket
    // plusz legyenek még elnevezve osztályok, amik aliasok
    typedef std::pair < Key , Value > Elem;
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
    HashMap( size_type n ):table( n , Bucket() ),f(n)
    {}

    // az insert hash-eli a bejövő elemet, majd megnézi, hogy volt-e már az eddigiek között.
    // ha nem volt, akkor beleteszi a megfelelő Bucket végére
    void insert( const Key& k , const Value& v )
    {
        size_type n = f( k );
        for( size_type i = 0 ; i < table[n].size() ; ++i )
        {
            if( table[n][i].first == k ) return;
        }
        table[n].insert( table[n].end() , std::make_pair( k , v ) );
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

    // lekérünk egy elemet a kulcs alapján
    // végigmegyünk az n. (n a key hash-e) Bucketen, ha van találat, akkor visszatérünk vele
    // különben meg egy invalid elemmel térünk vissza
    Value get( const Key& k ) const
    {
        size_type n = f( k );
        for( size_type i = 0 ; i < table[n].size() ; ++i )
        {
            if( table[n][i].first == k ) return table[n][i].second;
        }
        return Value();
    }

    // kitörlünk egy elemet a kulcs alapján
    // végigmegyünk az n. (n a key hash-e) Bucketen, ha van találat, akkor kitöröljük, és kilépünk
    void erase( const Key& k )
    {
        size_type n = f( k );
        for( size_type i = 0 ; i < table[n].size() ; ++i )
        {
            if( table[n][i].first == k )
            {
                table[n].erase( table[n].begin() + i );
                break;
            }
        }

    }
};

#endif // HEADER_INCLUDED
