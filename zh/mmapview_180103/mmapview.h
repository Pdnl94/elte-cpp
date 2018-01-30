#ifndef MMAPVIEW_H_INCLUDED
#define MMAPVIEW_H_INCLUDED

#include <map>
#include <vector>

template<class Key, class Value>
class multimap_view {
    std::vector<std::map<Key, Value>*> maps;
public:
    void add(std::map<Key, Value>& key) {
        maps.push_back(&key);
    }
    
    std::size_t count(const Key& key) const {
        std::size_t result = 0;
        for (std::size_t i = 0; i < maps.size(); ++i) {
            result += maps[i]->count(key);
        }
        return result;
    }
    
    std::size_t erase(const Key& key) {
        std::size_t result = 0;
        for (std::size_t i = 0; i < maps.size(); ++i) {
            result += maps[i]->erase(key);
        }
        return result;    
    }
    
    void remove(const std::map<Key, Value>& map) {
        maps.erase(
            std::remove(maps.begin(), maps.end(), &map),
            maps.end());
    }
    
    std::size_t size() const {
        std::size_t result = 0;
        for (std::size_t i = 0; i < maps.size(); ++i) {
            result += maps[i]->size();
        }
        return result;
    }

    typedef typename std::map<Key, Value>::iterator MapIt;
    
    template<class Cmp>
    operator std::multimap<Key, Value, Cmp>() const {
        std::multimap<Key, Value, Cmp> result;
        for (std::size_t i = 0; i < maps.size(); ++i) {
            for (MapIt it = maps[i]->begin(); it != maps[i]->end(); ++it) {
                result.insert(*it);
            }
        }
        return result;
    }
    
    class iterator : public std::iterator<std::input_iterator_tag, 
            std::pair<Key, Value> > {
            
        multimap_view<Key, Value>* parent;
        std::size_t map_index;
        MapIt ptr;
        
        void find_next_ptr() {
            ptr = MapIt();
            for (; map_index < parent->maps.size(); ++map_index) {
                if (parent->maps[map_index]->size() > 0) {
                    ptr = parent->maps[map_index]->begin();
                    break;
                }
            }    
        }
    public:
        iterator(multimap_view<Key, Value>* parent, bool begin) : 
            parent(parent), map_index(begin ? 0 : parent->maps.size()) {
            find_next_ptr();
        }
        
        iterator& operator++() {
            if(++ptr == parent->maps[map_index]->end()) {
                ++map_index;
                find_next_ptr();
            }
        }
        
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.parent != rhs.parent ||
                lhs.map_index != rhs.map_index ||
                lhs.ptr != rhs.ptr;
        }
        
        std::pair<Key, Value> operator*() {
            return *ptr;
        }
    };
    
    iterator begin() {
        return iterator(this, true);
    }

    iterator end() {
        return iterator(this, false);
    }
};

#endif // MMAPVIEW_H_INCLUDED
