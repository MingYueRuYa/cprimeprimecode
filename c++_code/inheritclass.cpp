/*
 *	关于类的继承
 * */
#include <iostream>
#include <stdio.h>
#include <string.h>

class Father
{
public:
	Father()
	{
		mChar = new char[10];
		strcpy(mChar, "linux");
		std::cout << "this is father constructor" << std::endl;
	}

	//将父类析构函数声明为虚函数，这样在父类在析构的时候，可以调用子类的析构函数，避免内存泄漏的危险
	virtual ~Father()
	{
		delete mChar;
		std::cout << "Father desconstruct..." << std::endl;
	}

	Father(const Father &pFather)
	{
		std::cout << "Father copy ...." << std::endl;
	}

	Father& operator=(const Father &pFather)
	{
		std::cout << "Father operator = " << std::endl;
		return *this;
	}

	void PrintName()
	{
		std::cout << "this is father." << std::endl;
	}

	void GetChar()
	{
		std::cout << mChar << std::endl;
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

private:
	char *mChar;
};

class Son: public Father
{
public:
	Son()
	{
		std::cout << "Son construct...\n";
	}
	 ~Son()
	{
		std::cout << "Son desconstruct...\n";
	}

	 Son(const Son &pSon)
	{
		std::cout << "Son copy construct...\n";
	}
	Son& operator=(const Son &pSon)
	{
		std::cout << "Father operator = .\n";
		return *this;
	}

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

int TestFun()
{
	Father *father = new Son();
	delete father;
	return 0;
}

int TestFun01()
{
	Father father = Son();
	father.PrintName();
	//此时父类已经将资源释放了，这里调用没有shutdown，也是很危险的，其他平台可能就会shutdown
	father.GetChar();
	return 0;
//	将子类对象赋值给父类是危险的行为，构造子类的时候先是构造父类对象，然后子类对象析构，再析构父类(此时父类可能释放资源了), 可能将匿名对象转为父类对象，这是匿名对象的析构可能会将父类的已经释放的资源在释放一次，导致bug出现。
//  console print content
//
//	this is father constructor
//	Son construct...
//	Son desconstruct...
//	Father desconstruct...
//	this is father.
//	Father desconstruct...
}

void TestFunc02()
{
	//编译器报错
	//父类对象不能赋值给子类对象
	//Son son = Father(); //error
}

void TestFunc03()
{
	//编译器报错
	//父类指针对象不能赋值给子类指针对象
	//Son *son = new Father();//error
}

int main()
{
	//TestFun();
	//TestFun01();	
	//TestFunc02();
	//TestFunc03();

	Son son;
	Son son01;
	//赋值运算符 只会调用子类的不会调用父类的赋值运算符
	son = son01;
	return 0;
}

int main01()
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













