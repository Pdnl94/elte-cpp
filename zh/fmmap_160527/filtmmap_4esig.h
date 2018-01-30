#ifndef FILTMMAP_H
#define FILTMMAP_H

#include <map>
#include <vector>

template<class Key, class Value, class KeyFilter, class ValueFilter>
class filterable_multimap {
	std::map<Key, std::vector<Value> > container;
	bool key_filter_is_on, value_filter_is_on;
	KeyFilter key_filter;
	ValueFilter value_filter;
	
	typedef typename std::map<Key, std::vector<Value> >::const_iterator map_const_iterator;
public:
	filterable_multimap() : key_filter_is_on(false), value_filter_is_on(false) {}

	void insert(const Key& key, const Value& value) {
		container[key].push_back(value);
	}
	
	void set_value_filter_on() {
		value_filter_is_on = true;
	}
	
	void set_value_filter_off() {
		value_filter_is_on = false;
	}
	
	int count(const Key& key) const {
		if(key_filter_is_on && key_filter(key)) {
			return 0;
		}
		map_const_iterator values = container.find(key);
		if(values == container.end()) {
			return 0;
		}
		
		return value_filter_is_on
			? std::count_if(values->second.begin(), values->second.end(), std::not1(value_filter))
			: values->second.size();
	}
	
	void set_key_filter_on() {
		key_filter_is_on = true;
	}
	
	void set_key_filter_off() {
		key_filter_is_on = false;
	}
	
	int size() const {
		// std::accumulate
		map_const_iterator first = container.begin(),
							last = container.end();
		int init = 0;
		for (; first != last; ++first) {
			init += count(first->first);
		}
		return init;
	}
	
	Value& operator()(const Key& key, int count) {
		return container[key][count];
	}
	
	const Value& operator()(const Key& key, int count) const{
		return container.find(key)->second[count];
	}
};

#endif // FILTMMAP_H
