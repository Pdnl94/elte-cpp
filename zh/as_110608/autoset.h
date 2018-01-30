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
    A feladat egy olyan set struktúra megvalósítása, mely pointereket tárol, 
    és ha kiveszünk egy elemet a halmazból, felszabadítja a pointert.
    A destruktorában az összes pointert felszabadítja (hisz kiürül a struktúra)

    Ha lekérünk egy elemét, akkor nem a pointert, hanem az értéket adja vissza
    Törölhetünk iterátoron keresztül értékeket

    Az összehasonlítás is az értékek szerint rendezi, és az szerint tárolja az értékeket
    Megadható neki rendező funktor
*/


#include <set>
#include <functional>

// ez egy olyan "rendező" funktor, ami 2 template paraméterében
// megkapja a típust, és az összehasonlítás alapját
// a () operátor meg két pointer között úgy dönti el, hogy melyik a "kisebb",
// hogy veszi a címüket, és a rendező funktornak odaadja
template <typename T , typename Comp>
struct p_to_val
{
    // azért const a függvény, mert a map tárol magában egy ilyen struktúrát
    // és egy const map-en nem szabad megváltoznia az értékének (így csak const függvény hívható
    bool operator()( const T* l , const T* r ) const
    {
        return Comp()( *l , *r );
    }
};

// 2 template paraméter, a halmaz elemének típusa, és a rendező (alapértelmezetten a < operátor) funktor
// származunk egy olyan set-ből, mely pointereket tartalmaz, és a mi pointer-összehasonlító struktúránkat
template <typename T , typename Comp = std::less < T > >
class auto_set : std::set < T* , p_to_val < T , Comp > >
{
    // nevezzük el az ősosztályt, és az iterátorait
    typedef std::set < T* , p_to_val < T , Comp > > Inher;
    typedef typename Inher::const_iterator const_iterator;
public:
    typedef typename Inher::iterator iterator;

    // könnyebb használhatóság miatt (és mivel most lustaságból nem public az ős)
    // tegyük láthatóvá a következő függvényeket
    using Inher::size;
    using Inher::begin;
    using Inher::end;
    using Inher::count;
    using Inher::find;

    // behelyez egy kulcs érték párt
    void insert( T* e )
    {
        // ha már létezik a halmazba, akkor töröljük a pointert
        if( count( e ) )
        {
            delete e;
        }
        else // ha nem, akkor tegyük bele
        {
            Inher::insert( e );
        }
    }

    // töröljünk egy intervallumnyi elemet
    void erase( iterator begin , iterator end )
    {
        // amíg vége nincs, az aktuális iterátort felszabadítjuk
        while( begin != end )
        {
            delete *begin;
            // majd kitöröljük a struktúrából, és növeljük az iterátort
            Inher::erase( begin++ );
        }
    }

    // a destruktor törli az egész intervallumot
    ~auto_set()
    {
        erase( begin() , end() );
    }

    // default, és copy konstruktor
    auto_set(){}

    auto_set( const auto_set& as )
    {
        // végigmegyünk a másik set-en, és behelyezzük egyesével az elemeket, amiket újrafoglalunk
        for( const_iterator it = as.begin() ; it != as.end() ; ++it )
            insert( new T(**it) );
    }

    // kitörlünk egy elemet.
    void erase( T e )
    {
        // megkeressük, hogy pontosan hol is van az az elem
        // ( pointere segítségével, hisz pointereket tárolunk, és arra van értelmezve )
        iterator begin = find( &e );
        // ha nem találtuk meg, ne csináljunk semmit
        if( begin == end() ) return;

        // különben meg hozzunk létre egy másik iterátort, amit megnövelünk egyel,
        // és hívjuk meg az intervallumos törlést
        iterator end = begin;
        erase( begin , ++end );
    }
};

#endif // HEADER_INCLUDED
