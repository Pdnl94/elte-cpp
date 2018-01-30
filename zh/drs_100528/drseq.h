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
    A feladat egy olyan szekvenciális konténer megvalósítása, mely bármikor megfordítható
    push_back - push_front, mely "halmozható"
    A megvalósítandó konténert template paraméterként kapjuk meg

*/

#include <deque>
#include <algorithm>

// első template paraméter az elem típusa
// a második template paraméter a container, amiben kell ábrázolni (letárolni)
//   default legyen a deque
template <typename T , typename Cont = std::deque < T > >
class DirectionReversibleSequence : public Cont
{
    // nevezzünk el típusokat
    typedef typename Cont::size_type size_type;
    typedef typename Cont::iterator iterator;
    typedef typename Cont::const_iterator const_iterator;
public:
    // default constructor
    DirectionReversibleSequence(){}

    // iterátoros constructor - átadjuk a szülő osztálynak
    template <typename It>
    DirectionReversibleSequence( It begin , It end ) : Cont( begin , end ){}

    // behelyezünk egy elemet a végére - majd vissza térünk saját magunkkal
    DirectionReversibleSequence& push_back( const T& t )
    {
        Cont::push_back( t );
        return *this;
    }

    // behelyezünk egy elemet a container elejébe 
    // (vectornak nincs push_front, ezért meg kell valósítani) 
    // majd vissza térünk saját magunkkal
    DirectionReversibleSequence& push_front( const T& t )
    {
        Cont::insert( this->begin() , t );
        return *this;
    }

    // kiszedjük az első elemet
    // (vectornak nincs pop_front, ezért meg kell valósítani) 
    void pop_front()
    {
        Cont::erase( this->begin() );
    }

    // cseréljük meg az irányt - fordítsuk meg a struktúrát
    void reverse_direction()
    {
        std::reverse( this->begin() , this->end() );
    }

    // kérjük le az i. elemet ( list-nek nincs ilyen, meg kell valósítani )
    T& operator[]( size_type i )
    {
        // lekérjük az első elem iterátorát, majd megnöveljük i-vel
        iterator it = this->begin();
        std::advance( it , i );
        // visszatérünk vele
        return *it;
    }

    // const módon is
    const T& operator[]( size_type i ) const
    {
        const_iterator it = this->begin();
        std::advance( it , i );
        return *it;
    }
};


#endif // HEADER_INCLUDED
