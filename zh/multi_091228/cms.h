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
    A feladatleírásért köszönet az őt megillető személynek! :)

    Feladat:
    A CachedMultiset<T, S, C> típus létrehozása. Ez a típus egy olyan T típusú elemek zsákját valósítja meg, 
    amelyben egyszerre legfeljebb S különböző érték tárolható. Ha beszúrásra kerül az S+1-dik különböző érték,
    akkor a legrégebben beszúrt érték automatikusan eldobásra kerül (ha a multiplicitása nagyobb, mint 1, akkor az összes példánya).
    A típusban az értékek a C funktor szerint rendezettek.

    Megvalósítandó metódusok:
     - elem beszúrása,
     - elem multiplicitásának lekérdezése,
     - elemszám lekérdezése (a különböző értékek darabszáma),
     - iterátorok támogatása, begin() és end() metódusok.

    Megvalósítandó még az alapértelmezetten kívül 3 további konstruktor:
     - copy konstruktor,
     - egy olyan konstruktor, amely egy std::map<T, int> paraméterrel azt is megadja, hogy az egyes értékekből
       hány kerülhet a CachedMultiset objektumba legfeljebb, és az elemek beszúrásakor ezt ellenőrizni kell,
     - egy olyan konsturktor, amely két iterátor közötti elemeket a konstruáláskor betölti a CachedMultiset objektumba.

*/

#include <set>
#include <functional>
#include <deque>
#include <map>

// 3 template paraméter, az első az elemek típusa
//  a második, hogy maximálisan hány elem lehet a multiset-ben
//  a harmadik a rendező operátor
template < typename T , std::size_t Max , typename Comp = std::less < T > >
class CachedMultiset : public std::multiset < T , Comp >
{
    // nevezzük el az ősosztályt
    typedef std::multiset < T , Comp > Inher;

    // paraméterül kaphatunk egy ilyen Limits-osztályt, mely megmondja,
    // hogy egy elem max hányszor lehet benne a struktúrában
    typedef std::map< T , int > Limits;
    typedef typename Limits::iterator limits_iterator;

    // ebbe tároljuk el a behelyezett elemek sorrendjét, e szerint törlünk
    typedef std::deque< T > Cache;

    // pédányosítsuk a limit-et, és a cache-t
    Limits limit;
    Cache cache;
public:
    // insert művelet
    //  bemenet : egy T típusú elem
    //  kimenet : Saját magunk, hogy meghívható legyen a .insert(1).insert(5).insert(8) ...

    CachedMultiset& insert( const T& t )
    {
        // megkeressük, hogy erre az elemre tartozik-e limitáció, 
        limits_iterator it = limit.find( t );
        
        // ha igen, és túlléptük, akkor semmit nem csinálunk, különben
        if( it == limit.end() || Inher::count( t ) < it->second )
        {
            // helyezzük be a halmazba és a cache-be az elemet
            Inher::insert( t );
            cache.push_back( t );

            // ha túlléptük a megengedett maximum elemszámot
            if( Inher::size() > Max )
            {
                // akkor töröljük a cache első elemét, majd a cache-ből is
                Inher::erase( Inher::find( cache.front() ) );
                cache.pop_front();
            }
        }
        // térjünk vissza magunkkal
        return *this;
    }

    // constructorok - default, semmi teendő
    CachedMultiset(){}

    // Limit-es constructor, csak másoljuk be a struktúránkba
    CachedMultiset( const Limits& l ) : limit(l) {}

    // Iterátoros constructor
    template <typename It>
    CachedMultiset( It begin , It end )
    {
        // végigmegyünk az intervallumon, majd az összes elemet belehelyezzük 
        // a megvalósított insert függvényünk segítségével
        while( begin != end )
            insert( *begin++ );
    }
};

#endif // HEADER_INCLUDED
