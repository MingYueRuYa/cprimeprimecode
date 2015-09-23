/*
 * c++11 final overide只针对虚函数
 * final 拒绝被重写，加了final关键字的虚函数，无法被重写，预留接口
 * override，警示符，声明我重写父类的方法，父类没有接口，会提示出错
 * */
#include <iostream>

class ye
{
public:
	//注意final必须是虚函数才行
	virtual void print() final //虚函数不能被重写
	{
		std::cout << "yeye\n";
	}

	virtual void run()
	{
		std::cout << "ye is run." << std::endl;
	}

};

class Ba : public ye
{
public:
	//警示作用，强调我覆盖了父类的方法，注意必须是虚函数
	void run() override
	{
		std::cout << "ba is run." << std::endl;
	}
};


int main(int argc, char *argv[])
{
	Ba b1;
	b1.run();
	b1.print();
	return 0;
}
