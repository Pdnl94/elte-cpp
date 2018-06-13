#ifndef DQVIEW_H_INCLUDED
#define DQVIEW_H_INCLUDED

#include <deque>
#include <vector>
#include <algorithm>

template<class T>
class deques_view {
    std::vector<std::deque<T>*> deques;
public:
    deques_view(std::deque<T>& first) {
        deques.push_back(&first);
    }
    
    void add(std::deque<T>& other) {
        deques.push_back(&other);
    }
    
    const T& at(int index) const {
        for(int i = 0; i < deques.size(); ++i) {
            if(deques[i]->size() > index) {
                return deques[i]->at(index);
            } else {
                index -= deques[i]->size();
            }
        }
    }
    
    int size() const {
        int all = 0;
        for(int i = 0; i < deques.size(); ++i) {
            all += deques[i]->size();
        }
        return all;
    }
    
    T& operator[](int index) {
        for(int i = 0; i < deques.size(); ++i) {
            if(deques[i]->size() > index) {
                return deques[i]->at(index);
            } else {
                index -= deques[i]->size();
            }
        }
    }
    
    const T& operator[](int index) const {
        return at(index);
    }
    
    void sort() {
        std::sort(begin(), end());
    }
    
    template<class Comp>
    void sort(Comp c) {
        std::sort(begin(), end(), c);
    }
    
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        deques_view<T>* parent;
        int deque_index;
        int element_index;
    public:
        iterator(deques_view<T>* parent, int deque_index = 0, int element_index = 0) : parent(parent), deque_index(deque_index), element_index(element_index) {}

        bool operator<(const iterator& it) const {
            return std::make_pair(deque_index, element_index) < std::make_pair(it.deque_index, it.element_index);
        }

        T& operator*() {
            return parent->deques[deque_index]->at(element_index);
        }
        
        iterator& operator+=(int with) {
            if(with >= 0) {
                with += element_index;
                while(parent->deques.size() > deque_index && with >= parent->deques[deque_index]->size()) {
                    with -= parent->deques[deque_index++]->size();
                }
                element_index = with;
            } else if(-with <= element_index) {
                element_index += with;
            } else {
                with += element_index;
                while(--deque_index > 0 && -with > parent->deques[deque_index]->size()) {
                    with += parent->deques[deque_index]->size();
                }
                element_index = parent->deques[deque_index]->size() + with;
            }

            return *this;
        }
        
        int operator-(const iterator& oth) const {
            if(deque_index == oth.deque_index) {
                return element_index - oth.element_index;
            }
            
            bool less = *this < oth;
            
            const iterator& from = less ? *this : oth;
            const iterator& to = less ? oth : *this;
            
            int result = from.parent->deques[from.deque_index]->size() - from.element_index + to.element_index;
            
            for(int between = from.deque_index + 1; between < to.deque_index; ++between) {
                result += from.parent->deques[between]->size();
            }
            return result * (less ? -1 : 1);
        }
        
        bool operator==(const iterator& it) const {
            return parent == it.parent && !(*this < it) && !(it < *this);
        }

        bool operator!=(const iterator& it) const {
            return !(*this == it);
        }                

        iterator& operator++() {
            return *this += 1;
        }
        
        iterator operator++(int) {
            iterator cp = *this;
            ++*this;
            return cp;
        }


        iterator& operator--() {
            return *this += -1;
        }        
        
        iterator operator--(int) {
            iterator cp = *this;
            --*this;
            return cp;
        }        
        
        friend iterator operator+(iterator it, int with) {
            return it += with;
        }
        
        friend iterator operator+(int with, iterator it) {
            return it += with;
        }
        
        iterator& operator-=(int with) {
            return *this += -with;
        }
        
        friend iterator operator-(iterator it, int with) {
            return it += -with;
        }
        
        T& operator[](int count) {
            return *(*this + count);
        }
        
        bool operator>(const iterator& it) const {
            return it < *this;
        }
        
        bool operator>=(const iterator& it) const {
            return !(*this < it);
        }

        bool operator<=(const iterator& it) const {
            return !(*this > it);
        }
    };
    
    iterator begin() {
        return iterator(this);
    }
    
    iterator end() {
        return iterator(this, deques.size());
    }
};

#endif // DQVIEW_H_INCLUDED
