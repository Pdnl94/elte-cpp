#ifndef ARRDECOR_H_INCLUDED
#define ARRDECOR_H_INCLUDED

// Szóval ez a vizsga megoldás távol álljon minden élőlénytől és magzatkezdeménytől.

// Figyelem! A kód öntudatlan használata bukást vonhat maga után! Érdmes valahogy megérdeklődni előtte, hogy mi mit csinál, és miért... (persze nem vizsgán)
//   Ha látsz egy typename -t, egy void -ot, vagy egy const -ot a kódban, jobb ha tudod miért van ott (és nem azért mert csak).
// ha meg neked mindegy, akkor szedd ki az összes kommentet. Egy egyszerű regex is írható rá: //.*

// kénytelen vagyok teleöklendezni a kódot ilyen (nekem kék) marhaságokkal (kommentekkel), mert különben megesz a farkas...

// szóval itt van két include:

// Az algorithm azért menő, mert abban már előre megvalósított függvények vannak, és pl ha sort, reverse, unique ... (http://www.cplusplus.com/reference/algorithm/) valamely ezek közül megvalósítandó, akkor kvázi egyszerűen és könnyen áttranszformálható a feladat egy függvényhívásra. (Persze ez félre is vezethet ha pl egy olyan ember olvassa ezt, akinek joga van beleszólni a C++ vizsgába, és ki akar veled szúrni)
#include <algorithm>

// Hmm, ez egy container. De minek ide... Szóval hogy kvázi semelyik hallgató se értse a következő mondatot:
// mivel az std::sort függvény RandomAccess iterátor koncepcióval (http://www.cplusplus.com/reference/iterator/) rendelkező iterátorokon keresztül tud csak rendezni, és az std::list-nek csak Bidirectional iterátora van, ezért egy std::list-et std::sort-al nem lehet megrendezni. De hogy egyszerűbb legyen az életünk, van az std::list::sort függvény (http://www.cplusplus.com/reference/list/list/sort), ami megrendezi helyettünk a cuccoskát
// lesz egy bazinagy elágazás arra az esetre ha list-et, vagy nem list-et rendeznénk 
#include <list>

// Basszus létre lehet hozni egy külön osztályt (FUNKTORT), ami arra képes, hogy attól függően hogy milyen paramétert adsz be neki, szépen megrendezi azt
// Azért hasznos, mert ... mert nekem ez most jelenleg így tetszik, és nincs aki megszabjon nekem bármilyen koncepciót is. 
struct Sorter {
	// hát ha valaki ezt elsőre megérti, megeszem a kalapom... (háhá úgysincs).
	template<class Container, class Comparer> // lehet több template paraméter?? És nem csak T -nek lehet elnevezni?? WTF? De miért class, miért nem typename?
	inline void operator()(Container& k, Comparer comp) const { // inline? operator() ? CONST és void??? Milyen típus az a Container, és a Comparer (van ilyen szó egyáltalán) ? :D
		std::sort(k.begin(), k.end(), comp); // mi az a 3. paraméter? Kell az oda egyáltalán?
	}; // itt egy nemkellő pontosvessző...
	
	// itt van ugyanaz, csak kicsit másképp, listára értelmezve. Csak itt meghívjuk a list::sort -ját
	template<class ListElement, class Comparer>
	inline void operator()(std::list<ListElement>& k, Comparer comp) const {
		k.sort(comp);
	}
};

// húha, ez ismerős valahonnan. Mintha már lett volna egy pár vizsgába. Nézzük csak meg az INDEX.txt -t...
// Hmm, a 3. fejezet : parameter alapjan : levő vizsgái mind ilyet dolgoznak fel. És mennyire trivik voltak.
//   itt van egy ősrégi (3 és fél éves) példa: stat_120611. Kicsit más volt a feladat, vagy mondjuk úgy, hogy nagyon, de meg van oldva végülis...
// és hasonló dolgok találhatóak meg itt is.
template<class Container, class Element = typename Container::value_type> // wtf itt egy egyenlőségjel. Ezt ki tanulta, tegye fel a kezét :)
class array_decorator { // kár, hogy ebben meg van kötve a kezem, pedig szívesen hívnám Ar_RaY_D3_CoRaT_T0R -nak
	// nincs leszármaztatás ahogy látjátok, az az ördög módszere arra, hogy szép kis dolgok történjenek a nem polimorfikus osztályokkal... (tudod akkor polimorf, ha virtuális a destruktora... vágod, nem? Ezek a szemét konténerek meg nem akaródzanak azok lenni)


	// szóval kaptunk tenplét paraméterként egy cuccot, amiről nem tudjuk hogy mi, de létrehozunk belőle egy tagváltozót. Ez fontos, mert valahova tárolnunk kell majd azt a sok szemetet, amit kapunk. És hogy mibe, azt majd kívülről megmondják. Hmm hallottatok már az adapter konténerekről?
	Container container;
	
	// public?? Eddig mi volt? 
public:

	// konstruktor. Ha nem akarsz ilyet írni magadtól, akkor nézd meg az összes konténer összes konstruktorát, tanulmányozd, és rájössz, hogy triviális mind. És még ciklus se kell hozzá
	// itt jelenleg egy tömb van átadva két paraméterként. Amit továbbadunk a Konténerünknek az inicializáló listában. (kettősponttól nyitó kapcsosig)
	// csak ezek a marha konténerek nem képesek érteni ha csak úgy továbbpasszintjuk. Viszont mindegyik képes egy iterátor párral megkonstruálódni (???). A pointerek meg a legmenőbb iterátorok, kvázi miattuk van iterátor. De miért pont így? Mi lesz, ha egy pointert meg egy számot összeadunk? De az array[size] az már nem létezik... WTF? 
	array_decorator(Element* array, int size) : container(array, array + size) {}
	
	// nem valami hatékony, de nem probléma. Könnyen leírható, és megoldja a problémát
	// na beszéljünk egy kicsit a visszatérési értékről. Amikor te valami nagyon furán .asd().fgh().jkl() módon paszíroznád össze a függvényeket, akkor a 
	//    függvénynek (pl az asd() fv) kell visszatérési érték (próbáld ki void -dal). Ennek a visszatérési értéknek olyan bigyókának kell lennie, hogy 
	//    meghívható legyen rá a fgh() függvény. De melyik ez az osztály? Hát nem az, amit épp megvalósítunk? Nem? De. Nem? De. Besenyő pistabá mindig megmondja... (https://www.youtube.com/watch?v=SFGDzHAeTrE#t=62)
	// arra, hogy miért nincsen kiírva a template paraméterei, és hogy miért referencia (és miért nem const), arra jöjj rá magadtól. :P
	array_decorator& reverse() {
		std::reverse(container.begin(), container.end()); // begin, end. Sziasztok. Ők az iterátorok. Iterátorok, Ők a tanulni vágyó egyetemisták. 
		return *this;// wtf ? Minek visszatérési érték? Mi az a this? Miért van előtte csillag??
	}
	
	// rendező cucc megbonyolítva. Hívjuk meg a másik rendező cuccot egy < operátorral (http://www.cplusplus.com/reference/functional/less/)
	// hogy miért ezzel? Mert egy rendezés általában ezt használja ha nincs paramétere. (gondolj csak a gonosz std::set -re, annak is vagy 3 template paramétere van, és azok között megtalálható ez. http://www.cplusplus.com/reference/set/set/)
	array_decorator& sort() {
		return sort(std::less<Element>());
	}

	// egyedi mi? És szerinted mit csinál?
	// miért kell container.erase ? Miért nem elég csak az std::unique?
	// MIÉRT NEM CONST?????
	array_decorator& unique() {
		container.erase(std::unique(container.begin(), container.end()), container.end());
		return *this; // ezt igazán leírhatnám
	}
	
	
	// szóval hogy legyen egy bonyolult része is a dolognak.
	//  kell egy ilyen filter nevű csodát megvalósítani. Ez kvázi felér egy std::remove_if -fel, (onnan copyztam a kódot: http://www.cplusplus.com/reference/algorithm/remove_if/), csak ez kevésbé hatékonyabb, és pl std::deque -ra úgy segfaultol(hat) mint a ház (mert a deque::erase annyira buta, hogy (lehetséges hogy) invalidálja az iterátorokat, míg a többi container csak részben. bővebben a deque oldalán)
	template<class T>
	array_decorator& filter(T pred) {
		//egyszer próbáld ki azt, hogy kiveszed innen a typename-t. Mi a francot fog kiírni a fordító?
		// azt hogy ne légy buta, te egy típusra gondolsz itt. De én (fordító) nem tudom kitalálni, hogy ez itt egy típus, vagy egy statikus változó, (vagy akár egy tagfüggvény, vagy egy tagváltozó? is lehet).
		
		typename Container::iterator first = container.begin(),
			last = container.end();

		while (first != last) {
			if (!pred(*first)) {
				container.erase(first--); // cheat magasiskolája. 
			}
			++first;
		}
		return *this;
	}
	
	// az eddigiek nem const-ok, ez meg igen. És több helyen is megtalálható...
	const Container& get() const {
		return container;
	}
	
	// áá, itt az emlegetett sort cucc, ami használja a külön osztályt. Ugye milyen trivi???
	template<class T> // hmm, nem találtam ki elsőre jobb nevet. 
	array_decorator& sort(T comp) {
		Sorter()(container, comp); // zárójel után zárójel. Menőőő 
		return *this;
	}

	// na ez durva... baráttá kell tenni magunkat. Ki az a félőrült, aki nem barátja magának?? meh.
	//   mentségére szóljon, az inteket tároló vektor nem ugyan az mint a stringeket tároló vektor...
	// milyen buta szintaxis
	template<class OtherContainer, class OtherElement>
	friend class array_decorator;
	
	
	// itt már megint miért csak egy tenplét paraméter van? nem valami konzisztens a kód...
	// mi aza swap? miért kell ennyire bonyolulttá tenni egy cserét? Miért void? Van erre pálda máshol is? Miért nem használható az std::swap?
	template<class OtherContainer>
	void swap(array_decorator<OtherContainer, Element>& other) {
		OtherContainer cp(container.begin(), container.end());
		container = Container(other.container.begin(), other.container.end()); /// WTF hívok egy sátánűzőt. Mi ez?
		other.container.swap(cp);
	}
}; // ezt meg ne hagyd le, mert rosszul jársz;


// tecccik ez a tenplét szó. Olyan template-re hasonlít, csak mégse.
// bocsánat, hogy a végére meguntam a kommentezést, de nem akartam senki agyát lefárasztani ennél jobban
// és nem szeretem, ha a megoldásom 120 sor felett van. hoopppp

#endif // ARRDECOR_H_INCLUDED
