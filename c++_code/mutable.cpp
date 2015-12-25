/*
	mutabel key word
*/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class A
{
public:
	A() = default;

	~A()
	{
	
	}

	void TestMutable() const
	{
		mutablevar++;
		cout << "test mutable var. mutablevar value is " << mutablevar << endl;
	}

private:
	mutable int mutablevar = 0;

};
int main(int argc, char **argv)
{
	const A a;
	a.TestMutable();
	a.TestMutable();
	a.TestMutable();
	return 0;
}
