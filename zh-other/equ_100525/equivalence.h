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
    A feladat egy olyan ekvivalencia osztály megvalósítása, mely kulcs-érték párokból áll, és egy kulcshoz több érték tartozhat
    Szemantikailag a kulcs-érték párok egy ekvivalenciát (egyértelmű hozzárendelést) valósítanak meg

    Az add_representative függvénnyel tudunk egy új kulcscot felvenni    
    Az insert függvény 2 paramétert vár
        Vagy egy kulcs-érték párat. (a kulcshoz hozzárendeli az értéket)
        Vagy egy érték-érték párat. (ha az első érték valamely kulcshoz tartozik, akkor a második értéket is hozzárendeli ahhoz a kulcshoz)
    A count függvény megadja, hogy egy kulcshoz vagy egy értékhez eddig hány ekvivalens elem tartozik (saját magát beleértve)
    A get_representative függvény visszaadja, hogy egy értékhez milyen kulcs tartozik
    Az erase kitöröl egy értéket (a hozzá tartozó kulcs már nem lesz ekvivalens vele)
    Az erase_representative kitöröl egy kulcs értéket
    A size megadja, hogy a kulcsoknak összesen hány ekvivalens eleme van
*/


#include <map>
#include <set>
#include <functional>


// Sajnos az insert meg a count függvények miatt külön kell kezelnünk azt az esetet (template specializációval)
// amikor a kulcs, és az érték típusa megegyezik, hisz akkor másképp viselkedik mindd az insert, mindd a count.
// mivel vannak közösen működő függvényeink, amiket nem akarunk kétszer leírni, ezért csinálunk egy ősosztályt,
// amiben ezeket a közös függvényeket megvalósítjuk, majd ebből fogunk származni

// 3 típus, kulcs, érték, összehasonlító funktor
// származzunk egy olyan map-ből, ami egy kulcshoz egy halmaznyi értéket tárol le
template <typename Key , typename Val , typename Comp >
class EquivalenceBase : public std::map < Key , std::set < Val > , Comp >
{
protected:
    // nevezzük el a típusokat (tegyük protecteddé, hogy a származó osztályaink tudják majd használni
    typedef std::map < Key , std::set < Val > , Comp > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;
public:
    
    // amikor hozzá adunk egy kulcs értéket, csak annyit mondunk meg neki, 
    // hogy hozz létre neki egy halmazt, amiben tárolni fogjuk a vele ekvivalenseket
    //  ezt a map-nek a operator[] -al el tudjuk érni
    void add_representative( const Key& k )
    {
        (*this)[k];
    }

    // az ősosztályban azt az esetet valósítjuk meg, amikor két értéket kapunk
    // ekkor meg kell keresni az első érték melyik kulcshoz tartozik, majd abba a halmazba beletenni a másodikat is
    void insert( const Val& k , const Val& v )
    {
        // végigmegyünk a map-en, és ha a map "second (halmaz)" értékébe benne van az első paraméter
        // akkor ugyan abba a halmazba tegyük bele a függvény második paraméterét is
        for( iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second.count( k ) )
            {
                it->second.insert( v );
                return;
            }

        // szemantikailag lehet, hogy fordítva is meg kéne csinálni, ami copy-paste lenne
    }

    // egy értékről eldöntjük, hogy melyik kulcshoz van rendelve, majd az ahhoz tartozó kulcsnak 
    // az összes értékének lekérjük a méretét + 1 (hisz maga a kulcs is számít) -el térünk vissza
    // különben 0-val
    size_type count( const Val& v ) const
    {
        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second.count( v ) )
                return it->second.size() + 1;

        return 0;
    }

    // megkeressük egy értékre, hogy melyik kulcshoz tartozik, és visszaadjuk
    Key get_representative( const Val& v ) const
    {
        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second.count( v ) )
                return it->first;

        throw;
    }

    // kitörlünk egy értéket, amit úgy teeszünk meg, hogy megkeressük, melyik kulcshoz tartozik, 
    // és az ő halmazából kivesszük a paramétert
    void erase( const Val& v )
    {
        for( iterator it = this->begin() ; it != this->end() ; ++it )
            if( it->second.count( v ) )
            {
                it->second.erase( v );
                break;
            }
    }

    // kitörlünk egy kulcsot - majd a map megcsinálja helyettünk
    void erase_representative( const Key& k )
    {
        Inher::erase( k );
    }

    // megszámoljuk az összes kulcshoz tartozó halmaz méretét. 
    // Ennyi hozzárendelés van, térjünk ezzel vissza
    size_type size() const
    {
        size_type res = 0;

        for( const_iterator it = this->begin() ; it != this->end() ; ++it )
            res += it->second.size();

        return res;
    }

    // virtuális destruktor, hogy "biztonságosabban" származhassunk belőle
    virtual ~EquivalenceBase(){}
};


// az osztályunk ugyan úgy 3 template paraméterből áll, kulcs, érték típusai, és a rendező operátor, mely default std::less<Key>
// származzunk a saját Base osztályunkból
template < typename Key , typename Val , typename Comp = std::less < Key > >
struct Equivalence : EquivalenceBase < Key , Val , Comp >
{
    // nevezzük el a saját base osztályunk, a könnyebb, láthatóbb hivatkozás érdekében
    typedef EquivalenceBase < Key , Val , Comp > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator const_iterator;

    // mivel megvalósítunk más insert-és count függvényeket a mi osztályunkban
    // (más a szignatúrája), de szeretnénk az ősosztálybelieket is használhatóvá tenni
    // ezért using-oljuk őket
    using Inher::insert;
    using Inher::count;

    // ha egy kulcshoz teszünk be egy értéket (és nem ugyan az a típusuk)
    // akkor egyszerűen a kulcshoz tartozó halmazba beletesszük az értéket.
    void insert( const Key& k , const Val& v )
    {
        (*this)[k].insert( v );
    }

    // megszámoljuk, hogy egy kulcshoz hány ekvivalens érték tartozik (+1, ő maga)
    // megkeressük a map-be, majd ha megtaláltuk, visszatérünk a halmaz mérete + 1-el, kben 0
    size_type count( const Key& k ) const
    {
        const_iterator it = this->find( k );
        return it == this->end() ? 0 : it->second.size() + 1;
    }

};

// template specializáció az azonos kulcs-érték típushoz
// származunk ugyan úgy az ősosztályból
template < typename Key , typename Comp >
struct Equivalence< Key , Key , Comp > : EquivalenceBase < Key , Key , Comp >
{
    // bázis típus elnevezgetések
    typedef EquivalenceBase < Key , Key , Comp > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;

    // felüldefiniáljuk az bázisosztály insert függvényét ( hisz ugyan az a típus, ugyan az a szignatúra )
    //  először megkeressük, hogy az első paraméter kulcs-e. 
    //     Ha megtaláltuk a map-ben kulcsként, akkor a kulcshoz tartozó halmazba beletesszük
    //     Ha nem találtuk meg, hívjuk meg a bázisosztály insert függvényét
    void insert( const Key& k , const Key& v )
    {
        iterator it = this->find( k );

        if( it == this->end() )
            Inher::insert( k , v );
        else
            it->second.insert( v );
    }

    // felüldefiniáljuk az bázisosztály count függvényét ( hisz ugyan az a típus, ugyan az a szignatúra )
    //  először megkeressük, hogy a paraméter kulcs-e. 
    //     Ha megtaláltuk a map-ben kulcsként, akkor a kulcshoz tartozó halmaz mérete + 1-el visszatérünk
    //     Ha nem találtuk meg, hívjuk meg a bázisosztály count függvényét
    size_type count( const Key& k ) const
    {
        const_iterator it = this->find( k );

        return it == this->end() ?
                Inher::count( k ) :
                it->second.size() + 1;
    }
};


#endif // HEADER_INCLUDED
