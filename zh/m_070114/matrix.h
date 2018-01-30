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

// 3 template paraméter, az első a tárolt elemek típusa
// a második a sorok száma, a harmadik az oszlopoké
template <typename T , std::size_t R , std::size_t C >
class Matrix
{
    // legyen egy sor egy vector
    typedef std::vector < T > Row;
    // legyen a mátrix reprezentáció egy vectornyi sor
    typedef std::vector <Row> Matrix_r;

    typedef typename Row::size_type size_type;

    Matrix_r m;
public:
    // def constructorba megadjuk az elemek kezdőértékeit
    Matrix( const T& t = T() ):m( R , Row( C , t ) ){}

    // lekérhető az x,y. elem
    T at( size_type x , size_type y ) const
    {
        return m[x][y];
    }

    // sorok száma == R == mátrix mérete (sorainak száma)
    size_type rows() const
    {
        return m.size();
    }

    // lekérhető az x,y. elem
    T operator()( size_type x , size_type y ) const
    {
        return m[x][y];
    }

    // referencia szerint is, hogy változtatható legyen
    T& operator()( size_type x , size_type y )
    {
        return m[x][y];
    }

};

// olyan slow sort, ami kap egy összehasonlító funktort
// és akkor cserél, ha NEM igaz
template <typename ItType , typename Comp >
void slow_sort( ItType begin , ItType end , Comp c )
{
    while( begin != end )
    {
        ItType it = begin;
        for( ++it ; it != end ; ++it )
        {
            if( !c(*it , *begin) )
                std::swap( *it , *begin );
        }
        ++begin;
    }
}

// hívjuk meg a összehasonlító funktorral rendelkező függvényt
// ugye ő akkor cserél, ha NEM igaz, ezért adjuk át neki a >= operátoros funktort
template <typename ItType>
void slow_sort( ItType begin , ItType end )
{
    return slow_sort( begin , end , std::greater_equal< typename std::iterator_traits< ItType >::value_type >() );
}


#endif // HEADER_INCLUDED
