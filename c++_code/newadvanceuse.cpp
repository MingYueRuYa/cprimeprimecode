/*
   new的高级用法
 */
#include <iostream>
#include <new>
const int buf(512); //限定一个常量整数 512
int N(5); //数组的长度
char buffer[buf] = {0}; //存储在静态区

//总结：
//p1，p3，p5作为指针变量在戦区，存储的地址指向堆区
//需要手动回收内存

//p2,p4,p6 作为指针变量在戦区，存储的地址在静态区。也叫缓冲区
//自动释放内存，用于分配用完了就不会再用的数据
//避免了内存泄漏，自动释放内存。牺牲了内存访问的独立性
using namespace std;

int main()
{
	double *p1, *p2;
	p1 = new double[N];  //分配内存大小为N个元素
	p2 = new (buffer)double[N]; //指定区域分配内存大小
	for(int i = 0; i < N; i++) {
		p1[i] = p2[i] = i + 10.8; //数组初始化
		std::cout << "p1 value " << &p1[i] << "  " << p1[i];
		std::cout << " p2 value " << &p2[i] << "  " << p2[i] << std::endl;
	}
	double *p3 = new double[N];  //分配内存大小为N个元素
	double *p4 = new (buffer)double[N]; //指定区域分配内存大小
	for(int i = 0; i < N; i++) {
		p3[i] = p4[i] = i + 10.8; //数组初始化
		std::cout << "p3 value " << &p3[i] << "  " << p3[i];
		std::cout << " p4 value " << &p4[i] << "  " << p4[i] << std::endl;
	}

	double *p5 = new double[N];  //分配内存大小为N个元素
	double *p6 = new (buffer)double[N]; //指定区域分配内存大小
	for(int i = 0; i < N; i++) {
		p5[i] = p6[i] = i + 10.8; //数组初始化
		std::cout << "p5 value " << &p5[i] << "  " << p5[i];
		std::cout << " p6 value " << &p6[i] << "  " << p6[i] << std::endl;
	}


	return 0;
}


