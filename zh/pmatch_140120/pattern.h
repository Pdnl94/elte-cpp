

#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <string>

/*
	--
	Schaum Béla
	SCBTAAI
	EQBVGX
	--
*/


// csináljunk egy ilyen jó kis osztályt, ami az összehasonlításhoz (ötös) fog kelleni nekünk.
// ellenőrzi egy template paraméter által adott osztály segítségével, hogy a constructorba kapott
// T típus egyenlő-e az operator() - segítségével
template <typename T , typename Eq >
class equalTo
{
	const T& c;
	Eq q;
public:
	equalTo( const T& c ):c(c){}
	inline bool operator()(const T& t)
	{
		return q( c , t );
	}
};

// 2 template paraméter.
// az első a mintának az eleme
// a második az, hogy mi alapján hasonlítjuk össze az elemeket (adunk neki default értéket)

// származunk egy mátrix-ból, reprezentálva vele az egyes
// helyeken szereplő felvehető értékeket.
//  első index az az, hogy hanyadik helyen, a második az az, hogy milyen értékek vehetőek fel
//  azért vector (a belső, és nem Set), mert a set az < operátorral hasonlít össze,
//   viszont nekünk az == operátort kell összehasonlításhoz használni
template <typename CharT , typename Eq = std::equal_to<CharT> >
class pattern : public std::vector < std::vector < CharT > >
{
	// nevezzük el az ősosztályt a könnyebb hivatkozás érdekében
	typedef std::vector < std::vector < CharT > > Inher;

	// alaptípusokat örököltessünk
	typedef typename Inher::value_type value_type;
	typedef typename Inher::size_type size_type;

	// ez egy vector-nyi státusz típus
	typedef std::vector < size_type > States;

	// ebben tároljuk el, hogy az i. karakter most épp:
	//  0 - egyezés kell - a bejövő karakterek közül az egyikkel meg kell egyeznünk
	//  1 - egy tetszőleges karakter lehet
	//  2 - több tetszőleges karakter lehet
	States  states;

	// ez egy belső függvény, ezzel valósítjuk meg az ellenőrzését annak, hogy :
	//  [begin, end) intervallum bemenetre illeszkedik-e az n-dik szabályunk
	template <typename ItType>
	bool match( ItType begin , ItType end , size_type n ) const
	{
		// ha vége a szabálynak, akkor sikerült illeszkedni
		if( n == Inher::size() ) return true;
		// ha vége a bemenetnek + a következő szabály nem bármennyi karakterre illeszkedik,
		// akkor nem volt jó a bemenet
		if( begin == end && states[n] != 2 ) return false;

		// a szabály szerint eljárunk:
		switch( states[n] )
		{
			// ha 0 volt, akkor illeszkednünk kell a mátrix n. sorában lévő vector egy elemére
			// és a következőeknek is egyeznie kell
		case 0 :
			return std::find_if( Inher::at(n).begin() ,
						Inher::at(n).end() ,
						equalTo<CharT , Eq>(*begin)
					) != Inher::at(n).end() &&
				match( ++begin , end , ++n );

			// ha 1 volt, az azt jelenti, hogy bármi a bemenet, illeszkedni fogunk rá
			// így elég csak a többire ellenőrizni, hogy jó-e
		case 1 :
			return match( ++begin , end , ++n );

			// ha 2 volt, akkor bármennyire illeszkedhetünk (akár 0-ra is)!
			// végigmegyünk a lehetséges illeszkedéseken. (ha 0-ra, 1-re, 2-re ... annyival léptetjük a bemenetet)
			// ha bárhol találat van, igazzal térünk vissza
		case 2 :
			{
				++n;
				for( ItType it = begin ; it != end ; ++it )
				{
					if( match( it , end , n ) )
						return true;
				}
				return match( end , end , n );
			}
		}
		// ide elvileg sose fut, de tegyük boldoggá a fordítót
		return false;
	}

public:
	// a push_back függvények az osztálybeli objektum referenciájával térnek vissza,
	// mert így hívható meg újra rájuk a push_back.
	// a visszatérés a ( pattern* típusú ) this mutató mutatott értékével (azaz amire meg lett hívva a függvény)


	// ha jön egy elem, akkor azt tegyük be egy vector-ba, majd azt a mátrix-ba (szülő osztály)
	// állítsuk be az állapotát 0-ra (fent, hogy miért)
	pattern& push_back( const CharT& c )
	{
		states.push_back(0);
		Inher::push_back( value_type( &c , &c + 1 ) );

		return *this;
	}

	// ha bármi más jön , akkor vegyük úgy, hogy ő egy Container,
	// és másoljuk be az elemeit egy vector-ba, majd ezt tegyük be a mátrix-ba (szülő osztály)
	// állítsuk be az állapotát 0-ra (fent, hogy miért)
	template <typename Cont>
	pattern& push_back( const Cont& cont )
	{
		states.push_back(0);
		Inher::push_back( value_type( cont.begin() , cont.end() ) );

		return *this;
	}

	// ekkor egy 1-es állapotú (bármely egyezés) karakter jön
	// tegyünk a mátrixba egy üres sort (hogy az indexelésünk ne romoljon el - szinkronba legyen az állapotokkal)
	pattern& push_back_one_arbitrary()
	{
		states.push_back( 1 );
		Inher::push_back( value_type() );

		return *this;
	}

	// ekkor egy 2-es állapotú (bármely egyezés, bármennyiszer) karakter jön
	// tegyünk a mátrixba egy üres sort (hogy az indexelésünk ne romoljon el - szinkronba legyen az állapotokkal)
	pattern& push_back_many_arbitraries()
	{
		states.push_back( 2 );
		Inher::push_back( value_type() );

		return *this;
	}

	// kitörli az utolsó szabályt , és a mátrix utolsó sorát
	pattern& pop_back()
	{
		states.pop_back();
		Inher::pop_back();

		return *this;
	}

	// meghívjuk a konténer kezdő-vég intervallumára a find-fv-t, ami visszaadja az iterátort, 
	// hogy hol volt találat. Ha nem volt, akkor az end()-el tér vissza. Ekkor a statikus npos-sal térünk vissza,
	// különben a megtalált elem helyével
	template <typename Cont>
	size_type index_of( const Cont& cont ) const
	{
		typename Cont::const_iterator cit = find( cont.begin() , cont.end() );
		return cit == cont.end() ? npos : cit - cont.begin();
	}

	// egy intervallumról eldönti, hogy hanyadik elemtől kezdődően illeszkedik a minta
	// visszaadja azt az iterátort, ahol volt az illeszkedés, ha nem volt, akkor az end-et
	template <typename ItType>
	ItType find( ItType begin , ItType end ) const
	{
		while( begin != end ) // beginning
		{
			if( match ( begin , end , 0 ) )
				return begin;
			++begin;
		}
		return end;
	}

	// statikus konstans adattag, a végtelent reprezentálja (nem volt egyezés)
	static const size_type npos = static_cast<size_type>(-1);

};

#endif // HEADER_INCLUDED
