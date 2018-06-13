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
// az első az az a Node típusa
// a második az az, hogy a gráf irányított-e
template <typename Node , bool Directed >
class Graph
{
    // nevezzük el a típusokat a könnyebb használhatóság érdekében
    // egy bool mátrixban tároljuk, hogy 2 csúcs között van-e él
    typedef std::vector <bool > Row; // sor típus, vector-nyi bool elem (az összekötésekért felel)
    typedef std::vector < Row > Edges; // mátrix típus, vector-nyi sor
    typedef typename Row::size_type size_type;
    typedef typename Row::iterator iterator;

    typedef std::map < Node , size_type > NodeCont; // Nodeok leképzése a [0..N) intervallumba
    typedef typename NodeCont::const_iterator node_c_iterator; //iterátorok...
    typedef typename NodeCont::iterator node_iterator;

    // eltároljuk az élmátrixot, és a Nodeok leképző map-jét
    Edges edges;
    NodeCont nodes;
public:
    // hozzáadunk egy Node-ot
    void add( const Node& n )
    {
        // ha még a node nincs benne
        if( !nodes.count(n) )
        {
            // tegyük bele a nodeok közé, és adjuk neki a köv. indexet
            nodes[n] = nodes.size() - 1;

            // egészítsük ki a mátrixunkat (minden sor végére szúrjunk be egy elemet, majd a végére egy új sort)
            for( size_type i = 0 ; i < edges.size() ; ++i )
                edges[i].push_back( false );
            edges.push_back( Row( nodes.size() , false ) );
        }
    }
    // hozzáadunk egy élet
    void add(const Node& r , const Node& c)
    {
        // megkeressük a Node-okhoz tartozó indexet, és ha megtaláltuk
        node_c_iterator rit = nodes.find(r),
                    cit = nodes.find(c);
        if ( rit != nodes.end() && cit != nodes.end() )
        {
            // lekérjük ezeket, majd
            size_type rnum = rit->second,
                        cnum = cit->second;

            // beírjuk a mátrixunkba, hogy itt van él. Ha irányítatlan, akkor a másik irányba is
            edges[rnum][cnum] = true;
            if( !Directed )
                edges[cnum][rnum] = true;
        }
    }

    // hasonló az add -hoz, annyi, hogy itt false-ra írjuk át
    void remove(const Node& r , const Node& c)
    {
        node_c_iterator rit = nodes.find(r),
                    cit = nodes.find(c);
        if ( rit != nodes.end() && cit != nodes.end() )
        {
            size_type rnum = rit->second,
                        cnum = cit->second;

            edges[rnum][cnum] = false;
            if( !Directed )
                edges[cnum][rnum] = false;
        }
    }

    // visszatérünk a template-ként megkapott booleannel
    bool is_directed() const
    {
        return Directed;
    }

    // van-e 2 Node között él
    bool has(const Node& r , const Node& c) const
    {
        // keressük meg az indexeiket
        node_c_iterator rit = nodes.find(r),
                    cit = nodes.find(c);
        if ( rit != nodes.end() && cit != nodes.end() )
        {
            size_type rnum = rit->second,
                        cnum = cit->second;

            // ha megvan, térjünk vissza a mátrix elemével
            return edges[rnum][cnum];
        }
        return false;
    }

    // adjuk vissza a Node-ok számát
    size_type countNodes() const
    {
        return nodes.size();
    }

    // adjuk vissza az élek számát úgy, hogy a mátrixba számoljuk össze az összes booleant
    // és ha irányított, térjünk vele vissza, ha irányítatlan akkor a felével.
    size_type countEdges() const
    {
        size_type res = 0;
        for( size_type i = 0; i < edges.size() ; ++i )
        {
            for( size_type j = 0; j < edges[i].size() ; ++j )
            {
                res += edges[i][j];
            }
        }
        return Directed ? res : res / 2;
    }

    // töröljünk egy csúcsot
    void remove( const Node& n )
    {
        // keressük meg az indexet
        node_iterator it = nodes.find( n );
        if( it != nodes.end() )
        {
            size_type x = it->second;
            // kitöröljük az x. sort
            edges.erase( edges.begin() + x );

            // kitöröljük az összes (maradék) sor x. elemét (azaz az x. oszlopot)
            for( size_type i = 0; i < edges.size() ; ++i )
            {
                edges[i].erase( edges[i].begin() + x );
            }

            // kitöröljük az indexek közül ezt az értéket
            nodes.erase( it );

            // végigmegyünk a többi index között, és mindegyik, amelyik nagyobb volt mint x,
            // csökkentjük az értékét egyel (hogy az index maradjon a [0..N) intervallumban )
            for( it = nodes.begin() ; it != nodes.end() ; ++it )
            {
                if( it->second > x )
                {
                    --it->second;
                }
            }
        }
    }

    // két gráf összeadása
    Graph operator+( const Graph& tr ) const
    {
        // hozzuk létre az eredményünket a meghívott gráf alapján
        Graph tmp = *this;

        // adjuk hozzá a másik gráfban lévő nodeokat

        // kimásolva a set_difference , kis változtatással
        // mivel rendezett a map, ezért csak össze kell futtatnunk a kettőt
        node_c_iterator first1 = tr.nodes.begin(),
                        last1 = tr.nodes.end(),
                        first2 = nodes.begin(),
                        last2 = nodes.end();

        // amíg mindkettőben van, lépünk előre
        while ( first1 != last1 && first2 != last2)
        {
            // ha a key értéküknél újat találtunk, akkor hozzáadjuk az új oszlopot
            if ( first1->first < first2->first ) { tmp.add( first1->first ); ++first1; }
            // minden más esetben lépünk előrébb
            else if ( first2->first < first1->first ) ++first2;
            else { ++first1; ++first2; }
        }
        // ha maradt még a végén, hozzáadjuk az összeset
        while( first1 != last1 )
        {
            tmp.add( first1->first );
            ++first1;
        }

        // végigmegyünk tr összes élén, és hozzáadjuk, ha létezett ez az él
        for ( first1 = tr.nodes.begin() ; first1 != last1 ; ++first1 )
        {
            for ( first2 = tr.nodes.begin() ; first2 != last1 ; ++first2 )
            {
                if ( tr.has( first1->first , first2->first ) )
                {
                    tmp.add( first1->first , first2->first );
                }
            }
        }

        return tmp;
    }
};

#endif // HEADER_INCLUDED
