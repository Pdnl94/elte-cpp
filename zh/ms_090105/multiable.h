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
    A feladat egy olyan halmaz, mely template paraméterként kap egy + boolean-t, hogy most úgy viselkedjen, mint egy set, vagy mint egy multiset
    A műveletek ugyan azok, mint a set/multiset-nek, egyedül az insert
        az ami úgy működik, hogy halmozottan is lehet belepakolni a dolgokat ( .insert(5).insert(7).insert(9) ... )
    A data függvény lekéri a set / multiset struktúrát
*/

#include <set>
#include <functional>

// csináljunk egy fordítási idejű típuseldöntő osztályt ( C++11-től létezik, std::conditional )
// http://www.cplusplus.com/reference/type_traits/conditional/
template < bool Cond, class T, class F > struct conditional                  { typedef F type; };
template <            class T, class F > struct conditional < true , T , F > { typedef T type; };


// legyen a halmaz struktúránk 3 template paraméterű, a típus, hogy több elem többször belekerülhet-e, és a rendező operátor
// származzunk a set-ből, vagy a multiset-ből, attól függően, hogy Multiable-k vagyunk-e
template < typename T , bool Multiable , typename Comp = std::less < T > >
class MultiableSet : public conditional < Multiable , std::multiset < T , Comp > , std::set < T , Comp > >::type
{
    // nevezzük el az ősosztályt
    typedef typename conditional < Multiable , std::multiset < T , Comp > , std::set < T , Comp > >::type Inher;

public:
    // az insert művelet a saját típus referenciájával tér vissza, 
    // behelyezzük az elemet, és visszatérünk magunkkal
    MultiableSet& insert( const T& t )
    {
        Inher::insert( t );
        return *this;
    }

    // a más szignatúrájú insert függvényeket ugyan úgy akarjuk használni, mint az ősosztályba
    // így csak megmondjuk a fordítónak, hogy használja azokat
    using Inher::insert;

    // visszatérünk a származó osztályunkkal, egyszerűen csak odaadjuk magunkat (hisz származunk belőle)
    const Inher& data() const
    {
        return *this;
    }
};


#endif // HEADER_INCLUDED
