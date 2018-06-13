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

// 3 template paraméter
//  - első, a Node típusa
//  - második az él súlyának típusa
//  - harmadik, hogy irányított-e a gráf
template <typename NodeType, typename EdgeType , bool IsDirected>
class WGraph
{
    // tároljuk a gráfot egy map-nyi map-ban, ahol az összes létező csúcsnak létezik szomszédsági map-je,
    // amiben csak akkor van érték, ha van él a két csúcs között. Ha van, akkor az lekérhető a második indexelésből
    typedef std::map < NodeType , EdgeType > ConnectTo;
    typedef std::map < NodeType , ConnectTo> Graph;
    typedef typename Graph::size_type size_type;
    typedef typename Graph::iterator g_iterator;
    typedef typename Graph::const_iterator g_c_iterator;
    typedef typename ConnectTo::iterator c_iterator;
    typedef typename ConnectTo::const_iterator c_c_iterator;

    Graph g;
public:
    // hozzáadunk egy csúcsot
    void add( const NodeType& n )
    {
        g[n];
    }

    // hozzáadunk egy élet 
    void add( NodeType f , NodeType t , const EdgeType& e )
    {
        // ha irányítatlan, és az első csúcs nagyobb, akkor cseréljük ki őket
        if( !IsDirected && t < f ) std::swap( f , t );

        // ha még nem léteztek a csúcsok, hozzuk létre őket, majd írjuk be az élsúlyt
        g[t];
        g[f][t] = e;
    }

    // térjünk vissza a template paraméterrel
    bool is_directed() const
    {
        return IsDirected;
    }

    // van-e 2 node között él
    // lekérjük az első (irányítatlanba a kisebb) csúcsból induló éleket, 
    // és megnézzük, hogy tartalmazza-e a másikat
    bool has( NodeType f , NodeType t ) const
    {
        if( !IsDirected && t < f ) std::swap( f , t );
        return g.find(f)->second.count(t);
    }

    // lekérjük az első (irányítatlanba a kisebb) csúcsból induló éleket, 
    // és megnézzük, hogy tartalmazza-e a másikat
    // ha igen, visszatérünk az él súlyával
    EdgeType weight( NodeType f , NodeType t ) const
    {
        if( !IsDirected && t < f ) std::swap( f , t );
        if( has( f , t ) )
        {
            return g.find(f)->second.find(t)->second;
        }
        return EdgeType();
    }

    // lekérjük az első (irányítatlanba a kisebb) csúcsból induló éleket, 
    // és megnézzük, hogy tartalmazza-e a másikat
    // ha igen, visszatérünk az él súlyával
    //  referencia szerint
    EdgeType& weight( NodeType f , NodeType t )
    {
        if( !IsDirected && t < f ) std::swap( f , t );
        if( has( f , t ) )
        {
            return g.find(f)->second.find(t)->second;
        }
        throw "";
    }

    // törlünk egy élet. Ha volt benne, kiszedjük
    void remove( NodeType f , NodeType t )
    {
        if( !IsDirected && t < f ) std::swap( f , t );
        if( has( f , t ) )
        {
            g[f].erase( g[f].find(t) );
        }
    }

    // végigmegyünk az összes csúcs mapjén, és összeszámoljuk az élek számát
    size_type countEdges() const
    {
        size_type res = 0;
        for( g_c_iterator it = g.begin() ; it != g.end() ; ++it )
        {
            res += it->second.size();
        }
        return res;
    }

    // törlünk egy Node-ot
    // először az ő szomszédjait, majd végigmegyünk a többi node-on,
    // és ha valakihez hozzá van kötve, akkor kiszedjük
    void remove( const NodeType& n )
    {
        g.erase( g.find( n ) );
        for( g_iterator it = g.begin() ; it != g.end() ; ++it )
        {
            c_iterator cc = it->second.find( n );
            if( cc != it->second.end() )
                it->second.erase( cc );
        }
    }

    // visszatérünk egy olyan gráffal, amelyben csak a paraméterként megkapott Node élei szerepelnek
    WGraph operator[]( const NodeType& n )
    {
        WGraph tmp = *this;

        // ami után lemásoltuk magunk menjünk végig az össszes csúcshoz tartozó élen
        for( g_iterator it = tmp.g.begin() ; it != tmp.g.end() ; ++it )
        {
            // ha a keresett csúcsról lenne szó, lépjünk tovább
            if( it->first == n ) continue;

            // ha nem találtuk meg a csúcsot a szomszédok között, akkor csak töröljük az éleket
            if( it->second.find( n ) == it->second.end() )
            {
                it->second.clear();
            }
            else // különben mentsük le a hozzánk tartozó él súlyát, töröljük az összes többit, majd írjuk vissza
            {
                EdgeType et = it->second[n];
                it->second.clear();
                it->second[n] = et;
            }
        }
        return tmp;
    }
};


#endif // HEADER_INCLUDED
