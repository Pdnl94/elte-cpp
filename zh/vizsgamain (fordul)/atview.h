#ifndef AT_VIEW_H
#define AT_VIEW_H

template<class T, class func>
class array_transform_view {
	const T* array;
public:
	
	array_transform_view(const T _array[], int size) {
		array = _array; 
	}
	
	T at(int pos) const {
	
		return array[pos];
	}
};

#endif
