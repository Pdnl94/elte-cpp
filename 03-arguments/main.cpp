#include <iostream>

int main(int argc, const char* args[]) {
	std::cout << "args:";
	for(int i = 0; i < argc; i++) {
		std::cout << " " << args[i];	
	}
	std::cout << std::endl;
	return 0;
}
