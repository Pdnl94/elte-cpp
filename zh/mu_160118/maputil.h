#ifndef MAPUTIL_H
#define MAPUTIL_H

// ezt a vizsgát úgy csináltam meg, hogy direkt nem használtam beépített függvényeket, hanem kifejtettem őket.

#include <map>
template<class Key, class Value, class Comparator = std::less<Key> >
class map_util {
	typedef std::map<Key, Value, Comparator> Container;
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;
	
	Container& container; // Az eddigi vizsgákhoz képest a különbség az, hogy most referenciát!!!! kell tárolni
public:
	map_util(Container& container) : // a referenciának kötelező értéket adni a konstruktor inicializáló listájában!
		container(container) {}
		
	map_util& reverse() { // std::reverse a map második komponensein
		iterator first = container.begin(), last = container.end();
		for(;first != last && first != --last; ++first) {
			std::swap(first->second, last->second);
		}
		return *this;
	}
	
	int count(const Value& v) const { // std::count a map második komponensein
		const_iterator first = container.begin(), last = container.end();
		int counter = 0;
		for(; first != last; ++first) {
			if(first->second == v) {
				++counter;
			}
		}
		return counter;
	}
	
	map_util& unique() { // std::unique ( + erase) a map második komponensein
		iterator first = container.begin(), last = container.end();
		
		if (first != last) {
			for(iterator result = first; ++first != last; result = first) {
				if (result->second == first->second) {
					container.erase(first--);
				}
			}
		}
		return *this;
	}
	
	const_iterator find(const Value& v) const { // std::find a map második komponensein
		const_iterator first = container.begin(), last = container.end();
		for(; first != last; ++first) {
			if(first->second == v) {
				return first;
			}
		}
		return last;
	}
	
	map_util& sort() { // sort funktor nélkül -> std::less
		return sort(std::less<Value>());
	}
	
	template<class ValueComarator>
	map_util& sort(ValueComarator comparator) { // sort funktorral. négyzetes megvalósítás az érthetőség kedvéért
		iterator first = container.begin(), last = container.end();
		
		for(; first != last; ++first) {
			iterator checker = first;
			for(++checker; checker != last; ++checker) {
				if(!comparator(first->second, checker->second)) {
					std::swap(first->second, checker->second);
				}
			}
		}
		return *this;
	}
};

#endif // MAPUTIL_H
