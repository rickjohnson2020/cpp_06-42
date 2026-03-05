#include "./Serializer.hpp"

int main() {
	Data data1;
	data1.x = 10;
	data1.y = 20;
	uintptr_t i = Serializer::serialize(&data1);
	Data* data2 = Serializer::deserialize(i);

	std::cout << "data1 address: " << &data1 << std::endl;
	// std::cout << i << std::endl;
	std::cout << "i(hex): " << std::hex << i << std::endl;
	std::cout << std::dec;
	std::cout << "data2 address: " << data2 << std::endl;
	std::cout << "data2 x: " << data2->x << std::endl;
	std::cout << "data2 y: " << data2->y << std::endl;

	return 0;
}