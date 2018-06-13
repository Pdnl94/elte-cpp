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
    A feladat egy olyan gráf struktúra megvalósítása, mely irányított-irányítatlan is lehet
    El kell tárolni a csúcsokat, éleket (élsúllyal)
    Lekérdezhető, hogy van-e egy bizonyos súlyú él
    Lekérdezhető, hogy 2 csúcs között van-e él
    Lekérdezhető, módosítható az él súlya 2 csúccsal lekérdezve
    Lekérdezhető a csúcsok élek száma
    Irányítatlan gráfból irányított készíthető úgy, hogy az élek megkétszereződnek
*/

#include <set>
#include <map>

// 3 template paraméter, az első az a node típusa, a második az az él típusa
// a harmadik, hogy irányított, vagy irányítatlan gráfról van-e szó
template <typename Node, typename Edge, bool Directed>
class LGraph
{
    // nevezzük el a típusokat

    // legyen a nodeok típusa egy halmaznyi node
    typedef std::set < Node > Nodes;

    // legyen az élek típusa az két node-hoz rendelt Edge (két csúcshoz rendelünk egy élet)
    typedef std::map < std::pair< Node , Node > , Edge > Edges;

    // + típusok
    typedef typename Edges::const_iterator edge_const_iterator;
    typedef typename Edges::iterator edge_iterator;
    typedef typename Edges::size_type size_type;
    
    // ebbe tároljuk a csúcsokat és éleket
    Nodes nodes;
    Edges edges;

public:

    // hozzáadunk egy csúcsot
    void add( const Node& t )
    {
        nodes.insert( t );
    }

    // hozzáadunk egy élet
    void add( const Node& t , const Node& e , const Edge& k )
    {
        edges.insert( std::make_pair( std::make_pair( t , e ) , k ) );
    }

    // lekérdezzük, hogy irányított-e a gráf
    bool is_directed() const
    {
        return Directed;
    }

    // lekérdezzük, hogy létezik-e olyan él, melynek ez a "súlya" 
    bool has( const Edge& k ) const
    {
        // végigmegyünk az éleken, és a a map akt. értéke megegyezik a paraméterrel, létezik, kben nem
        for( edge_const_iterator eci = edges.begin() ; eci != edges.end() ; ++eci )
            if( eci->second == k )
                return true;

        return false;
    }

    // zárójel operátor. Visszaadjuk, hogy mi az élnek a súlya, ha létezik
    Edge operator()( const Node& t , const Node& e ) const
    {
        // keressük meg az élek között azt a kulcsot, mely e két csúcs között megy
        edge_const_iterator eci = edges.find( std::make_pair( t , e ) );
        // ha nem volt ilyen, térjünk vissza egy "invalid" élköltséggel, különben pedig az éllel
        return eci == edges.end() ? Edge() : eci->second;
    }

    // lekérhetjük, hogy hány db node-unk van
    size_type countNodes() const
    {
        return nodes.size();
    }

    // felüldefiniálva a this const-ságán a () operrátort megvalósítjuk, hogy megváltoztatható legyen
    // az élnek a súlya
    Edge& operator()( const Node& t , const Node& e )
    {
        // megkeressük, visszatérünk vele
        return edges.find( std::make_pair( t , e ) )->second;
    }

    // törlünk egy node-ot a gráfból
    void remove( const Node& t )
    {
        // a csúcsok közül töröljük
        nodes.erase(t);

        // keressünk az élek között olyat, amiben szerepel, majd töröljük
        for( edge_iterator ei = edges.begin() ; ei != edges.end() ; ++ei )
            if( ei->first.first == t || ei->first.second == t )
                edges.erase( ei-- );
    }

    // visszaadjuk, hogy hány éle van a gráfunknak
    int countEdges() const
    {
        return edges.size();
    }

    // default constructor
    LGraph(){}

    // tegyük saját magunkat, (csak más template paraméterrel) frienddé, 
    // hogy elérhető legyen "saját magunk" számára a privát adattagok
    template < typename AnNode , typename AnEdge , bool AnDirected >
    friend class LGraph;

    // majdnem copy-constructor
    // constructorba várhatunk egy ugyan olyan gráfot, csak lehet, hogy irányított, vagy irányítatlan
    // másoljuk le a csúcsokat és az éleket is
    template <bool AnDirected>
    LGraph( const LGraph < Node , Edge , AnDirected >& lg ) :
        nodes( lg.nodes ) , edges( lg.edges )
    {
        // ha a másolandó gráf irányítatlan volt, most pedig irányítottá válunk, akkor le kell másolni az éleket
        // pont a fordított irányba.
        // végigmegyünk az éleken, és ahol (N1,N2) csúcsokhoz E1-et rendeltük, oda mostmár (N2,N1) hez is E1-et fogjuk
        if( !AnDirected && Directed )
            for( edge_const_iterator ei = lg.edges.begin() ; ei != lg.edges.end() ; ++ei )
                add( ei->first.second , ei->first.first , ei->second );
    }
};

#endif // HEADER_INCLUDED
