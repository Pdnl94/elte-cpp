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
    A feladat egy olyan vector megvalósítása, melytől le lehet kérdezni azt, hogy ha létezik benne egy bizonyos elem, akkor
        hanyadik indexen
    Ha lekérédeztük, akkor tároljuk el ezt az elemet, és ha legközelebbi lekérdezésnél először ezt az eltároltat nézzük meg

    Le lehet kérdezni predikátummal is

    Erase - törölje ki az összes előfordulását a paraméteri elemnek
*/

#include <vector>
#include <algorithm>

// 1 template, az elemek típusa. Származzunk a vector-ból
template <typename T>
class CachedVector : public std::vector< T >
{
    // típuselnevezések
    typedef std::vector < T > Inher;
    typedef typename Inher::const_iterator const_iterator;
    typedef typename Inher::size_type size_type;

    // ebbe fogjuk tárolni a cachelt elem indexét
    size_type index;
public :
    // def constructor - beállítja az indexet egy invalid elemre
    CachedVector(): index( not_in_vec() ){}

    // iterátoros constructor - átadjuk a szülőosztály-beli vectornak az intervallumot, index invalid
    template <typename It>
    CachedVector( It begin , It end ) : Inher( begin , end ), index( not_in_vec() ){}

    // lekérjük egy elem vectorban elhelyezkedő indexét
    size_type index_of( const T& e )
    {
        // először megnézzük a cache-t ( ha valid elemre mutat a cache , és megegyezik az értéke, térjünk vissza az indexxel
        if( index < this->size() && this->at(index) == e ) 
            return index;

        // ha nem cachelt, akkor keressük meg az elsőt.
        const_iterator it = std::find( this->begin() , this->end() , e );

        // ha nem találtuk meg, akkor térjünk vissza egy "invalid" elemmel
        if( it == this->end() )
            return not_in_vec();

        // ha  megtaláltuk, írjuk bele az index változóba, majd térjünk vele vissza
        return index = it - this->begin();
    }

    // legyen az invalid elem a -1, előjeletlen számként ( az a maximális unsigned típus )
    size_type not_in_vec() const
    {
        return static_cast<size_type>(-1);
    }

    // ha kitörlünk egy elemet, akkor az összes előforulásánál tegyük meg
    void erase( const T& e )
    {
        Inher::erase( std::remove( this->begin() , this->end() , e ) , this->end() );
    }

    // kapunk egy predikátumot, és erre kell visszaadnunk a méretét
    // hasonló az index_of -ra
    template <typename Pred>
    size_type predicate_index_of( Pred p )
    {
        // ha a cachelt index valid, és igaz a feltétel az annyiadik elemre, térjünk vele vissza
        if( index < this->size() && p( this->at(index) ) ) 
            return index;

        // különben keressük meg az elsőt, amire igaz (find_if - el)
        const_iterator it = std::find_if( this->begin() , this->end() , p );

        // ha nem találtunk ilyet, akkor nincs
        if( it == this->end() )
            return not_in_vec();

        // kben tegyük bele a cache-be, és térjünk vele vissza 
        return index = it - this->begin();
    }
};

#endif // HEADER_INCLUDED
