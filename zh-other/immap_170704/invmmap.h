#ifndef INVMMAP_H_INCLUDED
#define INVMMAP_H_INCLUDED

#include <map>

template<class T, class Cmp = std::less<T> >
class invertable_multimap {
	std::multimap<T, T, Cmp> map;
public:
	void insert(T key, T val) {
		map.insert(std::make_pair(key, val));
	}
	
	void invert(T key) {
		typename std::multimap<T, T, Cmp>::iterator it = map.begin();
		while(it != map.end()) {
			if(it->first == key) {
				insert(it->second, key);
				map.erase(it++);
			} else {
				++it;
			}
		}
	}
	
	int count(T key) const {
		return map.count(key);
	}
	
	void invert() {
		std::multimap<T, T, Cmp> new_map;
		typename std::multimap<T, T, Cmp>::iterator it = map.begin();
		while(it != map.end()) {
			new_map.insert(std::make_pair(it->second, it->first));
			++it;
		}
		std::swap(map, new_map);
	}
	
	void erase(T key) {
		map.erase(key);
	}
	
	template<class Tr>
	void transform_key(Tr tr) {
		std::multimap<T, T, Cmp> new_map;
		typename std::multimap<T, T, Cmp>::iterator it = map.begin();
		while(it != map.end()) {
			new_map.insert(std::make_pair(tr(it->first), it->second));
			++it;
		}
		std::swap(map, new_map);
	}
	
	template<class Tr>
	void transform_value(Tr tr) {
		std::multimap<T, T, Cmp> new_map;
		typename std::multimap<T, T, Cmp>::iterator it = map.begin();
		while(it != map.end()) {
			new_map.insert(std::make_pair(it->first, tr(it->second)));
			++it;
		}
		std::swap(map, new_map);
	}
	
	template<class OthT, class OthCmp>
	friend class invertable_multimap;
	
	template<class OthCmp>
	void operator+=(const invertable_multimap<T, OthCmp>& oth) {
		typename std::multimap<T, T, OthCmp>::const_iterator it = oth.map.begin();
		while(it != oth.map.end()) {
			insert(it->first, it->second);
			++it;
		}		
	}
};

#endif // INVMMAP_H_INCLUDED