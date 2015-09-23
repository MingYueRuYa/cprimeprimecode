/*
 *	类模板
 * */
#include <iostream>
#include <typeinfo>
template<class T>
class Base
{
public:
	Base(T a): t(a)
	{
		
	}
	void print() 
	{
		std::cout << "Base T type:" << typeid(t).name() << " t = " << t << std::endl;
		//std::cout << "hello world" << std::endl;
	}
private:
	T t;
};

int main()
{
	//Base<int> base(5);
	//base.print();
	
	Base<std::string> base("hello world");
	base.print();
	return 0;
}

