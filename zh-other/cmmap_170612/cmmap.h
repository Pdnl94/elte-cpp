#ifndef CMMAP_H_INCLUDED
#define CMMAP_H_INCLUDED

#include <map>
#include <set>

template<class Key, class Value, class Cmp = std::less<Key> >
class convenient_multimap : public std::multimap<Key, Value, Cmp> {

public:
    void add(const Key& key, const Value& value) {
        this->insert(std::make_pair(key, value));
    }
    
    void update_key(const Key& old_key, const Key& new_key) {
        Cmp cmp;
        if(!cmp(old_key, new_key) && !cmp(new_key, old_key)) {
            return;
        }
        
        while(this->find(old_key) != this->end()) {
            add(new_key, this->find(old_key)->second);
            this->erase(this->find(old_key));
        }
    }
    
    Value front() const {
        return this->begin()->second;
    }
    
    Value& front() {
        return this->begin()->second;
    }

    Value back() const {
        return (--this->end())->second;
    }

    Value& back() {
        return (--this->end())->second;
    }
    
    template<class Trans>
    void transform_keys(Trans trans) {
        convenient_multimap<Key, Value, Cmp> transformed;
        
        typename std::multimap<Key, Value, Cmp>::iterator it = this->begin();
        for(; it != this->end(); ++it) {
            transformed.add(trans(it->first), it->second);
        }
        std::swap(*this, transformed);
    }
    
    operator std::multiset<Key, Cmp>() const {
        std::multiset<Key, Cmp> result;
        typename std::multimap<Key, Value, Cmp>::const_iterator it = this->begin();
        for(; it != this->end(); ++it) {
            result.insert(it->first);
        }
        
        return result;
    }
};

#endif // CMMAP_H_INCLUDED
