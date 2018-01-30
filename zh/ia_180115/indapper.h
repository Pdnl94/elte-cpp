#ifndef INDAPPER_H_INCLUDED
#define INDAPPER_H_INCLUDED

#include <vector>

template<class Container, class T = typename Container::value_type>
class index_appender_view {
    std::vector<Container*> containers;
    
    // harmasig ezek helyett lehet hasznalni T& illetve const T& -et. 
    // A vetor<bool> miatt ez utan mar nem.
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
public:
    void add(Container& c) {
        containers.push_back(&c);
    }
    
    const_reference at(std::size_t index) const {
        for (int i = 0; i < containers.size(); ++i) {
            if (index < containers[i]->size()) {
                return containers[i]->at(index);
            }
            index -= containers[i]->size();
        }
    }
    
    std::size_t size() const {
        std::size_t result = 0;
        for (int i = 0; i < containers.size(); ++i) {
            result += containers[i]->size();
        }
        return result;
    }
    
    reference operator[](std::size_t index) {
        for (int i = 0; i < containers.size(); ++i) {
            if (index < containers[i]->size()) {
                return containers[i]->at(index);
            }
            index -= containers[i]->size();
        }
    }
    
    const_reference operator[](std::size_t index) const {
        return at(index);
    }
    
    template<class OtherContainer>
    bool operator==(const index_appender_view<OtherContainer, T>& other) const {
        if (size() != other.size()) {
            return false;
        }
        
        for (int i = 0; i < size(); ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }
};

#endif // INDAPPER_H_INCLUDED
