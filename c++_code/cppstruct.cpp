/*
 *	c++ 结构体
 * */

#include <iostream>


//编译匿名结构体时，要注意g++ 要加上-std=c++11 选项，以c++11编译
//匿名结构体在windows平台上不允许有默认值，但是linux平台下可以
//匿名结构体一般用在对象是唯一的或者是很少的制定数量
struct {
	int age = 20;
	char name[20] = "linux";
}CEO,CTO;

//结构体本身不可以再嵌套自身，但是可以包含指向自身的指针，链表等其他数据结构都是这样实现的



int main()
{
	std::cout << CEO.age << std::endl;
	std::cout << CEO.name << std::endl;
	std::cout << CTO.name << std::endl;
	std::cout << CTO.age << std::endl;
	return 0;
}
