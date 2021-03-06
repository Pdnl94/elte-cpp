#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <string>
#include <numeric>
#include <deque>

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
class filterable_vector
{
    // egy vectornyi T-ben valósítjuk meg, nevezzük el, könnyebb hivtkozás érdekében
    typedef std::vector< T > Inher;

    // a size_type-ot meg a iterátorát örökítsük ki
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator ih_const_iterator;
    typedef typename Inher::reference reference;
    typedef typename Inher::value_type value_type;

    // ebbe fogjuk eltárolni az elemeket
    Inher cont;

    // ezzel a booleannal fogjuk figyelni, hogy be vagy ki van-e kapcsolva a filter
    bool fIsOn;

    // ez lesz a filterünk, a () operátora mondja meg egy elemről, hogy szűrjük-e ki
    Fil filter;
public:
    // default constuctor - alapból a szűrő legyen kikapcsolva
    filterable_vector():fIsOn(false){}

    // copy constuctor - alapból a szűrő legyen kikapcsolva
    filterable_vector( const filterable_vector& fv ):cont(fv.cont),fIsOn(false){}


    // át tudunk változni vektor struktúrára
    // ekkor csak azokat az elemeinket másoljuk, akik átmennek a szűrőn
    operator Inher()
    {
        bool fWasOn = fIsOn;
        fIsOn = true;
        Inher tmp;
        for( const_iterator it = begin() ; it != end() ; ++it )
        {
            tmp.push_back(*it);
        }
        fIsOn = fWasOn;
        return tmp;
    }

    void push_back( const value_type& v )
    {
        cont.push_back(v);
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

    // visszaadjuk az indexedik helyen lévő elemet
    T at( size_type ind ) const
    {
        // ha nincs szűrő, akkor ugyan úgy működünk mint a szülő osztályban
        if( !fIsOn ) return cont.at(ind);

        // különben iterálunk addig, amig el nem érjük, majd visszatérünk vele
        const_iterator it = begin();
        while( ind-- )
        {
            ++it;
        }
        return *it;
    }

    // visszaadjuk az indexedik helyen lévő elemet (referencia szerint)
    reference at( size_type ind )
    {
        // ha nincs szűrő, akkor ugyan úgy működünk mint a szülő osztályban
        if( !fIsOn ) return cont.at(ind);

        // különben iterálunk addig, amig el nem érjük, majd visszatérünk az annyiadik elemmel
        const_iterator it = begin();
        while( ind-- )
        {
            ++it;
        }
        // *it-tel nem térhetünk vissza, mert const
        return cont.at( it - cont.begin() );
    }

    T operator[]( size_type ind ) const
    {
        return at(ind);
    }
    reference operator[](size_type ind )
    {
        return at(ind);
    }

    // visszaadjuk egy elem indexét
    size_type index_of( const T& e ) const
    {
        // ha nincs szűrő, akkor find-al megkeressük, és kiszámoljuk az indexét
        if( !fIsOn ) return std::find( cont.begin() , cont.end() , e ) - cont.begin();

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
        if( !fIsOn ) return cont.size();

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
        return std::max_element( begin() , end() ) - cont.begin();
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
        const filterable_vector* fd;
    public:
        // constructorba megkapjuk, hogy ki hhozott minket létre, és milyen kezdőértékkel
        // iniciáljuk magunkat
        const_iterator( const filterable_vector* fd, ih_const_iterator ici ) :ih_const_iterator(ici),fd(fd)
        {
            // ha be van kapcsolva a filter, és az első elemet ki kellett szűrni
            // akkor léptessük a legelső jó elemre (figyeljük,hogy ne fogyjon el az elemszám)
            if( fd->fIsOn )
                while( fd->cont.end() != *this && !fd->filter( **this ) )
                    ih_const_iterator::operator++();
        }
        
        // írjuk felül a ++ prefix operátort
        const_iterator& operator++()
        {
            // növeljük meg az iterátort
            ih_const_iterator::operator++();

            // ha be van kapcsolva a filter, és az az elem, amin vagyunk ki kellett szűrni
            // akkor léptessük a következő jó elemre (figyeljük,hogy ne fogyjon el az elemszám)
            if( fd->fIsOn )
                while( fd->cont.end() != *this && !fd->filter( **this ) )
                    ih_const_iterator::operator++();
            return *this;
        }
    };

    // amikor lekéri valak az iterátorokat, akkor csak adjuk át nekik
    const_iterator begin() const
    {
        return const_iterator( this , cont.begin() );
    }

    const_iterator end() const
    {
        return const_iterator( this , cont.end() );
    }

};

#endif // HEADER_INCLUDED
