#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <set>

// 2 template paraméter, az elemek típusa
template <typename T, typename U>
class AssocSet : public std::set < std::pair < T , U > >
{
    // típuselnevezések a könnyebb hivatkozás érdekében
    typedef std::pair < T , U > Elem;
    typedef std::set < Elem > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator const_iterator;
    
public:
    
    // behelyezünk egy elemet, készítünk a két paraméterből egy párt, és betesszük a halmazba
    void insert( const T& t, const U& u )
    {
        Inher::insert( Elem( t, u ) );
    }

    // megszámoljuk, hogy hánynszor van a halmazba (mindig 1x lesz, mert HALMAZ)
    size_type count( const T& t, const U& u ) const
    {
        return Inher::count( Elem( t, u ) );
    }

    // kitöröljük a paraméterként megkapott elemet, majd visszaadjuk, hogy benne volt-e
    bool erase( const T& t, const U& u )
    {
        // lekérjük a méretét, és ha a törlés után változott, akkor benne volt
        size_type n = Inher::size();
        Inher::erase( Elem( t, u ) );
        return n != Inher::size();
    }

    // def constructor
    AssocSet(){}
    
    // nem teljesen egyértelmű az elvárás...
    // van egy intervallum meg egy elem, és ilyen párokat kell betenni a struktúrába
    // most T vagy U típusú, és hogy melyik melyik, ez nem egy jól definiált dolog
    template <typename ItType>
    AssocSet( ItType begin, ItType end , const T& t )
    {
        while( begin != end )
        {
            insert( t , *begin++ );
        }
    }

    // le lehet kérdezni a (T vagy U típusú) elemekből mennyi van
    // menjünk végig a halmazon, és számoljuk meg
    size_type size( const T& n ) const
    {
        size_type res = 0;
        for( const_iterator cit = Inher::begin() ; cit != Inher::end() ; ++cit )
        {
            if ( cit->first == n )
            {
                ++res;
            }
        }
        return res;
    }

    // a halmaz méretével visszatérünk
    size_type size() const
    {
        return Inher::size();
    }
};

// transform_if
// majdnem olyan mint a transform, csak van egy feltétel is.
// ha igaz a feltétel, csak akkor hajtsuk végre rajta a függvényt, és csak akkor 
// tegyük bele a kimenetbe
template <class InItType, class OuItType, class Func , class Pred >
OuItType transform_if (InItType first1, InItType last1, OuItType result, Func f , Pred p )
{
    while (first1 != last1) {
        if( p( *first1 ) )
            *result++ = f(*first1);

        ++first1;
    }
    return result;
}

#endif // HEADER_INCLUDED
