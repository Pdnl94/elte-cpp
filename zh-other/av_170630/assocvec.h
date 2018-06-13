#ifndef ASSOCVEC_H_INCLUDED
#define ASSOCVEC_H_INCLUDED

#include <vector>
#include <algorithm>
#include <map>

template<class Key, class Val, class Cmp = std::less<Key> >
class associate_vector_view {
	std::vector<Val>& vec;
	std::map<Key, int, Cmp> map;
public:
	associate_vector_view(std::vector<Val>& vec) : vec(vec) {}
	
	void associate(Key key, Val val) {
		map[key] = std::find(vec.begin(), vec.end(), val) - vec.begin();
	}
	
	const Val& get(Key key) const {
		return vec[map.find(key)->second];
	}
	
	Val& operator[](Key key) {
		if(map.count(key)) {
			return vec[map[key]];
		}
		map[key] = vec.size();
		vec.push_back(Val());
		return vec.back();
	}
	
	void erase(Key key) {
		if(map.count(key)) {
			vec.erase(vec.begin() + map[key]);
			map.erase(key);
		}
	}
	
	typename std::vector<Val>::iterator find(Key key) {
		return map.count(key) ? vec.begin() + map[key] : vec.end();
	}
	
	void update_key(Key from, Key to) {
		if(map.count(from)) {
			map[to] = map[from];
			map.erase(from);
		}
	}
	
	template<class OthCmp>
	operator std::map<Key, Val, OthCmp>() const {
		std::map<Key, Val, OthCmp> result;
		typename std::map<Key, int, Cmp>::const_iterator it = map.begin();
		
		while(it != map.end()) {
			result[it->first] = vec[it->second];
			++it;
		}
		return result;
	}
};

#endif // ASSOCVEC_H_INCLUDED