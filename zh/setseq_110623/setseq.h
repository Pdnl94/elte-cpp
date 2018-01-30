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
    A feladat egy olyan halmaz struktúra megvalósítása, mely egy template paraméterként megkapott típusú container-be dolgozik
    Ha egy olyan elemet akarunk betenni a containerbe, ami már benne van, azt nem fogjuk tudni (nem történik semmi)

    Nem rendezetten tárolja az elemeket, és az elejére - végére lehet beszúrni elemet 

    Két ilyen halmaznak lehet venni az unióját, mely beleteszi a paraméterként kapott másik halmaz elemeit a konténer végébe

    Ki lehet törölni egy elemet
    Le lehet kérdezni, hogy benne van-e egy adott elem

    Két halmazról el lehet dönteni, hogy egyenlőek-e vagy sem, operátor == és != segítségével
*/

#include <algorithm>

// 2 template paraméter, az első a konténer típusa
//      a második az a konténer által tartalmazott elem típusa, amit default működésben kérjünk le a konténertől
//  származzunk a konténerből (public módon)
template < typename Cont , typename Elem = typename Cont::value_type >
class SetSequence : public Cont
{
    // nevezzük el magunknak ezeket a típusokat
    typedef typename Cont::size_type size_type;
    typedef typename Cont::iterator iterator;
public:

    // push_back - ha nem létezik az elem, helyezzük a végébe
    void push_back( const Elem& e )
    {
        if( ! count( e ) )
            Cont::push_back( e );
    }

    // push_front - ha nem létezik az elem, helyezzük az elejébe
    void push_front( const Elem& e )
    {
        if( ! count( e ) )
            Cont::push_front( e );
    }

    // nem kell a template-s dolog, de az == vizsgálat miatt egyszerűbbé válik a dolgunk, ha így csináljuk
    // szóval várunk paraméterként egy másik halmazt, ( melynek lehet más a containere is )
    // az összes elemet belőle magunkba push_back-eljük
    template < typename AnCont >
    void set_union( const SetSequence< AnCont , Elem > & ss )
    {
        // nevezzük el a barát-osztály konstans iterátorát (hogy ne a for ciklust csúnyítsa meg)
        typedef typename SetSequence< AnCont , Elem >::const_iterator an_const_iterator;

        // végigmegyünk az elemeken, és meghívjuk a saját push_back-ünket
        for( an_const_iterator it = ss.begin() ; it != ss.end() ; ++it )
            push_back( *it );
    }

    // kitörlünk egy elemet
    void erase( const Elem& e )
    {
        // megkeressük, hogy hol van. Ha megtaláltuk, kitöröljük az iterátorán keresztül
        iterator it = std::find( Cont::begin() , Cont::end() , e );
        if( it != Cont::end() )
            Cont::erase( it );
    }

    // visszaadjuk, hogy benne van-e a struktúránkban. Ha a find nem az utolsó elemmel tér vissza
    size_type count( const Elem& e )
    {
        return std::find( Cont::begin() , Cont::end() , e ) != Cont::end();
    }

    // tegyük baráttá a saját, de más template osztállyal megalkotott struktúránkat
    template < typename , typename >
    friend class SetSequence;

    // egy más halmazról eldöntjük, hogy egyenlőek-e
    template < typename AnCont >
    bool operator==( const SetSequence< AnCont , Elem > & ss )
    {
        // ha a két struktúránk mérete nem egyezik, akkor nem egyenlőek
        if( ss.size() != this->size() )
            return false;

        // másoljuk le a paraméterként megkapott halmazt, majd uniózzuk bele a mi elemeinket is
        SetSequence< AnCont , Elem > cpy = ss;
        cpy.set_union( *this );

        // ha megegyezik a mérete, azaz nem tettünk bele semmit, akkor egyenlőek
        return ss.size() == cpy.size();
    }

    // nem egyenlőség vizsgálat
    template < typename AnCont >
    bool operator!=( const SetSequence< AnCont , Elem >& ss )
    {
        // akkor nem egyenlőek, ha nem igaz rájuk, hogy egyenlőek
        return !( *this == ss );
    }
};


#endif // HEADER_INCLUDED
