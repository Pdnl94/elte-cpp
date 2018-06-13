#ifndef AT_VIEW_H
#define AT_VIEW_H

template<class T, typename func>
class array_transform_view 
{
	const T* array;
	func mod;
	int s;
public:
	
	array_transform_view(const T _array[], int _size) 
	{
		array = _array; 
		s = _size;
	}
	
	T at(int pos) const 
	{
		return mod(array[pos]);
	}
	
	T operator[](int pos) const
	{
		return mod(array[pos]); 
	}
   
	int size() const 
	{
		return s;
	}
	
};

#endif
