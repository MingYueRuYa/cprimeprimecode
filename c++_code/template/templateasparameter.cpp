/*
 * 类模板作为另一个模板的参数
 * */

#include <iostream>
#include <string>

using namespace std;

template<class T>
class Ren
{
public:
	T name;
	Ren(T t1) : name(t1)
	{

	}
};

template<class T>
class Man
{
public:
	T age;
	Man(T t1) : age(t1)
	{

	}
};

template<template<class T> class N>
class None
{
public:
	//N<std::string> n1("hello");
	None(N<int> n1)
	{
		std::cout << n1.age<< std::endl;
	}
	N<int> n1 = 5;
	string str = "hi";
	N<string> n2 = str;
};



int main(int argc, char *argv[])
{
	Ren<string> ren("ren");
	std::cout << ren.name << std::endl;
	Man<int> man(5);
	std::cout<< man.age << std::endl;
	//None<Ren> n1(ren);
	None<Man> n1(man);
	//std::cout << n1.name << std::endl;
	return 0;
}
