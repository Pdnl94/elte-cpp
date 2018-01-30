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
   A feladat egy olyan szekvenciális konténer megvalósítása, mely bármikor megfordítható

    Lusta megoldás
*/

/*

A négyesig elég ( CSAK!!! ) ennyi :

#include <algorithm>
#include <deque>

// 1 template paraméter, a típus amiket tartalmaz
template <typename T>
struct DirectionSequence : public std::deque < T >
{
    // ha bármikor megfordítanánk az irányt, akkor megfordítjuk az elemeket
    void change_direction()
    {
        std::reverse( begin() , end() );
    }
};

*/

#include <algorithm>
#include <deque>

// 1 template paraméter, a típus amiket tartalmaz
template <typename T>
struct DirectionSequence : public std::deque < T >
{
    // typedefek könnyebb hivatkozás érdekében
    typedef std::deque < T > Inher;
    typedef typename Inher::iterator cont_iterator;

    // eltároljuk, hogy volt-e irányváltás (milyen irányba nézzük)
    bool isFlipped;

    // ha bármikor megfordítanánk az irányt, akkor megfordítjuk az elemeket
    void change_direction()
    {
        isFlipped ^= 1; // eltároljuk, hogy most megfordítottuk
        std::reverse( Inher::begin() , Inher::end() );
    }

    // default constructor, hogy a booleannek legyen kezdőértéke
    DirectionSequence():isFlipped(){}

    // iterátor struktúra, ugyan olyan, mint a container iterátora
    struct iterator : std::iterator < std::random_access_iterator_tag , T >
    {
        // eltároljuk a szülőosztályt, azt, hogy kezdetben fordítva kezdtünk-e el iterálni,
        // és két iterátort, ami arra szolgál, hogyha megváltoztatjuk az irányt,
        // akkor a kezdettől kezdve kell újraiterálni.
        DirectionSequence* p;
        bool wasFlipped;
        cont_iterator cit,crit;

        // konstruktorában beállítjuk az értékeket
        iterator( DirectionSequence* p , cont_iterator cit ):
            p( p ),wasFlipped(p->isFlipped), cit( cit ) , crit( cit ){}

        // ez nem egyértelmű, de azt az iránybeli iterátort növeljük, amelyikben "épp vagyunk"
        //   ha a szülőosztály bool-ja megegyezik a milyenkével, akkor nem volt változás, különben igen
        iterator& operator++()
        {
            if ( p->isFlipped ^ wasFlipped )
                ++crit;
            else
                ++cit;
            return *this;
        }

        // lekérjük az iterátor aktuális elemét
        T& operator*()
        {
            return p->isFlipped ^ wasFlipped ? *crit : *cit;
        }

        // eldöntjük 2 iterátorról, hogy nem egyenlőek-e
        friend bool operator!=( const iterator& it1 , const iterator& it2 )
        {
            return ( it1.p->isFlipped ^ it1.wasFlipped ? it1.crit != it2.crit : it1.cit != it2.cit );
        }

        // kivonás operátor - visszaadja 2 iterátor különbségét
        friend long operator-( const iterator& it1 , const iterator& it2 )
        {
            return ( it1.p->isFlipped ^ it1.wasFlipped ? it1.crit - it2.crit : it1.cit - it2.cit );
        }
    };

    // visszaadjuk a saját megvalósított iterátorunkat
    iterator begin()
    {
        return iterator( this , Inher::begin() );
    }

    iterator end()
    {
        return iterator( this , Inher::end() );
    }
};

#endif // HEADER_INCLUDED
