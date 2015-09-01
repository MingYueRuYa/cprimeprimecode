/*
 *	虚方法 虚析构函数可以解决父类指针指向子类delete发生的内存泄漏问题
 *	构造函数不能为虚析构函数
 * */
#include <iostream>

class Base
{
public:
	int num;
	void PrintNum() {
		std::cout << "this is Base num = " << num << std::endl;
	}

	void Hi() {
		std::cout << "Hi" << std::endl;
	}
	virtual void SayHello() {
		std::cout << "virtual SayHello" << std::endl;
	}
	virtual ~Base() {
		std::cout << "Base ～" << std::endl;
	}
};

class Son : public Base
{
public:
	void SayHello() {
		std::cout << "this is Son SayHello" << std::endl;
	}
	virtual ~Son() {
		std::cout << "~Son()" << std::endl;
	}
};

class GreadSon : public Son
{
public:
	int num;
	void PrintNum() {
		std::cout << "this is Greadson num = " << num << std::endl;
	}
	void GreadSonHi() {
		std::cout << "Son Hi" << std::endl;
	}
	void SayHello() {
		std::cout << "Greadson sayhello" << std::endl;
	}
};


class SonSon : public GreadSon
{
public:
	SonSon(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	void SayHello() {
		std::cout << "a = " << a << " b = " << b << " c = " << c << " " << std::endl;
	}
	void GetA() {
		std::cout << " a = " << a << std::endl;
	}

private:
	int a;
	int b;
	int c;
};




int main()
{
	Son son;
	son.SayHello();
	//指针父类调用父类的方法
	//son.Base::SayHello();
	//Base *base = new Son;	
	//delete base;
	
	//段异常错误 C语言类型的强制类型转换
	//((GreadSon *)base)->SayHello();

	Base *base(nullptr);
	base = new GreadSon;	
	//base->SayHello();
	base->PrintNum();
	//用c++的强制类型转换则没有段错误
	//(static_cast<GreadSon *>(base))->SayHello();
	
	//虽然用把父类指针调用子类的特有的函数没有发生段异常错误，但是这是危险的事
	//一旦这个方法中用到了子类的成员变量，就会可能发生down，但也能没有发生
	//但这时危险的事
	//(static_cast<GreadSon *>(base))->GreadSonHi();
	//在ubuntu 14.04 LTS下测试没有down，但是在vs环境可能down
	//(static_cast<GreadSon *>(base))->PrintNum();


	//将父类指针转为子类指针
	Base *pbase = new Base;
	GreadSon *pson = static_cast<GreadSon *>(pbase);
	//pson->PrintNum();	


	SonSon *sonson = static_cast<SonSon *>(pbase);//new SonSon(1, 2, 3);
	sonson->SayHello();	
	//在ubuntu 14.04 LTS 测试下没有问题，但是在vs下可能有问题存在
	//sonson->GetA();
	SonSon sonson02(1, 2, 3);	
	sonson02.GetA();
	sonson02.Base::PrintNum();
	return 0;
}








