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
    A feladat egy olyan map megvalósítása, melynek nem csak a kulcsok, 
    hanem a hozzájuk rendelt értékek is egyediek

    Ha beteszünk egy elemet, akkor kitöröljük az előző elemet, mely ezzel az értékkel volt benn,
    majd betesszük az újat

    Vissza lehet adni, hogy létezik-e a paraméterként megadott kulcs érték a map-ben,

    operator[]-al le lehet kérdezni egy kulcshoz tartozó értéket úgy, hogy a map const maradjon

    size, begin, end ugyan az mint a map-nél 
*/


#include <functional>
#include <map>

// 3 template paraméter (ugyan az mint az std::map-nél), származunk a map-ből
template < typename Key , typename Val , typename Comp = std::less < Key > >
class UniqueValuedMap : public std::map < Key , Val , Comp >
{
    // nevezzünk el pár típust
    typedef std::map < Key , Val , Comp > Inher;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;
public:

    // behelyezünk egy elemet (kulcs-érték párat)
    void insert( const Key& k , const Val& v )
    {
        // végigszaladunk a map-en, és ha találunk egyezést az értékek között, akkor kitöröljük
        // mivel csak egyszer lehet ilyen, abbahagyjuk a for ciklust
        for( iterator it = Inher::begin() ; it != Inher::end() ; ++it )
            if( it->second == v )
            {
                Inher::erase( it );
                break;
            }

        // behelyezzük a map struktúrába az elemet, pár-ként
        Inher::insert( std::make_pair( k , v ) );
    }

    // visszaadjuk, hogy tartalmazza-e az adott kulcson az elemet, használjuk a map::count függvényét
    bool contains( const Key& k ) const
    {
        return Inher::count( k );
    }

    // lekérjük a k kulcs helyen lévő elem értékét const-ul 
    Val operator[]( const Key& k ) const
    {
        // keressük meg, ha létezik, akkor térjünk vissza a second (értékkel), ha nem, akkor egy invalid elemmel
        const_iterator it = Inher::find( k );
        return it == Inher::end() ? Val() : it->second;
    }
};

#endif // HEADER_INCLUDED
