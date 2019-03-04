// unittest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include <iostream>

#include "commonpack.h"
//#include "xptaskscheduler.h"
//#include "win7taskscheduler.h"

using std::cout;
using std::endl;
using std::shared_ptr;

// using XIBAO::TaskScheduler;

int _tmain(int argc, _TCHAR* argv[])
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

