/*
 * 汉诺塔 递归算法
 * */


#include <iostream>

void Hanoi(int num, char A, char B, char C)
{
	if(num <= 1) {
		std::cout << A << "-->" << C << std::endl;
		return ;
	}
	else {
		Hanoi(num - 1, A, C, B);
		std::cout << A << "-->" << C <<std::endl;
		Hanoi(num - 1, B, A, C); 
	}
}

int main()
{
	int n;
	std::cin >> n;
	std::cout << "n = " << n <<std::endl;
	Hanoi(n,'A', 'B', 'C');
	return 0;
}

