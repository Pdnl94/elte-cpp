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
    A feladat egy olyan map megvalósítása, mely konstruktorban kap egy értéket, hogy hány elemet tartalmazhat,
    és ha túllépi ezt a számot, akkor ki kell törölnie a legkorábban betett értéket

*/

#include <map>
#include <deque>
#include <algorithm>
#include <functional>

// 3 template, kulcs, érték, rendező funktor (defaultból a kisebb operátor), 
// származunk az std::map-ból, aminek átadjuk ezt a 3 paramétert
template < class Key , class Val , class Comp = std::less < Key > >
class CachedMap : public std::map < Key , Val , Comp >
{
    // nevezzük el a típusokat
    typedef std::map < Key , Val , Comp > Inher;
    typedef typename Inher::size_type size_type;

    // ebben a deque-ben fogjuk tárolni, hogy melyik elem mikor / milyen sorrendben érkezett
    std::deque < Key > dq;
    // ez a maximális elemszám ami lehet a map-ben
    const size_type n;
public:
    // default constructor, megkapjuk a max elemszámot
    CachedMap( size_type n ):n(n){}

    // a mapba behelyezünk egy kulcs-érték párt
    void insert( const Key& k , const Val& v )
    {
        Inher::insert( std::make_pair( k , v ) );

        // behelyezzük a deque-be is
        dq.push_back( k );

        // ha túlléptük a számot, akkor töröljük az első elemet a struktúrákból
        if( dq.size() > n )
        {
            Inher::erase( dq.front() );
            dq.pop_front();
        }
    }

    // lekérjük a 'k' elemhez tartozó értéket
    Val get( const Key& k ) const
    {
        // megkeressük, és ha volt ilyen, akkor visszatérünk azzal, különben egy invalid elemmel
        typename Inher::const_iterator it = Inher::find( k );
        return it == Inher::end() ? Val() : it->second;
    }

    // törlés
    void erase( const Key& k )
    {
        Inher::erase( k );
        // törlésnél figyelünk arra, hogy a deque-ből is legyen kitörölve
        // azért így, mert ha nem volt a 'k' benne a struktúrában, akkor is működik
        dq.erase( std::remove( dq.begin() , dq.end() , k ) , dq.end() );
    }
};

#endif // HEADER_INCLUDED
