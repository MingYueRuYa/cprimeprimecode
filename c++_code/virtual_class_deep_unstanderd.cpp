#include <iostream>

using namespace std;

class Base {
public:
	virtual void f() { cout << "Base::f" << endl;};
	virtual void g() { cout << "Base::g" << endl;};
	virtual void h() { cout << "Base::h" << endl;};
};

class Drived : public Base {
public:
	virtual void f() { cout << "Drived::f" << endl;};
//	virtual void g() { cout << "Drived::g" << endl;};
//	virtual void h() { cout << "Drived::h" << endl;};
};

typedef void (*Fun)();

int main02(void)
{
	Base b;
	Fun pFun = NULL;
	cout << "virtual table address:" << (int *)*(int *)(&b) << endl;
	cout << "virtual table first function address:" << (int *)*(int *)*(int *)(&b) << endl;
	

	pFun = (Fun)*((int *)*(int *)(&b) + 0);
	pFun();

	//attention: add 2 because in x64 OS, pointer sizese 8
	//pFun =(Fun)*((int *)*(int *)(&b) + 2); 
	pFun =(Fun)*((int *)*(int *)(&b) + sizeof(int *)/sizeof(int)); 
	pFun();

	pFun =(Fun)*((int *)*(int *)(&b) + 2*sizeof(int *)/sizeof(int));
	pFun();

	Drived d;
	pFun = (Fun)*((int *)*(int *)(&d) + 0);
	pFun();

	pFun = (Fun)*((int *)*(int *)(&d) + sizeof(int *)/sizeof(int));
	pFun();

	pFun = (Fun)*((int *)*(int *)(&d) + 2*sizeof(int *)/sizeof(int));
	pFun();
	
	//虚表的最后面是0表示没有虚函数了，如果还有为1
	pFun = (Fun)*((int *)*(int *)(&d) + 3*sizeof(int *)/sizeof(int));
	cout << pFun << endl;
	
	//this also invoke drived f function.
	(static_cast<Base *>(&d))->f();

//result:	
	//	virtual table address:0xbfe8bbd4
	//	virtual table first function address:0x8049028
	//	Base::f
	//	Base::g
	//	Base::h
	//	Drived::f
	//	Base::g
	//	Base::h
	//	0
	//	Drived::f

	return 0;
}

class Base1 {
public:
	virtual void f() { cout << "Base1:f" << endl;};
	virtual void g() { cout << "Base1:g" << endl;};
	virtual void h() { cout << "Base1:h" << endl;};
};


class Base2 {
public:
	virtual void f() { cout << "Base2:f" << endl;};
	virtual void g() { cout << "Base2:g" << endl;};
	virtual void h() { cout << "Base2:h" << endl;};
};


class Base3 {
public:
	virtual void f() { cout << "Base3:f" << endl;};
	virtual void g() { cout << "Base3:g" << endl;};
	virtual void h() { cout << "Base3:h" << endl;};
};

class Derive : public Base1, public Base2, public Base3 {
public:
	virtual void f() { cout << "Devive:f" << endl;};
	//virtual void g() { cout << "Devive:g" << endl;};
};

int main(void)
{
	Fun pFun = NULL;
	Derive d;
	int **pVtab = (int **)&d;
	//Base1's vtable
	pFun = (Fun)pVtab[0][0];
	pFun();

	pFun = (Fun)pVtab[0][1];
	pFun();

	pFun = (Fun)pVtab[0][2];
	pFun();

	//the tail of vtable
	pFun = (Fun)pVtab[0][3];
	cout << pFun << endl;
	
	//Base2's vtable
	pFun = (Fun)pVtab[1][0];
	pFun();

	pFun = (Fun)pVtab[1][1];
	pFun();

	pFun = (Fun)pVtab[1][2];
	pFun();
	
	pFun = (Fun)pVtab[1][3];
	cout << pFun << endl;
	
	//Base3's vtable
	pFun = (Fun)pVtab[2][0];
	pFun();

	pFun = (Fun)pVtab[2][1];
	pFun();

	pFun = (Fun)pVtab[2][2];
	pFun();

	pFun = (Fun)pVtab[2][3];
	cout << pFun << endl;
	return 0;
}


