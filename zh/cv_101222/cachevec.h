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
    A feladat egy olyan vector megvalósítása, melytől le lehet kérdezni azt, hogy létezik-e benne egy elem
    Ha lekérédeztük, akkor tároljuk el ezt, és ha legközelebbi lekérdezésnél először ezt böngésszük végig
*/

#include <vector>
#include <algorithm>

// 1 template, az elemek típusa. Származzunk a vector-ból
template <typename T>
class CachedVector : public std::vector< T >
{
    // típuselnevezés, és a cached vector
    typedef std::vector < T > Inher;
    Inher c;
public :
    // def constructor - semmit nem csinál
    CachedVector(){}

    // iterátoros constructor - átadjuk a szülőosztály-beli vectornak az intervallumot 
    template <typename It>
    CachedVector( It begin , It end ) : Inher( begin , end ){}

    // annak eldöntése, hogy tartalmaz-e egy elemet
    bool contains(const T& e)
    {
        // ha megtaláljuk a cache-k között, vagy ha az ősosztályban (ha az ősben, akkor mentsük el)
        return std::find( c.rbegin() , c.rend() , e ) != c.rend() ||
            ( std::find( this->begin() , this->end() , e ) != this->end() &&
                ( c.push_back( e ) , true ) );
    }

    // elem törlése
    void erase( const T& e )
    {
        // töröljük ki a cache-ből is meg az ősosztályból is
        c.erase( std::remove( c.begin() , c.end() , e ) , c.end() );
        Inher::erase( std::remove( this->begin() , this->end() , e ) , this->end() );
    }
};


#endif // HEADER_INCLUDED
