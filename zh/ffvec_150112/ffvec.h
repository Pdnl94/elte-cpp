#ifndef FFVEC_H_INCLUDED
#define FFVEC_H_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
    Ezen fájl a 2015. január 12.-ei vizsgára készült, 2015. január 13.-án.

    ~ Feladatleírás:

    Hozzunk létre egy olyan sablon konténert, mely a memóriában egymás mellett tárolja az elemeit, 
        és meg vannak valósítva bizonyos string műveletek, (rész-konténer keresés, hozzáfűzés, kicserélés, kimásolás)
        amit az std::string mind tud (de csak POD típusokra - http://www.cplusplus.com/reference/type_traits/is_pod/).
    Mivel az std::vector az a konténer, amiben sorfolytonosan vannak tárolva az elemek, használjuk ősosztályként (bázisosztályként).

    Megvalósítandó függvények:


    // kettes

    kell egy statikus konstans változó (npos), mely egy nagy (maximális) szám ami a végtelent reprezentálja.

    find(vector) - megnézi, hogy a paraméterül kapott vector tartalma benne van-e a meghívott objektumban (folytonos tartalmazás)
        Ha benne van, visszaadja az első indexet ahol a keresett vektor előfordulásának első indexe van
        Ha nincs akkor npos-t ad vissza
            az std::string ugyanúgy viselkedő függvénye (1) : http://www.cplusplus.com/reference/string/string/find/

    - ha származtatsz vagy publikusan, vagy using-olod ezeket a függvényeket, nincs szükség a megvalósításukra,
        hisz már az std::vector megvalósítja ezeket:
 
    push_back(T) - beletesz a tároló végébe egy (template paraméterben megkapott típusú) elemet
    size - visszaadja a tárolóban lévő elemek számát
    at - visszaadja a függvényparaméterként megadott indexű elem értékét (vagy const referenciáját)


    // hármas

    append(const T*, size) - hozzáteszi a konténer végéhez az első paraméterben megkapott pointertől kezdődően az elemeket a második paraméter darabszámnyit
        az std::string ugyanúgy viselkedő függvénye (4) : http://www.cplusplus.com/reference/string/string/append/

    replace(i1, i2, vector) - az első két paraméterben megkapott iterátorok által közrefogott elemeket kell kicserélni a
        3. paraméterként megkapott vector elemeire (teljes másolás! - ha több volt, akkor több elem lesz, ha kevesebb volt, akkor kevesebb)
            az std::string ugyanúgy viselkedő függvénye (1 (2)) : http://www.cplusplus.com/reference/string/string/replace/

    - mivel származtatni kell, a többi függvényt, ami az std::vector-nak megvan, nincs szükség a megvalósítására


    // négyes

    copy(T*, len, pos) - az eltárolt pos. kezdőelemtől len darab elemet átmásol az első paraméterként megadott memóriaterületre
        az std::string ugyanúgy viselkedő függvénye : http://www.cplusplus.com/reference/string/string/copy/

    find(vector, fun) - hasonló az egyparaméteres find()-hez, csak ez második paraméterbe kap egy funtort, hogy két T típusú elemet
        mi szerint tartsunk egyenlőnek. E szerint keressük meg az első egyezést.
            (ilyenje az std::string-nek nincs :( )


    // ötös

    operator+=(vector)  - hozzáfűző, konkatenáló operátor, a jobboldali vector elemeit hozzáfűzi a baloldali objektum végére
        az std::string ugyanúgy viselkedő függvénye (1) : http://www.cplusplus.com/reference/string/string/operator+=/

    replace(i1, i2, begin, end) - az első két paraméterben megkapott iterátorok által közrefogott elemeket kell kicserélni az
        utolsó két paraméterként megkapott iterátorok által közrefogott elemeire 
        (teljes másolás! - ha több volt, akkor több elem lesz, ha kevesebb volt, akkor kevesebb)
            az std::string ugyanúgy viselkedő függvénye (6) : http://www.cplusplus.com/reference/string/string/replace/

*/



#include <vector>
#include <algorithm>

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!Az osztálykódban lévő komment nem mindig elegendő a feladat megértéséhez, a felső feladatleírás elolvasása ajánlott először!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Legyen egy T a sablonunk típusa, mely a tárolandó elemek típusát fogja jelenteni,
// majd származzunk egy std::vector<T> STL konténerből, hogy a jó tulajdonságai, függvényei meglegyenek
template<typename T>
class full_fledged_vector : public std::vector<T>
{
    //nevezzük el a bázisosztályunkat (ősosztály, amiből származunk) Base-nek
    // hogyha egy std::vector-beli függvényt szeretnénk használni, akkor könnyebben hivatkozhassunk rá 
    //    (ne kelljen mindig leírni, hogy std::vector<T>)
    typedef std::vector<T> Base;

public:
    // nevezzünk el pluszba típusokat (http://www.cplusplus.com/reference/vector/vector/#types)
    typedef typename Base::size_type size_type;
    typedef typename Base::iterator iterator;
    typedef typename Base::const_iterator const_iterator;

    // Statikus konstans npos változó. A deklarálása az osztály után következik.
    // http://www.cplusplus.com/reference/string/string/npos/
    static size_type npos;

    // vectorban való keresés
    //      használjuk az std::search függvényt (1) - http://www.cplusplus.com/reference/algorithm/search/
    //      mely visszaadja az első egyezésnek a kezdeti iterátorát, ha volt. Ha nem volt, akkor a végiterátort
    //      Döntsük el, hogyha volt, akkor hanyadik helyen, egyszerű iterátor-különbséggel 
    size_type find(const Base& vec) const
    {
        const_iterator res = std::search(Base::begin(), Base::end(), vec.begin(), vec.end());
        return res == Base::end() ? npos : res - Base::begin();
    }


    // hármas

    // hozzáfűzés
    //      Az std::vector insert műveletének (3) - http://www.cplusplus.com/reference/vector/vector/insert/
    //      az iterátoros beillesztését használva átmásoljuk a pointer által mutatott len hosszúságig lévő elemeket
    void append(const T* arr, size_type len)
    {
        Base::insert(Base::end(), arr, arr + len);
    }

    // kicserélés
    //      két lépésben csináljuk meg, először törlünk, majd behelyezzük az új elemeket
    //      nulladik lépésként elmentjük a helyét a kitörlés kezdetének, hogy hova kell majd behelyeznünk az elemeket. 
    //          (mert az erase és az insert műveletek is iterátor invalidálást okoznak, és ugyanazon iterátoron nem lehetne elvégezni 2 műveletet)
    //      első lépésben kitöröljük az iterátorokkal az elemeket http://www.cplusplus.com/reference/vector/vector/erase/
    //      második lépésben behelyezzük a konténer elmentett számú helyére a vector teljes intervallumát
    //          az std::vector insert műveletének segítségével (3) - http://www.cplusplus.com/reference/vector/vector/insert/
    void replace(iterator i1, iterator i2, const Base& vec)
    {
        size_type n = i1 - Base::begin();
        Base::erase(i1, i2);
        Base::insert(Base::begin() + n, vec.begin(), vec.end());
    }

    // négyes

    // http://www.cplusplus.com/reference/algorithm/copy/
    void copy(T* arr, size_type len, size_type pos) const
    {
        std::copy(Base::begin() + pos, Base::begin() + pos + len, arr);
    }

    // (2) - http://www.cplusplus.com/reference/algorithm/search/
    template<typename Pred>
    size_type find(const Base& vec, Pred p) const
    {
        const_iterator res = std::search(Base::begin(), Base::end(), vec.begin(), vec.end(), p);
        return res == Base::end() ? npos : res - Base::begin();
    }

    // ötös

    // hozzáfűzés
    //      tegyük be intervallummal a paraméter összes elemét
    void operator+=(const Base& vec)
    {
        Base::insert(Base::end(), vec.begin(), vec.end());
    }

    // kicserélés
    //      Legyen sablonfüggvény, mely (3. és 4. paraméter) iterátor típusától függetlenül működőképes, és ugyan azt csinálja, mint a 
    //      3 paraméteres társa, csak nem konténert, hanem iterátorokat kap meg.
    template<typename iter>
    void replace(iterator i1, iterator i2, iter first, iter last)
    {
        size_type n = i1 - Base::begin();
        Base::erase(i1, i2);
        Base::insert(Base::begin() + n, first, last);
    }
};

template<typename T>
typename full_fledged_vector<T>::size_type full_fledged_vector<T>::npos = -1;

#endif // FFVEC_H_INCLUDED
