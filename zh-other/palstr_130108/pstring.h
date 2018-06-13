#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

// egy template paraméter, a character típusa ( char / wchar_t )
template <typename CharType>
class basic_palindrom_string
{
    // nevezzük el a string típusokat
    typedef std::basic_string<CharType> StrType;
    typedef typename StrType::size_type size_type;
    typedef typename StrType::iterator str_iterator;
    typedef typename StrType::const_iterator str_c_iterator;

    // csináljuk meg a string végét, az első karakter legyen a közepe
    // csináljunk ezen kívül egy booleant, hogy van-e közepe 
    StrType last;
    bool middle;
public:
    // default constructor beállítja a string első karakterét, hogy a középső 'nem valid' elem legyen
    // és a middle-t beállítja hamisra (azaz kívülről még nincs középső elem)
    basic_palindrom_string():last( 1 , CharType() ),middle(false){}

    // csak bele tesszük a végére a karaktert
    void push_front_back( const CharType& c )
    {
        last.push_back( c );
    }

    // ha középső elemet állítunk be, akkor az első karaktert felülírjuk, és beállítjuk a boolean változót
    void push_middle( const CharType& c )
    {
        last[0] = c;
        middle = true;
    }

    // a stringünk mérete - 1 jének kétszerese ( hisz a középső elemet leszámítva 2szerezzük az elemeket )
    // majd ha van középső elem, akkor hozzáadunk 1-et (a true == 1, a false == 0)
    size_type size() const
    {
        return ( last.size() - 1 ) * 2 + middle;
    }

    // keressük meg, állítsuk össze a stringet, és keressünk abban
    size_type find( const StrType& s ) const
    {
        // elindulunk a végéről, ha van közepe, akkor az egészet bemásoljuk (ha nincs, akkor a legelső elemet nem)
        StrType tmp( last.rbegin() , last.rend() - !middle );
        // hozzátesszük az első elemtől (a középső kivételével) az összes elemet
        tmp.insert( tmp.end() , ++last.begin() , last.end() );
        return tmp.find( s );
    }

    // indexelés
    CharType& operator[]( size_type i )
    {
        // ha a középső elem előtt vagyunk, akkor megfordítjuk az indexelést (0. elem lesz a last.size() - 1. stb)
        if( i < last.size() - 1 )
        {
            return last[ last.size() - 1 - i ];
        }
        // ha nem, akkor kivonjuk az indexből a string felét, és attól függően, hogy van-e középső elem, a megfelelő helyet visszaadjuk
        return last[ i - last.size() + 1 + !middle ];
    }
    // constans felüldefiniálás
    CharType operator[]( size_type i ) const
    {
        if( i < last.size() - 1 )
        {
            return last[ last.size() - 1 - i ];
        }
        return last[ i - last.size() + 1 + !middle ];
    }

    // állítsuk össze a stringet, és hasonlítsuk össze 
    int compare( const StrType& s ) const
    {
        StrType tmp( last.rbegin() , last.rend() - !middle );
        tmp.insert( tmp.end() , ++last.begin() , last.end() );
        return tmp.compare( s );
    }

    // csináljunk egy egyedi iterátort
    class const_iterator
    {
        // tároljuk el, hogy mi a struktúra, amin végigiterálunk
        const basic_palindrom_string* p;
        // hanyadik elemnél tartunk
        size_type n;
    public:

        // mivel egyedi az iterátorunk, a következő típusokat meg kell adni.
        // mivel "kb" a string const_iterator szerint működünk, annak a típusai tökéletesek nekünk
        // az iterator_traits - mindenféle dolgot (típusokat) elmond az iterátorról, amit le tudunk kérni
        typedef std::iterator_traits< str_c_iterator > ItTr;
        typedef typename ItTr::difference_type      difference_type;
        typedef typename ItTr::iterator_category    iterator_category;
        typedef typename ItTr::value_type           value_type;
        typedef typename ItTr::pointer              pointer;
        typedef typename ItTr::reference            reference;

        // constructor, beállítjuk
        const_iterator( const basic_palindrom_string* p , size_type n ):p(p),n(n){}

        // műveletek . n. karakternél vagyunk ...
        // ezek kellenek a RAI (random access iterator) típushoz
        void operator++(){ ++n; }
        bool operator!=( const const_iterator& it ) const { return n != it.n; }
        bool operator==( const const_iterator& it ) const { return n == it.n; }
        difference_type operator-( const const_iterator& it ) const { return n - it.n; }

        // a * típus felüldefiniáljuk úgy, hogy a struktúrán keresztül lekérjük az n. elemet
        value_type operator*(){ return p->operator[](n); }
    };

    // a struktúra a 0. karakterrel kezdődik
    const_iterator begin() const
    {
        return const_iterator( this , 0 );
    }
    
    // és a méret-edik karakterrel fejeződik be
    const_iterator end() const
    {
        return const_iterator( this , size() );
    }
};

#endif // HEADER_INCLUDED
