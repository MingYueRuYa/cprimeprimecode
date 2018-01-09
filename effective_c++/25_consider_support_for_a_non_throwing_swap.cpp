/*
 * 	25 考虑写出一个不抛异常的swap函数
 * */

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::swap;

#define test_template_swap 1
// #define test_normal_swap 1

#ifdef test_normal_swap
class WidgetImpl
{
public:
	//...

private:
	int a, b, c;
	vector<double> v;

};

class Widget
{
public:
	Widget() : impl(new WidgetImpl())
	{

	}
	Widget(const Widget &rhs) {}
	Widget &operator=(const Widget &rhs) {
		//...

		//...
		return *this;
	}

	void swap(Widget &p2) {
		cout << "2 step..." << endl;
		using std::swap;
		swap(impl, p2.impl);
	}

private:
	WidgetImpl *impl;	// pimpl(point to implemetation 技法)
						// 实际包含数据的class
};

namespace std {
template<>
void swap<Widget>(Widget &p1, Widget &p2) {
  cout << "1 step..." << endl;
  p1.swap(p2);
};
}

void normal_swap()
{
	Widget w1;
	Widget w2;
	swap(w1, w2);
	cout << "normal swap" << endl;
	
	//result:
		//1 step...
		//2 step...
}

#elif test_template_swap

namespace WidgetStuff
{
template<typename T>
class WidgetImpl {
	//...data member
};

template<typename T>
class Widget {
public:
	void swap(Widget<T> w1) {
		cout << "2 step..." << endl;
		using std::swap;
		swap(this->impl, w1.impl);
	}

private:
	WidgetImpl<T> *impl;
};

template<typename T>
void swap(Widget<T> &w1, Widget<T> &w2)
{
	cout << "1 step..." << endl;
	w1.swap(w2);
}

void template_swap()
{
	// using WidgetStuff;

	Widget<int> w1;	
	Widget<int> w2;	
	swap(w1, w2);
	cout << "template swap" << endl;
}

};

#endif //

int main(int argc, char *argv[])
{
#ifdef test_normal_swap
	normal_swap();
#else
	WidgetStuff::template_swap();
#endif
	return 0;
}
