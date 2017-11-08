#include <iostream>
#include "list.h"

int main(int argc, const char* args[]) {
	List<int> list;
	list.data = 1;
	List<int> listSecond;
	listSecond.data = 2;
	list.next = &listSecond;

	std::cout << "ASD" << std::endl;
	std::cout << (&list)->next->data << std::endl;
	return 0;
}
