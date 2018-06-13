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
    A feladat egy olyan lista megvalósítása, mely rendezetten tárolja az elemeket, 
    és amikor beszúrunk egy elemet, ,már rögtön sorrendben teszi be

    Template paraméterként kapunk még egy funktort, ami alapján rendezzük az elemeket
*/

#include <list>
#include <functional>
#include <algorithm>

// 2 template paraméter, az első az elemek típusa
// a második paraméter a rendezés alapja
template <typename T,  typename Comp = std::less<T> >
class SortedList : public std::list < T >
{
    // nevezzük el a szülő osztályt (list-ből származunk)
    typedef std::list< T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;

    // példányosítsunk egy rendező funktort
    Comp c;
public:
    // def constructort
    SortedList(){}

    // intervallumos konstruktor. Az összes elemet helyezzük be, majd tegyük sorrendbe a funtor alapján.
    template <typename ItType>
    SortedList( ItType begin , ItType end ) : Inher( begin , end )
    {
        Inher::sort( c );
    }

    // helyezzük be az elemet
    void insert( const T& e )
    {
        // keressük meg az iterátor helyét, majd helyezzük be oda
        Inher::insert( std::lower_bound( Inher::begin() , Inher::end() , e , c ) , e );
    }
};

#endif // HEADER_INCLUDED
