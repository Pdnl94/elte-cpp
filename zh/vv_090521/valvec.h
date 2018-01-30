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
    A feladat egy olyan vector megvalósítása, melynek az elemeit ideiglenesen  ki lehet venni a vectorból.
    Ekkor ők nem "látszódnak" a struktúrában

    push_back - beszúr a vector végére egy elemet
    inval - a paraméterként megkapott indexű elemet invaliddá teszi
    val - a paraméterként megkapott indexű elemet validdá teszi
    size - lekéri, hogy hány valid elem van a struktúrában
    pop_back - letörli az utolsó valid elemet
    front / back - visszaadja az első / utolsó valid elemet

    iterátorral végig lehet a valid elemeken menni

    intervallumos constructor megvalósítása

*/

#include <numeric>
#include <vector>

// 1 template paraméter, az elemek típusa, származzunk egy vectorból
template < typename T >
class Valvec : public std::vector < T >
{
    // nevezzük el a következő típusokat
    typedef std::vector < T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator inher_const_iterator;

    // csináljunk egy vectort, mely megmondja, hogy az i. elem benne van-e a struktúrában 
    typedef std::vector < bool > Valid;
    typedef typename Valid::const_iterator valid_const_iterator;

    // példányosítsuk
    Valid valid;
public:

    // beteszünk egy elemet - validdá tesszük
    void push_back( const T& t )
    {
        Inher::push_back( t );
        valid.push_back( true );
    }

    // módosíthatjuk az n. elem validságát
    void inval( size_type n )
    {
        valid[n] = false;
    }

    void val( size_type n )
    {
        valid[n] = true;
    }

    // megszámoljuk, hogy a valid vectorunkban hány igaz érték van - ennyi az összméretünk
    size_type size() const
    {
        return std::accumulate( valid.begin() , valid.end() , 0 );
    }

    // az utolsó valid elemet kitöröljük.
    void pop_back()
    {
        // kérjük le a saját megvalósított iterátorunktól, hogy melyik az utolsó valid elem, 
        // majd nézzük meg a távolságát a vector elejétől. Ennyiedik elem lesz az utolsó valid
        size_type s = ( --end() ).base() - Inher::begin();

        // már csak ki kell törölni mindkét struktúrából
        Inher::erase( Inher::begin() + s );
        valid.erase( valid.begin() + s );
    }

    // a megvalósított saját iterátor struktúránkat használva lekérhetjük az első, és az utolsó valid elemet
    const T& front() const { return *begin(); }
    const T& back() const { return *--end(); }

    // a saját const_iterátor struktúránk. Egyszerűség kedvéért származzunk a vector::iterátorából
    class const_iterator : public inher_const_iterator
    {
        // tároljuk el a vector struktúrát, illetve a valid vector pozícióját is
        const Valvec* p;
        valid_const_iterator vcit;

    public:
        // lekérhetjük a base() iterátort, ami a vector iterátora
        inher_const_iterator& base()
        {
            return *this;
        }

        // constructor, megkapjuk az adatokat, és inicializáljuk vele az iterátorunkat
        const_iterator( const Valvec* p , inher_const_iterator it , valid_const_iterator vcit ) :
            inher_const_iterator( it ) , p( p ) , vcit( vcit )
        {
            // ha már az első elem nem valid, akkor léptetnünk kell az iterátort az elsőre
            // mindkét pointerünkkel ezt megtesszük
            while( vcit != p->valid.end() && !*vcit )
            {
                ++vcit;
                ++base();
            }
        }

        // ++ operátor - növeljük meg az iterátorunkat
        const_iterator& operator++()
        {
            // növeljük meg mindkét iterátort, és addig tegyük ezt meg, míg ( vagy el nem jutottunk a végéig, vagy )
            //  megtaláljuk a következő valid elemet
            do
            {
                ++vcit;
                ++base();
            }
            while( vcit != p->valid.end() && !*vcit );
            // magunkkal térünk vissza
            return *this;
        }

        // -- operátor - csökkentsük meg az iterátorunkat
        const_iterator& operator--()
        {
            // csökkentsük mindkét iterátort, és addig tegyük ezt meg, míg ( vagy el nem jutottunk az elejéig, vagy )
            //  megtaláljuk az előző valid elemet
            do
            {
                --vcit;
                --base();
            }
            while( vcit != p->valid.begin() && !*vcit );
            // magunkkal térünk vissza
            return *this;
        }
    };

    // visszatérünk a saját iterátor struktúránk kezdetével, végével
    const_iterator begin() const
    {
        return const_iterator( this , Inher::begin() , valid.begin() );
    }

    const_iterator end() const
    {
        return const_iterator( this , Inher::end() , valid.end() );
    }

    // default constructor
    Valvec(){}

    // iterátoros / intervallumos constructor. Adjuk át az ősosztálynak, majd a valid vector-unkat inicializáljuk
    //  pont annyi elemre amennyit megkaptunk, és mind legyen igaz
    template < typename It >
    Valvec( It begin , It end ) : Inher( begin , end ) , valid( Inher::size() , true ){}

};


#endif // HEADER_INCLUDED
