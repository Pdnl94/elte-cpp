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
    A feladat egy olyan konténer megvalósítása, mely template paraméterként az elemek típusán kívül még megkapja azt, hogy
    Stack, vagy Queue adatszerkezetként viselkedjen, egy boolean értékként.
    Harmadik template paraméterként még azt is megkapja, hogy mind ez milyen konténerrel legyen megvalósítva

    A push a konténer végébe helyez be egy elemet
    A get és a pop attól függően, hogy most Stack-e vagy sem, az adatszerkezet elejéhez, vagy végéhez nyúl

    Le lehet kérni a stack-et meg a queue adatszerkezeteket a data függvény segítségével

    Segítségként kaptunk egy mellékelt "if.h" headert, amit felhasználunk 
    ( C++11-től már std::condition is ugyan azt csinálja )
*/

#include <deque>
#include <stack>
#include <queue>
#include "if.h"

// 3 template paraméter, az első az elemek típusa, a második, hogy stack, vagy queue-e,
// a harmadik a container típusa, ami default legyen a deque
//   származunk a container-ből
template < typename T , bool Stack , typename Cont = std::deque < T > >
class StackQueue : public Cont
{
    // nevezzük el a stack, vagy a queue típust, a mellékelt segítő osztályt felhasználva
    typedef typename If < Stack , std::stack < T > , std::queue < T > >::Ret DataType;

public:

    // push a végébe, push_back...
    void push( const T& t )
    {
        Cont::push_back( t );
    }

    // get - ha stack, akkor a végén, ha queue akkor az elején lévő elemet adja vissza 
    T get() const
    {
        return Stack ? Cont::back() : Cont::front() ;
    }

    // túlterheltük a get-et a this const-ságán, a működése ugyan az
    T& get()
    {
        return Stack ? Cont::back() : Cont::front() ;
    }

    // pop - ha stack, akkor a végén, ha queue akkor az elején lévő elemet töröljük     
    void pop()
    {
        Stack ? Cont::pop_back() : Cont::pop_front() ;
    }

    // ha le akarjuk kérni a data-t, akkor hozzunk létre egy deque-t a saját containerünkből
    // majd cast-oljuk át biztonságosan stack-é vagy queue-é a template paramétertől függően
    DataType data() const
    {
        return static_cast< DataType >( std::deque< T >( Cont::begin() , Cont::end() ) );
    }

};


#endif // HEADER_INCLUDED
