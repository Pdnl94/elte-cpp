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
    A feladat egy olyan map megvalósítása, mely az alap funkcióin (amit a map is tud) kívül még van két különleges függvénye

    inval - egy kulcsot vár paraméterként, és az ezzel a kulcsal szereplő értékeket kiveszi a struktúrából, de eltárolja
    val - egy kulcsot vár paraméterként, és a kivett elemek közül ha létezik ez az elem, visszateszi a struktúrába

    insert - annyi + van, hogy egymás után meghívható ( insert().insert().insert()... ), ami úgy érhető el, hogy
        a visszatérési értéke saját maga lesz 

    operator[] - mivel a map-ben nem const ez az operátor, meg kell írnunk úgy, hogy const legyen
*/

#include <functional>
#include <map>

// 3 template paraméter, ugyan az mint a map-nek. Származzunk a map-ből
template < typename Key , typename Val , typename Comp = std::less < Key > >
class Valmap : public std::map < Key , Val , Comp >
{
    // nevezznük el típusokat
    typedef std::map < Key , Val , Comp > Inher;
    typedef typename Inher::iterator iterator;

    // hozzunk létre egy tárolót, melyben tároljuk a kivett elemeket
    Inher invalid;
public:
    // tegyük publikussá a const_iterator - t, hisz a main használja
    typedef typename Inher::const_iterator const_iterator;

    // behelyezés - a kulcs-érték ből csináljunk egy pár-t, majd helyezzük be a struktúrába
    // térjünk vissza magunkkal
    Valmap& insert( const Key& k , const Val& v )
    {
        Inher::insert( std::make_pair( k , v ) );
        return *this;
    }

    // keressük meg a kulcs értéket a struktúránkban, és ha létezik,
    // tegyük be kivett elemek közé, majd töröljük ki az eredetiből
    void inval( const Key& k )
    {
        iterator it = Inher::find( k );
        if( it != Inher::end() )
        {
            invalid.insert( *it );
            Inher::erase( it );
        }
    }

    // keressük meg a kulcs értéket a kivett elemek között, és ha létezik,
    // tegyük be a struktúránkba, majd töröljük ki a kivettekből
    void val( const Key& k )
    {
        iterator it = invalid.find( k );
        if( it != invalid.end() )
        {
            Inher::insert( *it );
            invalid.erase( it );
        }
    }
    
    // kérjük le a kucs-helyen lévő értéket, ha megtaláltuk, akkor térjünk vissza az értékkel
    // különben egy "invalid" elemmel
    Val operator[]( const Key& k ) const
    {
        const_iterator it = Inher::find( k );
        return it == Inher::end() ? Val() : it->second ;
    }
};


#endif // HEADER_INCLUDED
