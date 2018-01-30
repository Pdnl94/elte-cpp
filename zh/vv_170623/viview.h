#ifndef VIVIEW_H_INCLUDED
#define VIVIEW_H_INCLUDED

#include <map>
#include <algorithm>

template<class T>
class vector_index_view {
    std::vector<T>& viewed;
    std::map<int, int> indices;
    std::map<int, int> backward;
    bool direction_swap;

    int transform(int& ind) const {
        if(direction_swap) {
            ind = viewed.size() - 1 - ind;
        }
        return indices.find(ind) != indices.end() ? indices.find(ind)->second : ind;
    }

    int transform_back(int ind) const {
        int result = backward.find(ind) != backward.end() ? backward.find(ind)->second : ind;
        return direction_swap ? viewed.size() - 1 - result : result;
    }
public:
    vector_index_view(std::vector<T>& viewed) : viewed(viewed), direction_swap(false) {}

    void swap(int ind1, int ind2) {
        int ind1real = transform(ind1);
        int ind2real = transform(ind2);

        indices[ind1] = ind2real;
        indices[ind2] = ind1real;
        backward[ind1real] = ind2;
        backward[ind2real] = ind1;
    }

    const T& at(int ind) const {
        return viewed.at(transform(ind));
    }

    T& operator[](int ind) {
        return viewed[transform(ind)];
    }

    static int npos;

    int index_of(const T& elem) const {
        typename std::vector<T>::const_iterator it = std::find(viewed.begin(), viewed.end(), elem);
        return it == viewed.end() ? npos : transform_back(it - viewed.begin());
    }

    void operator-() {
        direction_swap = true;
    }

    void operator+() {
        direction_swap = false;
    }

    struct iterator : std::iterator<std::forward_iterator_tag, const T>, std::pair<int, vector_index_view*> {
        iterator(vector_index_view* parent, int where = 0) : std::pair<int, vector_index_view*>(where, parent) {}

        iterator& operator++() {
            ++this->first;
            return *this;
        }

        iterator operator++(int) {
            iterator res = *this;
            ++*this;
            return res;
        }

        const T& operator*() {
            return this->second->at(this->first);
        }

        const T* operator->() {
            return &**this;
        }
    };

    iterator begin() {
        return iterator(this);
    }

    iterator end() {
        return iterator(this, viewed.size());
    }
};

template<class T>
int vector_index_view<T>::npos = -1;

#endif // VIVIEW_H_INCLUDED
