# CMakeList.txt : CMake project for finance_cpp, include source and define 
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

add_executable (finance_cpp "main.cpp" 
	"random_generator.cpp" "random_generator.h" 
	"math_func.h" 
	"motion.h" 
	"print_func.h")
# add_executable (finance_cpp "main.cpp")

# file(GLOB helloworld_SRC
#    "*.h"
#    "*.cpp"
#)

# add_executable (finance_cpp ${helloworld_SRC})


# TODO: Add tests and install targets if needed.
