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
// 3 template paraméter, CPP-ben leírás
template <typename T, std::size_t N , T e>
struct Array : std::vector < T >
{
    // a constuctorba beállítja, hogy N elemű legyen, és olyan elem, ammi template paraméter
    Array():std::vector < T >( N , e ){}

    // kvázi "copy" constructor, más kezdőértékes Array-el
    template <T an>
    Array( const Array<T,N,an>& f ):std::vector < T >(f){}
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
