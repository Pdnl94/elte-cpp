#ifndef PALALG_H
#define PALALG_H

#include <algorithm>

template<class InputIt>
bool is_palindrome(InputIt first, InputIt last) {
	InputIt middle = first;
	std::advance(middle, std::distance(first, last) / 2);
	return std::equal(first, middle, std::reverse_iterator<InputIt>(last));
}

template<class InputIt>
void make_palindrome(InputIt first, InputIt last) {
	InputIt middle = first;
	std::advance(middle, std::distance(first, last) / 2);
	std::copy(first, middle, std::reverse_iterator<InputIt>(last));	
}

template<class InputIt, class OutputIt>
void copy_palindrome(InputIt first, InputIt last, OutputIt d_first, bool duplication) {
	d_first = std::copy(first, last, d_first);
	
	std::reverse_iterator<InputIt> r_first(last), r_last(first);

	if(!duplication) {
		++r_first;
	}
	
	std::copy(r_first, r_last, d_first);
}

template<class InputIt, class UnaryPredicate>
bool is_palindrome(InputIt first, InputIt last, UnaryPredicate pred) {
	InputIt middle = first;
	std::advance(middle, std::distance(first, last) / 2);
	return std::equal(first, middle, std::reverse_iterator<InputIt>(last), pred);
}

template<class InputIt>
void shift_palindrome(InputIt first, InputIt last) {
	InputIt middle = first, before_middle = first;
	
	int middle_index = (std::distance(first, last) + 1) / 2;
	
	std::advance(middle, middle_index);
	std::advance(before_middle, middle_index > 0 ? middle_index - 1 : 0);

	std::rotate(first, before_middle, middle);
	make_palindrome(first, last);
}

#endif // PALALG_H
