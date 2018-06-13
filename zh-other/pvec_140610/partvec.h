#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
	--
	Schaum Béla
	SCBTAAI
	EQBVGX
	--
*/


#include <vector>

/* négyeshez */

// olyan funktor, ami minden elemre igazzal tér vissza a () operátort meghívva
template <typename T>
struct alwaysTrue
{
    inline bool operator()( const T& )
    {
        return true;
    }
};

// két template paraméter
// az első az elemeink típusa
// a második a szűrő, ami kettészedi a struktúrát
// (alapértelmezetten mindent elfogad -> négyesért )
template <typename T , typename Filt = alwaysTrue<T> >
class partitioned_vector
{
    // kettészedjük a jó és a rossz elemeket
    std::vector<T> ok;
    std::vector<T> notOk;

    // a vector<bool> miatt reference
    typedef typename std::vector<T>::reference reference;
    typedef typename std::vector<T>::size_type size_type;
    
    // ez lesz a példányosított szűrő funktorunk
    Filt f;
public:

    // behelyezünk a filtertől függően egy vektorba egy elemet
    void insert( const T& t )
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
    
    // kicserélünk két azonos filterrel rendelkező vectort
    void swap( partitioned_vector& pv )
    {
        ok.swap( pv.ok );
        notOk.swap( pv.notOk );
    }

    // ha az elsőbe nincs elem, akkor a második front-jával, különben az első frontjával térünk vissza
    // referenciás
    reference front()
    {
        return ok.empty() ? notOk.front() : ok.front();
    }

    // ha az elsőbe nincs elem, akkor a második front-jával, különben az első frontjával térünk vissza
    // felüldefiniált const-ra
    T front() const
    {
        return ok.empty() ? notOk.front() : ok.front();
    }

    // ha a másodikba nincs elem, akkor az első back-jével, különben a második backjével térünk vissza
    // referenciát adunk vissza
    reference back()
    {
        return notOk.empty() ? ok.back() : notOk.back();
    }

    // ha a másodikba nincs elem, akkor az első back-jével, különben a második backjével térünk vissza
    // felüldefiniált const-ra
    T back() const
    {
        return notOk.empty() ? ok.back() : notOk.back();
    }

    // négyes

    // friend class - á tesszük az összes más template paraméterrel megadott partition_vector-t
    // mert csak így érhetjük el egymás tagjait, és így működik a swap
    template <typename U, typename F2>
    friend class partitioned_vector;

    // kicserélünk 2 más filterrel rendelkező vectort
    template <typename F2>
    void swap( partitioned_vector<T,F2>& pv )
    {
        // lementjük a másodikban lévő elemeket, majd kiürítjük
        std::vector< T > tmp1 = pv.ok;
        std::vector< T > tmp2 = pv.notOk;
        pv.ok.clear();
        pv.notOk.clear();

        // az elsőből az összes elemet beletesszük (az insert majd úgy is szétosztja)
        for( int i = 0; i < ok.size() ; ++i )
        {
            pv.insert( ok[i] );
        }
        for( int i = 0; i < notOk.size() ; ++i )
        {
            pv.insert( notOk[i] );
        }

        // kitöröljük az elsőből az elemeket, majd amit lementettünk, azokat beletesszük
        // (az insert itt is szétosztja)
        ok.clear();
        notOk.clear();
        for( int i = 0; i < tmp1.size() ; ++i )
        {
            insert( tmp1[i] );
        }
        for( int i = 0; i < tmp2.size() ; ++i )
        {
            insert( tmp2[i] );
        }
    }

    // otosert:

    // default constuctor
    partitioned_vector(){}

    // iterátoros constuctor
    template <typename ItType>
    partitioned_vector( ItType begin, ItType end )
    {
        // végigmegyünk rajtuk, és az összeset beletesszük
        while( begin != end )
        {
            insert(*begin++);
        }
    }

};

#endif // HEADER_INCLUDED
