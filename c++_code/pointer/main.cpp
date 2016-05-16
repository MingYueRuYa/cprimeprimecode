/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "strblob.h"

using namespace std;

int main01(int argc, char *argv[])
{
	StrBlob blob{"I", "like", "linux"};
	cout << blob.size() << endl;
	cout << blob.front() << " --- " << blob.back();
	return 0;
}

int main02(int argc, char *argv[])
{
	//int * const pint = new int(10) const; error
	//int * const pint = const new int(10) ; error
	const int *pint = new const int(10);
	pint = new const int(20); //correct, but this is cause memory leak.
	//*pint = 20; error
	int *pint01 = new (nothrow) int(0); //if new error, this will be not throw bad_alloc exception, but return null.

	boost::shared_ptr<int> p1(new int(80));
	boost::shared_ptr<int> p2(p1);
	p1.reset(); //p1 is equal null.
	if (nullptr == p1) {
		cout << "p1 reset." << endl;
	}
	cout << *p2 << endl;
	return 0;
}

void process(boost::shared_ptr<int> p1)
{

}

int main(int argc, char *argv[])
{
	int *p1 = new (nothrow)int(10);
	//process(boost::shared_ptr<int>(p1));
	//cout << *p1 << endl; //test: discover *p1=0. undifine action.
	boost::shared_ptr<int> p2(p1);
	process(p2);
	cout << *p1 << endl;
    {
 		//don't use p2.get() init shared_ptr, get() return build in type pointer
		//then *p1 is undifine action.
		boost::shared_ptr<int> p3(p2.get());
	}
	cout << *p1 << endl;

	//judge p2 is or not unique user.
	if (p2.unique()) {
		p2.reset(new int(70));
	}
	else {
		*p2 += 20;
	}
	return 0;
}

