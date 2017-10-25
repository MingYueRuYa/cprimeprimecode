/*
 * typeid用法
 * typeid(type|expr)返回一个const type_info &类型
 * */
#include <string>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;
using std::string;
using std::type_info;

class B	//base class, non polymorphic
{
public:
	int mData1;
};

class D : public B
{
public:
	int mData2;
};

class C
{
	virtual void fun() { cout << "C fun..." << endl; }
};

class E : public C
{
	virtual void fun() { cout << "E fun..." << endl; }
};


int main(int argc, char *argv[])
{
	B *pb = new B();
	D *pd = new D();

	string info = (typeid(B) == typeid(*pb) 
			? "pb is B type." : "pb is not B type");
	cout << info << endl;

	info = (typeid(D) == typeid(*pd) 
			? "pb is D type." : "pb is not D type");
	cout << info << endl;

	cout << "pb's type name:" << typeid(pb).name() << endl;
	cout << "pd's type name:" << typeid(pd).name() << endl;

	cout << "*pb's type name:" << typeid(*pb).name() << endl;
	cout << "*pd's type name:" << typeid(*pd).name() << endl;

	info = typeid(pb).before(typeid(pd)) 
		? "pb before pd." : "pb not before pd.";
	cout << info << endl;

	info = typeid(*pb).before(typeid(*pd)) 
		? "*pb before *pd." : "*pb not before *pd.";
	cout << info << endl;

	B *b1 = new D();	//base ptr point to derived object
	cout << "b1's type name:" << typeid(b1).name() << endl;
	cout << "*b1's type name:" << typeid(*b1).name() << endl;

	info = typeid(*b1).before(typeid(B)) 
		? "b1 before B." : "b1 not before B.";
	cout << info << endl;

	info = typeid(*b1).before(typeid(D)) 
		? "*b1 before D." : "*b1 not before D.";
	cout << info << endl;

	C *c1 = new E();	//base ptr point to derived object
	cout << "c1's type name:" << typeid(c1).name() << endl;
	cout << "*c1's type name:" << typeid(*c1).name() << endl;

	info = typeid(*c1).before(typeid(C)) 
		? "c1 before C." : "c1 not before C.";
	cout << info << endl;

	info = typeid(*c1).before(typeid(E)) 
		? "*c1 before E." : "*c1 not before E.";
	cout << info << endl;
//result:
	//pb is B type.
	//pb is D type.
	//pb's type name:P1B
	//pd's type name:P1D
	//*pb's type name:1B
	//*pd's type name:1D
	//pb before pd.
	//*pb before *pd.
	//b1's type name:P1B	//is ok.
	//*b1's type name:1B	//accient
	//b1 not before B.		//is ok.
	//*b1 before D.			//accient

	//notice: polymorphic class...
	//c1's type name:P1C
	//*c1's type name:1E
	//c1 not before C.
	//*c1 not before E.
	return 0;
}
