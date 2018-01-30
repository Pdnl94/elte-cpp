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
    A feladat egy olyan prioritásos konténer megvalósítása, mely stackeket képes rétegekbe ábrázolni, kap template paraméterbe
    egy elem típust, meg egy prioritás típust, meg egy rendező funtort, és az elemek prioritásától függően 
    helyezi őket a stackekbe úgy, hogy utána mindig a legnagyobb prioritású konténerrel dolgozik

    push - kap két paramétert, az első az elem prioritása, a második maga az elem. 
        A prioritástól függően be kell tenni a megfeleő stackbe az elemet
    pop - letörli a legmagasabb prioritások közül az utolsó elemet, és ha elfogynak az elemek, akkor a konténert is
    top - visszatér a legmagasabb prioritású elemek közüli felső elemmel
    size paraméterrel - a paraméterként megkapott prioritású elemek számát adja vissza
    size - az összes elem számát visszaadja
*/

#include <functional>
#include <map>
#include <stack>

// 3 template paraméter :
//      1. az elem típusa.
//      2. a prioritás típusa. Alapból legyen egy előjeletlen szám érték
//      3. a prioritás típus rendezési funktora. Alapból legyen a < operátor
//  származzunk egy map-nyi konténerből, melyet a prioritással indexelünk
template <  typename Elem ,
            typename Prior = std::size_t ,
            typename PriorComp = std::less < Prior > >
class priority_stack : std::map < Prior , std::stack < Elem > , PriorComp >
{
    // nevezzük el az ősosztályt, és pár típusát
    typedef std::map < Prior , std::stack < Elem > , PriorComp > Inher;
    typedef typename Inher::iterator iterator;
    typedef typename Inher::const_iterator const_iterator;
    typedef typename Inher::size_type size_type;

public:

    // amikor beteszünk egy elemet, akkor lekérjük az ebbe a prioritásba tartozó stacket
    // és ennek a végére betesszük az elemet
    void push( const Prior& p , const Elem& e )
    {
        (*this)[p].push( e );
    }

    // kitöröljük a legnagyobb prioritásos stack utolsó elemét
    void pop()
    {
        // ha nincs egyáltalán elemünk, nothing to do
        if( !Inher::empty() )
        {
            // lekérjük a map-ban lévő utolsó containert
            iterator it = --Inher::end();

            // pop
            it->second.pop();

            // ha üres lett a container, akkor töröljük
            if( it->second.empty() )
                Inher::erase( it );
        }
    }

    // visszatérünk a legnagyobb prioritásos stack első elemével
    Elem& top()
    {
        if( !Inher::empty() )
            return Inher::rbegin()->second.top();
        // ha nem volt, throw - ide úgy se jövünk
        throw;
    }

    // túlterheljük a top-ot a this const-ságán
    const Elem& top() const
    {
        if( !Inher::empty() )
            return Inher::rbegin()->second.top();

        throw;
    }

    // lekérjük a p prioritásos stack elemszámát
    size_type size( const Prior& p ) const
    {
        // megkeressük a map-ben
        const_iterator it = Inher::find( p );
        // ha nem volt ilyen elem, akkor 0, különben meg a stack méretével térünk vissza
        return it == Inher::end() ? 0 : it->second.size();
    }

    // megszámoljuk a map-ben lévő összes stack méretét, majd visszatérünk vele
    size_type size() const
    {
        size_type res = 0; // ebbe fogjuk gyűjteni

        // végighaladunk a map elemein, majd a (second - érték) típusnak lekérjük a size-át (azaz a stacknek)
        for( const_iterator it = Inher::begin() ; it != Inher::end() ; ++it )
            res += it->second.size();

        return res;
    }
};


#endif // HEADER_INCLUDED
