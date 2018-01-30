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
    A feladat egy olyan vector megvalósítása, melytől le lehet kérdezni azt, hogy egy bizonyos elem hanyadik indexen található meg
    Ezt eltároljuk, és ha újra lekérdezzük, akkor először az eltárolt elemekből próbálja meg megkeresni az indexét

    Template paraméterként kapunk egy számot, hogy maximálisan ennyi elemről tárolhatjuk el, hogy hanyadik indexen van 

    A not_in_vec függvény egy olyan értékkel tér vissza, ami egy nem létező indexnek felel meg ( általában -1 )  
    A last_index_of az utolsó egyezés indexét adja meg a vectorban

    Ha történik egy elem lekérés, akkor frissíteni kell az eltárolt elemeket

*/


#include <vector>
#include <deque>
#include <algorithm>

// 2 template paraméter, az első az elem típusa, a második, hogy max mennyi elemet tárolhat el a cache-be
// származzunk a vector-ból
template < typename T , std::size_t Max >
class CachedVector : public std::vector < T >
{
    // nevezgessünk el típusokat
    typedef std::vector < T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_reverse_iterator const_reverse_iterator;

    // legyen a cache egy olyan deque ( sor adatszerkezetként használva )
    // mely párokat tárol, az elemet, és a hozzá tartozó indexét
    typedef std::deque < std::pair < T , size_type > > Cache;
    typedef typename Cache::iterator cache_iterator;
    typedef typename Cache::const_iterator cache_const_iterator;

    // példányosítsuk
    Cache cache;
public:
    // publikussá tettük a const_iterator-t, mert használják kívülről
    typedef typename Inher::const_iterator const_iterator;

    // egy elemnek lekérjük az indexét
    size_type index_of( const T& e )
    {
        // végig nézzük a cache-be, ha a pár első elemével megegyezik, akkor benne van
        // visszatérünk vele
        for( cache_const_iterator ccit = cache.begin() ; ccit != cache.end() ; ++ccit )
            if( ccit->first == e )
                return ccit->second;

        // ha nincs a cachebe, akkor keressük meg az ősosztályban
        const_iterator it = std::find( this->begin() , this->end() , e );

        // ha nem találtuk meg, akkor nincs a vectorban, 
        // különben az iterátor (ahol megtaláltuk) visszaadja az indexét egy kivonással
        size_type res = it == this->end() ? not_in_vec() : it - this->begin();

        // tegyük bele a cache-be az új értéket
        cache.push_front( std::make_pair( e , res ) );

        // ha több van a cache-be, mint a max, akkor vegyük ki az első elemét
        if( cache.size() > Max )
            cache.pop_back();

        // térjünk vissza az eredménnyel
        return res;
    }

    // invalid elemmel térünk vissza, legyen a -1
    size_type not_in_vec() const
    {
        return static_cast<size_type>(-1);
    }

    // megkeressük az elemet reverse_iterátorral, és visszatérünk az értékével
    size_type last_index_of( const T& e ) const
    {
        const_reverse_iterator it = std::find( this->rbegin() , this->rend() , e );
        return it == this->rend() ? not_in_vec() : this->rend() - it - 1;
    }

    // ha valaki lekéri [] operátorral az értéket,
    // akkor vegyük ki a cache-ből az ezen indexű elemeket
    T& operator[]( size_type t )
    {
        // ha van ilyen eltárolás, ami azt mondja, hogy a t. elemen található, töröljük
        for( cache_iterator ccit = cache.begin() ; ccit != cache.end() ; ++ccit )
            if( ccit->second == t )
                 cache.erase( ccit-- );

        // térjünk vissza úgy, mint ahogy az ősosztály
        return Inher::operator[]( t );
    }

    // a const túlterhelését lusta módon így tudjuk használhatóra bírni
    using Inher::operator[];

    // constructor
    CachedVector(){}

    // constructorba, ahol más a Max, annál csak lemásoljuk az elemeket
    // meghívódik a copy constructor
    template <std::size_t AnMax>
    CachedVector( const CachedVector< T , AnMax >& v ):
        Inher( v ){}
};

#endif // HEADER_INCLUDED
