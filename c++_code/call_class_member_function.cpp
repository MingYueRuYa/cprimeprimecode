/*
 * 测试调用class的成员函数
 * */
#include <iostream>

using std::cout;
using std::endl;


class Base
{
public:
	Base() {}
	~Base() {}
};

typedef void (Base::*pFun)();

class Child : public Base
{
public:
	Child(const int &pID) : mID(pID) {}
	~Child() {}

	void Print() { cout << "child print..." << mID << endl; }

private:
	int mID;
};

typedef void (Child::*pChildFun)();


int main(int argc, char *argv[])
{
	
	Base *base = new Child(2);
	//base->Print(); //Error: 父类中不存在Print 方法
	pFun fun = static_cast<pFun>(&Child::Print);
	(base->*fun)();

	//已经内存泄露了，注意这不是重点
	base = new Child(3);
	(base->*fun)();

	Child *child = new Child(3);
	pChildFun childfun = static_cast<pChildFun>(&Child::Print);
	(child->*childfun)();

	//result:
		//child print...2
		//child print...3
		//child print...3

	return 0;
}

