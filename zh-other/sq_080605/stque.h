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
    A feladat egy olyan konténer megvalósítása, mely template paraméterként az elemek típusán kívül még megkapja azt, hogy
    Stack, vagy Queue adatszerkezetként viselkedjen, egy boolean értékként.
    Harmadik template paraméterként még azt is megkapja, hogy mind ez milyen konténerrel legyen megvalósítva

    A push a konténer végébe helyez be egy elemet
    A get és a pop attól függően, hogy most Stack-e vagy sem, az adatszerkezet elejéhez, vagy végéhez nyúl

    Le lehet kérni a stack-et meg a queue adatszerkezeteket

    A struktúrát létre lehet hozni egy intervallum segítségével
*/

#include <deque>
#include <stack>
#include <queue>

// 3 template paraméter, az első az elemek típusa, a második, hogy stack, vagy queue-e,
// a harmadik a container típusa, ami default legyen a deque
//   származunk a container-ből
template < typename T , bool Stack , typename Cont = std::deque < T > >
class StackQueue : public Cont
{
    // nevezzük el a stack, és a queue típusokat, melyek ugyan azt a containert használják mint mi
    typedef std::stack < T , Cont > StackType;
    typedef std::queue < T , Cont > QueueType;
public:

    // push a végébe, push_back...
    void push( const T& t )
    {
        Cont::push_back( t );
    }

    // get - ha stack, akkor a végén, ha queue akkor az elején lévő elemet adja vissza 
    T get() const
    {
        return Stack ? Cont::back() : Cont::front() ;
    }

    // túlterheltük a get-et a this const-ságán, a működése ugyan az
    T& get()
    {
        return Stack ? Cont::back() : Cont::front() ;
    }

    // pop - ha stack, akkor a végén, ha queue akkor az elején lévő elemet töröljük     
    void pop()
    {
        Stack ? Cont::pop_back() : Cont::pop_front() ;
    }

    // ha stack-ről van szó, akkor térjünk vissza egy stack-el, aminek átadjuk magunkat, kben egy üres stackkel
    StackType get_stack() const
    {
        return Stack ? static_cast< StackType >( *this ) : StackType();
    }

    // ha queue-ről van szó, akkor térjünk vissza egy queue-el, aminek átadjuk magunkat, kben egy üres queueval
    QueueType get_queue() const
    {
        return Stack ? QueueType() : static_cast< QueueType >( *this );
    }

    // default constructor
    StackQueue(){}

    // intervallumos, iterátoros constructor, adjuk tovább az ősosztálynak
    template < typename It >
    StackQueue( It begin , It end ) : Cont( begin , end ){}
};


#endif // HEADER_INCLUDED
