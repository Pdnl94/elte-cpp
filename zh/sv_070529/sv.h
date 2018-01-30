#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <vector>
#include <functional>

// 2 template paraméter, az első az elemek típusa
// a második paraméter a rendezés alapja
template <typename T,  typename Comp = std::less<T> >
class SortedVector : public std::vector < T >
{
    // nevezzük el a szülő osztályt
    typedef std::vector< T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;

    // példányosítsunk egy rendező funktort
    Comp c;
public:
    // def constructort
    SortedVector(){}

    // intervallumos konstruktor. Az összes elemet helyezzük be.
    template <typename ItType>
    SortedVector( ItType begin , ItType end )
    {
        while( begin != end )
        {
            insert( *begin++ );
        }
    }

    // helyezzük be az elemet
    void insert( const T& e )
    {
        // menjünk el addig az iterátorral, amíg kisebbek az elemek, majd helyezzük be az iterátor helyére
        iterator it = Inher::begin();
        while( it != Inher::end() && c( *it , e ) ) ++it;
        Inher::insert( it , e );
    }
};

#endif // HEADER_INCLUDED
