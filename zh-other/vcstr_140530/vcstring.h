#ifndef VCSTRING_H_INCLUDED
#define VCSTRING_H_INCLUDED

#include <vector>
#include <string>

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

// egy template paraméter - a character típusa ( char vagy wchar_t )
// származunk egy basic_string T típusú paraméterből
// aki nem tudná : string == basic_string<char>
//                wstring == basic_string<wchar_t>
template <typename T>
class version_controlled_basic_string : public std::basic_string< T >
{
    // ebből származunk, nevezzük el Inher-nek
    typedef std::basic_string< T > Inher;

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

    // swap - kcseréli a két stringet, és a mentéseit is
    // ezt felül kell definiálni, mert ha nem tennénk, a mentések nem cserédlőnének ki
    void swap( version_controlled_basic_string<T>& an )
    {
        this->Inher::swap( an );
        an.v.swap( v );
    }

    // default constructor - semmit nem csinál
    // (azért kell ezt ideírni, mert ha létrehoztuk a másikat, akkor ez eltűnik)
    version_controlled_basic_string(){}

    // iterátoros constructor
    // template paramétere az iterátor típusa (amit szépen kitalál a fordító meghívásakor)
    // egyszerűen tovább adjuk a belőlünk származó osztálynak
    template <typename Iter>
    version_controlled_basic_string(Iter begin, Iter end):
        Inher(begin, end)
    {}

    // character tömbbös constructor
    // ha valaki így inicializálja a stringet, akkor azt úgy kezeljük le, hogy továbbadjuk
    version_controlled_basic_string( const T* v ):
        Inher( v )
    {}

    // lekérjük, hogy most épp hanyadik revízióban (mentésnél) járunk
    // const, hisz nem változtat a struktúrán
    size_type number_of_revisions() const
    {
        return v.size();
    }
};

#endif // VCSTRING_H_INCLUDED
