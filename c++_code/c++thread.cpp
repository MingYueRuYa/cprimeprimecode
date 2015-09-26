/*
 *	c++ 线程
 * */

#include <iostream>
#include <thread> //包含头文件
#include <vector>

using namespace std;
using namespace std::this_thread;


void CallByThread()
{
		while(1) {
			//cout << "thread id = " << get_id() << endl;
			printf("hi \n");
		}
}

int main()
{
	auto n = thread::hardware_concurrency();
	cout << n <<endl;
	thread thread01(CallByThread);	
	thread thread02(CallByThread);	
	thread01.join();
	thread02.join();
	return 0;
}
