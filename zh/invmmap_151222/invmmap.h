#ifndef INVMMAP_H
#define INVMMAP_H

#include <map>

// Kérésre származtatás nélkül

template<class Key, class Value, class Compare = std::less<Key>, class InvCompare = std::less<Value> >
class invertable_multimap {
    typedef std::multimap<Key, Value, Compare> Container;
    
    Container container;
public:
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::iterator iterator;

    template<class OtherCompare>   
    invertable_multimap(const std::multimap<Key, Value, OtherCompare>& elems) : container(elems.begin(), elems.end()) {}
    
    void insert(const Key& key, const Value& value) {
        container.insert(std::make_pair(key, value));
    }

    invertable_multimap<Value, Key, InvCompare, Compare> inverse() const {
    	std::multimap<Value, Key, InvCompare> result;
        const_iterator it = container.begin();
        while(it != container.end()) {
            result.insert(std::make_pair(it->second, it->first));
            ++it;
        }
        
        return result;
    }
    
    invertable_multimap<Value, Key, InvCompare, Compare> operator~() const {
        return inverse();
    }
    
    Value& operator()(const Key& k, std::size_t n) {
    	iterator it = container.lower_bound(k);
    	std::advance(it, n);
    	return it->second;
    }
    
    const Value& operator()(const Key& k, std::size_t n) const {
    	const_iterator it = container.lower_bound(k);
    	std::advance(it, n);
    	return it->second;
    }
    
    std::size_t count(const Key& k) const {
    	return container.count(k);
    }
};

#endif // INVMMAP_H
