#include "./Serializer.hpp"

int main() {
	Data* data1 = new Data();
	data1->x = 1;
	data1->y = 2;
	uintptr_t i = Serializer::serialize(data1);
	Data* data2 = Serializer::deserialize(i);

	std::cout << data1 << std::endl;
	std::cout << i << std::endl;
	std::cout << data2 << std::endl;
	std::cout << data2->x << std::endl;
	std::cout << data2->y << std::endl;

	// delete data1;
	delete data2;

	return 0;
}