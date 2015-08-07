/*
	new type array
*/
#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>

int main()
{
	std::string str01 = "fire";
	std::string str02 = "fox";
	system((str01 + str02).c_str());
	return 0;
}
int main02()
{
	std::array<std::string, 3> str01 = {"notepadqq", "chrome", "firefox"};
	for(int i = 0; i < 3; i++) {
		std::cout << str01[i] << std::endl;
		system(str01[i].c_str());
	}
	return 0;
}
int main01()
{
	double db[4] = { 1.1, 2.2, 3.3, 4.4};
	std::array<double, 4> dbnew1 = { 10.1, 10.2, 10.3, 10.4};
	//实现数组之间整体的操作
	std::array<double, 4> dbnew2 = dbnew1; 
	for(int i = 0; i < 4; i++) {
		std::cout << dbnew2[i]	<< "  " << dbnew1[i] <<std::endl;
	}
	return 0;
}
