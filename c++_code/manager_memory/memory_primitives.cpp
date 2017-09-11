/*
 * C++ memory primitivies
 * */
#include <stdlib.h>
#include <complex>
#include <iostream>

using std::complex;

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

	return 0;
}


