#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <string>
#include <list>
#include <cstring>

using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::begin;
using std::end;
using std::string;
using std::list;
using std::list;
using std::pair;

//Demo不是POD类型数据
//POD 就是简单数据类型的组成struct或class
//何为简单：就是没有ctor，dtor，virtual，权限修饰符只有一种
class Demo
{
public:
	Demo()
	{ 
		age = 0;
		name = "lsx";
		cout << "ctor." << endl;
	}

	~Demo() { cout << "dtor." << endl; }

	virtual void Show() { /*....*/ }

	Demo(const Demo &pDemo) { cout << "copy ctor..." << endl; }

private:
	int age;
	std::string name;

};

int main03(void)
{
	//get block of uninitialized memory:
	std::pair<Demo*, std::ptrdiff_t> result = std::get_temporary_buffer<Demo>(3);

	Demo demo;
	if (result.second>0) {
		std::uninitialized_fill ( result.first, result.first+result.second, demo );
	}
	std::return_temporary_buffer(result.first);
	return 0;
}

void test_uninitialized_fill()
{
	list<Demo> demolist;
	demolist.resize(10);
	
	Demo demo;
	std::uninitialized_fill(demolist.begin(), demolist.end(), demo);
}

int main(void)
{
	test_uninitialized_fill();
	return 0;
}


