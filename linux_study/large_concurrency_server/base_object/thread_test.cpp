#include <unistd.h>

#include <iostream>
#include <boost/bind.hpp>

#include "thread.h"

using std::cout;
using std::endl;

class Foo
{
public:
	explicit Foo(int count): mCount(count)
	{
	}

	void MemberFunc()
	{
		while (mCount--) {
			cout << "this is a test ..." << endl;
			sleep(1);
		}
	}

	void MemberFunc2(int count)
	{
		while (count--) {
			cout << "this is a MemberFunc2 ..." << endl;
			sleep(1);
		}
	}

public:
	int mCount;
};

void ThreadFunc()
{
	cout << "ThreadFunc..." << endl;
}

void ThreadFunc2(int count)
{
	while (count--) {
		cout << "this is a ThreadFunc2 ..." << endl;
		sleep(1);
	}
}

int main(void)
{
	Thread t1(ThreadFunc);	
	t1.Start();
		
	Thread t2(boost::bind(ThreadFunc2, 5));
	t2.Start();

	Foo foo(5);
	Thread t3(boost::bind(&Foo::MemberFunc, boost::ref(foo)));
	t3.Start();

	// Foo foo(5);
	Thread t4(boost::bind(&Foo::MemberFunc2, boost::ref(foo), 5));
	t4.Start();

	t1.Join();
	t2.Join();
	t3.Join();
	t4.Join();
	// result:
		// this is a MemberFunc2 ...
		// this is a test ...
		// this is a ThreadFunc2 ...
		// ThreadFunc...
		// this is a MemberFunc2 ...
		// this is a test ...
		// this is a ThreadFunc2 ...
		// this is a MemberFunc2 ...
		// this is a test ...
		// this is a ThreadFunc2 ...
		// this is a MemberFunc2 ...
		// this is a test ...
		// this is a ThreadFunc2 ...
		// this is a MemberFunc2 ...
		// this is a test ...
		// this is a ThreadFunc2 ...
	
	return 0;
}

