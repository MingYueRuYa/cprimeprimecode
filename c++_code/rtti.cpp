/*
 * 实时类型检测
 * typeid,dynamic_cast 必须依赖于虚函数表
 * 类型不匹配转换失败，返回为空，类型安全
 * */
#include <iostream>
#include <typeinfo>
class A
{
public:
	int num;
	virtual void run()
	//void run()
	{
		std::cout << "Arun\n";
	}
};

class B : public A
{
public:
	int num = 0;
	void run()
	{
		std::cout << "Brun\n";
	}
	void test()
	{
		std::cout << num << std::endl; 
		std::cout << "btest\n";
	}
};

int main(int argc, char *argv[])
{
	A a1;
	B b1;
	A *p1 = &a1;
	A *p2 = &b1;
	B *p3(nullptr);
	p3 = static_cast<B *>(p1); //直接赋值地址，不安全，于虚函数无关
	//p3->test();
	p3 = reinterpret_cast<B *>(p2);
	p3->test();
	return 0;
}

int main03(int argc, char *argv[])
{
	A a1;
	B b1;
	A *p1 = &a1;
	A *p2 = &b1;
	B *p3(nullptr);
	//类的空指针可以调用不调用内部数据成员的函数，一旦函数中使用了内部的成员变量，就会shutdown
	//p3->test();
	p3 = dynamic_cast<B *>(p2);
	//dynamic_cast必须要有虚函数表，根据虚函数表进行转换，否则不能转换
	//在这里如果run函数不是虚函数，语法编译就不能通过
	//如果转换失败，p3为空，类的空指针可以调用不调用内部数据成员的函数
	//转换成功，就是地址
	std::cout << p3 << std::endl;
	p3->test();
	return 0;
}
int main02(int argc, char *argv[])
{
	A a1;
	B b1;
	A *p1 = &a1;
	A *p2 = &b1;
	std::cout << typeid(p1).name() << " " << typeid(p2).name() << std::endl;
	std::cout << ( typeid(p1).name() == typeid(p2).name() )<< std::endl;
	//根据虚函数表判断类型
	std::cout << typeid(*p1).name() << " " << typeid(*p2).name() << std::endl;
	return 0;
}

int main01(int argc, char *argv[])
{
	B b1;
	b1.num = 10; //覆盖现象
	b1.A::num = 20;
	std::cout << b1.num << "  " << b1.A::num << std::endl;
	std::cout << &b1.num << "  " << &b1.A::num << std::endl;
	return 0;
}
