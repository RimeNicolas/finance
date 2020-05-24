#include <iostream>
#include "random_generator.h"


int main()
{
	std::cout << "Hello CMake." << std::endl;
	RandomGenerator randgen;
	std::cout << randgen.randint(3, 4) << std::endl;
	return 0;
}
