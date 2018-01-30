#ifndef MAPUTIL_H
#define MAPUTIL_H

#include <map>

template<class Key, class Value, class Comp = std::less<Key> >
class map_util {
	typedef std::map<Key, Value, Comp> MapType;
	typedef typename MapType::iterator iterator;

	MapType* ptr;
public:
	map_util(MapType& map) : ptr(&map) {}
	
	void use(MapType& map) {
		ptr = &map;	
	}

	void shift(std::size_t count = 1) {
		iterator first = ptr->begin(),
				middle = ptr->begin(),
				last = ptr->end();

		// beállítjuk a "középső elemet" (ahonnan kezdve forgatnunk kell)
		// figyeljünk arra, hogy lehet hogy többet forgatnánk az elemek számánál
		std::advance(middle, ptr->size() - count % ptr->size());
		
		// ha nem kell forgatnunk semmit, akkor hát ne tegyük meg
		if(middle == last) return;
		
		// std::rotate kimásolva (http://www.cplusplus.com/reference/algorithm/rotate/)
		// nem a teljes (*) <kulcs, érték> párokat, hanem csak a (->second) értékéket cseréljük fel
		iterator next = middle;
		while(first != next) {
			std::swap(first++->second, next++->second);
			if(next == last) next = middle;
			else if(first == middle) middle = next;
		}
	}
	
	void erase(const Value& val) {
		return erase_if(std::bind1st(std::equal_to<Value>(), val));
	}
	
	void operator>>(std::size_t count) {
		return shift(count);
	}
	
	template<class T>
	void erase_if(T fun) {
		iterator it = ptr->begin();
		while(it != ptr->end()) {
			if(fun(it->second)) {
				ptr->erase(it++);
			}
			else {
				++it;
			}
		}
	}
};

#endif // MAPUTIL_H
