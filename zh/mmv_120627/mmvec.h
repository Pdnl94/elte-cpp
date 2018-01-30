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
    A feladat egy olyan Vector készítése, mely tárolja az értékek közül a minimumot, maximumot
    Ha egy behelyező művelet történik, akkor eldönti, hogy felül kell-e írnia a minimumot, maximumot
    Ha lekérjük a min/max műveletekkel, akkor konstans időben kell tudnia kiszámítani, kivéve :

    Ha bármilyen módosító művelet (referencia szerinti átadás) történik, akkor újra kell számolni a következő lekérésnél
        a minimumot és a maximumot
    Ha iterátoron keresztül lekérjük (referncia szerint) az értékét.
*/


#include <vector>

// egy template paraméter, az eltárolandó típus
template <typename T>
class MinMaxVector
{
    // nevezzük el a típusokat
    // 
    typedef std::vector<T> Vector;
    typedef typename Vector::const_iterator const_iterator;
    typedef typename Vector::iterator ih_iterator;
    typedef typename Vector::size_type size_type;

    // a data-ban fogjuk tárolni a vectort
    // a mine-maxe változókban a data container minimum és maximum értékéhez tartozó
    //  indexeket
    // a reCalc mondja meg azt, hogy újra kell-e számolnunk a minimumot-maximumot
    Vector data;
    size_type mine, maxe;
    bool reCalc;

    // ez egy segéd függvény, ami újraszámolja a minimum-maximum helyeket, és eltárolja a mine/maxe változókban
    void reC()
    {
        // beállítjuk őket az első értékre
        mine = maxe = 0;

        // végigmegyünk a vector-on, és az értékeket összehasonlítva minimum, és maximumkeresést végzünk az elemeken
        for( size_type i = 1 ; i != data.size() ; ++i )
            if( data[maxe] < data[i] )
                maxe = i;
            else if( data[i] < data[mine] )
                mine = i;

        // beállítjuk, hogy most már nem kell újra számolni
        reCalc = false;
    }
public:
    //default constructor - a mine/maxe változók invalid elemre mutatnak
    MinMaxVector() : mine( 0 ),maxe( 0 ),reCalc(false){}

    // ha lemásoljuk a vectort, akkor újra kell számolni az indexeket
    MinMaxVector( const MinMaxVector& mm ):data(mm.data)
    {
        reC();
    }

    // visszatér az adatok mennyiségével
    size_type size() const
    {
        return data.size();
    }

    // behelyez a vector végébe egy elemet
    // vissza térünk saját magunk referenciájával (*this) (hogy újra lehessen ránk hívni push_back-et)
    MinMaxVector& push_back( const T& t )
    {
        // tegyük bele, majd számoljuk ki az indexét
        data.push_back( t );
        size_type i = data.size() - 1;

        // ha újra kell számolni, tegyük meg, ha nem kell, akkor döntsük el, hogy ő volt-e az első, vagy ő lesz-e a min-max
        //    ha igen, akkor írjuk felül mine/maxe-t
        if( reCalc )
            reC();
        else if( data[maxe] < t )
            maxe = i;
        else if( t < data[mine] )
            mine = i;

        return *this;
    }

    // max - min függvények. Ha újra kell számolni, akkor számoljuk.
    //    ekkor megjavul, és visszatérhetünk a max / min értékkel
    // ha nem kellett, akkor csak simán visszatérünk
    T max()
    {
        if( reCalc )
        {
            reC();
        }
        return data[maxe];
    }

    T min()
    {
        if( reCalc )
        {
            reC();
        }
        return data[mine];
    }

    // max - min const függvények. Ha újra kell számolni, akkor számoljuk, de sajnos nem tudjuk ezt eltárolni (maxe/mine változókba)
    //   ezért csak lokálisan tudjuk kiszámolni a max/min értéket
    // ha nem kell, csak térjünk vissza az értékkel
    T max() const
    {
        if( reCalc )
        {
            T elem = data[0];
            for( size_type i = 1 ; i != data.size() ; ++i )
            {
                if( elem < data[i] )
                    elem = data[i];
            }
            return elem;
        }
        return data[maxe];
    }

    T min() const
    {
        if( reCalc )
        {
            T elem = data[0];
            for( size_type i = 1 ; i != data.size() ; ++i )
            {
                if( data[i] < elem )
                    elem = data[i];
            }
            return elem;
        }
        return data[mine];
    }

    // ha lekérjük az elemet const módon, akkor semmi teendő, mint továbbadni
    T at( size_type k ) const
    {
        return data.at( k );
    }


    // ha lekérjük az elemet referencia szerint, akkor beállítjuk, hogy újra kelljen számolni
    // mert a típusunkat kívülről megváltoztathatják
    // mind az 'at' , mind az operátor[]-nál , hisz mindkettő változtathat a struktúrán
    T& at( size_type k )
    {
        reCalc = true;
        return data.at( k );
    }

    T& operator[]( size_type k )
    {
        reCalc = true;
        return data[k];
    }

    // hozzunk létre egy dummy iterátort, ami használja a vector iterátorát annyi különbséggel, hogy
    // ha lekérjük bármelyik elemet az iterátor segítségével, akkor kívülről megváltoztathatóvá
    // tesszük megintcsak a struktúrát, így majd újra kell megint számoltatni a min/max-ot
    struct iterator : ih_iterator
    {
        typedef typename ih_iterator::reference reference;
        typedef typename ih_iterator::pointer pointer;

        MinMaxVector* p;
        // eltároljuk a szülő struktúra pointerét, hogy később tudjunk rá hivatkozni
        iterator( MinMaxVector* p , ih_iterator i):ih_iterator(i),p(p){}

        // ez a két operátor az, ami referencia szerint változtathatja az értéket, írjuk felül, majd viselkedjünk úgy, mintha
        // a vector iterátorai lennénk
        reference operator*()
        { 
            p->reCalc = true; 
            return ih_iterator::operator*(); 
        }

        pointer operator->()
        {
            p->reCalc = true; 
            return ih_iterator::operator->(); 
        }
    };

    // a begin és end függvények a mi megvalósított iterátorunkkal térjenek vissza
    iterator begin()
    {
        return iterator(this , data.begin() );
    }

    iterator end()
    {
        return iterator(this , data.end() );
    }
};


#endif // HEADER_INCLUDED
