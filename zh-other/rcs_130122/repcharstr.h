#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <vector>
#include <string>

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <string>

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
    void push_back( const CharType& c )
    {
        data.push_back( c );
    }

    // cout típusa : basic_ostream< char >
    // wcout típusa: basic_ostream<wchar_t>
    void print( std::basic_ostream< CharType> & o ) const
    {
        // minden karaktert kiíratunk "rep"-szer
        for( size_type i = 0; i < data.size() ; ++i )
        {
            o << StrType( rep , data[i] );
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
    size_type rfind( const StrType& w ) const
    {
        StrType tmp;
        for( size_type i = 0; i < data.size() ; ++i )
        {
            tmp += StrType( rep , data[i] );
        }
        return tmp.rfind( w );
    }

    // az n. karakter az a n/ismétlődés karaktert jelenti
    // felüldefiniáljuk a [] operátort const-ra is
    CharType& operator[]( size_type n )
    {
        return data[ n / rep ];
    }
    CharType operator[]( size_type n ) const
    {
        return data[ n / rep ];
    }

    // állítsuk össze a stringet, és hasonlítsuk össze
    int compare( const StrType& str ) const
    {
        StrType tmp;
        for( size_type i = 0; i < data.size() ; ++i )
        {
            tmp += StrType( rep , data[i] );
        }
        return tmp.compare( str );
    }

    // iterátor megvalósítás, származunk a string iterátorából
    class iterator : public str_iterator
    {
        // eltároljuk a szülő struktúrát, és n-et (hogy hol tartunk)
        basic_repeating_string* p;
        size_type n;
    public:
        // konstruktorba megkapjuk az adatokat
        iterator( basic_repeating_string* p , str_iterator it , size_type n = 0 ): str_iterator(it),p(p),n(n){}

        // ++ művelet. Növeljük n-et. Ha elérte az ismétlődések számát, lépjünk a köv. karakterre
        iterator& operator++()
        {
            if( ++n == p->rep )
            {
                str_iterator::operator++();
                n = 0;
            }
            return *this;
        }
        // == ha az összes tagja ==
        bool operator==( const iterator& it ) const
        {
            return n == it.n && p == it.p && static_cast<str_iterator>(*this) == static_cast<str_iterator>(it);
        }
        // != ha ! ( == )
        bool operator!=( const iterator& it ) const
        {
            return ! ( *this == it );
        }
    };
    // ugyan az, csak constans iteerátorból származunk
    class const_iterator : public str_c_iterator
    {
        const basic_repeating_string* p;
        size_type n;
    public:
        const_iterator( const basic_repeating_string* p , str_c_iterator it , size_type n = 0 ): str_c_iterator(it),p(p),n(n){}

        const_iterator& operator++()
        {
            if( ++n == p->rep )
            {
                str_c_iterator::operator++();
                n = 0;
            }
            return *this;
        }

        bool operator==( const const_iterator& it ) const
        {
            return n == it.n && p == it.p && str_c_iterator::operator==(it);
        }

        bool operator!=( const const_iterator& it ) const
        {
            return ! ( *this == it );
        }
    };

    // attól függően, hogy const, vagy nem const, a megfelelő  iterátort visszaadjuk
    iterator begin()
    {
        return iterator( this , data.begin() );
    }
    iterator end()
    {
        return iterator( this , data.end() );
    }
    const_iterator begin() const
    {
        return const_iterator( this , data.begin() );
    }
    const_iterator end() const
    {
        return const_iterator( this , data.end() );
    }
};


#endif // HEADER_INCLUDED
