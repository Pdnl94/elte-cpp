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
    ???
    A feladat egy olyan lista megvalósítása, mely eltárolja az utolsó elemet, amivel foglalkozott (berakta, megkereste)
    majd ha el kell döntenünk egy elemről, hogy benne van-e a list-ben ( contains ) , akkor először megnézi, hogy
    esetleg az az elem volt-e, amelyiket eltároltuk, ha nem, utána kezd el keresni a struktúrában
*/

#include <list>
#include <algorithm>

// 1 template paraméter, az elemek típusa, származunk az std::list - ből
template <typename T>
class cached_list : public std::list < T >
{
    // nevezzük el a típusokat...
    typedef std::list < T > Inher;
    typedef typename Inher::size_type size_type;
    typedef typename Inher::const_iterator const_iterator;

    // legyen egy iterátorunk, ami mindig az utoljára "piszkált" elemre mutasson
    // kezdetben a lista végére mutasson, ez az invalid állapotot mutassa
    const_iterator last;
public :
    // annak érdekében, hogy a függvényekben ne kelljen kiírni a this->begin() és this->end() - et (vagy az Inher::begin() ... )
    using Inher::begin;
    using Inher::end;

    // beleteszünk a container végébe egy elemet, majd elmentjük utoljára módosított elemként
    // hogy meghívható legyen a .push_back().push_back().push_back()
    //   ezért saját magunkkal ( cached_list& ) térünk vissza, hogy a következő fv-hívás is ránk legyen hatással
    //   visszatérés így a *this - el
    cached_list& push_back( const T& v )
    {
        last = Inher::insert( end() , v );
        return *this;
    }

    // beleteszünk a container elejébe egy elemet, majd elmentjük utoljára módosított elemként
    cached_list& push_front( const T& v )
    {
        last = Inher::insert( begin() , v );
        return *this;
    }

    // ellenőrizzük, hogy tartalmazza-e a lista az elemet
    bool contains( const T& v )
    {
        // ha az iterátorunk, ami az utolsó piszkált elemre mutat az valid
        // és egyenlő a kért elemmel, akkor tartalmazzuk
        if( last != end() && *last == v )
            return true;

        // ha nem, akkor keressük meg
        const_iterator it = std::find( begin() , end() , v );

        // ha megtaláltuk, akkor írjuk be, hogy őt piszkáltuk utoljára, és térjünk vissza igazzal
        if ( it != end() )
        {
            last = it;
            return true;
        }
        // kben nincs benne az elem
        return false;
    }

    // default constructor - állítsuk be az eltárolt elemet invalidra
    cached_list():last(end()){}

    // iterátoros constructor - adjuk át a list-nek az intervallumot, majd ő behúzza magának
    // az utolsó "piszkált" elemet állítsuk az utolsó elemre
    template <typename It>
    cached_list( It ibegin , It iend ):Inher( ibegin , iend ),last( --end() ) {}
};


#endif // HEADER_INCLUDED
