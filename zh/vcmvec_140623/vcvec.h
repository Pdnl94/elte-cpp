#ifndef VCVEC_H_INCLUDED
#define VCVEC_H_INCLUDED

/*
    --
    Schaum Béla
    SCBTAAI
    EQBVGX
    --
*/

/*
    A feladat egy olyan verziókezelt vectort létrehozni, mely tárolja a verziók mellé azon felhasználói üzeneteket, melyek
    leírják a verzióban lévő változtatásokat.
    A verziókból ezek lekérdezhetőek 
    ( + előző funkcionalitások - commit , update, revert )
*/

#include <vector>
#include <algorithm>

// egy template paraméter
// származunk egy vektornyi T típusú paraméterből
template <typename T>
class version_controlled_vector : public std::vector< T >
{
    // ebből származunk, nevezzük el Inher-nek
    typedef std::vector< T > Inher;

    // egy vektornyi belőlünk, ez a mentések típusa
    typedef std::vector< Inher > Saves;
    // amik a commitokat jelentik

    // typedef-eljük a size_type-ot, hogy egyszerűbben tudjuk használni
    typedef typename Inher::size_type size_type;

    // egy ilyenbe tároljuk el azt, hogy az i. commitnak mi az üzenete (mi a tartalma)
    // a commit számmal indexelünk
    typedef std::vector < std::string > CommitMessages;
    typedef typename CommitMessages::const_reverse_iterator comm_const_reverse_iterator;


    Saves v; // mentések
    CommitMessages cms; // commit üzenetek
public:
    // constructor, 2 paraméter, az egyik a kezdeti hossza a vectornak
    // a második, hogy milyen kezdőértékkel töltse fel a kezdeti hosszt
    // átadjuk a szülőosztálynak
    version_controlled_vector( size_type init_length = 0 , const T& init_val = T() ) :
            Inher( init_length , init_val ){}

    // commit :
    // a meglévő dolgokat elmentjük a mentéseink közé
    // de csak akkor, ha volt változás ( azaz az utolsó mentéssel nem egyezünk meg )! ( vagy ha még nem volt semmi eddig )
    // visszatérünk a commit számával ( 0-tól indexelünk, ezért a -1 )
    // alapból egy commit message legyen üres
    size_type commit( std::string cm = "" )
    {
        if( !v.size() || v.back() != *this )
        {
            // a mentések közé tesszük magunk, és a commitmessagesbe elemntjük a szöveget
            v.push_back( *this );
            cms.push_back( cm );
        }
        return v.size() - 1;
    }

    // visszatérünk egy előző verzióra, a mentés számából visszakeressük,
    // és egyenlővé teszük magunkkal (azaz az öröklődött osztályunkkal)
    void update(size_type n)
    {
        this->Inher::operator=( v[n] );
    }

    // lekérjük az n. commit üzenetet
    std::string get_commit_message( size_type n ) const
    {
        return cms[n];
    }

    // visszatérünk a legutolsó mentésünkre (ha volt ; ha nem volt, kiürítjük a vektort)
    void revert()
    {
        if( v.size() )
            this->Inher::operator=( v.back() );
        else
            this->Inher::clear();
    }

    // visszaadjuk a Commit üzeneteket a kezdetitől és végpontokig
    CommitMessages diff( size_type from , size_type to ) const
    {
        // létrehozunk egy temporálist, aminek átadunk 2 iterátort, a kezdetit, meg a vég utánit egyel
        // ezt szépen le fogja másolni
        return CommitMessages( cms.begin() + from , cms.begin() + to + 1 );
    }

    // kicserélünk 2 verzió kezelt vectort - az összes tagmezőjével együtt
    void swap( version_controlled_vector<T>& an )
    {
        this->Inher::swap( an );
        an.v.swap( v );
        an.cms.swap( cms );
    }

    // lekérjük az utolsó olyan reviziószámot, amiben szerepel a paraméterként megadott string
    size_type get_latest_revision_number( std::string cm ) const
    {
        // végigmegyünk az intervallumon, és a string beépített find-jét használva
        // ha visszaad egy nem "végtelen" pozíciót, akkor visszatérünk azzal
        // hogy mennyire vagyunk az iterálással a végéig ( mivel visszafele megyünk (reverse) )
        for( comm_const_reverse_iterator it = cms.rbegin() ; it != cms.rend() ; ++it )
            if( it->find( cm ) != std::string::npos )
                return cms.rend() - it - 1;
        // ha nem találtunk egy ilyet se, térjünk vissza "végtelennel"
        return std::string::npos;
    }
};

#endif // VCVEC_H_INCLUDED
