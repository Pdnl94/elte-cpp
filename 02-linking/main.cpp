#include <iostream>
#include "other.cpp"

//The other class is written in another file called other.cpp
//It holds only a const public int value to read it
//In order to compile it, 
int main(int argc, const char* args[]) {
	Other a;
	std::cout << "other a: " << a.a << std::endl;
}
