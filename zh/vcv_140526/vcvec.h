#ifndef VCVEC_H_INCLUDED
#define VCVEC_H_INCLUDED

#include <vector>

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

// egy template paraméter
// származunk egy vektornyi T típusú paraméterből
template <typename T>
class version_controlled_vector : public std::vector< T >
{
    // ebből származunk, nevezzük el Inher-nek
    typedef std::vector< T > Inher;

    // egy vektornyi belőlünk, ez a mentések típusa
    typedef std::vector< Inher > Saves;
    // amik a commitokat jelentik

    Saves v; // mentések
public:
    // typedef-eljük a size_type-ot, hogy egyszerűbben tudjuk használni
    typedef typename Inher::size_type size_type;

    // commit :
    // a meglévő dolgokat elmentjük a mentéseink közé
    // de csak akkor, ha volt változás ( azaz az utolsó mentéssel nem egyezünk meg )! ( vagy ha még nem volt semmi eddig )
    // visszatérünk a commit számával ( 0-tól indexelünk, ezért a -1 )
    size_type commit()
    {
        if( !v.size() || v.back() != *this )
            v.push_back(*this);
        return v.size() - 1;
    }

    // visszatérünk egy előző verzióra, a mentés számából visszakeressük,
    // és egyenlővé teszük magunkkal (azaz az öröklődött osztályunkkal)
    void update(size_type n)
    {
        this->Inher::operator=( v[n] );
    }

    // visszatérünk a legutolsó mentésünkre (ha volt ; ha nem volt, kiürítjük a vektort)
    void revert()
    {
        if( v.size() )
            this->Inher::operator=( v.back() );
        else
            this->Inher::clear();
    }

    // le lehet kérni az eddigi mentéseinket, ez egy osztály operátor (amivé átváltozódunk)
    // beletesszük a mostani verziónkat is, mert az még nincs a mentések között, majd visszatérünk vele
    operator Saves() const
    {
        Saves tmp (v);
        tmp.push_back(*this);
        return tmp;
    }

    // swap - kcseréli a két vectort, és a mentéseit is
    // ezt felül kell definiálni, mert ha nem tennénk, a mentések nem cserédlőnének ki
    void swap( version_controlled_vector<T>& an )
    {
        this->Inher::swap( an );
        an.v.swap( v );
    }

    // default constructor - semmit nem csinál
    // (azért kell ezt ideírni, mert ha létrehoztuk a másikat, akkor ez eltűnik)
    version_controlled_vector(){}

    // iterátoros constructor
    // template paramétere az iterátor típusa (amit szépen kitalál a fordító meghívásakor)
    // egyszerűen tovább adjuk a belőlünk származó osztálynak
    template <typename Iter>
    version_controlled_vector(Iter begin, Iter end):
        Inher(begin, end)
    {}
};

#endif // VCVEC_H_INCLUDED
