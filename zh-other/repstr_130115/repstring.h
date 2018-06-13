#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <vector>
#include <string>
#include <iostream>


// egy template paraméter, hogy milyen char ( char / wchar_t )
template <typename CharType>
class basic_repeating_string
{
    // nevezzük el a típusokat
    typedef std::basic_string<CharType> StrType;
    typedef typename StrType::size_type size_type;
    typedef typename StrType::iterator str_iterator;
    typedef typename StrType::const_iterator str_c_iterator;

    // hozzunk létre egy stringet
    StrType data;

    // ebbe tároljuk, hogy hányszor kell ismétlődnie
    size_type rep;
public :

    // default constructorba beállítjuk, hogy csak 1x ismétlődjön kezdetben
    basic_repeating_string():rep(1){}

    // no comment :)
    void repeating_string_push_back( const CharType& c )
    {
        data.push_back( c );
    }

    void print() const
    {
        // "rep"-szer kiiratjuk a stringet
        for( size_type i = 0; i < rep ; ++i )
        {
            std::cout << data;
        }
    }

    // beállítjuk az ismétlődés számát
    void set_repeating( size_type x )
    {
        rep = x;
    }

    // a méret a karakterek száma * ismétlődés
    size_type size() const
    {
        return data.size() * rep;
    }

    // állítsukk össze a stringet, és keressünk abban
    size_type find( const StrType& w ) const
    {
        StrType tmp;
        for( size_type i = 0; i < rep ; ++i )
        {
            tmp += data;
        }
        return tmp.find( w );
    }

    // az n. karakter az a n%karakterek száma - karaktert jelenti
    // felüldefiniáljuk a [] operátort const-ra is
    CharType& operator[]( size_type n )
    {
        return data[ n % data.size() ];
    }
    CharType operator[]( size_type n ) const
    {
        return data[ n % data.size() ];
    }

    // állítsuk össze a stringet, és hasonlítsuk össze
    int compare( const StrType& str ) const
    {
        StrType tmp;
        for( size_type i = 0; i < rep ; ++i )
        {
            tmp += data;
        }
        return tmp.compare( str );
    }

    // iterátor megvalósítás, származunk a string iterátorából
    class iterator : public str_iterator
    {
        // eltároljuk a szülő struktúrát, és n-et (hogy hol tartunk)
        basic_repeating_string* p;
        size_type n;

        // ezekkel egyszerűbben le tudjuk kérni a szülő osztályban tárolt
        // string iterátorát, és az operátorokat végre tudjuk rajta hajtani könnyebben
        inline str_iterator& me(){ return *this; }
        inline const str_iterator& me() const{ return *this; }

    public:
        // két pointer különbségére szükségünk van, ehhez typedefeljük a megfelelő typust
        typedef typename std::iterator_traits<str_iterator>::difference_type difference_type;

        // konstruktorba megkapjuk az adatokat
        iterator( basic_repeating_string* p , str_iterator it , size_type n = 0 ):str_iterator(it),p(p),n(n){}

        // ++ művelet. Növeljük a pointert. Ha elértünk a tároló végére, kezdjük előről n-et növelve
        iterator& operator++()
        {
            if( ++me() == p->data.end() )
            {
                me() = p->data.begin();
                ++n;
            }
            return *this;
        }

        // == ha az összes tagja ==
        bool operator==( const iterator& it ) const
        {
            return n == it.n && p == it.p && me() == it.me();
        }

        // != ha ! ( == )
        bool operator!=( const iterator& it ) const
        {
            return n != it.n || p != it.p || me() != it.me();
        }

        // két pointer különbsége a körök különbsége * a karakterek száma + a jelenlegi stringbeli különbség
        difference_type operator-( const iterator& it ) const
        {
            return ( n - it.n ) * p->data.size() + ( me() - it.me() );
        }
    };


    // visszaadjuk a kezdő, meg a vége iterátort
    iterator begin()
    {
        return iterator( this , data.begin() );
    }
    iterator end()
    {
        // akkor van vége, ha az utolsó sornak is a végére ért, és a 'rep'. kör első elemére mutat
        return iterator( this , data.begin() , rep );
    }
};

#endif // HEADER_INCLUDED
