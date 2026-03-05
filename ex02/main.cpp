#include "./Base.hpp"
#include "./A.hpp"
#include "./B.hpp"
#include "./C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


Base* generate() {
	int randomNum = std::rand();
	Base* base;
	if (randomNum % 3 == 0)
		base = new A();
	else if (randomNum % 2 == 0)
		base = new B();
	else
		base = new C();
	return base;
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "unknown type" << std::endl;
}

void identify(Base& p) {
	try {
		A a = dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (const std::exception&) {}

	try {
		B b = dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (const std::exception&) {}

	try {
		C c = dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (const std::exception&) {}

	std::cout << "unknown type" << std::endl;
}

int main() {
	std::srand(std::time(NULL));
	
	Base* b1 = generate();
	Base* b2 = generate();
	Base* b3 = generate();

	identify(b1);
	identify(b2);
	identify(b3);
	
	std::cout << "==========" << std::endl;

	identify(*b1);
	identify(*b2);
	identify(*b3);

	delete b1;
	delete b2;
	delete b3;

	return 0;
}