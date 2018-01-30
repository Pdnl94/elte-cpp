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
Leírás :

Segítség: a cél olyan asszociatív hozzárendelésű adatszerkezett meírása, amelyben minden eltárolt elemhez tartozik egy előre megadott szám, ami számláló munkáját végzi. Minden elemhozzáféréskor az elem számlálója visszaáll a "maximumra", minden más elem számlálója csökken 1-gyel. Ha egy elemnek a számlálója elérte a 0-t az elem eltűnik az adatszerkezetből, azaz megszünik létezni!

Másik féle leírás :

// Feladat(kb):
//Hozzon letre egy mapet, ahol minden elemnek van egy eletbenmaradasi ideje,
//ami kezdetben egy megadott ertekre van beallitva
//Ha barmilyen elemhez hozzanyul, akkor a hivatkozott elem elete felmegy
//a kezdeti (max) ertekre, meg a tobbi elem elete csokken


*/

#include <map>
#include <functional>

// 3 template, kulcs, érték, rendező funktor (defaultból a kisebb operátor),
// származunk az std::map-ból, aminek átadjuk ezt a 3 paramétert
template < class Key , class Val , class Comp = std::less < Key > >
class ControlledMap : public std::map < Key , Val , Comp >
{
    // az ősosztály típusa
    typedef std::map < Key , Val , Comp > Inher;
    typedef typename Inher::size_type size_type;

    // ilyen típusban tároljuk az elemek élettartamát
    typedef std::map < Key , size_type > Amor;
    typedef typename Amor::iterator am_iterator;
    
    // hozzuk is létre, illetve még egy változót, hogy ennyi ideig maradjanak életben
    Amor amor;
    size_type cont;

    // ez fogja frissíteni az élettartamát az elemeknek
    void refresh( const Key& k )
    {
        // beállítjuk a jelenlegi elem számát a maximumra (+ 1)
        amor[k] = cont;
        // az összesből kivonunk egyet, és ha ez 0, akkor kitöröljük a struktúrából
        for( am_iterator it = amor.begin() ; it != amor.end() ; ++it )
            if( ! --it->second )
                Inher::erase( it->first ),
                amor.erase( it-- );
    }

public:

    // default constructor - elmentjük az élettartamot 
    // (hozzáadunk 1-et a könnyed kezelés kedvéért)
    ControlledMap( size_type c ) : cont(++c){}

    // egy intervallumnyi elemet kapunk template paraméterként, adjuk az ősosztálynak
    template <typename It>
    ControlledMap( size_type c , It begin , It end ):Inher( begin , end ),cont(++c){}

    // behelyezünk egy elemet, majd frissítjük (kidobjuk a régieket)
    void insert( const Key& k , const Val& v )
    {
        Inher::insert( std::make_pair( k , v ) );
        refresh( k );
    }

    // lekérdezzük, hogy benne van-e a bizonyos kulcs
    // miután csökkentettük az értékeket
    bool contains_key( const Key& k )
    {
        refresh( k );
        return Inher::count( k );
    }

    // frissítjük az elemeket, majd kitöröljük a kulcs-értéket
    void erase( const Key& k )
    {
        refresh( k );
        Inher::erase( k );
    }

    // lekérjük az elemet, de előtte frissítjük a struktúrát
    Val& operator[]( const Key& k )
    {
        refresh( k );
        return Inher::operator[]( k );
    }
};

#endif // HEADER_INCLUDED
