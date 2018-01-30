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
    A feladat egy olyan map megvalósítása, melynek ugyan az a kulcs és érték típusa, és balról-jobbról kereshető

    Az insert beleteszi a kulcs-érték párt a map-be
    A get függvény visszaadja, hogy egy kulcsnak, vagy egy értéknek mi a hozzá tartozó párja
    Az operator[] is ugyan azt csinálja mint a get
    A size függvény visszaadja a kulcs-érték párok darabszámát
    A remove művelettel ki lehet törölni egy kulcs, vagy egy értéket, attól függően hol szerepel.
    
    Végig lehessen iterálni a struktúrán, mint egy map-en
    Ha konstruktorba megkapunk egy intervallumot, akkor azt kezeljük úgy, hogy ezekkel a kezdőértékekkel konstruáljuk meg
*/

#include <map>

// egy! template paraméter, az indexelésnek a típusa
// származunk egy map-nyi < T , T > ből
template <typename T>
class Invmap : std::map < T , T >
{
    // nevezzük el a típusokat
    typedef std::map < T , T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;
public :
    // egyszerűség kedvvéért használjuk az ősosztály ezen függvényeit
    using Inher::begin;
    using Inher::end;
    using Inher::size;

    // behelyezünk egy elemet (a map az a kulcs-értékeket
    //   egy párban tárolja, így kell behelyeznünk nekünk)
    void insert( const T& k , const T& v )
    {
        Inher::insert( std::make_pair( k ,v ) );
    }

    // ha lekérjük egy elemhez tartozó értéket, akkor
    //  végig kell mennünk a map-en, és az első kulcs, vagy érték egyezést
    //  vissza kell adnunk (nem elég egyértelmű a kódból, de így működik jól)
    T get( const T& k ) const
    {
        for( const_iterator it = begin() ; it != end() ; ++it )
            if( it->first == k ) return it->second;
            else if( it->second == k ) return it->first;
        // ha nem volt, akkor egy üres, invalid elemmel térünk vissza
        return T();
    }

    T operator[]( const T& k ) const
    {
        return get( k );
    }

    // kitöröljük az összes előfordulását a paraméternek
    // (akár bal, akár jobb oldalon találjuk meg)
    void remove( const T& k )
    {
        for( iterator it = begin() ; it != end() ; ++it )
            if( it->first == k || it->second == k )
            {
                Inher::erase( it-- );
                return;
            }
    }

    // default konstruktor
    Invmap(){}

    // iterátoros konstruktor. Adjuk tovább az ősosztálynak
    template <typename It>
    Invmap( It begin , It end ):Inher( begin , end ){}
};



#endif // HEADER_INCLUDED
