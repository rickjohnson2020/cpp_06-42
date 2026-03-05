#include <iostream>
#include <stdint.h>


int main() {
	std::string s = "hello";
	char* cptr = (char*)s.c_str();
	// int* iptr;

	int* iptr = reinterpret_cast<int*>(cptr);
	std::cout << cptr << std::endl;
	std::cout << *iptr << std::endl;

	return 0;
}