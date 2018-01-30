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
        truncatedMean - a legkisebb és a legnagyobb elem kivételével az összes elem átlagát veszi
        mostFrequentElement - visszaadja a leggyakoribb elemet
        median - a rendezett struktúra középső elemét adja vissza
        max / min - a struktúra maximumát - minimumát adja vissza (funktoros megvalósítással is)
*/

#include <set>
#include <map>
#include <algorithm>

// egy template paraméter, hogy milyen típussal foglalkozunk
template <typename T>
class Statistics
{
    // nevezzük el a típusokat (multiset - olyan halmaz, melyben 1 elem többször is előfordulhat)
    typedef std::multiset < T > Container;
    typedef typename Container::size_type size_type;
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::iterator iterator;

    // pédányosítsuk a konténert
    Container data;
public:

    // hozzáad egy elemet 
    void add( const T& t )
    {
        data.insert( t );
    }

    // kitörli az első előfordulását az elemnek
    // ( ha csak simán data.erase(t) - t írnánk, akkor az összeset kitörölné )
    void erase( const T& t )
    {
        // keressük meg a legelső ilyet, és ha volt ilyen elem, töröljük ki
        iterator it = data.find( t );
        if( it != data.end() )
            data.erase( it );
    }

    // leírásban
    T truncatedMean() const
    {
        T sum = T();

        // kiszámoljuk, hogy honnan meddig menjünk, és az összes elemet hozzáadjuk
        const_iterator begin = ++data.begin(),
                        end = --data.end();
        while( begin != end )
        {
            sum += *begin++;
        }
        // visszatérünk az elemek összege / ( méret - 2 ) -vel (hisz az első & az utolsó elem nincs benne)
        return sum / ( data.size() - 2 );
    }

    // méret lekérdezése
    size_type size() const
    {
        return data.size();
    }

    // leggyakoribb elem
    T mostFrequentElement() const
    {
        // hozzunk létre egy map-et, amiben ideiglenesen tárolni fogjuk, 
        // hogy egy elem hányszor van benne a struktúránkban
        std::map< T , size_type > mp;

        // végigmegyünk az elemeken, és a hozzá tartozó értéket mindig növeljük egyel
        const_iterator begin = data.begin(),
                        end = data.end();

        while( begin != end )
        {
            ++mp[ *begin++ ];
        }

        // végzünk egy maximumkeresést a map value (second) értékein
        T max; // elem
        int maxdb = 0; // az elem hányszor volt benne

        for ( typename std::map< T , size_type >::const_iterator it = mp.begin() ;
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

    // a középső elem meghatározása
    T median() const
    {
        // kérjük le az elemszámok felét, és az első elemre mutató iterátort
        size_type half = data.size() / 2;
        const_iterator it = data.begin();

        // léptessük az iterátort pont a felével
        std::advance( it , half );

        // térjünk vissza az itteni értékkel
        return *it;
    }

    // maximum és minimum a multiset első és utolsó eleme (hisz rendezett, asszociatív struktúra)
    // rbegin - utolsó elem, hisz visszafelé iterálásnak az első eleme
    T max() const
    {
        return *data.rbegin();
    }

    T min() const
    {
        return *data.begin();
    }

    // egy template paraméter alapján megkapott funktor szerinti maximum/minimum.
    // hívjuk meg a beépített max_element - STL algoritmust
    template <typename Fun>
    T max( Fun f ) const
    {
        return *std::max_element( data.begin() , data.end() , f );
    }

    template <typename Fun>
    T min( Fun f ) const
    {
        return *std::min_element( data.begin() , data.end() , f );
    }

    // iterátoros konstruktor, adjuk tovább az adatszeerkezetünknek
    template <typename It>
    Statistics( It begin, It end ): data( begin , end )
    {}

    // default konstruktor - kell, mert megvalósítottunk egy iterátorosat, és így eltűnik a default
    Statistics(){}
};


#endif // HEADER_INCLUDED
