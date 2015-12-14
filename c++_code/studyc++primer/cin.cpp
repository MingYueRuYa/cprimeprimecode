#include <iostream>

int main()
{
	std::cout << "input number." << std::endl;
	/*
	int num;
	std::cin >> num;
	std::cout << num << std::endl;
	*/
	std::cout << /* "*/" */; error
	//std::cout << /* "/*" /* "*/" */; error
	
	int value = 0, sum = 0;
	while (std::cin >> value) {
		std::cout << value << std::endl;
		sum += value;
	}
	std::cout << sum << std::endl;
	return 0;
}
