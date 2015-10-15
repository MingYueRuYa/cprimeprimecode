/*
 * 类嵌套，以及类模板嵌套
 * */
#include <iostream>

class myclass
{
public:
	class newclass
	{
		public:
			int num = 10; 
	}new1; //类的嵌套 直接初始化
};

class newnewlass : public myclass
{
	public:
			
};

template<class T>
class templateclass
{
public:
	class A
	{
		public:
			int num;
	}new1; //非模板类可以直接初始化
	A a;
	
	template<class V>
	class B
	{
		public:
			V x;
	}; //不能直接初始化
	B<T> b; //T来初始化V
	B<double> bb;
};

int main(int argc, char *argv[])
{
	templateclass<int> tmpclass;
	tmpclass.new1.num = 10;
	std::cout << tmpclass.new1.num << std::endl;
	tmpclass.b.x = 20;
	std::cout << tmpclass.b.x << std::endl;
	tmpclass.bb.x = 20.1;
	std::cout << tmpclass.bb.x << std::endl;
	return 0;
}

int main02(int argc, char *argv[])
{
	newnewlass new01;
	std::cout << new01.myclass::new1.num << std::endl;
	return 0;
}

int main01(int argc, char *argv[])
{
	myclass my;
	std::cout << my.new1.num << std::endl;
	return 0;
}
