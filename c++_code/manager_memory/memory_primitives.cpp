/*
 * C++ memory primitivies
 * */
#include <stdlib.h>
#include <complex>
#include <iostream>

using std::complex;
using std::cout;
using std::endl;

class Complex
{
public:
	Complex()
	{
		cout << "Complex ctor..." << endl;
	}
	Complex(int x, int y)
	{
		cout << "Complex ctor..." << "x:" << x << " y:" << y <<  endl;
	}
	~Complex()
	{
		cout << "Complex dector..." <<endl;
	}
};

int main(int argc, char *argv[])
{
	void *p1 = malloc(512); //512 bytes
	free(p1);

	complex<int> *p2 = new complex<int>; // one object
	delete p2;

	void *p3 = ::operator new(512); //512 bytes
	::operator delete(p3);

//一下使用c++标准库提供的allocators.
//其接口虽有标准规格，但实现厂商并未完全遵守；下面三者形式略异
#ifdef _MSC_VER
	//以下两个函数都是non-static,一定要通过object调用，以下分配3个int
	int *p4 = allocator<int>().allocate(3, (int *)0);
	allocator<int>().deallocate(p4, 3);
#endif //_MSC_VER

#ifdef __BORLANDC__
	//以下两个函数都是non-static,一定要通过object调用，以下分配3个int
	int *p4 = allocator<int>().allocate(5);
	allocator<int>.deallocate(p4, 5);
#endif //__BORLANDC__

#ifdef __GUNC__
	//以下两个函数都是static,可通过全名调用之。以下分配512bytes
	void *p4 = alloc::allocate(512);
	alloc::deallocate(p4, 512);
#endif //__GUNC__

	Complex *com = new Complex();
	cout << "com address " << std::hex << com << endl;

	Complex *com1 = new (com)Complex(1, 2);
	cout << "com1 address " << std::hex << com << endl;

//	result:
//	Complex ctor...
//	com address 0x14f6008
//	Complex ctor...x:1 y:2
//	com1 address 0x14f6008

	return 0;
}


