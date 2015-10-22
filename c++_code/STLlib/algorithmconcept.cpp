/*
 * 算法的概念
 * */
#include <algorithm>
#include <iostream>

using namespace std;

struct print
{
	void operator()(int num)
	{
		cout << num << endl;
	}
	void Print(int num)
	{
		cout << num << endl;
	}
};

void printNum(int num)
{
	cout << num << endl;
}


int main()
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//首地址a开始，a+10表示最后一个地址，但是注意最后一个在数组中不存在的。
	//int *p = find(a, a + 10, 8);
	int *p = find(a, a + 10, 0);
	std::cout << (void *)a << " " <<(void *)(a + 10) << endl;
	std::cout << *p << std::endl;
	if (p == a + 10) {
		std::cout << "Not find.\n";	
	}
	//遍历数组中每一个元素
	//起始地址，终止地址，函数指针
	//for_each(a, a + 4, printNum);
	//重载了结构体中()运算符
	for_each(a, a + 4, print());
	return 0;
}
