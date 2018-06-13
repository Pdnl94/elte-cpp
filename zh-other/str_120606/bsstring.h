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
    A feladat egy olyan biztonságos string létrehozása, melytől ha egy olyan indexedik elemet kérünk le, 
    amelyik nem létezik, akkor megnöveli a struktúrát akkorára, hogy létezzen az az elem, majd visszatér vele
    
*/

#include <string>

// 1 paraméter, a character típusa, származunk a 
// std::string == std::basic_string< char >
// std::wstring== std::basic_String<wchar_t>
template <typename CharType>
class basic_safe_string : public std::basic_string<CharType>
{
    // typedefek
    typedef std::basic_string<CharType> StrType;
    typedef typename StrType::size_type size_type;

public:
    // default, és string-es konstruktor (ahol továbbadjuk csak a szülő-osztálynak)
    basic_safe_string(){}
    basic_safe_string(const StrType& s):StrType(s){}

    // amikor lekérjük az elemet, akkor megnézzük, hogy létezik-e az elem
    // ha nem, akkor méretezzük át, és töltsük fel a szülő osztályt
    //   aminek a default értékei legyen a c-paraméter
    CharType& at( size_type pos , const CharType& c )
    {
        if( StrType::size() <= pos )
            StrType::resize( pos + 1 , c );
        return StrType::at( pos );
    }

    // amikor lekérjük az elemet, akkor megnézzük, hogy létezik-e az elem
    // ha nem, akkor méretezzük át, és töltsük fel a szülő osztályt
    CharType& operator[](size_type pos)
    {
        if( StrType::size() <= pos )
            StrType::resize( pos + 1 );
        return StrType::operator[](pos);
    }
};

// typedef-eljük el magunkat
typedef basic_safe_string<char>    safe_string;
typedef basic_safe_string<wchar_t> safe_wstring;

#endif // HEADER_INCLUDED
