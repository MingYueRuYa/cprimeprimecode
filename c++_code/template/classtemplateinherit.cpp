/*
 * 类模板继承
 * 1.类模板可以从类模板继承，必行必须传递
 * 2.普通类继承模板类，需要明确类型实例化类模板
 * 3.类模板继承普通类，常规的操作方法
 * 4.类模板当作普通类，需要模板参数对类进行实例化
 * */
#include <iostream>

template<class T>
class myclass
{
public:
	T x;
	myclass(T t) : x(t)
	{
		
	}

	virtual void print()
	{
		std::cout << x << std::endl;
	}

};

template<class T>
class newclass : public myclass<T> //类模板继承类模板
{
public:
	T x;
	newclass(T t1, T t2) : myclass<T>(t1), x(t2)
	{

	}
	void print() override
	{
		std::cout << x << " " << myclass<T>::x << std::endl;
	}
};

int main()
{
	//newclass<double> class1(1.1, 2.2);
	//class1.print();
	
	newclass<std::string> class2("abc", "zyx");
	class2.print();

	return 0;
}

//普通类继承模板类----> 要实例化模板参数
class General : public myclass<int>
{
public:
	int x;
	General(int x1, int x2) : myclass<int>(x1), x(x2)
	{

	}
	void print() override
	{
		std::cout << x << "	" << myclass<int>::x << std::endl;
	}
};


int main02()
{
	General general(1, 2);
	general.print();
	return 0;
}

//类模板继承普通类
template<class T>
class TeShi01 : public General
{
public:
	T x;
	TeShi01(T x1) : General(x1, x1), x(x1)
	{
	}
	void print()
	{
		std::cout << x << "	" <<General::x << std::endl;
	}
};


int main03()
{
	TeShi01<int> ts(1);
	ts.print();
	return 0;
}




