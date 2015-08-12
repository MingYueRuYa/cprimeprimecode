/*
 * 智能指针
 **/

#include <iostream>
#include <memory>
int main()
{
	for(int i = 0; i < 1000; i++){
		double *p = new double;
		std::auto_ptr<double> autop(p);
		//创建智能指针管理指针p指向内存
		//智能指针
	}
	//新型智能指针，可以直接new一个对象进去
	std::auto_ptr<double> autop(new double);
	return 0;
}
