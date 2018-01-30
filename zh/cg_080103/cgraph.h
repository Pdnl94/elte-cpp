#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

#include <map>
#include <vector>

// 3 template paraméter
//  - első, a Node típusa
//  - második a csúcshoz rendelt típus
//  - harmadik, hogy irányított-e a gráf
template <typename NodeType, typename NodeMark , bool Directed>
class CGraph
{
    // nevezzük el a típusokat a könnyebb használhatóság érdekében
    // egy bool mátrixban tároljuk, hogy 2 csúcs között van-e él
    typedef std::vector <bool > Row; // sor típus, vector-nyi bool elem (az összekötésekért felel)
    typedef std::vector < Row > Edges; // mátrix típus, vector-nyi sor
    typedef typename Row::size_type size_type;
    typedef typename Row::iterator iterator;

    typedef std::map < NodeType , size_type > NodeCont; // Nodeok leképzése a [0..N) intervallumba
    typedef typename NodeCont::const_iterator node_c_iterator; //iterátorok...
    typedef typename NodeCont::iterator node_iterator;
    typedef std::map < NodeType , NodeMark > Node_Mark; // Nodeokhoz rendelt érték
    typedef typename Node_Mark::const_iterator nodem_c_iterator; //iterátorok...
    typedef typename Node_Mark::iterator nodem_iterator;

    // eltároljuk az élmátrixot, és a Nodeok leképző map-jét és a node megjelölést
    Edges edges;
    NodeCont nodes;
    Node_Mark mark;

public:

    // hozzáadunk egy Node-ot
    void add( const NodeType& n , const NodeMark& m )
    {
        // ha még a node nincs benne
        if( !nodes.count(n) )
        {
            // tegyük bele a nodeok közé, és adjuk neki a köv. indexet
            nodes[n] = nodes.size() - 1;
            // tegyük bele a mark-ok közé is
            mark[n] = m;

            // egészítsük ki a mátrixunkat (minden sor végére szúrjunk be egy elemet, majd a végére egy új sort)
            for( size_type i = 0 ; i < edges.size() ; ++i )
                edges[i].push_back( false );
            edges.push_back( Row( nodes.size() , false ) );
        }
    }

    // hozzáadunk egy élet
    void add(const NodeType& r , const NodeType& c)
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
            if( !Directed  && rnum > cnum ) std::swap( rnum , cnum );
            edges[rnum][cnum] = true;
        }
    }

    // visszatérünk a template-ként megkapott booleannel
    bool is_directed() const
    {
        return Directed;
    }

    // van-e 2 Node között él
    bool has(const NodeType& r , const NodeType& c) const
    {
        // keressük meg az indexeiket
        node_c_iterator rit = nodes.find(r),
                    cit = nodes.find(c);
        if ( rit != nodes.end() && cit != nodes.end() )
        {
            size_type rnum = rit->second,
                        cnum = cit->second;

            // Ha irányítatlan, akkor a másik irányba is
            if( !Directed  && rnum > cnum ) std::swap( rnum , cnum );
            // ha megvan, térjünk vissza a mátrix elemével
            return edges[rnum][cnum];
        }
        return false;
    }

    // számoljuk meg, hogy hány csúcs van a paraméterként kapott jelzéssel ellátva
    size_type count( const NodeMark& nm )
    {
        size_type res = 0;

        // végigmegyünk a mark-okon, és a az érték megegyezik a paraméterrel, akkor növeljük az eredményt
        for( nodem_iterator it = mark.begin() ; it != mark.end() ; ++it )
            if( it->second == nm )
                ++res;

        return res;
    }

    // visszaadjuk a node jelzését referencia szerint
    NodeMark& operator[]( const NodeType& n )
    {
        return mark[n];
    }

    // visszaadjuk a node jelzését konstans módon
    NodeMark operator[]( const NodeType& n ) const
    {
        return mark.find( n )->second;
    }

    // adjuk vissza a Node-ok számát
    size_type countNodes() const
    {
        return nodes.size();
    }

    // adjuk vissza az élek számát úgy, hogy a mátrixba számoljuk össze az összes booleant
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
        return res;
    }

    // tegyük frienddé a saját osztályunkat, amit másképp template-sítettek
    template <typename A , typename B , bool C>
    friend class CGraph;

    // alkossuk meg azt az operátort, mely képes az irányítatlan gráfból irányítottat - és fordítva csinálni
    operator CGraph< NodeType, NodeMark , !Directed>()
    {
        // másoljunk le mindent
        CGraph< NodeType, NodeMark , !Directed> res;
        res.edges = edges;
        res.nodes = nodes;
        res.mark = mark;

        // az összes i,j csúcs közötti párra, ha volt odafele él, akkor csináljunk visszafele is.
        // ha irányított volt, akkor vigyük a felső háromszögbe
        for( size_type i = 0; i < res.edges.size() ; ++i )
        {
            for( size_type j = i; j < res.edges[i].size() ; ++j )
            {
                if( !Directed )
                    res.edges[j][i] = res.edges[i][j];
                else
                {
                    res.edges[i][j] = ( res.edges[j][i] || res.edges[i][j] );
                    res.edges[j][i] = false;
                }
            }
        }
        return res;

    }
};

#endif // HEADER_INCLUDED
