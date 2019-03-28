// unittest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include <iostream>

#include "commonpack.h"

using std::cout;
using std::endl;
using std::shared_ptr;

using XIBAO::SysTrayInfo;
using XIBAO::singleton::Singleton;

class DemoSingleton : SINGLETON_INHERIT(DemoSingleton)
{
	DECLARE_PRIVATE_CONSTRUCTOR(DemoSingleton, Initialize)
	DECLARE_FRIEND_SINGLETON(DemoSingleton)

private:
	DemoSingleton(const string &name): mName(name)
	{}

	void Initialize()
	{
		mName = "";
	}

public:
	void showName() { cout << mName << endl; }

private:
	string mName;

};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

int _tmain_test_singleton(int argc, _TCHAR* argv[])
{
	// SINGLETON_INSTANCE_EX(DemoSingleton, "name");

	Singleton<DemoSingleton>::Instance("liushixiong");

	SINGLETON_GET_INSTANCE(DemoSingleton).showName();
	

//	DemoSingleton *s = (DemoSingleton *)malloc(sizeof(DemoSingleton));
//	s->showName();
//	free(s);
//	s = nullptr;
	
	system("pause");
	return 0;
} 

int _tmain_test_systray(int argc, _TCHAR* argv[])
{
	vector<SysTrayInfo::TrayInfo> vecInfo(
										std::move(SysTrayInfo::GetTrayInfo()));

	system("pause");
	return 0;
}


int _tmain_test_service(int argc, _TCHAR* argv[])
{
	XIBAO::TaskScheduler task(L"C:\\Create_Service.exe", 
								L"appdemo", L"", L"", L"",
								{pair<int, int>(18,30)});
	if (task.CreateTaskSheduler()) {
		cout << "create task successfule..." << endl;
	} else {
		cout << "create task failed..." << endl;
	}

	if (task.DeleteTaskSheduler()) {
		cout << "delete task successfule..." << endl;
	} else {
		cout << "delete task failed..." << endl;
	}

	system("pause");
	return 0;
}

