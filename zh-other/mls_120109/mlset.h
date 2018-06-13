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

Segítség: a cél egy olyan halmazszerű adatszerkezet megvalósítása, ami "rétegzett" haslmazként működik! Ez a szerkezet többszintű halmaz és ha be akarujuk szúrni egy elemet, akkor először a 0-adik szintet nézzük, ha abban már benne van az elem, akkor a következőt, ezt mindaddig, míg nem jututnk el olyan szinthet, ahol még nincs, vagy addig, amíg nem megyünk végig az összes eddig létező szinten és mindegyikben benne van. Ezutóbbi esetben egy új színtet hozunk létre és abba szúrjuk a beszúrandó elemet be, hiszen abban az új szintben még nincs benne.
Törléskor kivesszük az eltávolítandó elemet az összes szintről és figyelünk arra, hogy az üres szintek szünjenek meg!

    Mivel elsőre nem volt tiszta, hogy mit kellene csinálnia, ezért leszedtem netről megoldásokat, és abban volt ez a szöveg. Köszönöm :)
    És mivel lusta voltam átírni az egészet, csak egy függvényt kellett, így nem csináltam előről, és nem elég szép, remélem nem probléma
*/

#include <map>
#include <set>
#include <functional>

// 2 template paraméter
// első az elem típusa, a második egy rendező funktor
template <typename T , typename Compare = std::less< T > >
class multilevel_set : public std::multiset< T , Compare >
{
    // hozzunk létre típusdefiníciókat
    typedef std::multiset< T , Compare > Container;
    typedef typename Container::size_type size_type;
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::iterator iterator;
    typedef std::pair< iterator , iterator > eq_range;

public:

    // le lehet kérdezni, hogy mennyi szintre van szükség ahhoz,
    // hogy az eddigi elemeket el tudjuk tárolni
    // azaz hogy egy elemből max mennyi van eddig (mekkora a legnagyobb létszámú elem száma)
    size_type height() const
    {
        // ebbe fogjuk gyűjteni T szerint a darabszámokat
        std::map< T , size_type , Compare > map;

        // az összes elem megnöveli egyel a darabszámát
        const_iterator begin = Container::begin();

        while( begin != Container::end() )
        {
            ++map[ *begin++ ];
        }

        // végzünk a darabszámokon egy max-keresést
        size_type max = 0;

        for( typename std::map< T , size_type , Compare >::const_iterator it = map.begin();
                it != map.end() ; ++it )
        {
            if( max < it->second )
                max = it->second;
        }
        return max;
    }

    // visszaadja, hogy a pos. elemen lévő halmazban hány elem van
    // ez azt jelenti nekünk, hogy megszámoljuk, hogy hány elemből van pos-nál több vagy egyenlő
    size_type size( size_type pos ) const
    {
        // ebbe fogjuk gyűjteni T szerint a darabszámokat
        std::map< T , size_type , Compare > map;

        // az összes elem megnöveli egyel a darabszámát
        const_iterator begin = Container::begin();

        while( begin != Container::end() )
        {
            ++map[ *begin++ ];
        }

        // végzünk számlálást a darabszámaikon
        size_type count = 0;

        for( typename std::map< T , size_type , Compare >::const_iterator it = map.begin();
                it != map.end() ; ++it )
        {
            if( pos < it->second )
                ++count;
        }
        return count;
    }

    // az elemszámok méretét visszaadja
    using Container::size;

    // kitörli az összes t elemet
    void remove( const T& t )
    {
        // kérjük le az intervallumot, hogy hol található meg t, majd töröljük ezt
        eq_range eq = Container::equal_range( t );
        Container::erase( eq.first , eq.second );
    }

    // default konstruktor
    multilevel_set(){}

    // iterátoros konstruktor, továbbadjuk a szülőosztálynak
    template <typename It>
    multilevel_set( It begin , It end ) : Container( begin , end ){}
};

#endif // HEADER_INCLUDED
