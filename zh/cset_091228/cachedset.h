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
    A feladat egy olyan halmaz megvalósítása, mely kap konstruktorban paraméterként egy számot, ami azt mondja meg, hogy maximálisan
        annyi elem lehet a halmazban egyidejűleg. Ha többbet tennénk bele, akkor egy elemet töröljük ki.
        azt, hogy melyiket, template paraméterben kapjuk meg, aszerint, hogy queue, vagy stack szerint töröljünk 
        ( az érkező elemeket időbeli sorrendbe kell tenni, és ha queue, akkor a legrégebbit, ha stack, akkor a legkorábbit )

*/

#include <queue>
#include <stack>
#include <set>
#include <functional>
#include <algorithm>

// csináljunk egy fv-t, ami annyit tesz, hogy egy deque-ből 
//  kiveszi az első elemet, kitörli, majd visszatér vele VAGY
//  kiveszi az utolsó elemet, kitörli, majd visszatér vele
// attól függően, hogy milyen boolean paramétert kaptunk meg
template <typename T>
T nextPop( std::deque< T >& d , bool l )
{
    T res( l ? d.front() : d.back() );
    l ? d.pop_front() : d.pop_back() ;
    return res;
}

// csináljunk egy fordítási időben eldőlő típus - eldöntést
// 3 template paraméter, typedef-eljük a hamis típust type-nek
template <  bool cond,
            class true_type,
            class false_type>
struct conditional
{
    typedef false_type type;
};

// template specializáljuk az előző struktúrát úgy, hogy
// az első paraméter true. Ekkor typedefeljük el az igaz típust
template <  class true_type,
            class false_type>
struct conditional<true, true_type, false_type>
{
    typedef true_type type;
};

// pl:
// typename conditional< true  , int , bool > ::type  erre az int típust kapjuk vissza
// typename conditional< false , int , bool > ::type  erre a bool típust kapjuk vissza

// 3 template paraméter
// 1. halmazban szereplő típusok
// 2. hogy queue vagy stack-ként kezeljük a méretkorlátot
// 3. rendező operátor
template < typename T , bool queue , typename Comp = std::less < T > >
class CachedSet : public std::set< T , Comp >
{
    // nevezzünk el típusokat
    typedef std::set< T , Comp > Inher;
    typedef typename Inher::size_type size_type;
    typedef std::deque< T > Cache;

    // nevezzük el a QoS típust, attól függően, hogy ő egy queue, vagy egy stack 
    typedef typename conditional< queue , std::queue< T > , std::stack< T > >::type QoS;

    // Max-ba tároljuk a maximális elemszámot
    const size_type Max;

    // ebben tároljuk az elemeket időrendi sorrendben
    Cache cache;
public:
    // constructor, megkapjuk a max értéket, és inicializáló listában értékül adjuk neki
    CachedSet( size_type n ):Max(n){}

    // behelyező művelet
    void insert( const T& e )
    {
        // bele próbáljuk tenni (vissza ad egy pair-t), kérjük le a 2. elemét (hogy ő most új elem volt-e)
        if( Inher::insert( e ).second )
        {
            // ellenőrizzük, hogy nem-e léptük túl a határt
            if( cache.size() == Max )
            {
                // ha több elemünk van benne, akkor töröljük a halmazból a Cache első elemét, majd a cache-ből is
                this->erase( nextPop( cache , queue ) );
            }
            // új elem, tároljuk el a cache-be
            cache.push_back( e );
        }
    }

    // kitörlünk egy elemet
    void erase( const T& t )
    {
        // töröljük ki a halmazból
        Inher::erase( t );
        // töröljük ki a cache-ből is ezt az elemet
        cache.erase( std::remove( cache.begin() , cache.end() , t ) , cache.end() );
    }

    // térjünk vissza a cache-el, queue vagy stack típussal
    QoS data() const
    {
        // static cast, MERT
        // bár van a queue-nek is, meg a stack-nek is deque-s constructora, de EXPLICIT
        // azaz konkrétan nekünk kell megmondani, hogy mi szeretnénk belőle egy ilyet csinálni
        return static_cast<QoS>( cache );
    }
};

#endif // HEADER_INCLUDED
