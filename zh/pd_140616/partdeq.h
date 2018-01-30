#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
	--
	Schaum Béla
	SCBTAAI
	EQBVGX
	--
*/


#include <deque>

/* négyeshez */

// olyan funktor, ami minden elemre igazzal tér vissza a () operátort meghí­vva
template <typename T>
struct alwaysTrue
{
    inline bool operator()( const T& )
    {
        return true;
    }
};

// két template paraméter
// az első az elemeink tí­pusa
// a második a szűrő, ami kettészedi a struktúrát
// (alapértelmezetten mindent elfogad -> négyesért )
template <typename T , typename Filt = alwaysTrue<T> >
class partitioned_deque
{
    // kettészedjük a jó és a rossz elemeket
    std::deque<T> ok;
    std::deque<T> notOk;

    typedef typename std::deque<T>::size_type size_type;

    // ez lesz a példányosí­tott szűrő funktorunk
    Filt f;
public:

    // beleteszünk egy elemet az elejére
    // ha a funtor elfogadta, akkor a jó elejére
    // ha a funktor nem fogadta el, akkor a rossz elejére
    void push_front( const T& t )
    {
        if( f( t ) )
        {
            ok.push_front( t );
        }
        else
        {
            notOk.push_front( t );
        }
    }
    // behelyezünk a filtertől függően egy dequebe egy elemet
    // attól függően, hogy elfogadja
    void push_back( const T& t )
    {
        if( f( t ) )
        {
            ok.push_back( t );
        }
        else
        {
            notOk.push_back( t );
        }
    }

    // a méret a kettőnek az összege
    int size() const
    {
        return ok.size() + notOk.size();
    }

    // ha az első vector méreténél kisebb, abba van, különben a másikban
    // lekérjük az elemet constansként, hisz nem változtathatunk a struktúrán
    T operator[]( int i ) const
    {
        if( i < ok.size() )
            return ok[i];
        else
            return notOk[ i - ok.size() ];
    }

    // hármasért

    // ha az elsőbe nincs elem, akkor a második front-jával, különben az első frontjával térünk vissza
    // felüldefiniált const-ra
    T front() const
    {
        return ok.empty() ? notOk.front() : ok.front();
    }

    // ha a másodikba nincs elem, akkor az első back-jével, különben a második backjével térünk vissza
    // felüldefiniált const-ra
    T back() const
    {
        return notOk.empty() ? ok.back() : notOk.back();
    }

    // négyes

    // friend class - á tesszük az összes más template paraméterrel megadott partition_vector-t
    // mert csak í­gy érhetjük el egymás tagjait, és í­gy működik a swap
    template <typename U, typename F2>
    friend class partitioned_deque;

    // akkor egyenlő 2 queue, ha a méretük egyenlő, és
    // végigmenve az elemeiken az összes i. indexű elem megegyezik
    template <typename U, typename F2>
    bool operator==(const partitioned_deque<U,F2>& pd) const
    {
        if ( size() == pd.size() )
        {
            size_type i = 0;
            while(  i < size() &&  (*this)[i] == pd[i] )
            {
                ++i;
            }
            if( i == size() )
                return true;
        }

        return false;
    }

    // akkor nem egyenlőek, ha nem igaz rájuk, hogy egyenlőek
    template <typename U, typename F2>
    bool operator!=(const partitioned_deque<U,F2>& pd) const
    {
        return ! ( *this == pd );
    }

    // otosert:

    // egy olyan konvertáló függvényt írunk, ami
    // képes egy p_q-t egy másik filterrel rendelkező p_q -ra
    //   végigmegyünk az elemeken, és behelyezgetjük őket
    template <typename Filt2>
    operator partitioned_deque<T,Filt2>() const
    {
        partitioned_deque<T,Filt2> f;
        for( size_type i = 0; i < size() ; ++i )
        {
            f.push_back( (*this)[i] );
        }
        return f;
    }
};

#endif // HEADER_INCLUDED
