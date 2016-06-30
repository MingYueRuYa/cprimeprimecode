/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class father
{
public:
	father(string pName)
	{
		mName = pName;
		cout << "father construct..." << mName << endl;
	}
	~father()
	{
		cout << "father desconstruct..." << mName << endl;
	}
	father(const father &pFather)
	{
		mName = pFather.mName;
		cout << "father copy construct..." << mName << endl;
	}

	void GetName()
	{
		cout << "father " << mName << endl;
	}

private:
	string mName;
};

class son : public father
{
public:
	son(string pName): father(pName)
	{
		mName = pName;
		cout << "son construct..." << mName << endl;
	}
	~son()
	{
		cout << "son desconstruct..." << mName << endl;
	}
	son(const son &pSon) : father("father")
	{
		//mName = pSon.mName;
		cout << "son copy construct..." << endl;
	}
private:
	string mName;
};
int main(int argc, char *argv[])
{
	son son02("son");
	son son01 = son02;
	return 0;
}
