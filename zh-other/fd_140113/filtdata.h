#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <string>
#include <numeric>

/*
	--
	Schaum Béla
	SCBTAAI
	EQBVGX
	--
*/


// két template paraméter.
// az első az eltrolt elemek típusa
// a második a szűrő, ami alapjáná szűrjük az elemeket
template<typename T , typename Fil>
class filterable_data : public std::vector< T >
{
    // egy vectornyi T-ből származunk, nevezzük el, könnyebb hivtkozás érdekében
    typedef std::vector< T > Inher;

    // a size_type-ot meg a iterátorát örökítsük ki
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator ih_const_iterator;

    // ezzel a booleannal fogjuk figyelni, hogy be vagy ki van-e kapcsolva a filter
    bool fIsOn;

    // ez lesz a filterünk, a () operátora mondja meg egy elemről, hogy szűrjük-e ki
    Fil filter;
public:
    // default constuctor - alapból a szűrő legyen kikapcsolva
    filterable_data():fIsOn(false){}

    // át tudunk változni egy hozzánk hasonló (más filteres) struktúrára
    // ekkor csak azokat az elemeinkte másoljuk, akik átmennek a szűrőn
    template <typename Fil2>
    operator filterable_data<T, Fil2>() const
    {
        filterable_data<T, Fil2> tmp;
        for( const_iterator it = begin() ; it != end() ; ++it )
        {
            tmp.push_back( *it );
        }
        return tmp;
    }

    // a filter be és kikapcsolása
    void set_filter_on()
    {
        fIsOn = true;
    }
    void set_filter_off()
    {
        fIsOn = false;
    }

    // visszaadjuk egy elem indexét
    size_type index_of( const T& e ) const
    {
        // ha nincs szűrő, akkor find-al megkeressük, és kiszámoljuk az indexét
        if( !fIsOn ) return std::find( Inher::begin() , Inher::end() , e ) - Inher::begin();

        // különben végigiterálunk a filteres iterátorral a struktúrán
        // ha megtaláljuk, visszatérünk az indexel
        size_type ind = 0;
        for( const_iterator it = begin() ; it != end() ; ++it )
        {
            if( *it == e ) return ind;
            ++ind;
        }
        return ind;
    }

    // visszaadjuk a méretet, hány elem van benne
    size_type size() const
    {
        // ha nincs szűrő, akkor az összes elem mérete a kérdés
        if( !fIsOn ) return Inher::size();

        // ha van, a filteres iterátorral végigmegyünk, és megszámoljuk őket
        size_type ind = 0;
        for( const_iterator it = begin() ; it != end() ; ++it )
        {
            ++ind;
        }
        return ind;
    }

    // visszatérünk a maximális elemmel (filteres iterátorral)
    const T& max() const
    {
        return *std::max_element( begin() , end() );
    }

    // visszatérünk a maximális elem indexével (filteres iterátorral)
    size_type index_of_max() const
    {
        return std::max_element( begin() , end() ) - Inher::begin();
    }

    // kiszámoljuk az átlagát (filteres iterátorral)
    T average() const
    {
        return std::accumulate( begin() , end() , 0 ) / size();
    }

    // a saját (filteres) iterátor megvalósítása
    // származunk az eredeti vector::const_iterátorból
    // eltároljuk azt a struktúrát, aki létrehozott minket
    class const_iterator : public ih_const_iterator
    {
        const filterable_data* fd;
    public:
        // constructorba megkapjuk, hogy ki hhozott minket létre, és milyen kezdőértékkel
        // iniciáljuk magunkat
        const_iterator( const filterable_data* fd, ih_const_iterator ici ) :ih_const_iterator(ici),fd(fd)
        {
            // ha be van kapcsolva a filter, és az első elemet ki kellett szűrni
            // akkor léptessük a legelső jó elemre (figyeljük,hogy ne fogyjon el az elemszám)
            if( fd->fIsOn )
                while( fd->Inher::end() != *this && fd->filter( **this ) )
                    ih_const_iterator::operator++();
        }
        const_iterator& operator++()
        {
            // növeljük meg az iterátort
            ih_const_iterator::operator++();

            // ha be van kapcsolva a filter, és az az elem, amin vagyunk ki kellett szűrni
            // akkor léptessük a következő jó elemre (figyeljük,hogy ne fogyjon el az elemszám)
            if( fd->fIsOn )
                while( fd->Inher::end() != *this && fd->filter( **this ) )
                    ih_const_iterator::operator++();
            return *this;
        }
    };

    // amikor lekéri valak az iterátorokat, akkor csak adjuk át nekik
    const_iterator begin() const
    {
        return const_iterator( this , Inher::begin() );
    }

    const_iterator end() const
    {
        return const_iterator( this , Inher::end() );
    }

};

#endif // HEADER_INCLUDED
