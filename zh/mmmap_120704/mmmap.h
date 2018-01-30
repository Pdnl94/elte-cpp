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
    A feladat egy olyan Map készítése, mely tárolja az értékek közül a minimumot, maximumot
    Ha egy behelyező művelet történik, akkor eldönti, hogy felül kell-e írnia a minimumot, maximumot
    Ha lekérjük a min/max műveletekkel, akkor konstans időben kell tudnia kiszámítani, kivéve :

    Ha bármilyen módosító művelet (referencia szerinti átadás) történik, akkor újra kell számolni a következő lekérésnél
        a minimumot és a maximumot
    Ha iterátoron keresztül lekérjük (referncia szerint) az értékét.
*/


#include <map>

// két template paraméter, az egyik a kulcs, a másik a kulcshoz rendelhető érték
template <typename Key, typename T>
class MinMaxMap
{
    // nevezzük el a típusokat
    // 
    typedef std::map<Key, T> Map;
    typedef typename Map::const_iterator const_iterator;
    typedef typename Map::iterator ih_iterator;
    typedef typename Map::size_type size_type;

    // a data-ban fogjuk tárolni a map kulcs-érték párjait
    // a mine-maxe változókban a data container minimum és maximum értékéhez tartozó
    //  iterátorokat
    // a reCalc mondja meg azt, hogy újra kell-e számolnunk a minimumot-maximumot
    Map data;
    const_iterator mine, maxe;
    bool reCalc;

    // ez egy segéd függvény, ami újraszámolja a minimum-maximum helyeket, és eltárolja a mine/maxe változókban
    void reC()
    {
        // beállítjuk őket az első értékre
        mine = maxe = data.begin();

        // végigmegyünk a map-en, és az értékeket összehasonlítva minimum, és maximumkeresést végzünk az elemeken
        for( const_iterator it = ++data.begin() ; it != data.end() ; ++it )
            if( maxe->second < it->second )
                maxe = it;
            else if( it->second < mine->second )
                mine = it;

        // beállítjuk, hogy most már nem kell újra számolni
        reCalc = false;
    }
public:
    //default constructor - a mine/maxe változók invalid elemre mutatnak
    MinMaxMap() : mine( data.end() ),maxe( data.end() ),reCalc(false){}

    // ha lemásoljuk a map-et, akkor újra kell számolni az iterátorokat
    MinMaxMap( const MinMaxMap& mm ):data(mm.data)
    {
        reC();
    }

    // visszatér az adatok mennyiségével
    size_type size() const
    {
        return data.size();
    }

    // behelyez a map-be egy kulcs-érték párat
    void insert( const Key& k , const T& t )
    {
        // tegyük bele, majd visszatér az iterátorral, ahova tette
        const_iterator it = data.insert( std::make_pair( k , t ) ).first;

        // ha újra kell számolni, tegyük meg, ha nem kell, akkor döntsük el, hogy ő volt-e az első, vagy ő lesz-e a min-max
        //    ha igen, akkor írjuk felül mine/maxe-t
        if( reCalc )
            reC();
        else if( mine == data.end() )
            mine = maxe = it;
        else if( maxe->second < t )
            maxe = it;
        else if( t < mine->second )
            mine = it;
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
        return maxe->second;
    }

    T min()
    {
        if( reCalc )
        {
            reC();
        }
        return mine->second;
    }

    // max - min const függvények. Ha újra kell számolni, akkor számoljuk, de sajnos nem tudjuk ezt eltárolni (maxe/mine változókba)
    //   ezért csak lokálisan tudjuk kiszámolni a max/min értéket
    // ha nem kell, csak térjünk vissza az értékkel
    T max() const
    {
        if( reCalc )
        {
            T elem = data.begin()->second;
            for( const_iterator it = ++data.begin() ; it != data.end() ; ++it )
            {
                if( elem < it->second )
                    elem = it->second;
            }
            return elem;
        }
        return maxe->second;
    }

    T min() const
    {
        if( reCalc )
        {
            T elem = data.begin()->second;
            for( const_iterator it = ++data.begin() ; it != data.end() ; ++it )
            {
                if( it->second < elem )
                    elem = it->second;
            }
            return elem;
        }
        return mine->second;
    }

    // ha lekkérjük az elemet const módon, akkor semmi teendő, mint továbbadni
    T at( const Key& k ) const
    {
        return data.at( k );
    }


    // ha lekérjük az elemet referencia szerint, akkor beállítjuk, hogy újra kelljen számolni
    // mert a típusunkat kívülről megváltoztathatják
    // mind az 'at' , mind az operátor[]-nál , hisz mindkettő változtathat a struktúrán
    T& at( const Key& k )
    {
        reCalc = true;
        return data.at( k );
    }

    T& operator[]( const Key& k )
    {
        reCalc = true;
        return data[k];
    }

    // hozzunk létre egy dummy iterátort, ami használja a map iterátorát annyi különbséggel, hogy
    // ha lekérjük bármelyik elemet az iterátor segítségével, akkor kívülről megváltoztathatóvá
    // tesszük megintcsak a struktúrát, így majd újra kell megint számoltatni a min/max-ot
    struct iterator : ih_iterator
    {
        typedef typename ih_iterator::reference reference;
        typedef typename ih_iterator::pointer pointer;

        MinMaxMap* p;
        // eltároljuk a szülő struktúra pointerét, hogy később tudjunk rá hivatkozni
        iterator( MinMaxMap* p , ih_iterator it):ih_iterator(it),p(p){}

        // ez a két operátor az, ami referencia szerint változtathatja az értéket, írjuk felül, majd viselkedjünk úgy, mintha
        // a map iterátorai lennénk
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
