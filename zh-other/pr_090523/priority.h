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
    A "mire gondolhatott a költő" című magyarázatot leírom

    A feladat egy olyan prioritásos konténer megvalósítása, mely kap template paraméterében egy konténer típust, 
    egy elem típust, meg egy prioritás típust, meg egy rendező funtort, és az elemek prioritásától függően 
    helyezi őket egy struktúrába úgy, hogy mindig a legnagyobb prioritású konténerrel dolgozik

    push_back kap két paramétert, az első az elem prioritása, a második maga az elem. 
        A prioritástól függően be kell tenni a megfeleő konténerbe az elemet
    pop_back letörli a legmagasabb prioritások közül a back - elemet, és ha elfogynak az elemek, akkor a konténert is
    front - back visszatér a legmagasabb prioritású elemek közüli első - utolsó elemmel
    size paraméterrel - a paraméterként megkapott prioritású elemek számát adja vissza
    size - az összes elem számát visszaadja
*/

#include <functional>
#include <map>

// 4 template paraméter :
//      1. a konténer típusa
//      2. az elem típusa. A default legyen az, amit a container elemeket tárol (ezt a value_type-ből lehet megtudni)
//      3. a prioritás típusa. Alapból legyen egy előjeletlen szám érték
//      4. a prioritás típus rendezési funktora. Alapból legyen a < operátor
//  származzunk egy map-nyi konténerből, melyet a prioritással indexelünk
template <  typename Cont ,
            typename Elem = typename Cont::value_type ,
            typename Prior = std::size_t ,
            typename PriorComp = std::less < Prior > >
class PrioritySequence : std::map < Prior , Cont , PriorComp >
{
    // nevezzük el az ősosztályt, és pár típusát
    typedef std::map < Prior , Cont , PriorComp > Inher;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;
    typedef typename Inher::size_type size_type;

public:

    // amikor beteszünk egy elemet, akkor lekérjük az ebbe a prioritásba tartozó konténert
    // és ennek a végére betesszük az elemet
    void push_back( const Prior& p , const Elem& e )
    {
        (*this)[p].push_back( e );
    }

    // kitöröljük a legnagyobb prioritásos konténer utolsó elemét
    void pop_back()
    {
        // ha nincs egyáltalán elemünk, nothing to do
        if( !Inher::empty() )
        {
            // lekérjük a map-ban lévő utolsó containert
            iterator it = --Inher::end();

            // pop_back
            it->second.pop_back();

            // ha üres lett a container, akkor töröljük
            if( it->second.empty() )
                Inher::erase( it );
        }
    }

    // visszatérünk a legnagyobb prioritásos konténer első elemével
    // mivel a vector-nak nincs front-ja, ezért a begin() iterátoron keresztül kérjük le
    Elem& front()
    {
        if( !Inher::empty() )
            return *Inher::rbegin()->second.begin();
        // ha nem volt, throw - ide úgy se jövünk
        throw;
    }

    // túlterheljük a front-ot a this const-ságán
    const Elem& front() const
    {
        if( !Inher::empty() )
            return *Inher::rbegin()->second.begin();

        throw;
    }

    // visszatérünk a legnagyobb prioritásos konténer utolsó elemével
    Elem& back()
    {
        if( !Inher::empty() )
            return Inher::rbegin()->second.back();

        throw;
    }

    // túlterheljük a back()-et a this const-ságán
    const Elem& back() const
    {
        if( !Inher::empty() )
            return Inher::rbegin()->second.back();

        throw;
    }

    // lekérjük a p prioritásos container elemszámát
    size_type size( const Prior& p ) const
    {
        // megkeressük a map-ben
        const_iterator it = Inher::find( p );
        // ha nem volt ilyen elem, akkor 0, különben meg a konténer méretével térünk vissza
        return it == Inher::end() ? 0 : it->second.size();
    }

    // megszámoljuk a map-ben lévő összes container méretét, majd visszatérünk vele
    size_type size() const
    {
        size_type res = 0; // ebbe fogjuk gyűjteni

        // végighaladunk a map elemein, majd a (second - érték) típusnak lekérjük a size-át (azaz a containernek)
        for( const_iterator it = Inher::begin() ; it != Inher::end() ; ++it )
            res += it->second.size();

        return res;
    }
};


#endif // HEADER_INCLUDED
