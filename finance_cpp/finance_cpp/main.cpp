#include <iostream>
#include "random_generator.h"


int main()
{
	std::cout << "Hello CMake." << std::endl;
	RandomGenerator randgen(0);
	for (int i(0); i < 20; i++) {
		std::cout << randgen.randint() << std::endl;
	}
	return 0;
}
