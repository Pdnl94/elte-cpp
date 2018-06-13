#ifndef FILTMMAP_H
#define FILTMMAP_H

#include <map>
#include <vector>

// std::next (c++11)
template<class ForwardIt>
ForwardIt next(ForwardIt it, typename std::iterator_traits<ForwardIt>::difference_type n = 1) {
	std::advance(it, n);
	return it;
}

template<class Key, class Value, class KeyFilter, class ValueFilter>
class filterable_multimap {
	std::multimap<Key, Value> container;
	bool key_filter_is_on, value_filter_is_on;
	KeyFilter key_filter;
	ValueFilter value_filter;
	
	typedef typename std::multimap<Key, Value>::iterator map_iterator;
	typedef typename std::multimap<Key, Value>::const_iterator map_const_iterator;
public:
	filterable_multimap() : key_filter_is_on(false), value_filter_is_on(false) {}

	void insert(const Key& key, const Value& value) {
		container.insert(std::make_pair(key, value));
	}
	
	void set_value_filter_on() {
		value_filter_is_on = true;
	}
	
	void set_value_filter_off() {
		value_filter_is_on = false;
	}
	
	int count(const Key& key) const {
		std::pair<map_const_iterator, map_const_iterator> range = container.equal_range(key);
		return std::distance(const_iterator(this, range.first), const_iterator(this, range.second));
	}
	
	void set_key_filter_on() {
		key_filter_is_on = true;
	}
	
	void set_key_filter_off() {
		key_filter_is_on = false;
	}
	
	int size() const {
		return std::distance(begin(), end());
	}
	
	Value& operator()(const Key& key, int count) {
		map_iterator mutable_it = container.lower_bound(key);
		return next(mutable_it, std::distance<map_const_iterator>(mutable_it, next(const_iterator(this, mutable_it), count)))->second;
	}
	
	const Value& operator()(const Key& key, int count) const {
		return next(const_iterator(this, container.lower_bound(key)), count)->second;
	}
	
	class const_iterator : public map_const_iterator {
		const filterable_multimap* parent;
	public:
		bool is_good() const {
			return parent->container.end() == *this || (
				!(parent->key_filter_is_on && parent->key_filter((*this)->first)) && 
				!(parent->value_filter_is_on && parent->value_filter((*this)->second)));
		}
	
		const_iterator(const filterable_multimap* parent, map_const_iterator it) : map_const_iterator(it), parent(parent) {
			if(!is_good()) {
				++*this;
			}
		}
		
		const_iterator& operator++() {
			do {
				map_const_iterator::operator++();
			} while(!is_good());
			return *this;
		}
	};
	
	const_iterator begin() const {
		return const_iterator(this, container.begin());
	}

	const_iterator end() const {
		return const_iterator(this, container.end());
	}
};

#endif // FILTMMAP_H
