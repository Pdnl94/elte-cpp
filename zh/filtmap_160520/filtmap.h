#ifndef FILTMAP_H
#define FILTMAP_H

#include <map>

template<class Key, class Value, class Filter, class Comp = std::less<Key> >
class filterable_map {
	std::map<Key, Value, Comp> container;
	bool filtered;
	Filter filter;
	
	typedef typename std::map<Key, Value, Comp>::const_iterator const_iterator;
public:
	filterable_map() : filtered(false) {}

	void insert(const Key& key, const Value& val) {
		container.insert(std::make_pair(key, val));
	}
	
	void set_filter_on() {
		filtered = true;
	}
	
	void set_filter_off() {
		filtered = false;
	}
	
	int size() const {
		if(filtered) {
			// from std::count_if
			const_iterator first = container.begin(),
				last = container.end();

			int ret = 0;
			for (; first != last; ++first) {
				if (!filter(first->first)) { // first->first is the key - filtered, if filter says OK -> if NOK then count
					++ret;
				}
			}
			return ret;
		}
		
		return container.size();
	}
	
	int count(const Key& key) const {
		if(filtered && filter(key)) { // if filtered then count = 0
			return 0;
		}
		return container.count(key);
	}
	
	Value& at(const Key& key) {
		return container[key];
	}
	
	const Value& at(const Key& key) const {
		return container.find(key)->second;
	}
	
	
	operator std::map<Key, Value, Comp>() const {
		if(filtered) {
			std::map<Key, Value, Comp> cpy;
			// from std::copy_if (C++11)
			const_iterator first = container.begin(),
				last = container.end();

			while (first != last) {
				if (!filter(first->first)) // like in size()
					cpy.insert(*first); // *d_first++ =  is now an insert (like std::inserter iterator)
				first++;
			}
			return cpy; // return with the map
		}
	
		return container;
	}
};

#endif // FILTMAP_H
