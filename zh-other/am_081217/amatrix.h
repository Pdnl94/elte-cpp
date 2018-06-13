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
    A feladat egy olyan mátrix létrehozása, mely egy template paraméterként kapott típus objektumaival indexelhető
    Lekérhető, beállítható elem
    Sorok, oszlopok száma is lekérdezhető
    Végig lehet rajtuk iterálni

*/

#include <map>

// két template paramétere van,
// az első az az a típus, amivel tudjuk indexelni a mátrixunkat
// a második az az, hogy milyen típusú elemeket tárolunk el a mátrixba
template <typename Index , typename Val>
class AssocMatrix
{
    // nevezzük el a típusokat a könnyebb használhatóság érdekében
    typedef std::map < Index , Val > Row; // a csatlakozó mezők, és a hozzárendeelt értékei, ez egy sor
    typedef std::map < Index , Row > Matrix; // mátrix típus, mindex mezőhöz tartozik egy sor
    typedef typename Row::size_type size_type; // (unsinged long) típus
    typedef typename Row::const_iterator r_const_iterator;
    typedef typename Matrix::const_iterator const_iterator;

    // a mátrix példányosítva
    Matrix data;
public:
    // lekérjük a r(ow)-adik sor c(olumn)-adik elemét, majd beállítjuk 
    void set( const Index& r , const Index& c , const Val& v )
    {
        data[r][c] = v;
    }

    // constans módon lekérdezhető a mátrix egy eleme 
    Val get( const Index& r , const Index& c ) const
    {
        // meg kell keresni, hogy létezik-e már ilyen oszlop (a [] nem használható, hisz az ha nem létezne az elem, létrehozná)
        const_iterator it = data.find( r );
        // ha létezik (akkor nem a végére mutat) , akkor keressük meg, hogy létezik-e ilyen oszlop
        if( it != data.end() )
        {
            r_const_iterator it2 = it->second.find( c );
            if( it2 != it->second.end() )
            {
                // térjünk vissza az értékkel
                return it2->second;
            }
        }
        // ha nem volt sor-oszlop, akkor egy "üres" elemmel térünk vissza
        return Val();
    }

    // same as get()
    Val operator()( const Index& r , const Index& c ) const
    {
        return get( r , c );
    }

    // ha nem const módon kérjük le, akkor létre is hozhatjuk rögtön, egy elem referenciával térünk vissza
    Val& operator()( const Index& r , const Index& c )
    {
        return data[r][c];
    }

    // adjuk vissza a sorok számát
    size_type rows() const
    {
        return data.size();
    }

    // adjuk vissza a sorok közül a leghosszabb oszloppal rendelkező oszlopok számát (maxkeresés)
    size_type cols() const
    {
        size_type res = 0;

        for( const_iterator it = data.begin(); it != data.end() ; ++it )
            if( res < it->second.size() )
                res = it->second.size();

        return res;
    }

    // mivel pont úgy csináltuk a struktúrát, ahogy elvárta (és ahogy végig tudjon rajta iterálni)
    // ezért elég csak a mátrixot iterátorokkal átadni
    const_iterator begin() const
    {
        return data.begin();
    }

    const_iterator end() const
    {
        return data.end();
    }
};

#endif // HEADER_INCLUDED
