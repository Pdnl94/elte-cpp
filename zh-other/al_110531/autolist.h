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
    A feladat egy olyan lista struktúra megvalósítása, mely pointereket tárol, 
    és ha kiveszünk egy elemet a listából, felszabadítja a pointert.
    A destruktorában az összes pointert felszabadítja (hisz kiürül a struktúra)

    Ha lekérünk egy elemét, akkor nem a pointert, hanem az értéket adja vissza
    Iterátoron keresztül is 


    // megj
        azért ilyen összevissza az elrendezésem, mert mindent egyszer akartam megvalósítani, és csak hivatkozni rá
        ezért nem a megvalósítás sorrendjébe vannak
*/
#include <list>

// 1 template paaraméter, a típus, amelyre mutató pointereket kell tárolnunk
// öröklődünk a std::list< T* > ból
template <typename T>
class auto_list : public std::list < T* >
{
    // definiáljuk a típusokat
    typedef std::list < T* > Container;
    typedef typename Container::size_type size_type;
    typedef typename Container::iterator c_iterator;
    typedef typename Container::const_iterator c_const_iterator;

public:
    // default konstruktor , semmi dolgunk
    auto_list(){}

    // töröljünk egy iterátort
    void erase( c_iterator it )
    {
        // az értékét felszabadítjuk, majd kivesszük a listából
        delete *it;
        Container::erase( it );
    }    

    // töröljük az első elemet, kérjük le begin()-nel az első iterátorát, majd töröljük
    void pop_front() 
    { 
        erase( begin() ); 
    }

    // destruktor - iteráljunk végig, majd töröljük egyesével az elemeket
    ~auto_list()
    {
        c_iterator it = begin();
        while( it != end() )
            erase( it++ );
    }

    // először szabadítsuk fel a területet ( a destruktor meghívásával )
    // majd másoljuk át az értékadó operátor második paraméterének az összes elemét
    // térjünk vissza magunkkal
    auto_list& operator=( const auto_list& al )
    {
        this->~auto_list();

        c_const_iterator it = al.begin();
        while( it != al.end() )
            this->push_back( new T(**it++) );

        return *this;
    }

    // copy constructor - hívjuk meg az értékadó operátort // nagyon lusta megoldás
    auto_list( const auto_list& al )
    {
        *this = al;
    }

    // le lehet kérni a struktúra első és utolsó elemeit, akár konstansokon is.
    // a struktúra a pointert tárolja, ezet dereferáljuk mind a négy esetben
    T& front()
    {
        return *Container::front();
    }

    T& back()
    {
        return *Container::back();
    }

    T front() const
    {
        return *Container::front();
    }

    T back() const
    {
        return *Container::back();
    }

    // iterátor struktúra, ugyan az mint a list iterátora, azzal a különbséggel
    // hogyha az iterátoron keresztül akarsz elérni egy elemet, akkor 
    // nem a struktúra által tárolt T* elemmel térünk vissza, hanem vesszük azt
    // az értéket, amire mutat
    struct iterator:c_iterator
    {
        // konstruktorban továbbadjuk az ősosztálynak
        iterator( c_iterator c ):c_iterator(c){}

        // ha lekérünk egy elemet, akkor használjuk a list operator* függvényét, 
        // ami a T* -al tér vissza, és ennek vegyük a mutatott értékét
        T& operator*()
        {
            return *c_iterator::operator*();
        }

        // ha lekérünk egy elemet, akkor használjuk a list operator-> függvényét, 
        // ami a T** -al tér vissza, és ennek vegyük a mutatott értékét
        T* operator->()
        {
            return *c_iterator::operator->();
        }
    };

    // begin - end , semmi különöset nem csinál, csak a saját iterátor típusunkkal tér vissza
    // amibe beleteszi a szülő osztály begin - end iterátorát
    iterator begin()
    {
        return Container::begin();
    }

    iterator end()
    {
        return Container::end();
    }

    // hogy tudjuk feljebb használni a begin() - end() függvényeket
    // const struktúrán is (és most nem akarjuk megvalósítani (amúgy trivi lenne) )
    // ezt a kkét using-ot használva ha meghívódik, továbbadjuk a bázisosztálynak a kérést    
    using Container::begin;
    using Container::end;
};

#endif // HEADER_INCLUDED
