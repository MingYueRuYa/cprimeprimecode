/*
 * vector 练习
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

void print(const int &pNum)
{
	cout << pNum << endl;		
}

void printstr(const string &pNum)
{
	cout << pNum << endl;		
}

class Demo
{
public:
	Demo(const int pID): mID(pID) { cout << "demo ctor " << mID << endl; }
	~Demo() { cout << "demo dtor " << mID << endl; }
	void Print() { cout << "print demo " << mID << endl; }

	Demo(const Demo &pDemo) { cout << "copy ctor " << pDemo.mID << endl; }

	Demo operator=(const Demo &pDemo) 
	{ 
		cout << "assignment ctor " << pDemo.mID << endl; 
		return *this;
	}

private:
	int mID;
	char *name;
};

class Object
{
public:
	Object() { cout << "object ctor..." << endl; }
	~Object() { cout << "~object dtor..." << endl; }
	Object(const Object &) { cout << "copy object ctor." << endl; }
	virtual void Show() {}
};

int main01(int argc, char *argv[])
{
	vector<int> intvector = {1, 2, 3};
	for_each(intvector.begin(), intvector.end(), print);
	vector<int> intvector01(10, -1);
	//for_each(intvector01.begin(), intvector01.end(), print);
	//vector<int> intvector02(intvector01.begin(), intvector01.end());
	//for_each(intvector02.begin(), intvector02.end(), print);
	vector<int> intvector03 = intvector;
	//for_each(intvector03.begin(), intvector03.end(), print);
	vector<int>::iterator begin = intvector.begin();
	vector<int>::iterator insertiterator = intvector.insert(begin, 4);
	cout << *insertiterator;
	return 0;
}

void test_erase_function()
{
	vector<Demo *>demovec;

	for (int i=0; i<10; ++i) {
		demovec.push_back(new Demo(i));
	}

	//TODO 删除元素的时候没有发现任何的拷贝东西，同时也没有发现调用析构函数
	//这里没有调用dtor是因为Demo被认为是POD类型的数据
	demovec.erase(demovec.begin()+1);
	demovec[1]->Print();

	vector<Object> objvec;
	objvec.push_back(Object());
	//objvec.erase(objvec.begin());
}

int main(int argc, char *argv[])
{
//	vector<string> vectorstring;
//	string inputstr;
//	while (cin >> inputstr) {
//		vectorstring.push_back(inputstr);
//	}
//	for_each(vectorstring.begin(), vectorstring.end(), printstr);

	test_erase_function();

	return 0;
}

