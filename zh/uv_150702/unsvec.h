#ifndef UNSVEC_H_INCLUDED
#define UNSVEC_H_INCLUDED

#include <vector>
#include <algorithm>

template<class T>
class unsortable_vector
{
	std::vector<T> unsorted;
	std::vector<T> sorted;
	bool _is_sorted;
public:

	unsortable_vector( const T* ptr, int size ) : unsorted(ptr, ptr + size), _is_sorted(false){}
	
	unsortable_vector& set_sort_on()
	{
		_is_sorted = true;
		sorted = unsorted;
		std::sort(sorted.begin(), sorted.end());
		return *this;
		
		/* return set_sort_on(std::less<T>()); */
	}
	
	unsortable_vector& set_sort_off()
	{
		_is_sorted = false;
		return *this;
	}
	
	bool is_sorted() const
	{
		return _is_sorted;
	}
	
	// hozzunk letre egy segedfuggvenyt:
	const std::vector<T>& get() const
	{
		return (is_sorted() ? sorted : unsorted);
	}
	
	std::vector<T>& get()
	{
		return (is_sorted() ? sorted : unsorted);
	}
	
	const T& at(int index) const 
	{
		return get().at(index);
	}
	
	int size() const
	{
		return get().size();
	}
	
	template<class Fun>
	unsortable_vector& set_sort_on(Fun f)
	{
		_is_sorted = true;
		sorted = unsorted;
		std::sort(sorted.begin(), sorted.end(), f);
		return *this;
	}
	
	const T& operator[](int index) const 
	{
		return get()[index];
	}
	
	void operator+=(const unsortable_vector& v)
	{
		unsorted.insert(unsorted.end(), v.get().begin(), v.get().end());
		if(is_sorted())
		{
			set_sort_on();
		}
	}
	
	typedef typename std::vector<T>::const_iterator const_iterator;
	
	const_iterator begin() const
	{
		return get().begin();
	}
	
	const_iterator end() const
	{
		return get().end();
	}
};

#endif // UNSVEC_H_INCLUDED