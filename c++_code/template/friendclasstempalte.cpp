/*
 * 类模板于友元函数
 * 关于友元函数的声明，是个比较复杂的问题
 * 1.在模板内部的时，声明友元不需要加<T>，在外部需要加上<T>
 * 2.在外部的时候还必须加上类和友元函数的说明，此时友元函数不需要再加上<T>，如print02函数
 * 3.友元类的声明也是如此.
 * */
#include <iostream>

template<class T> class myclass;
template<class T> void print02(myclass<T> &my);

template<class T>
class myclass
{
public:
	friend void print(myclass<T> &my)
	{
		std::cout << my.x << "--" << my.y << std::endl;
	}
	friend void print02<T>(myclass<T> &my);
	myclass(T t1, T t2) : x(t1), y(t2)
	{

	}
private:
	T x;
	T y;

};

template<class T> 
void print02(myclass<T> &my)
{
	std::cout << my.x << " " << my.y << std::endl;
}


int main()
{
	myclass<int> myclass1(2, 1);
	//print(myclass1);
	print02(myclass1);
	return 0;
}


