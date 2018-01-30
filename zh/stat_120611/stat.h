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
    A feladat egy olyan statisztikai osztály megvalósítása, melynek vannak a következő függvényei
        average - visszaadjaa az elelmek átlagát
        mostFrequentElement - visszaadja a leggyakoribb elemet
        numberOfDifferentElements -  visszaadja hány különböző elem van benne
        count - egy elem hányszor van benne a struktúrában
        max / min - a struktúra maximumát - minimumát adja vissza (funktoros megvalósítással is)
*/


#include <algorithm>
#include <numeric>
#include <set>
#include <map>

// két template paraméter
// az első a konténer, amiben tárolnunk kell az elemeket
// a második paraméter az elemek típusa - alapértelmezetten kérjük le a konténerben lévő értékek típusát
template <typename Container , typename Elem = typename Container::value_type>
class Statistics
{
    // ebben tároljuk az elemeket
    Container data;

    // egy pár typedef
    typedef typename Container::size_type size_type;
    typedef typename Container::const_iterator const_iterator;
public:

    // default konstruktor
    Statistics(){}

    // konstruktor, ami egy containert vár. Ezt továbbadjuk a data-nak
    Statistics( const Container& c ):data(c){}

    // belehelyezünk egy elemet
    void insert( const Elem& e )
    {
        data.push_back( e );
    }

    // visszaadjuk a min/max értékét a struktúrának
    // használjuk a beépített függvényeket
    Elem max() const
    {
        return *std::max_element( data.begin() , data.end() );
    }

    Elem min() const
    {
        return *std::min_element( data.begin() , data.end() );
    }

    // visszaadjuk az átlagot úgy, hogy a beépített accumulate -el kiszámoljuk az elemek összegét
    // majd leosztjuk a méretével
    Elem average() const
    {
        return std::accumulate( data.begin() , data.end() , Elem() ) / data.size();
    }

    // visszaadjk a méretét
    size_type size() const
    {
        return data.size();
    }

    // a különböző elemek számát adja vissza
    size_type numberOfDifferentElements() const
    {
        // csináljunk egy temporális halmazt, melybe beletesszük az elemeket
        // majd kérjük le a méretét - ennyi különböző elem lesz
        return std::set<Elem>( data.begin() , data.end() ).size();
    }

    // leggyakoribb elem meghatározása
    Elem mostFrequentElement() const
    {
        // hozzunk létre egy map-et, amiben ideiglenesen tárolni fogjuk,
        // hogy egy elem hányszor van benne a struktúránkban
        std::map< Elem , size_type > mp;

        // végigmegyünk az elemeken, és a hozzá tartozó értéket mindig növeljük egyel
        for( const_iterator begin = data.begin() ; begin != data.end() ; ++begin )
        {
            ++mp[ *begin ];
        }

        // végzünk egy maximumkeresést a map value (second) értékein
        Elem max; // elem
        int maxdb = 0; // az elem hányszor volt benne

        for ( typename std::map< Elem , size_type >::const_iterator it = mp.begin() ;
                    it != mp.end() ; ++it )
        {
            if( it->second > maxdb )
            {
                maxdb = it->second;
                max = it->first;
            }
        }
        //visszatérünk a max elemmel
        return max;

    }

    // megszámoljuk, hogy egy elem hányszor van benne - beépített függvénnyel
    size_type count( const Elem& e )
    {
        return std::count( data.begin() , data.end() , e );
    }

    // egy template paraméter alapján megkapott funktor szerinti maximum/minimum.
    // hívjuk meg a beépített max_element - STL algoritmust
    template <typename Fun>
    Elem max( Fun f ) const
    {
        return *std::max_element( data.begin() , data.end() , f );
    }

    template <typename Fun>
    Elem min( Fun f ) const
    {
        return *std::min_element( data.begin() , data.end() , f );
    }

};

#endif // HEADER_INCLUDED
