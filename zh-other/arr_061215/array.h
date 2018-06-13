#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

// lusta megoldás :)

#include <vector>

// származzon a tömb típus a vector-ból
// 2 template paraméter, az egyik az elemek típusa, 
// a másik egy int, ami megmondja, hogy hány elem van a tömbben
template <typename T , std::size_t N >
struct Array : public std::vector < T >
{
    // a constuctorba beállítja, hogy N elemű legyen
    Array( const T& e = T() ) : std::vector < T >( N , e ){}
};

// egy függvény megvalósítás
// az intervallumon belül amelyikre igaz a p feltétel, arra elvégezzük az f függvényt
// visszatérünk az f fügvénnyel
template <typename ItType, typename Pred , typename Func>
Func for_each_if( ItType begin, ItType end , Pred p , Func f )
{
    for ( ; begin != end ; ++begin )
        if( p( *begin ) )
            f( *begin );
    return f;
}

#endif // HEADER_INCLUDED
