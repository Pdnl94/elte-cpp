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
    A feladat egy olyan halmaz megvalósítása, mely kap template paraméterként egy számot, ami azt mondja meg, hogy maximálisan
        annyi elem lehet a halmazban egyidejűleg. Ha többbet tennénk bele, akkor a legkorábbi elemet töröljük ki
    Két halmaznak le lehet kérdezni az unióját és a metszetét
*/

#include <set>
#include <deque>
#include <functional>
#include <algorithm>

// 3 template paraméter
// első a halmazban lévő elemek típusa
// második egy szám, ami megmondja, hogy max hány elem lehet egyszerre benn a struktúránkban
// a harmadik egy rendező operátor, mely alapból a kisebb operátor
//  származzunk az std::set-ből
template < typename T , std::size_t Max , typename Comp = std::less < T > >
class CachedSet : public std::set < T , Comp >
{
    // nevezzünk el típusokat 
    typedef std::set < T , Comp > Inher;
    typedef typename Inher::size_type size_type;
    typedef std::deque < T > Cache;

    // ebbe tároljuk az elemeket, hogy milyen sorrendben "érkeztek"
    Cache cache;
public:
    // default constructor
    CachedSet(){}

    // intervallumos constructor - adjuk tovább a halmaznak
    template < typename It >
    CachedSet( It begin , It end ):Inher( begin , end ){}

    // behelyező művelet
    void insert( const T& e )
    {
        // bele próbáljuk tenni (vissza ad egy pair-t), kérjük le a 2. elemét (hogy ő most új elem volt-e)
        if( Inher::insert( e ).second )
        {
            // új elem, tároljuk el a cache-be, és ellenőrizzük, hogy nem-e léptük túl a határt
            cache.push_back( e );
            if( cache.size() > Max )
            {
                // ha több elemünk van benne, akkor töröljük a halmazból a Cache első elemét, majd a cache-ből is
                this->erase( cache.front() );
                cache.pop_front();
            }
        }
    }

    // két halmaz uniója
    CachedSet set_union( const CachedSet& s ) const
    {
        // csináljunk egy visszatérési ideiglenes változót
        Cache res;

        // hívjuk meg a beépített set_union-t, adjunk át minden információt.
        std::set_union( this->begin() , this->end() ,
                        s.begin() , s.end() ,
                        std::inserter( res , res.begin() ) , Comp() );

        // csak az utolsó elemeket kell megadni (ellenőrizzük, hogy ha több elem van benne, mint a Max, 
            //akkor annyival toljuk vissza a mutatót a végétől, ha kevesebb, akkor az elemek méretényivel
        return CachedSet( res.end() - std::min( Max , res.size() ) , res.end() );
    }

    // két halmaz metszete
    CachedSet set_intersection( const CachedSet& s ) const
    {
        // csináljunk egy visszatérési ideiglenes változót
        Cache res;

        // hívjuk meg a beépített set_intersection-t, adjunk át minden információt.
        std::set_intersection(  this->begin() , this->end() ,
                                s.begin() , s.end() ,
                                std::inserter( res , res.begin() ) , Comp() );

        // csak az utolsó elemeket kell megadni (ellenőrizzük, hogy ha több elem van benne, mint a Max, 
            //akkor annyival toljuk vissza a mutatót a végétől, ha kevesebb, akkor az elemek méretényivel
        return CachedSet( res.end() - std::min( Max , res.size() ) , res.end() );
    }
};


#endif // HEADER_INCLUDED
