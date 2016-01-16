/*
 * list 操作
 * */
#include <iostream> 
#include <list>
#include <algorithm>
#include <string>

//using namespace std;
using std::list;
using std::string;
using std::cout;
using std::endl;

list<string> stringlist;

template<class T>
void Print(T pBegin, T pEnd)
{
	for (; pBegin != pEnd; ++pBegin) {
		cout << *pBegin << endl;		
	}
}

void PrintForEach(string pOSName)
{
	cout << pOSName << endl;
}

void Init()
{
	stringlist.push_back("linux");
	stringlist.push_back("freeBSD");
	stringlist.push_front("unix");
	stringlist.push_back("0001 Soap");
	stringlist.push_back("0002 Shampoo");
	stringlist.push_back("0003 Toothbrush");
	stringlist.push_back("0003 Toothbrush");
	stringlist.push_back("0004 Toothpaste");
}

/*******************push***********************/
int pushmain(int argc, char *argv[])
{
	stringlist.push_back("linux");
	stringlist.push_back("freeBSD");
	stringlist.push_front("unix");
	Print(stringlist.begin(), stringlist.end());
	return 0;
}
/*******************push***********************/

/*******************delete***********************/
int deletemain(int argc, char *argv[])
{
	Init();
	//在pop之前，应该要先判断容器中是否存在元素
	//弹出栈空间
	//stringlist.pop_front();		
	//stringlist.pop_back();		
	//根据位置删除
	stringlist.erase(stringlist.begin());
	//根据 元素值
	stringlist.remove("freeBSD");
	//根据范围删除
	stringlist.erase(stringlist.begin(), stringlist.end());
	Print(stringlist.begin(), stringlist.end());
	stringlist.push_back("windows");
	stringlist.push_back("linux");
	stringlist.push_back("unix");
	stringlist.push_back("freeBSD");
	//general algorithm, it return new end itrator.
	list<string>::iterator tmpiterator = remove(stringlist.begin(), stringlist.end(), "windows");
	for_each(stringlist.begin(), tmpiterator, PrintForEach);	
	return 0;
}
/*******************delete***********************/

/*******************foreach***********************/
int foreachmain(int argc, char *argv[])
{
	Init();
	stringlist.push_back("linux");
	stringlist.push_back("linux");
	//cout << stringlist.size() << endl;
	for_each(stringlist.begin(), stringlist.end(), PrintForEach);		
	return 0;
}
/*******************foreach***********************/

class IsAToothbrush
{
public:
	IsAToothbrush(string pMarkCode) : mMarkCode(pMarkCode)
	{
	}
	bool operator()(string pString)
	{
		cout << pString.substr(0, 4) << endl;
		return pString.substr(0, 4) == mMarkCode;
	}
private:
	string mMarkCode;
};

/*******************count(_if)***********************/
int count_ifmain(int argc, char *argv[])
{
	Init();
	int countnumber(0);
	countnumber = count(stringlist.begin(), stringlist.end(), "linux");
	cout << countnumber << endl;
	countnumber = 0;
	countnumber = count_if(stringlist.begin(), stringlist.end(), IsAToothbrush("0001"));	
	cout << countnumber << endl;
	
	return 0;
}
/*******************count(_if)***********************/

/*******************list operation***********************/
int operationmain(int argc, char *argv[])
{
	Init();
	list<string>::iterator finditerator = find(stringlist.begin(), stringlist.end(), "linux");
	if (finditerator != stringlist.end()) {
		//cout << *finditerator << endl;
	}
	//与之类似的就是通用算法find_if, 和之前的count_if一样


	list<char> charlist;
	charlist.push_back('\0');
	charlist.push_back('\0');
	charlist.push_back('\0');
	charlist.push_back('1');
	charlist.push_back('2');
	int zerocount(0);
	zerocount = count(charlist.begin(), charlist.end(), '\0');
	//cout << zerocount << endl;

	list<char> targecharlist(4, '\0');
	list<char>::iterator finditerator01 = search(charlist.begin(), charlist.end(), targecharlist.begin(), targecharlist.end());
	if (finditerator01 == charlist.end()) {
		cout << "Not find target char" << endl;
	} else {
		cout << *finditerator01 << endl;
	}

	int intarray[] = {1, 20, 19, 4, 5, 2};
	list<int> intlist(intarray, intarray + sizeof(intarray) / sizeof(*intarray));
	//Print(intlist.begin(), intlist.end());
	intlist.sort();
	//Print(intlist.begin(), intlist.end());
	
	intlist.insert(intlist.end(), 30);
	
	int intarray02[] = {31, 32};
	//intlist.insert(intlist.end(), &intarray02[0], &intarray[2]);
	std::vector<int> intvector{31, 32};
	//intlist.insert(intlist.end(), intarray02, intarray + 2);
	intlist.insert(intlist.end(), intvector.begin(), intvector.end());
	Print(intlist.begin(), intlist.end());
	return 0;
}
/*******************list operation***********************/

class IsAFlag
{
public:
	bool operator() (const string &pStr)
	{
		return pStr.substr(0, 1) == "-";
	}
};

class IsFileName
{
public:
	bool operator() (const string &pStr)
	{
		return !IsAFlag()(pStr);
	}
};

class IsHelpFlag
{
public:
	bool operator() (const string &pStr)
	{
		return pStr == "-h";
	}
};

int main(int argc, char *argv[])
{
	list<string> CmdParameters;
	list<string>::iterator StartOfFiles;
	list<string> flags;
	list<string> filenames;
	for (int i = 0; i < argc; ++i) {
		CmdParameters.push_back(argv[i]);
	}	
	//remove application name
	CmdParameters.pop_front();

	//for_each(CmdParameters.begin(), CmdParameters.end(), PrintForEach);	
	StartOfFiles = stable_partition(CmdParameters.begin(), CmdParameters.end(), IsAFlag());
	for_each(CmdParameters.begin(), CmdParameters.end(), PrintForEach);	
	//aution: splice 会将原来的CmdParameters中元素删除在添加到flags集合中
	flags.splice(flags.end(), CmdParameters, CmdParameters.begin(), StartOfFiles);
	for_each(flags.begin(), flags.end(), PrintForEach);
	filenames.splice(filenames.begin(), CmdParameters, CmdParameters.begin(), CmdParameters.end());
	for_each(filenames.begin(), filenames.end(), PrintForEach);
	if ((flags.begin(), flags.end(), IsHelpFlag()) == flags.end()) {
		cout << "Not find -h flag." << endl;
	}
	for_each(CmdParameters.begin(), CmdParameters.end(), PrintForEach);	
	return 0;
}


