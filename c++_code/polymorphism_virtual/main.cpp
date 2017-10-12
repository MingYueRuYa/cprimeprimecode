#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;

class ClassA
{
public:
	int m_data1;
	int m_data2;

	void func1() { cout << "ClassA::func1" << endl; }
	void func2() { cout << "ClassA::func2" << endl; }

	virtual void vfunc1() { cout << "ClassA::vfunc1" << endl; }
	virtual void vfunc2() { cout << "ClassA::vfunc2" << endl; }
};

class ClassB : public ClassA
{
public:
	int m_data3;

	void func2() { cout << "ClassB::func2" << endl; }

	virtual void vfunc1() { cout << "ClassB::vfunc1" << endl; }
};

class ClassC : public ClassB
{
public:
	int m_data1;
	int m_data4;

	void func2() { cout << "ClassC::func2" << endl; }

	virtual void vfunc1() { cout << "ClassC::vfunc1" << endl; }
};

void print_address()
{
	ClassA a; 
	ClassB b; 
	ClassC c;

	cout << &a << endl;				//0xbf8f0cbc
	cout << &(a.m_data1) << endl;	//0xbf8f0cc0
	cout << &(a.m_data2) << endl;	//0xbf8f0cc4
	cout << &b << endl;				//0xbf8f0cc8
	cout << &(b.m_data1) << endl;	//0xbf8f0ccc
	cout << &(b.m_data2) << endl;	//0xbf8f0cd0
	cout << &(b.m_data3) << endl;	//0xbf8f0cd4
	cout << &c << endl;				//0xbf8f0cd8
	cout << &(c.ClassA::m_data1) << endl;	//0xbf8f0cdc
	cout << &(c.m_data2) << endl;	//0xbf8f0ce0
	cout << &(c.m_data3) << endl;	//0xbf8f0ce4
	cout << &(c.m_data1) << endl;	//0xbf8f0ce8
	cout << &(c.m_data4) << endl;	//0xbf8f0cec
	//从上面的地址来看，地址都是连续的
}

/*! 
 * 测试vtbl的地址
 * */
void test_vtbl_address()
{
	ClassB b1, b2, b3;
	
	cout << "b1 address=" << &b1 << endl; //b1 address=0xbff980b0
	cout << "b2 address=" << &b2 << endl; //b2 address=0xbff980c0
	cout << "b3 address=" << &b3 << endl; //b3 address=0xbff980d0

	long *v1, *v2, *v3; // 代表 b1, b2, b3 的 vptr
	v1 = (long *)&b1;
	v2 = (long *)&b2;
	v3 = (long *)&b3;
	printf("%x \n",*v1); //8048d60 
	printf("%x \n",*v2); //8048d60 
	printf("%x \n",*v3); //8048d60 

}

namespace mem_fun_layout
{
/*! 
 * 测试memeber function 布局 
 * */
void test_mem_fun_layout()
{
	ClassA a;
	ClassB b;
	ClassC c;

	long *v;	//v is the address of vptr
	long *vtbl0;//vtabl0 is the address of vtbl[0]

	v = (long *)&a;
	vtbl0 = (long *)(*v);
	cout << "vtbl0 " << vtbl0 << endl;
	cout << "&a " << v << endl;
	for (int i=0; i<6; ++i) {
		printf("ClassA vtbl[%d]=%#x \n", i, vtbl0[i]);
	}
	//vtbl0 0x8048f48
	//ClassA vtbl[0]=0x8048ce8 
	//ClassA vtbl[1]=0x8048d14 
	//ClassA vtbl[2]=0x616c4336 
	//ClassA vtbl[3]=0x437373 
	//ClassA vtbl[4]=0x804b128 
	//ClassA vtbl[5]=0x8048f50 

	v = (long *)&b;
	vtbl0 = (long *)(*v);
	cout << "vtbl0 " << vtbl0 << endl;
	cout << "&a " << v << endl;
	for (int i=0; i<6; ++i) {
		printf("ClassB vtbl[%d]=%#x \n", i, vtbl0[i]);
	}
	//vtbl0 0x8048f38
	//ClassB vtbl[0]=0x8048d40 
	//ClassB vtbl[1]=0x8048d14 
	//ClassB vtbl[2]=0 
	//ClassB vtbl[3]=0x8048f80 
	//ClassB vtbl[4]=0x8048ce8 
	//ClassB vtbl[5]=0x8048d14 

	v = (long *)&c;
	vtbl0 = (long *)(*v);
	cout << "vtbl0 " << vtbl0 << endl;
	cout << "&a " << v << endl;
	for (int i=0; i<6; ++i) {
		printf("ClassC vtbl[%d]=%#x \n", i, vtbl0[i]);
	}
	//vtbl0 0x8048f28
	//ClassC vtbl[0]=0x8048d6c 
	//ClassC vtbl[1]=0x8048d14 
	//ClassC vtbl[2]=0 
	//ClassC vtbl[3]=0x8048f6c 
	//ClassC vtbl[4]=0x8048d40 
	//ClassC vtbl[5]=0x8048d14 

	cout << endl;
	cout << &a << endl;				//0xbf8f0cbc
	cout << &(a.m_data1) << endl;	//0xbf8f0cc0
	cout << &(a.m_data2) << endl;	//0xbf8f0cc4
	cout << &b << endl;				//0xbf8f0cc8
	cout << &(b.m_data1) << endl;	//0xbf8f0ccc
	cout << &(b.m_data2) << endl;	//0xbf8f0cd0
	cout << &(b.m_data3) << endl;	//0xbf8f0cd4
	cout << &c << endl;				//0xbf8f0cd8
	cout << &(c.ClassA::m_data1) << endl;	//0xbf8f0cdc
	cout << &(c.m_data2) << endl;	//0xbf8f0ce0
	cout << &(c.m_data3) << endl;	//0xbf8f0ce4
	cout << &(c.m_data1) << endl;	//0xbf8f0ce8
	cout << &(c.m_data4) << endl;	//0xbf8f0cec
	//从上面的地址来看，地址都是连续的

}
};


int main(int argc, char *argv[])
{
	//print_address();

	//test_vtbl_address();

	mem_fun_layout::test_mem_fun_layout();

	return 0;
}
