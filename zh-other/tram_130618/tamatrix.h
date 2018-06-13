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
#include <cstdlib>
#include <algorithm>

// két template paramétere van,
// az első az az a típus, amivel tudjuk indexelni a mátrixunkat
// a második az az, hogy milyen típusú elemeket tárolunk el a mátrixba
template <typename Index , typename T>
class tridiagonal_associative_matrix
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
    tridiagonal_associative_matrix():N(0){}

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
        (*this)(r,c) = val;
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

            // ha a tridiagonális részben vannak, akkor lekérjük a mátrix elemét
            if( std::abs( rnum - cnum ) < 3 )
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
    bool operator==( const tridiagonal_associative_matrix& tr ) const
    {
        return N == tr.N && indexes == tr.indexes && matrix == tr.matrix;
    }

    // két mátrix nem egyenlő, ha nem igaz, hogy egyenlőek
    bool operator!=( const tridiagonal_associative_matrix& tr ) const
    {
        return ! ( (*this) == tr );
    }


    // tridiagonális léte miatt elég csak a főátló melletti elemeket kicserélni
    void transpose()
    {
        for( size_type i = 1; i < N ; ++i )
        {
            std::swap( matrix[i][i-1] , matrix[i-1][i] );
        }
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

    // kivonás operátor
    // ( nem biztos, hogy a vizsgán elhangzottak szerint működik, mert nem egyértelmű )
    tridiagonal_associative_matrix operator-( const tridiagonal_associative_matrix& tr) const
    {
        // hozzuk létre az eredményünket
        tridiagonal_associative_matrix tmp = *this;

        // nem egyértelmű, hogy melyik oszlopoknak-soroknak kell megmaradnia
        // és hogy hogy változik az indexelés

        // végigmegyünk a mátrixon (az indexük szerint),
        // és kivonjuk azon értékeket, amelyek közösen megjelentek mindkettő struktúrában
        for( index_iterator it1 = tmp.indexes.begin() ; it1 != tmp.indexes.end() ; ++it1 )
        {
            for( index_iterator it2 = tmp.indexes.begin() ; it2 != tmp.indexes.end() ; ++it2 )
            {
                tmp( it1->first , it2->first ) -= tr( it1->first , it2->first );
            }
        }

        return tmp;
    }
};

#endif // HEADER_INCLUDED
