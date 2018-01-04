#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;

class Foo {
public:
	void memberFunc(double a, int i, int j)
	{
		cout << a << endl;
		cout << i << endl;
		cout << j << endl;
	}
};

bool test(int a, double b)
{
	cout << "a " << a << " b " << b << endl;
	return false;
}

int main(int argc, char *argv[])
{
	Foo foo;
	boost::function<void (int, int)> fp = boost::bind(&Foo::memberFunc
														, &foo, 0.5, _1, _2);

	fp(100, 200);
	//0.5
	//100
	//200

	boost::function<void (int, int)> fp2 = boost::bind(&Foo::memberFunc
														, boost::ref(foo)
														, 0.5, _1, _2);
	fp2(55, 66);	
	//0.5
	//55
	//66

	boost::function<bool (double)> fp3 = boost::bind(&test, 5, _1);
	fp3(100.0);
	//a 5 b 100

	return 0;
}
