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
#include <map>
#include <algorithm>

// két template paramétere van,
// az első az az a típus, amivel tudjuk indexelni a mátrixunkat
// a második az az, hogy milyen típusú elemeket tárolunk el a mátrixba
template <typename Index , typename T>
class triangular_associative_matrix
{
    // nevezzük el a típusokat a könnyebb használhatóság érdekében
    typedef std::vector <T> Row; // sor típus, vector-nyi T elem
    typedef std::vector <Row> Matrix; // mátrix típus, vector-nyi sor
    typedef typename Row::size_type size_type; // index (unsinged long) típus
    typedef typename Row::reference reference; // referencia (vector<bool> miatt)
    typedef std::map < Index , size_type > IndexCont; // indexelés leképzése a [0..N) intervallumba
    typedef typename IndexCont::const_iterator index_c_iterator; //iterátorok...
    typedef typename IndexCont::iterator index_iterator;

    // a mátrix, az indexek, meg a mátrix mérete
    Matrix matrix;
    IndexCont indexes;
    size_type N;
public:
    // default constructor N-et beállítjuk 0-ra
    triangular_associative_matrix():N(0){}

    // hozzáadunk egy sor-oszlopot
    void add_row_column( const Index& in )
    {
        // adjuk először az indexekhez hozzá. Ő lesz az N. sor
        indexes.insert( std::make_pair( in , N ) );

        // az összes eddigi sorhoz hozzáadunk egy értéket
        for( size_type i = 0; i < N ; ++i )
        {
            matrix[ i ].push_back( T() );
        }
        // megnöveljük N-et;
        ++N;
        // beteszünk egy N hosszú sort a mátrixba
        matrix.push_back( Row( N ) );
    }

    // beállítjuk az r,c.et val-ra
    void set( const Index& r , const Index& c , const T& val )
    {
        index_iterator rit, cit;
        // ha mindkettőt megtaláltuk
        if ( ( ( rit = indexes.find(r) ) != indexes.end() ) && ( ( cit = indexes.find(c) ) != indexes.end() ) )
        {
            // lekérjük az értékeit (hogy hanyadik sorba-oszlopba van)
            signed long rnum = rit->second,
                        cnum = cit->second;

            // ha a felsőháromszög részben vannak, akkor lekérjük a mátrix elemét
            if( rnum >= cnum )
            {
                matrix[rnum][cnum] = val;
            }
        }

    }

    // visszatérünk, először const-al, utána referenciával
    T at(const Index& r , const Index& c) const
    {
        return (*this)(r,c);
    }

    reference at(const Index& r , const Index& c)
    {
        return (*this)(r,c);
    }


    // megkeressük az (r,c). elemet
    reference operator()(const Index& r , const Index& c)
    {
        index_iterator rit, cit;
        // ha mindkettőt megtaláltuk
        if ( ( ( rit = indexes.find(r) ) != indexes.end() ) && ( ( cit = indexes.find(c) ) != indexes.end() ) )
        {
            // lekérjük az értékeit (hogy hanyadik sorba-oszlopba van)
            signed long rnum = rit->second,
                        cnum = cit->second;

            // ha a felsőháromszög részben vannak, akkor lekérjük a mátrix elemét
            if( rnum >= cnum )
            {
                return matrix[rnum][cnum];
            }
        }
        throw "bad";
    }

    // megkeressük az (r,c). elemet
    // felüldefiniált a konstansságán, a működése ugyan az
    T operator()(const Index& r , const Index& c) const
    {
        index_c_iterator rit, cit;
        if ( ( ( rit = indexes.find(r) ) != indexes.end() ) && ( ( cit = indexes.find(c) ) != indexes.end() ) )
        {
            signed long rnum = rit->second,
                        cnum = cit->second;
            // itt nem ellenőrizzük, hogy benne van-e, mert ha nincs,
            // úgy is nem változtatott értékkel van dolgunk
            return matrix[rnum][cnum];
        }
        return T();
    }

    // két mátrix egyenlő, ha mindnük egyenlő
    bool operator==( const triangular_associative_matrix& tr ) const
    {
        return N == tr.N && indexes == tr.indexes && matrix == tr.matrix;
    }

    // két mátrix nem egyenlő, ha nem igaz, hogy egyenlőek
    bool operator!=( const triangular_associative_matrix& tr ) const
    {
        return ! ( (*this) == tr );
    }

    // kiszámolja a determinánsát (háromszögmátrix determinánsa az átló elemeinek szorzata)
    T determinant( T b ) const
    {
        for( size_type i = 0;i < N ; ++i )
        {
            b *= matrix[i][i];
        }
        return b;
    }

    // kitörlünk egy sort-oszlopot
    void erase( const Index& in )
    {
        // megkeressük, hogy hanyadik indexen található , és ha benne van, akkor
        index_iterator it = indexes.find( in );
        if( it != indexes.end() )
        {
            size_type x = it->second;
            // kitöröljük az x. sort, csökkentjük N értékét
            matrix.erase( matrix.begin() + x );
            --N;

            // kitöröljük az összes (maradék) sor x. elemét (azaz az x. oszlopot)
            for( size_type i = 0; i < N ; ++i )
            {
                matrix[i].erase( matrix[i].begin() + x );
            }

            // kitöröljük az indexek közül ezt az értéket
            indexes.erase( it );

            // végigmegyünk a többi index között, és mindegyik, amelyik nagyobb volt mint x,
            // csökkentjük az értékét egyel (hogy az index maradjon a [0..N) intervallumban )
            for( it = indexes.begin() ; it != indexes.end() ; ++it )
            {
                if( it->second > x )
                {
                    --it->second;
                }
            }
        }
    }

    // összeadás operátor
    triangular_associative_matrix operator+( const triangular_associative_matrix& tr) const
    {
        // hozzuk létre az eredményünket a meghívott mátrix alapján
        triangular_associative_matrix tmp = *this;

        // adjuk hozzá a másik mátrixban lévő oszlopokat

        // kimásolva a set_difference , kis változtatással
        // mivel rendezett a map, ezért csak össze kell futtatnunk a kettőt
        index_c_iterator first1 = tr.indexes.begin(),
                        last1 = tr.indexes.end(),
                        first2 = indexes.begin(),
                        last2 = indexes.end();

        // amíg mindkettőben van, lépünk előre
        while ( first1 != last1 && first2 != last2)
        {
            // ha a key értéküknél újat találtunk, akkor hozzáadjuk az új oszlopot
            if ( first1->first < first2->first ) { tmp.add_row_column( first1->first ); ++first1; }
            // minden más esetben lépünk előrébb
            else if ( first2->first < first1->first ) ++first2;
            else { ++first1; ++first2; }
        }
        // ha maradt még a végén, hozzáadjuk az összeset
        while( first1 != last1 )
        {
            tmp.add_row_column( first1->first );
            ++first1;
        }

        // végigmegyünk a paraméter összes mezőjén, és hozzáadjuk
        for ( first1 = tr.indexes.begin() ; first1 != last1 ; ++first1 )
        {
            for ( first2 = tr.indexes.begin() ; first2 != last1 ; ++first2 )
            {
                // mivel a set, és a constans () operátor úgy van megírva, hogy csak akkor ír bele, és csak akkor olvas ki
                // jó értéket, ha van ott valami, így ezzel végigmehetünk az összesen (attól függetlenül, hogy nem csak
                //  abban a háromszögben maradunk, amelyikben vannak igazi értékek )
                tmp.set( first1->first , first2->first ,
                    // azért kell ez a const_cast, hogy a () operátor közül a const - hívódjon meg
                    // (a nem const hibát dob, ha rossz az indexelés)
                    const_cast<const triangular_associative_matrix&>(tmp)( first1->first , first2->first ) +
                        tr( first1->first , first2->first ) );
            }
        }

        return tmp;
    }
};

#endif // HEADER_INCLUDED
