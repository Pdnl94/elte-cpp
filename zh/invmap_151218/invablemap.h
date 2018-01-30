#ifndef INVABLEMAP_H
#define INVABLEMAP_H

#include <map>

template<class Key, class Value, class Compare = std::less<Key>, class InvCompare = std::less<Value> >
class invertable_map : public std::map<Key, Value, Compare> {
    typedef std::map<Key, Value, Compare> Base;
public:
    typedef typename Base::const_iterator const_iterator;
    using Base::operator[];
    
    void insert(const Key& key, const Value& value) {
        Base::insert(std::make_pair(key, value));
    }

    invertable_map<Value, Key, InvCompare, Compare> inverse() const {
        invertable_map<Value, Key, InvCompare, Compare> result;
        const_iterator it = Base::begin();
        while(it != Base::end()) {
            result.insert(it->second, it->first);
            ++it;
        }
        
        return result;
    }
    
    invertable_map<Value, Key, InvCompare, Compare> operator-() const {
        return inverse();
    }
    
    Value operator[](const Key& key) const {
        const_iterator it = Base::find(key);
        return it == Base::end() ? Value() : it->second;
    }
};

#endif // INVABLEMAP_H
