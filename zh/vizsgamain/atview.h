#ifndef AT_VIEW_H
#define AT_VIEW_H

#include <vector>


template<class T, typename func>
class array_transform_view {
	const T* array;
	func mod;
	int s;
public:

	array_transform_view(const T _array[], int _size) {
		array = _array; 
		s = _size;
	}
	
	array_transform_view(const std::vector<T> &v) {
		array = &v[0];
		s = v.size();
	}
	
	T at(int pos) const {
		return mod(array[pos]);
	}
	
	T operator[](int pos) const {
		return mod(array[pos]); 
	}
   
	int size() const {
		return s;
	}
	
};

#endif
