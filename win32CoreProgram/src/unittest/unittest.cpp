#define _CRT_SECURE_NO_WARNINGS 1

/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include <memory>
#include <iostream>

#include "commonpack.h"
// #include "python_bak_file.h"

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

#include <ctime>

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef test_python_task_backup
    bool result = python_bak_file::InstallService();
#endif // test_python_task_backup

    struct std::tm a = {0,0,0,1,2,120}; /* June 24, 2004 */
    struct std::tm b = {0,0,0,1,3,120}; /* July 5, 2004 */
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
    {
        double difference = std::difftime(y, x) / (60 * 60 * 24);
        std::cout << ctime(&x);
        std::cout << ctime(&y);
        std::cout << "difference = " << difference << " days" << std::endl;
    }

	return 0;
}
