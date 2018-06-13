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
    A feladat egy olyan map struktúra megvalósítása, mely pointereket tárol, 
    és ha kiveszünk egy elemet a listából, felszabadítja mindkét pointert.
    A destruktorában az összes pointert felszabadítja (hisz kiürül a struktúra)

    Ha lekérünk egy elemét, akkor nem a pointert, hanem az értéket adja vissza
    Törölhetünk iterátoron keresztül értékeket

    Az összehasonlítás is az értékek szerint rendezi, és az szerint tárolja az értékeket
    Megadható neki rendező funktor
*/

#include <map>
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

// 3 template paraméter, a kulcs, a hozzá rendelt érték, és a rendező (alapértelmezetten a < operátor) típusok 
// származunk egy olyan map-ből, mely pointereket tartalmaz, és a mi pointer-összehasonlító struktúránkat
template <typename Key , typename Val , typename Comp = std::less < Key > >
class auto_map : std::map < Key* , Val* , p_to_val < Key , Comp > >
{
    // nevezzük el az ősosztályt, és az iterátorait
    typedef std::map < Key* , Val* , p_to_val < Key , Comp > > Inher;
    typedef typename Inher::const_iterator const_iterator;
public:
    typedef typename Inher::iterator iterator;

    // könnyebb használhatóság miatt (és mivel most lustaságból nem public az ős)
    // tegyük láthatóvá a következő függvényeket
    using Inher::size;
    using Inher::begin;
    using Inher::end;
    using Inher::count;

    // behelyez egy kulcs érték párt
    void insert( Key* k , Val* v )
    {
        // ha már létezik a kulcs (érték szerint), akkor töröljük a pointereket
        if( count( k ) )
        {
            delete k;
            delete v;
        }
        else // ha nem, akkor tegyük bele
        {
            (*this)[k] = v;
        }
    }

    // töröljünk egy intervallumnyi elemet
    void erase( iterator begin , iterator end )
    {
        // amíg vége nincs, az aktuális iterátor first - second -jét felszabadítjuk
        while( begin != end )
        {
            delete begin->first;
            delete begin->second;
            // majd kitöröljük a struktúrából, és növeljük az iterátort
            Inher::erase( begin++ );
        }
    }
    
    // a destruktor törli az egész intervallumot
    ~auto_map()
    {
        erase( begin() , end() );
    }

    // default, és copy konstruktor
    auto_map(){}

    auto_map( const auto_map& am )
    {
        // végigmegyünk a másik map-en, és behelyezzük egyesével az elemeket, amiket újrafoglalunk
        for( const_iterator it = am.begin() ; it != am.end() ; ++it )
            insert( new Key(*it->first) , new Val(*it->second) );
    }

    // lekérdezhető, hogy egy kulcson milyen érték szerepel (referencia szerint - megváltoztatható)
    Val& at( const Key& k )
    {
        // végigmegyünk a map-en, és ha a kulcs egyezik, visszatérünk az értékkel
        for( iterator it = begin() ; it != end() ; ++it )
            if( k == *it->first )
                return *it->second;
        // ha nem volt, dobjunk hibát
        throw "";
    }
    // const módon is lekérhető, de ha nem talált elemet kér, akkor térjünk vissza egy "nem létező" elemmel
    Val at( const Key& k ) const
    {
        for( const_iterator it = begin() ; it != end() ; ++it )
            if( k == *it->first )
                return *it->second;
        return Val();
    }
};

#endif // HEADER_INCLUDED
