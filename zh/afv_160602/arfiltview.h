#ifndef ARFILTVIEW_H
#define ARFILTVIEW_H

#include <vector>
#include <algorithm>

template<class Type, class Filter>
class array_filter_view {
	std::vector<Type> copy;
	Type* array;
	int filtered_size;
public:
	array_filter_view(Type* array, int size) : copy(array, array + size), array(array),
		filtered_size(std::remove_copy_if(array, array + size, array, std::not1(Filter())) - array)
	{}
	
	~array_filter_view() {
		std::copy(copy.begin(), copy.end(), array);
	}
	
	int size() const {
		return filtered_size;
	}
	
	static const int npos;
	
	int index_of(const Type& elem) const {
		int index = std::find(array, array + size(), elem) - array;
		return index == size() ? npos : index;
	}
	
	template<class Fun>
	int index_if(const Fun& fun) const {
		int index = std::find_if(array, array + size(), fun) - array;
		return index == size() ? npos : index;
	}
	
	typedef const Type* const_iterator;

	const_iterator begin() const {
		return array;
	}
	
	const_iterator end() const {
		return array + size();
	}
};

template<class Type, class Filter>
const int array_filter_view<Type, Filter>::npos = -1;

#endif // ARFILTVIEW_H
