/*
 *	关于类的继承
 * */
#include <iostream>

class Father
{
public:
	Father()
	{
		std::cout << "this is father constructor" << std::endl;
	}
	void PrintName()
	{
		std::cout << "this is father." << std::endl;
	}
protected:
	void ProFun()
	{
		std::cout << "this is father profunc." << std::endl;
	}
private:
	void PriFun()
	{
		std::cout << "this is father prifunc......" << std::endl;
	}
};

class Son: public Father
{
public:
	void PrintName()
	{
		std::cout << "this is son." << std::endl;
		ProFun();
	}
	void WhoAmI() {
		std::cout << "this is Son." << std::endl;
	}
protected:
	void ProFun()
	{
		std::cout << "this is son profunc." << std::endl;
		//调用父类的保护方法
		this->Father::ProFun();
	}
private:
	void PriFun()
	{
		std::cout << "this is son prifunc......" << std::endl;
	}

};

class Sonson : protected Son
{
public:
	void PrintName(){
		std::cout << "this is Sonson." << std::endl;
		this->Son::WhoAmI();
	}
};

int main()
{
	//Father father;
	//father.PrintName();
	Son son;
	son.PrintName();
	//子类想调用父类重名的方法 子类对象中存在了一个指向父类的对象的指针
	//son.Father::PrintName();
	//protected保护方法只能在内部使用
	//son.ProFun(); //报错 error	
	std::cout << "-------------------------------"	<< std::endl;
	Sonson sonson;
	sonson.PrintName();
	//如果是public继承WhoAmI可以访问，如果是protected继承，这个方法不能被访问，只能在内部使用，protect继承，是一脉相传
	//sonson.WhoAmI();
	//private 继承，下面的子类不能在继承
	return 0;
}













