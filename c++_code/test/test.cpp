#include "test.h"
#include <iostream>

Test::Test()
{
	std::cout << "hello world!" << std::endl;
}

Test::~Test()
{
	std::cout << "~Test" << std::endl;
}
void Test::Printf()
{
	std::cout << "Printf" << std::endl;
}
