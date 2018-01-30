#ifndef MSETVEC_H_INCLUDED
#define MSETVEC_H_INCLUDED

#include <vector>
#include <algorithm>

template<class T, class Cmp>
class multiset_vector {
	std::vector<T>* vec;

public:
	multiset_vector(std::vector<T>& vec) : vec(&vec) {
		std::sort(vec.begin(), vec.end(), Cmp());
	}
	
	int count(const T& elem) const {
		std::pair<typename std::vector<T>::const_iterator, typename std::vector<T>::const_iterator> its = 
			std::equal_range(vec->begin(), vec->end(), elem, Cmp());
		return its.second - its.first;
	}
	
	void use(std::vector<T>& vec) {
		this->vec = &vec;
		std::sort(vec.begin(), vec.end(), Cmp());
	}
	
	typename std::vector<T>::const_iterator find(const T& elem) const {
		return count(elem) == 0 ? vec->end() : std::lower_bound(vec->begin(), vec->end(), elem, Cmp());
	}
	
	template<class Ord>
	void secondary_ordering(Ord ord) {
		std::sort(vec->begin(), vec->end(), ord);
		std::stable_sort(vec->begin(), vec->end(), Cmp());
	}
};

template<class T, class Cmp>
class sorted_iterator : public std::iterator<std::input_iterator_tag, const T> {
	std::vector<const T*> elements;
	int elem;
	
	struct {
		const T* operator()(const T& o) const {
			return &o;
		}
	} const address_of;
	
	struct CmpByPtr {
		Cmp cmp;
		CmpByPtr(Cmp cmp) : cmp(cmp) {}
		
		bool operator()(const T* t1, const T* t2) const {
			return cmp(*t1, *t2);
		}
	} const cmp;
public:
	sorted_iterator(const std::vector<T>& elements, Cmp cmp, int elem = 0) : 
		elem(elem), address_of(), cmp(cmp) {
		std::transform(elements.begin(), elements.end(), std::back_inserter(this->elements), address_of);
		std::sort(this->elements.begin(), this->elements.end(), this->cmp);
	}
	
	const T* operator->() {
		return elements[elem];
	}
	const T& operator*() {
		return *elements[elem];
	}
	
	bool operator==(const sorted_iterator& oth) const {
		return oth.elem == elem;
	}
	
	bool operator!=(const sorted_iterator& oth) const {
		return oth.elem != elem;	
	}
	
	sorted_iterator& operator++() {
		++elem;
		return *this;
	}
};

template<class T, class Cmp>
inline sorted_iterator<T, Cmp> sorted_iterator_begin(const std::vector<T>& it, Cmp cmp) {
	return sorted_iterator<T, Cmp>(it, cmp);
}

template<class T, class Cmp>
inline sorted_iterator<T, Cmp> sorted_iterator_end(const std::vector<T>& it, Cmp cmp) {
	return sorted_iterator<T, Cmp>(it, cmp, it.size());
}

#endif // MSETVEC_H_INCLUDED