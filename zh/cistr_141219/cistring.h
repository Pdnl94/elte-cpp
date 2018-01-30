#ifndef CISTRING_H_INCLUDED
#define CISTRING_H_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
    Ezen fájl a 2014. december 19-ei vizsgára készült, 2014. december 23-án.

    ~ Feladatleírás:

    Hozzunk létre egy olyan karaktereket tároló sablon osztályt, mely a kis-nagy betűk között nem tesz különbséget;
        a sablon paramétere legyen a karakter típusa ( char / wchar_t ), a neve pedig case_insensitive_basic_string.
    Megvalósítandó függvények:


    // kettes

    push_back - beletesz a tárolóba egy karaktert
    size - visszaadja a tárolóban lévő karakterek számát
    
    find (egy karakter) - Megkeresi a karakter első előfordulását a tárolónkba, majd visszaadja a pozícióját
    find (több karakter) - Megkeresi a karaktersorozat első előfordulását a tárolónkba (kis-nagy betű eltérés nem számít!), 
        majd visszaadja az első karakter pozícióját


    // hármas

    npos - hozzunk létre egy statikus konstanst, mely a végtelent reprezentálja, és ->

    Ha nem található meg a karakter, vagy a karaktersorozat a tárolónkba a find függvényeknél, 
        akkor térjünk visza egy "végtelent" reprezentáló nagy értékkel: npos (~ általában a visszatérési érték maximum eleme,
            ha unsigned típusról van szó, akkor -1).

    operator[] - visszaadja az i. elem referenciáját, mely elemet felül lehet írni kívülről.
    operator[] const - visszaadja az i. elem értékét (megváltozhatatlanul)


    // négyes

    rfind (egy karakter) - Megkeresi a karakter utolsó előfordulását ...
    rfind (több karakter) - Megkeresi a karaktersorozat utolsó előfordulását ...

        ha nem találja ugyan úgy npos-sal kell visszatérni


    // ötös

    operator== - valósítsuk meg az egyenlő-e operátort std::basic_string és a mi reprezentációnk között

    nevezzük el a 'char'-al példányosított sablon osztályunkat case_insensitive_string -nek
     
*/

#include <string>

//  Kiegészítő megoldás (nem muszáj értened, nem muszáj használnod) - a nagybetűsítő osztály megvalósítása - a behúzott rész

    /*
        Hogy nagybetűsítünk egy 'char' típusú változót? Egyszerűen. std::toupper(c)
        Hogy nagybetűsítünk egy 'wchar_t' típusú változót? std::towupper(wc)
            --> hozzunk létre egy sablon funktort, amely eldönti helyettünk, hogy melyiket használjuk (melyik esetben)

        Azért kiegészítő megoldás, mert e nélkül is a jelenlegi vizsgafeladatban működőképes, viszont ezzel teljesebb. 
    */

    // legyen a default osztály, ami egy tetszőleges sablonparaméterre semmit nem csinál
    template<typename T>
    struct To_Upper
    {};

    // legyen egy char -os template specializációja, mely op() -ra meghívja a toupper-t
    template<>
    struct To_Upper<char>
    {
        inline char operator()(const char& c) const{ return std::toupper(c); }
    };

    // legyen egy wchar_t -s template specializációja is, mely op() -ra meghívja a towupper-t
    template<>
    struct To_Upper<wchar_t>
    {
        inline wchar_t operator()(const wchar_t& c) const{ return std::towupper(c); }
    };


// Legyen 1 template paraméter - A karakter típusa
// származzunk private módon a std::basic_string -ből (http://www.cplusplus.com/reference/string/basic_string/)
//      segítség, megértéshez -> 
//          std::string == std::basic_string<char> 
//          (azaz az std::string az egy olyan std::basic_string példány amibe 'char' típusú változókat írhatunk)
template<typename T>
class case_insensitive_basic_string : std::basic_string<T>
{
    // koncepcionálisan úgy fogjuk eltárolni a karaktereket, hogy mindent "nagybetűsítünk"
    // így az összehasonlítás, a keresésnél nagybetűket fogunk használni

    // Kiegészítő megoldás - a nagybetűsítő funktorunk itt lesz
    To_Upper<T> to_upper;

public:
    // nevezzünk el típusokat
    //      Base - ősosztály - a könnyebb hivatkozás érdekében
    typedef std::basic_string<T> Base;
    //      size_type (előjeletlen egész típus, lsd pl std::string::size_type)
    typedef typename Base::size_type size_type;
    //      const_iterator (könnyebb iterálás végett)
    typedef typename Base::const_iterator const_iterator;

    // push_back függvény, nincs visszatérési értéke, egy karaktert vár paraméterként
    void push_back(const T& ch)
    {
        // az ősosztály tárolóját használva beletesszük a nagybetűsített karaktert
        // Kiegészítő megoldás 
        Base::push_back(to_upper(ch));
        // az eredeti megoldás ez volt:
        //Base::push_back(std::toupper(ch));
    }

    // keressünk egy karaktert (size_type visszatérési értékkel - előjeletlen egész)
    size_type find(const T& ch) const
    {
        // hívjuk meg az ősosztály ugyanolyan nevű függvényét, melybe a nagybetűs karaktert keressük meg
        // Kiegészítő megoldás 
        return Base::find(to_upper(ch));
        // az eredeti megoldás ez volt:
        //return Base::find(std::toupper(ch));
    }

    // keressünk egy karaktersorozatot (ugyan olyan típusba kapjuk, mint az ősosztályunk, size_type visszatérési értékkel )
    size_type find(const Base& cp) const
    {
        // hozzunk létre egy nagybetűsített változatot a bejövő karaktersorozatból úgy, hogy használjuk az osztályunk eddigi műveleteit
        case_insensitive_basic_string<T> what;
        // végigiterálunk a bejövő adatokon, és beletesszük push_back-el, ami majd nagybetűsíti a karaktereket
        const_iterator it = cp.begin();
        while(it != cp.end()) what.push_back(*it++);

        // visszatérünk az ősosztály ugyanolyan nevű függvényének eredményével (csak most itt nagybetűsek mind a keresendő, mind a tárolt karakterek)
        return Base::find(what);
    }

    // a size függvény ugyan az, mint amit az ősosztályunk használ, ezt nem kell felülírni, csak publikussá tenni, hogy kívülről lehessen használni
    using Base::size;

    // hármas

    // operator[] kérdés? Mi van, ha valaki kívülről referencián keresztül betesz egy kisbetűt a tárolónkba? Hogy tudjuk ezt figyelni?
    // válasz : pl. Saját referencia osztállyal. Ha valaki felül akar írni egy karaktert kívülről, akkor a saját osztályunkon keresztül "nagybetűsítjük"
    struct reference
    {
        // Kiegészítő megoldás - a nagybetűsítő funktorunk itt (is) lesz
        To_Upper<T> to_upper;

        // tároljuk el a lekért karakter referenciáját, amit konstruktorba megkapunk
        T& ref;
        reference(T& ref):ref(ref){}

        // ha valaki értéket akar adni neki, akkor nagybetűsítve továbbítjuk az értékadást
        // visszatérünk a referenciával (most nem szükségszerű, pl (ics[4] = ics[5] = 'z') esetén az lenne)
        reference& operator=(const T& ch)
        {
            // Kiegészítő megoldás 
            ref = to_upper(ch);
            // az eredeti megoldás ez volt:
            //ref = std::toupper(ch);
            return *this;
        }

        // operator tetszőleges_típus() <- ez egy olyan függvény, mely megmondja, hogy mit kell tenni ahhoz, hogy 
        //      az osztályunkból egy tetszőleges_típus objektum hogy lesz.
        //      (ez azt mondja meg hogy hogyan legyen reference típusból char)
        //      (hogy pl (char c = ics[4]) értékadás működjön)
        operator T()
        {
            return ref;
        }

    };

    // az i. elemet lekérjük -> adjuk vissza az ősosztály i. elemét, beburkolva egy reference osztályba 
    reference operator[](size_type i)
    {
        return Base::operator[](i);
    }

    // publikussá tesszük a konstans op[]-t, illetve az ősosztály npos statikus változóját 
    using Base::operator[];
    using Base::npos;

    // négyes

    // ugyan az, mint a find - csak most rfind, az ősosztályban is

    size_type rfind(const T& ch) const
    {
        // Kiegészítő megoldás 
        return Base::rfind(to_upper(ch));
        // az eredeti megoldás ez volt:
        //return Base::rfind(std::toupper(ch));
    }

    size_type rfind(const Base& cp) const
    {
        case_insensitive_basic_string<T> what;
        const_iterator it = cp.begin();
        while(it != cp.end()) what.push_back(*it++);
        return Base::rfind(what);
    }

    // ötös

    // tegyük baráttá az == globális operátort, hogy lássa az ősosztályunkban lévő megvalósítást
    template<typename U>
    friend
    bool operator==(const case_insensitive_basic_string<U>& l, const case_insensitive_basic_string<U>& r);

};

// ötös

// két saját, csupa nagybetűs osztálybeli string akkor egyenlő, ha az alattuk lévő, ősosztályukban eltárol std::basic_string karakterei megegyeznek.
template<typename T>
bool operator==(const case_insensitive_basic_string<T>& l, const case_insensitive_basic_string<T>& r)
{
    return std::basic_string<T>(l) == std::basic_string<T>(r);
}

// egy sima basic_string, és egy nagybetűsített string akkor egyenlő, ha 
//  nagybetűsítjük a sima basic_string -beli paramétert, és úgy megegyeznek (felettünk lévő == -re hivatkozik)
template<typename T>
bool operator==(const std::basic_string<T>& l, const case_insensitive_basic_string<T>& r)
{
    case_insensitive_basic_string<T> what;
    typename std::basic_string<T>::const_iterator it = l.begin();
    while(it != l.end()) what.push_back(*it++);
    return r == what;
}

// megcserélt paraméterekkel (nagybetűs - sima) akkor egyenlő, ha másik irányba (sima - nagybetűs) is egyenlő
template<typename T>
bool operator==(const case_insensitive_basic_string<T>& l, const std::basic_string<T>& r)
{
    return r == l;
}

// typedef-eljük el az osztályunk példányát, ezzel egyszerűbben lesz használható
typedef case_insensitive_basic_string<char> case_insensitive_string;

#endif // CISTRING_H_INCLUDED
