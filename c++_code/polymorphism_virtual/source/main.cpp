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
private:
    int m_data5;    //如果成员是private则不会向下传递到子类中
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
    void ShowAddres() { printf("ClassB vfunc1 address:%x.\n", &ClassB::vfunc1); }
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

    cout << "------------member offset------------" << endl;
    //&ClassC::ClassA::m_data1:4.
    printf("&ClassC::ClassA::m_data1:%x.\n", &ClassC::ClassA::m_data1);
    //&ClassC::ClassA::m_data2 : 8.
    printf("&ClassC::ClassA::m_data2:%x.\n", &ClassC::ClassA::m_data2);
    //&ClassC::m_data3 : c.
    printf("&ClassC::m_data3:%x.\n", &ClassC::m_data3);
    //&ClassC::m_data1 : 10.
    printf("&ClassC::m_data1:%x.\n", &ClassC::m_data1);
    //&ClassC::m_data4 : 14.
    printf("&ClassC::m_data4:%x.\n", &ClassC::m_data4);
    cout << "------------member offset------------" << endl;
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

    cout << 
        "--------------- no object virtual function address ---------------" 
         << endl;
    printf("A:vfun1:%x.\n", &(ClassA::vfunc1));
    printf("A:vfun2:%x.\n", &(ClassA::vfunc2));
    printf("B:vfun1:%x.\n", &(ClassB::vfunc1));
    printf("B:vfun2:%x.\n", &(ClassB::vfunc2));
    printf("C:vfun1:%x.\n", &(ClassC::vfunc1));
    printf("C:vfun2:%x.\n", &(ClassC::vfunc2));
    cout << 
        "--------------- no object virtual function address ---------------" 
         << endl;
    //result:
        //A:vfun1:c514e2.
        //B:vfun1:c514e2.
        //C:vfun1:c514e2.
        //A:vfun2:c514dd.
        //B:vfun2:c514dd.
        //C:vfun2:c514dd.
    //这里看出虚函数vfun1, vfun2地址都是一样的 
}

};

namespace no_natrual_polymorphism
{
class CPoint2d
{
public:
    CPoint2d(float x = 0.0, float y = 1.0)
        :_x(x), _y(y) {};
    float x() { return _x; }
    void x(float newX)  { _x = newX; }

    float y() { return _y; }
    void y(float newY)  { _y = newY; }

    virtual float z() { return 0.0; }
    virtual void z(float) {}

public:
    float _x, _y;
};

class CPoint3d : public CPoint2d
{
public:
   CPoint3d(float x = 0.0, float y = 1.0, float z = 2.0) 
       : CPoint2d(x, y), _z(z) {};

    virtual float z() { cout << "Point3D" << endl; return _z; }
    virtual void z(float newZ) { cout << "Point3D" << endl;/*_z = newZ;*/  }

public:
    float _z;
};

class CVertex
{
public:
    virtual void foo() { std::cout << "vertex foo..." << std::endl; }

public:
    CVertex *next;
};

class CVertex3d : public CPoint3d, public CVertex
{
public:
    CVertex3d(float m = 5.0) { mumble = m;}

public:
    float mumble;
};

void test_memeber_layout()
{
    cout <<"-----------member layout-----------"<< endl;
    cout << "CVertex3d size:" << sizeof(CVertex3d) << endl;
    printf("_x:%x.\n", &CVertex3d::_x);
    printf("_y:%x.\n", &CVertex3d::_y);
    printf("_z:%x.\n", &CVertex3d::_z);
    printf("next:%x.\n", &CVertex3d::CVertex::next);
    printf("mumble:%x.\n", &CVertex3d::mumble);
    //result:
        //CVertex3d size : 28
        //_x : 4.
        //_y : 8.
        //_z : c.
        //next : 4. //这个偏移量奇怪是在CVertex中相对偏移量
        //mumble : 18.

    CVertex3d av3d;
    cout << &av3d << endl;          //006FF81C
    cout << &(av3d._x) << endl;     //006FF820
    cout << &(av3d._y) << endl;     //006FF824
    cout << &(av3d._z) << endl;     //006FF828
    //_z与next之间相差8bytes，因为是在006FF82C这个地址格式虚表
    cout << &(av3d.next) << endl;   //006FF830
    cout << &(av3d.mumble) << endl; //006FF834

    printf("_x:%f.\n", *(float *)((char *)&av3d+4));
    printf("_y:%f.\n", *(float *)((char *)&av3d+8));
    printf("_z:%f.\n", *(float *)((char *)&av3d+12));
    printf("%#x.\n", *(long *)((char *)&av3d+16));  //第二个虚表地址
    printf("%#x.\n", *(long *)((char *)&av3d+20));
    printf("mumber:%f.\n", *(float *)((char *)&av3d+24));

    cout <<"-----------member layout-----------"<< endl;

    cout <<"-----------print first vptr-----------"<< endl;
    //v is address of vptr
    void *v;
    //vtbl is the address of vtbl
    void *vtbl;
    v = (void *)&av3d;
    vtbl = (void *)(*(long *)v);
    printf("1st vptr = %#x \n", *(long *)v);
    for (int i=0; i<6; ++i) {
        //二级指针
        printf("1st vtbl[%d]=%#x \n", i, *((long *)vtbl+i));
    }

    //result:
        //1st vptr = 0x9fed18
        //1st vtbl[0] = 0x9f138e
        //1st vtbl[1] = 0x9f1339
        //1st vtbl[2] = 0
        //1st vtbl[3] = 0xa00478
        //1st vtbl[4] = 0x9f1447
        //1st vtbl[5] = 0
    cout <<"-----------print first vptr-----------"<< endl;

    cout <<"-----------print second vptr-----------"<< endl;
    v = (void*)((char *)&av3d + sizeof(CPoint3d));
    printf("2st vptr = %#x \n", *(long *)v);
    vtbl = (void *)(*(long *)v);
    for (int i=0; i<6; ++i) {
        //二级指针
        printf("2st vtbl[%d]=%#x \n", i, *((long *)vtbl+i));
    }
    //result:
        //2st vptr = 0x9fed28
        //2st vtbl[0] = 0x9f1447
        //2st vtbl[1] = 0
        //2st vtbl[2] = 0x2d2d2d2d
        //2st vtbl[3] = 0x2d2d2d2d
        //2st vtbl[4] = 0x6d2d2d2d
        //2st vtbl[5] = 0x65626d65
    cout <<"-----------print second vptr-----------"<< endl;

    // 准备想模仿linux下直接调用虚函数，测试发现两者的虚函数表布局不一样
    // 在linux下如果是多继承的话，所有的虚函数表放在开头出，然后
    // 是一个数组形式的函数指针
    //typedef void (*Fun)();
    //Fun fun = (Fun)*((long*)vtbl+0);
    //fun();
    //fun = (Fun)*((long*)vtbl+1);
    //fun();
    // 当调用第二个虚函数表的时候，发现虚函数表位置不正确
    //fun = (Fun)*((long*)vtbl+2);
    //fun();
}

}


int main(int argc, char *argv[])
{
	//print_address();

	//test_vtbl_address();

	//mem_fun_layout::test_mem_fun_layout();

    no_natrual_polymorphism::test_memeber_layout();

    system("pause");
	return 0;
}
