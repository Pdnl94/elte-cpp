#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <string>   

// első paraméterként kapunk egy Konténert, amiben kell tárolnunk a stringet
// a második a benne lévő elem ( defaultból a Container-ben lévő elem típusa )
template <typename Container , typename CharType = typename Container::value_type>
class basic_string_adapter
{
    // egyszerűség kedvéért nevezzük el/át a következő osztályokat
    typedef typename Container::size_type size_type;
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::reference reference;

    // példányosítunk egy Containert, amibe eltároljuk a stringet.
    Container cont;

public:

    // default constuctor
    basic_string_adapter(){}

    // string-es constructor. bemásoljuk a stringet az iterátorai segítségével
    basic_string_adapter( std::basic_string<CharType> str ) : cont( str.begin() , str.end() ){}

 
    // iterátoros constructor. bemásoljuk az elemeket az iterátorai segítségével
    template <typename ItType>
    basic_string_adapter( ItType begin, ItType end ) : cont( begin , end ){}

    // push_back-eljük a karaktert
    basic_string_adapter& push_back( CharType c )
    {
        cont.push_back( c );
        return *this;
    }

    // lekérhetjük a méretet
    size_type size() const
    {
        return cont.size();
    }

    // kereshetünk egy stringet az adapterben
    size_type find( std::basic_string<CharType> str ) const
    {
        // számoljuk ki, hogy melyik az a pont, ahol még a string kezdődhet ( összes karakter - string hossza + 1 )
        // használjunk std::advance-t, mert ez működik az összes containerre
        const_iterator end = cont.begin();
        std::advance( end , cont.size() - str.size() + 1 );

        // iteráljunk végig az összes lehetséges kezdődéssel
        for( const_iterator it = cont.begin() ; it != cont.end() ; ++it )
        {
            // ha megegyezik az it-tel kezdődő pozicióval..
            if( std::equal( str.begin() , str.end() , it ) )
            {
                // számoljuk ki, hogy mennyit léptünk
                return std::distance( cont.begin() , it );
            }
        }
        // ha nem volt egyezés, térjünk vissza -1 - el
        return static_cast<size_type>(-1);
    }

    // ha += van, akkor szúrjuk be insert-el a stringet a container végére
    basic_string_adapter& operator+=( std::basic_string<CharType> str )
    {
        cont.insert( cont.end() , str.begin() , str.end() );
        return *this;
    }

    // lekérhető az i. karakter (const felüldefiniálással)
    CharType operator[]( size_type i ) const
    {
        const_iterator it = cont.begin();
        std::advance( it , i );
        return *it;
    }

    // lekérhető az i. karakter referencia szerint
    CharType& operator[]( size_type i )
    {
        iterator it = cont.begin();
        std::advance( it , i );
        return *it;
    }

    // baráttá tesszük a más template paraméterrel megalkotott saját osztályunkat
    // hogy elérhessük a tagváltozóit
    template <typename C , typename U>
    friend class basic_string_adapter;
    
    // == operátort megvalósítjuk, ha jobbról, vagy balról van egy basic_string
    friend bool operator==( std::basic_string<CharType> l , basic_string_adapter r )
    {
        // legyen a méretük egyenlő, és a bennük lévő karakterek is
        return l.size() == r.cont.size() && std::equal( l.begin() , l.end() , r.cont.begin() );
    }

    friend bool operator==( basic_string_adapter l , std::basic_string<CharType> r )
    {
        return l.size() == r.cont.size() && std::equal( l.begin() , l.end() , r.cont.begin() );
    }

    // == operátor, ha más template-el elkészített osztállyal hasonlítjuk össze
    template <typename C , typename U>
    bool operator==( basic_string_adapter<C , U> r ) const
    {
        // legyen a méretük egyenlő, és a bennük lévő karakterek is
        return cont.size() == r.cont.size() && std::equal( cont.begin() , cont.end() , r.cont.begin() );
    }

    // át tudunk változni a saját osztályunk beli, de más template paraméterrel megalkotott osztállyá
    template <typename C , typename U>
    operator basic_string_adapter<C , U>() const
    {
        // csak át adjuk a saját iterátorunkat, és létrejön
        return basic_string_adapter<C , U>( cont.begin() , cont.end() );
    }
};

#endif // HEADER_INCLUDED
