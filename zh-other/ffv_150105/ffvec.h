#ifndef FFVEC_H_INCLUDED
#define FFVEC_H_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
    Ezen fájl a 2015. január 5.-ei vizsgára készült, 2015. január 6.-án.

    ~ Feladatleírás:

    Hozzunk létre egy olyan sablon konténert, mely a memóriában egymás mellett tárolja az elemeit, 
        de meg vannak valósítva a kevésbé, illetve nem a leghatékonyabb műveletei, (első helyre való behelyezés, rendezés, egyedivé tétel, áthelyezés)
        amit az std::list mind tud.
    Mivel az std::vector az a konténer, amiben sorfolytonosan vannak tárolva az elemek, használjuk ősosztályként (bázisosztályként).

    Megvalósítandó függvények:


    // kettes

    push_front(T) - beletesz a tároló elejébe egy (template paramétere szerinti típusú) elemet

    - ha származtatsz vagy publikusan, vagy using-olod ezeket a függvényeket, nincs szükség a megvalósításukra,
        hisz már az std::vector megvalósítja ezeket:
 
    push_back(T) - beletesz a tároló végébe egy (template paraméterben megkapott típusú) elemet
    size - visszaadja a tárolóban lévő elemek számát
    at - visszaadja a függvényparaméterként megadott indexű elem értékét (vagy const referenciáját)


    // hármas

    pop_front() - kiveszi a tároló elejéből az első elemet.
    sort() - rendezi a konténerben található elemeket növekvő sorrrendbe
        az std::list kontérnernek az ilyen nevű, és így viselkedő művelete (1) : http://www.cplusplus.com/reference/list/list/sort/

    - ha származtatsz vagy publikusan, vagy using-olod ezeket a függvényeket, nincs szükség a megvalósításukra,
        hisz már az std::vector megvalósítja ezeket:

    operator[] - visszaadja az i. elem referenciáját.


    // négyes

    unique() - Kitörli az összes (kivéve az első elemét) az ugyanazon elemekből álló egymás utáni csoportjainak. pl:
           kezdet: 1 1 1 4 4 1 6 6 8 8 8 2 8 4 3 4
                   \---/ \-/   \-/ \---/
           cél:     1     4  1  6   8    2 8 4 3 4
        az std::list kontérnernek az ilyen nevű, és így viselkedő művelete (1) : http://www.cplusplus.com/reference/list/list/unique/

    sort(Funktor) - rendezi a konténerben található elemeket egy, a függvényparaméterben megadott funktor szerinti sorrendben.
            (A "binér" relációt megvalósító funktor azt határozza meg két elemről, hogy az első elemnek előbb kell-e következnie mint a másodiknak)
        az std::list kontérnernek az ilyen nevű, és így viselkedő művelete (2) : http://www.cplusplus.com/reference/list/list/sort/


    // ötös

    splice(iterátor, konténer, iterátor, iterátor) - A függvény áthelyezi a függvényparaméterként megadott konténernek az 
            (utána lévő további 2 iterátort magába foglaló intervallumbeli) elemeit a saját, első függvényparamétereként megkapott  
            iterátora elé, majd az eredetiből kitörli az átmásolt elemeket
        az std::list kontérnernek az ilyen nevű, és így viselkedő művelete (3) : http://www.cplusplus.com/reference/list/list/splice/

    - ha származtatsz vagy publikusan, vagy using-olod ezeket a függvényeket, nincs szükség a megvalósításukra,
        hisz már az std::vector megvalósítja ezeket:

    begin - visszaadja az első elemre mutató iterátort
    end - visszaadja az utolsó elemre mutató iterátort
       
*/



#include <vector>
#include <algorithm>

// Legyen egy T a sablonunk típusa, mely a tárolandó elemek típusát fogja jelenteni,
// majd származzunk egy std::vector<T> STL konténerből, hogy a jó tulajdonságai (pl sorfolytonos ábrázolás) meglegyenek, 
//    illetve publikusan, hogy meghívhatóak legyenek a függvényei
template<typename T>
class full_fledged_vector : public std::vector<T>
{
    //nevezzük el a bázisosztályunkat (ősosztály, amiből származunk) [mostantól :) ] Base-nek
    // hogyha egy std::vector-beli függvényt szeretnénk használni, akkor könnyebben hivatkozhassunk rá 
    //    (ne kelljen mindi leírni, hogy std::vector<T>)
    typedef std::vector<T> Base;
public:

    // A konténer elejébe helyezzünk egy elemet. 
    // az std::vector - nak van egy insert művelete (1) : http://www.cplusplus.com/reference/vector/vector/insert/
    //    melyben egy elemet be lehet helyezni egy iterátor elé. 
    //    kérjük le a kezdeti iterátort (begin()), és az elé szúrjuk be a függvényparaméterként megkapott elemet
    void push_front(const T& e)
    {
        Base::insert(Base::begin(), e);
    }

    // hármas:

    // A konténer elejéből töröljünk egy elemet.
    // az std::vector - nak van egy erase művelete : http://www.cplusplus.com/reference/vector/vector/erase/
    //    melyben egy elem (vagy akár egy intervallum) a konténerből való kitörlését teszi lehetővé iterátorokon keresztül
    //    kérjük le a kezdeti iterátort (begin()), és azt töröljük ki
    void pop_front()
    {
        Base::erase(Base::begin());
    }

    // Rendezzük az elemeket.
    // hívjuk meg az <algorithm> header-ben lévő STL sablonfüggvényt (1) : http://www.cplusplus.com/reference/algorithm/sort/
    //    mely képes arra, hogy rendezzen egy intervallumot. Kérjük le a kezdeti, és a vég iterátorokat 
    //    (azaz a konténerünk teljes adathosszának intervallumát), és hívjuk meg rá az std::sort-ot
    void sort()
    {
        std::sort(Base::begin(), Base::end());
    }

    // négyes

    // egyedivé tétel (részletesebben a feladatleírásbal).
    // hívjuk meg az <algorithm> header-ben lévő STL sablonfüggvényt (1) : http://www.cplusplus.com/reference/algorithm/unique/
    //    mely képes arra, hogy a feladatnak megfelelő módon az egyedivé tételt elvégezze 
    //    nem kitörlendő-kitörlendő csoportosítással, majd visszaadja az utolsó megtartandó elem utáni iterátort.
    //    (megj: Az std::unique nem törli ki az elemeket, így erről nekünk kell gondoskodni.)
    void unique()
    {
        Base::erase(std::unique(Base::begin(), Base::end()), Base::end());
    }

    // rendezés, funktor szerint. - a funktor típusa egy tetszőleges típus, így legyen template függvény
    // hívjuk meg az <algorithm> header-ben lévő STL sablonfüggvényt (2) : http://www.cplusplus.com/reference/algorithm/sort/
    //    mely képes arra, hogy rendezzen egy intervallumot egy kapott funktor szerint. Kérjük le a kezdeti, és a vég iterátorokat 
    //    (azaz a konténerünk teljes adathosszának intervallumát), és hívjuk meg rá az std::sort-ot úgy, hogy átadjuk neki a funktort is
    template<typename Comp>
    void sort(Comp comp)
    {
        std::sort(Base::begin(), Base::end(), comp);
    }

    // ötös

    // áthelyezés (összefonás) - a feladat fent :)
    // Két függvényhívással, az std::vector insert műveletének (3) - http://www.cplusplus.com/reference/vector/vector/insert/
    //    az iterátoros beillesztését használva átmásoljuk az intervallumban lévő elemeket, 
    //    majd az eredeti konténerből kitöröljük ezeket.
    //    ++   Az első paraméter az a mi osztályunkbeli iterátor (std::vector<T>::iterator), hisz ide akarjuk behelyezni
    //         A második paraméter egy tetszőleges, iterátorokkal és erase művelettel rendelkező konténer típus (typename Cont)  
    //         A harmadik, negyedik paraméter az előző konténernek két iterátora (Cont::iterator)
    template<typename Cont>
    void splice(typename Base::iterator to, Cont& cont, typename Cont::iterator begin, typename Cont::iterator end)
    {
        Base::insert(to, begin, end);
        cont.erase(begin, end);
    }

    // megvalósítjuk az intervallumos konstruktort (ami a paramétereiben kapott 
    //    tetszőleges iterátor típus kezdeti és végértékével inicializálja a struktúrát)
    //    hívjuk meg a bázisosztályunk ugyanilyen (range) konstruktorát (3) - http://www.cplusplus.com/reference/vector/vector/vector/
    template<typename iter>
    full_fledged_vector(iter begin, iter end):Base(begin, end){}

    // mivel megvalósítottuk az intervallumos konstruktort, kénytelenek vagyunk a default-ot is...    
    full_fledged_vector(){}
};

#endif // FFVEC_H_INCLUDED
