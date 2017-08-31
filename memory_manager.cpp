/****************************************************************
 **
 **	Copyright (C) 2017 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

//测试环境 Linux raspberrypi 4.4.13-v7+ #894 SMP Mon Jun 13 13:13:27 BST 2016 armv7l GNU/Linux
//Using built-in specs.
//COLLECT_GCC=g++
//COLLECT_LTO_WRAPPER=/usr/lib/gcc/arm-linux-gnueabihf/4.9/lto-wrapper
//Target: arm-linux-gnueabihf
//Configured with: ../src/configure -v --with-pkgversion='Raspbian 4.9.2-10' --with-bugurl=file:///usr/share/doc/gcc-4.9/README.Bugs --enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.9 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.9 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --disable-libitm --disable-libquadmath --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.9-armhf/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.9-armhf --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.9-armhf --with-arch-directory=arm --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-sjlj-exceptions --with-arch=armv6 --with-fpu=vfp --with-float=hard --enable-checking=release --build=arm-linux-gnueabihf --host=arm-linux-gnueabihf --target=arm-linux-gnueabihf
//Thread model: posix
//gcc version 4.9.2 (Raspbian 4.9.2-10) 

/*
 * 内存管理学习 Tue Aug 29 23:13:56 CST 2017
 *
 * */

#include <stdlib.h>

#include <iostream>
#include <string>
#include <complex>
#include <memory>

using namespace std;

namespace demo01
{
void test_primitives()
{
	cout << "\ntest_primitives()..........\n";
	void *p1 = malloc(512);	//512 bytes
	free(p1);
	p1 = NULL;

	complex<int> *p2 = new complex<int>;	//one object
	delete p2;
	p2 = NULL;

	void *p3 = ::operator new(512);	//512 bytes
	::operator delete(p3);
	p3 = NULL;

//以下使用c++标准库提供的allocators.
//其接口虽有标准规范，但实现厂商并未完全遵守：下面三者形式略异
#ifdef _MSC_VER
	//以下两个函数都是non-static，定要通过object调用。以下分配3个ints
	int *p4 = allocator<int>().allocate(3, (int*)0);
	allocator<int>().deallocate(p4, 3);
#endif

#ifdef __BORLANDC__
	//以下两个函数都是non-static，定要通过object调用。以下分配3个ints
	int *p5 = allocator<int>().allocate(3);
	allocator<int>().deallocate(p5, 3);
#endif

#ifdef __GUNC__
	//以下兩函數都是 static，可通過全名調用之。以下分配 512 bytes.
	//void *p6 = alloc::allocate(512);
	//alloc::deallocate(p4, 512);

	//以下兩函數都是 non-static，定要通過 object 調用。以下分配 3 個 ints.    
	int *p7 = allocator<int>().alllocate(3);
	allocator<int>().deallocate(p7, 3);

	//以下兩函數都是 non-static，定要通過 object 調用。以下分配 3 個 ints.    
	void *p8 = __gun_cxx::__pool_alloc<int>().allocate(3);
	__gun_cxx::__pool_alloc<int>().deallocate(p8, 3);
#endif
}
}

namespace demo02
{
class A
{
public:
	int id;

	A():id(0) {cout << "default ctor. this=" << this << " id=" << id << endl;}
	A(int i):id(i){cout << "ctor. this=" << this << " id=" << id << endl;}
	~A() {cout << "dtor, this=" << this << " id=" << id << endl;}
};

void test_call_ctor_directory()
{
	cout << "\ntest_call_ctor_directory().......\n";
	string *pstr = new string("liushixiong like program!");
	cout << "str= " << *pstr << endl;
	//! pstr->string::string("demo2"); [Error] 'class std::basic_string<char>' has no member named 'string'
 
	pstr->~string(); //crash ----其语法语义是正确的，crash只因为上一行被remark起来[侯捷]，但是实际情况在pi环境下测试并没有crash，此处灰色地带

	A *pA = new A(1); //ctor. this=0x16d8048 id=1
	cout << pA->id << endl; // 1
	//! pA->A::A(3); //in VC6 : ctor, this0013FF60 id 3
					 //in GCC : [Error] cannot call constructor ‘demo02::A::A’ directly

	cout << pA->id << endl; 		//in VC6 : 3
									//in GCC : 1
	pA->~A(); 						//dtor, this=0xd37048 id=1，手动调用析构函数
	cout << pA->id << endl; 		//测试内存是否被手动调用析构函数释放，但其实内存并没有释放

	delete pA;						// dtor, this=0x16d8048 id=1

	//simulate new
	void *p = ::operator new(sizeof(A));
	cout << "p=" << p << endl;		//this=000307A8
	pA = static_cast<A *>(p);
	//! pA->A(2); 					//[Error]: invalid use of ‘demo02::A::A’
	//!	pA->A::A(2);				//in VC6 : ctor. this=000307A8 id=2
									//in GCC : [Error] cannot call constructor 'demo02::A::A' directly 
	cout << pA->id << endl;			//in VC6 : 2
									//in GCC : 0

	//simulate delete
	pA->~A(); 						//dtor. this=000307A8, id=0
	::operator delete(pA);			//free();	
}
}

int main(int argc, char *argv[])
{
	demo01::test_primitives();
	demo02::test_call_ctor_directory();
	return 0;
}
