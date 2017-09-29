/*
 * 智能指针
 **/

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <exception>

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;

class Demo
{
public:
	Demo () { cout << "demo ctor." << endl; }
	~Demo () { cout << "demo dtor." << endl; }
	void show() { cout << "demo show" << endl; }
};

void test_auto_ptr()
{
	std::auto_ptr<Demo> autop1(new Demo());
	std::auto_ptr<Demo> autop2;
	autop2 = autop1;
	(*autop2).show();
	//! (*autop1).show(); //warning: 因为将autop1赋值给autop2，所以指针的控制权转移到autop2，autop1为空指针。再调用autop1是危险的事
						  //但在pi下测试没有shutdown
}

std::unique_ptr<int> make_int(int n)
{
	return std::unique_ptr<int>(new int(n));
}

void show(std::unique_ptr<int> &p1)
{
	cout << *p1 << ' ';
}

void test_unique_ptr()
{
	std::unique_ptr<int> uni1(new int(10));
	//! std::unique_ptr<int> uni2 = uni1; // error: use of deleted function 
										  //‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
	//std::unique_ptr<class> 不允许显式copy，因为copy之后uni1控制权转移给uni2,此时uni1为空。这个编译器检查出有隐患。所以报错
	//但是unique_ptr比较智能，如果是temporary转为unique_ptr则是允许
	std::vector<std::unique_ptr<int>> vp(5);
	for (int i=0; i<vp.size(); ++i) {
		vp[i] = make_int(rand()%1000);		//copy temporary unique_str
	}
	vp.push_back(make_int(rand()%1000));		//copy temporary unique_str
	
	for_each(vp.begin(), vp.end(), show);
}

void free_demo(Demo *pDemo) { cout << "free demo..." << endl; }

void test_share_point()
{
	Demo demo;
	//std::shared_ptr<Demo> demo_ptr(&demo, free_demo);
	std::shared_ptr<Demo> demo_ptr2(new Demo());
	throw "test throw exception.";
}

vector<shared_ptr<Demo>> g_vector;

void test_vector_shared_ptr()
{
//	shared_ptr<Demo> demoptr = make_shared<Demo>();
//
//	vector<shared_ptr<Demo>> shared_vector{demoptr};

	//当vector中元素没有用处，使用erase移除元素，智能指针会自动调用析构函数
	g_vector.push_back(make_shared<Demo>());
	cout << "vector eraser...." << endl;
	g_vector.erase(g_vector.begin());
	cout << "vector eraser...." << endl;
//result:
	//	demo ctor.
	//	vector eraser....
	//	demo dtor.
	//	vector eraser....
}


int main()
{
	/*
	for(int i = 0; i < 1000; i++){
		double *p = new double;
		std::auto_ptr<double> autop(p);
		//创建智能指针管理指针p指向内存
		//智能指针
	}
	//新型智能指针，可以直接new一个对象进去
	std::auto_ptr<double> autop(new double);
	*/

	//test_auto_ptr();	
	//test_unique_ptr();	
<<<<<<< HEAD
	test_share_point();

=======

	/*
	std::vector<std::unique_ptr<int>> vp(5);
	for (int i=0; i<vp.size(); ++i) {
		vp[i] = make_int(rand()%1000);		//copy temporary unique_str
	}
	vp.push_back(make_int(rand()%1000));		//copy temporary unique_str
	
	for_each(vp.begin(), vp.end(), show);
	*/

	test_vector_shared_ptr();
>>>>>>> 3e3b2b2f59bf6539b86e39044943d5e59021bac9

	return 0;
}
