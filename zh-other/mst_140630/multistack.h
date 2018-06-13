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
    A feladat egy olyan adatszerkezet megvalósítása, mely képes egy stacket csoportokba szervezni
    Ebbe a stack-be alapból push-al kell tenni elemet
    Van egy Join művelet, van egy szám paramétere (legyen n), mely a stack felső n elemét / csoportját 
    összecsoportosítja egy (új) csoportba, ami lesz a stack felső eleme

    A top az megadja a stack legfelső csoportját
    A height az megadja a magasságát a stacknek
    A size meg az összes elemet ami a stackben van

    Végig lehet iterálni a struktúrán a stack elemeinek megfelelően
*/


#include <deque>
#include <vector>
#include <stack>
#include <algorithm>

// alkossuk meg ezt a std::next függvényt, mely C++11-től létezik
// kap egy iterátort, meg egy számot, és az iterátort megnöveli n-el, 
// majd visszatér a megnövelt iterátorral
template <typename It, typename Val>
It next( It p , Val n )
{
    std::advance( p , n );
    return p;
}

// 1 template paraméter, az első az elemek típusa,
template <typename T >
class multistack : public std::deque < T >
{
    // nevezzük el a származó osztályt
    typedef std::deque < T > Cont;
    // nevezzük el a size_type-t
    typedef typename Cont::size_type size_type;
    
    // csináljunk egy vector-nyi "check"-et, ami annyit fog tenni, hogy figyeli, 
    // hogy a stack hanyadik elemétől vannak a csoportok. Alapból minden új elem egy-egy csoportot alkot
    typedef std::vector < size_type > ChecksType;

    // példányosítsuk
    ChecksType checks;

public:
    // push - beleteszünk egy elemet
    // a check-lista végébe beleszúrjuk, hogy a stack egy új része kezdődik ( a jelenlegi méretnél ), 
    // majd a konténer végébe beleszúrjuk az elemet
    // visszatérünk "magunkkal"
    multistack& push( const T& e )
    {
        checks.push_back( Cont::size() );
        Cont::push_back( e );
        return *this;
    }

    // kitöröljük az utolsó t-1 check-et, amely azt fogja elérni, 
    // hogy az utolsó 't' stack-részt össze fogja olvasztani
    void join( size_type t )
    {
        checks.erase( next( checks.end() , - --t ) , checks.end() );
    }

    // visszaadja a magasságot (hogy hány darab check van, hány darab stack része van)
    size_type height() const
    {
        return checks.size();
    }

    // visszaadja a stack utolsó részét
    Cont top() const
    {
        return Cont( Cont::rbegin() , next( Cont::rend() , - checks.back() ) );
    }

    // letörli a stack utolsó részét, illetve a check-ek közül az utolsót
    void pop()
    {
        Cont::erase( next( Cont::begin() , checks.back() ) , Cont::end() );
        checks.pop_back();
    }

    // pop majd push
    void replace_top( const T& e )
    {
        pop();
        push( e );
    }

    // default constructor
    multistack(){}

    // stack-es constructor, mely tárolója bármi lehet
    template <typename AnCont>
    multistack( std::stack < T , AnCont > s )
    {
        //indítsunk egy ciklust, mely törzsében mindig a stack legfelső
        // eleme van, amíg ki nem fogy
        for( ; ! s.empty() ; s.pop() )
        {
            // tegyük be a container elejébe az elemet, és vegyük fel a checks-et is
            // hisz a stack elemei külön csoportba tartoznak
            Cont::push_front( s.top() );
            checks.push_back( checks.size() );
        }
    }    

    // végig iterálhatunk az elemeken (fordított sorrendben)
    typedef typename Cont::const_reverse_iterator const_iterator;

    // térjünk vissza a konténer rbegin és rend-jével (reverse_begin, reverse_end)
    // ezzel fordítva végigiterálva a struktúrán
    const_iterator begin() const
    {
        return Cont::rbegin();
    }

    const_iterator end() const
    {
        return Cont::rend();
    }
};

#endif // HEADER_INCLUDED
