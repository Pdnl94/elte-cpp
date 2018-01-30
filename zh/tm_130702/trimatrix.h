#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

// első paraméterként kapunk egy Konténert, amiben kell tárolnunk a mátrixot
// a második a benne lévő elem ( defaultból a Container-ben lévő elem típusa )
template <typename Container , typename Elem = typename Container::value_type>
class TriangularMatrix
{
    // egyszerűség kedvéért nevezzük el az osztályokat
    typedef typename Container::size_type size_type;
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    // példányosítunk egy Containert, amibe eltároljuk.
    Container c;

    // eltároljuk a mátrix oldalhosszát
    size_type n;

public:

    // konstruktorba kapjuk a mátrix méretét, létrehozunk n*n db elemet, és elmentjük ezt
    TriangularMatrix( size_type n ) : c( n*n ), n(n) {}

    // ha alsó háromszög mátrixba volt, akkor beállítjuk, különben nem
    // visszatérünk az objektummal, amire meghívtuk ( hogy újra hívható legyen rá a fv )
    TriangularMatrix& set( size_type x , size_type y , const Elem& e )
    {
        if ( x >= y )
        {
            (*this)(x,y) = e;
        }
        return *this;
    }

    // visszatérünk az (x,y) elemmel
    Elem at( size_type x , size_type y ) const
    {
        return (*this)(x,y);
    }

    // visszatér a mérettel (n*n)
    size_type size() const
    {
        return c.size();
    }

    // visszatérünk az (x,y) elemmel, ha alsó-háromszög mátrixba van
    // (különben hibát dobunk)
    Elem& operator()( size_type x , size_type y )
    {
        if ( x >= y )
        {
            // lekérjük a kezdő pointert, majd std::advance - vel
            // ( azért így, mert pl az std::list-nek nincs + operátora (azaz begin() + 10 nem fordulna le) )
            // megnöveljük az értékét a mátrixban elhelyezkedő indexére
            iterator it = c.begin();
            std::advance( it , (x-1)*n+y-1 );
            return *it;
        }
        throw "bad element";
    }


    // visszatérünk az (x,y) elemmel
    // nem tud változtatni a struktúrán
    Elem operator()( size_type x , size_type y ) const
    {
        const_iterator it = c.begin();
        std::advance( it , (x-1)*n+y-1 );
        return *it;
    }

    // kiszámolja a determinánst (a főátló szorzatát)
    Elem determinant() const
    {
        // hozzunk létre egy változót, amibe tároljuk a szorzatot
        Elem prod = 1;
        for(size_type i = 1; i <= n; ++i)
        {
            // szorozzuk végig az ( i , i ). elemekkel (főátló elemei)
            prod *= at( i , i );
        }
        return prod;
    }

    // kitörlünk egy sor/oszlopot
    void erase(size_type k)
    {
        // csökkentsük az elején a könnyebb indexelhetőség miatt
        --k;--n;
        
        // először a k. oszlopban lévő elemeket keressük meg, és ezeket töröljük

        // beállítjuk az iterátort az első elemre, majd kitöröljük
        iterator it = c.begin();
        std::advance( it , k );
        it = c.erase( it );
        // megyünk n-1 -ig, és kitöröljük az n-1-el későbbit 
        for( size_type i = 0; i < n; ++i )
        {
            std::advance( it , n );
            it = c.erase( it );
        }
        
        // állítsuk be a [it,ite) intervallumot a k. sorra
        it = c.begin();
        std::advance( it , k*n );
        iterator ite = it;
        std::advance( ite , n );

        // töröljük ki az intervallumot
        c.erase( it , ite );

    }

    // friend-é tesszük az osztály más template paraméterekkel megvalósított osztályait
    // csak így érhetjük el az adattagjait
    template <typename C2 , typename U>
    friend class TriangularMatrix;

    // egyenlőség operátor
    // akkor == két Mátrix, ha a méretük, és az elemeik is megegyeznek
    // lehet, hogy pl list-et és vector-t kell összehason
    template <typename C2 , typename U>
    bool operator==( const TriangularMatrix<C2,U>& tm ) const
    {
        return tm.n == n && std::equal( c.begin() , c.end() , tm.c.begin() );
    }

    // akkor nem egyezik meg két mátrix, ha
    // nem egyenlőek a méreteik, vagy bármely elembe is különböznek
    template <typename C2 , typename U>
    bool operator!=( const TriangularMatrix<C2,U>& tm ) const
    {
        return tm.n != n || !std::equal( c.begin() , c.end() , tm.c.begin() );
    }

};

#endif // HEADER_INCLUDED
