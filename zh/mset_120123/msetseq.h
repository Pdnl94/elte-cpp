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
    A feladat egy olyan adatszerkezet megvalósítása, amely template paraméterként megkap egy
    konténert, és ebben kell eltárolni rendezetten az elemeket.
    Megszámoltathatjuk, hogy egy elem hányszor van benne a struktúrában
    Kisebb operátort kap a hermadik template paraméterben, 
        amellyel eldönti a struktúra rendezettségének feltételét
*/

#include <deque>
#include <functional>
#include <algorithm>

// csinálunk egy funktort ---
// konstruktorba kap egy T template paraméterben megadott típusú értéket
// van egy 2. template paramétere, egy rendező (kisebb) operátor
// és az egyparaméteres zárójel operátora akkor tér vissza igazzal, ha
//   a megkapott érték se nem kisebb nála, se nem nagyobb
//   (azaz egyenlő, de nem az == operátorral, hanem rendezési < operátorral).
template <typename T , typename Compare = std::less< T > >
struct equal_comp
{
    Compare c;
    T e;
    equal_comp(const T& elem):e(elem){}

    bool operator() ( const T& x ) const {return !c(x,e) && !c(e,x);}
};

// 3 template paraméter
// első az elem típusa
// a második a konténer, amivel meg kell valósítani. Default legyen a deque , ebből származzunk
// a harmadik egy rendező operátor, amivel sorba tudjuk tenni az elemeket. default a kisebb operátor
template <typename T , typename Container = std::deque< T > , typename Compare = std::less< T >  >
class MultisetSortedSeq : public Container
{
    // típusdefiniálások...
    typedef typename Container::size_type size_type;
    typedef typename Container::iterator iterator;

public:
    // behelyezéskor meg kell tartani a struktúra rendezettségét,
    // arra a helyre szúrjuk, ahol az első "nagyobb" értéket találjuk
    //   (azaz megkeressük azt az elemet ami már nagyobb nála)
    // hogy meghívható legyen az .insert().insert().insert(), ezért vissza kell
    // térnünk "saját magunk referenciájával", azaz (*this)-el
    MultisetSortedSeq& insert( const T& t )
    {
        Container::insert( std::find_if( Container::begin() , Container::end() , std::bind1st( Compare() , t ) ) , t );
        return *this;
    }

    // megszámoljuk, hogy egy elemből mennyi van
    // használjuk a < operátort az egyenlőség megállapítására
    size_type count( const T& t ) const
    {
        return std::count_if( Container::begin() , Container::end() , equal_comp<T,Compare>(t) );
    }

    // töröljük ki az összes t elemet a struktúránkból
    void erase( const T& t )
    {
        Container::erase( std::remove( Container::begin() , Container::end() , t ) , Container::end() );
    }
};

#endif // HEADER_INCLUDED
