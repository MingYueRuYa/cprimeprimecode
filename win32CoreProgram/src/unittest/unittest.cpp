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
using XIBAO::SyncQueue;
using XIBAO::ThreadPool;

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
								{pair<int, int>(18,30)}, XIBAO::Win7TaskScheduler::TaskMode::Normal);
	if (task.CreateTaskScheduler()) {
		cout << "create task successfule..." << endl;
	} else {
		cout << "create task failed..." << endl;
	}

	if (task.DeleteTaskScheduler()) {
		cout << "delete task successfule..." << endl;
	} else {
		cout << "delete task failed..." << endl;
	}

	system("pause");
	return 0;
}

#include <ctime>

int _tmain_time(int argc, _TCHAR* argv[])
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

// 测试线程池和同步队列
int _tmain_threadpool(int argc, _TCHAR* argv[])
{
    ThreadPool tpool(2, 1);
    tpool.Start();

    std::thread t1([&tpool] () {
        for (int i = 0; i < 10; ++i) {
            auto thread_id = std::this_thread::get_id();

            tpool.AddTask([thread_id, i] () {
                cout << "同步层线程1的线程ID：" << thread_id 
                     << " index:" << i << endl;
            });
        }
    });

    std::thread t2([&tpool] () {
        for (int i = 0; i < 10; ++i) {
            auto thread_id = std::this_thread::get_id();

            tpool.AddTask([thread_id, i] () {
                cout << "同步层线程2的线程ID：" << thread_id 
                     << " index:" << i << endl;
            });
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));

    getchar();

    tpool.Stop();

    t1.join();
    t2.join();

	return 0;
}


#include <Windows.h>
#include <stdio.h>
#include <WtsApi32.h>
#pragma comment( lib, "Wtsapi32.lib" )


int test_enum_process_main( void )
{
	DWORD				dwCount			= 0;
	PWTS_PROCESS_INFO	pi				= { 0 };
	int					i				= 0;
	DWORD				dwSize			= 0;
	char				username[128]	= { 0 };
	SID_NAME_USE		nameuse			= SidTypeUser;

	if( WTSEnumerateProcesses(NULL, 0, 1, &pi, &dwCount) ) {
		for( i = 0; i < dwCount; i++ ) {
			wprintf( L"Process Name: %s\n", pi[i].pProcessName );
			printf( "Process Id:   %d\n", pi[i].ProcessId );
			printf( "Session Id:   %d\n", pi[i].SessionId );

			memset( username, 0, sizeof(char) * 128 );
			dwSize = 128;
			if( LookupAccountSidA(NULL, pi[i].pUserSid, username, &dwSize, NULL, &dwSize, &nameuse) )
				printf( "User Name:    %s\n\n", username );
			else
				printf( "User Name:    Unknown\n\n" );
		}
	}

	WTSFreeMemory( pi );

    getchar();

	return 0;
}


#include <set>
#include <string>
#include <algorithm>

using std::set;
using std::string;

// 测试STL的在关联容器中指针类型的排序
int _tmain_stl(int argc, _TCHAR* argv[])
{
    //set<string *, std::LessDerefrence<string>> pstr_set;   
    //pstr_set.insert(new string("b"));
    //pstr_set.insert(new string("a"));
    //pstr_set.insert(new string("c"));

    //// std::for_each(pstr_set.begin(), pstr_set.end(), [](string *pstr) { cout << *pstr << std::hex << pstr << endl; });
    //// 类型不一致，编译出错
    //// std::copy(pstr_set.begin(), pstr_set.end(), std::ostream_iterator<string>(cout, "\n"));

    //std::transform(pstr_set.begin(), pstr_set.end(),std::ostream_iterator<string>(cout, "\n"), std::Derefrence()); 

	return 0;
}

#include "task_scheduler.h"

wstring get_user_name()
{
	wchar_t username[MAX_PATH + 1];
	DWORD usernameLen = MAX_PATH + 1;

	// 获取当前机器的用户名
	if (GetUserNameW(username, &usernameLen)) {
		std::cout << XIBAO::StringHelper::to_string(L"当前用户名为：") << XIBAO::StringHelper::to_string(username) << std::endl;
		return username;
	}
	else {
		std::cout << XIBAO::StringHelper::to_string(L"无法获取用户名") << std::endl;
		return L"";
	}
	return L"";
}

void print_info(const wstring &action, HRESULT hr)
{
		if (S_OK == hr)
		{
			XIBAO::DebugHelper::OutputDebugString(action + L" successful");
		}
		else
		{
      std::stringstream ss;
      ss << std::hex << hr;
			wstring msg = action + wstring(L" error, code:") + XIBAO::StringHelper::to_wstring(ss.str());
			XIBAO::DebugHelper::OutputDebugString(action);
		}
}

void create_task2()
{
		wstring user_name = get_user_name();
		if (user_name.empty())
		{
			std::cout << XIBAO::StringHelper::to_string(L"获取用户名失败, 需要手动输入用户名:");
			string name;
			std::getline(std::cin, name);
			user_name = XIBAO::StringHelper::to_wstring(name);
		}

    std::cout << XIBAO::StringHelper::to_string(L"请输入密码：");
    string passwd;
    std::getline(std::cin, passwd);

		if (CreateTaskScheduler(user_name, XIBAO::StringHelper::to_wstring(passwd)))
		{
			print_succuss();
		}
		system("pause");
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	if (!ReadConfig())
	{
		system("pause");
		return 1;
	}

	if (argc < 2)
	{
		create_task2();
		return 0;
	}

	string command = argv[1];
	if (command == "-d")
	{
		bool result = XIBAO::TaskScheduler::DeleteTaskScheduler(config.app_name);
		if (result)
		{
			std::cout << XIBAO::StringHelper::to_string(wstring(L"删除计划任务成功:") + config.app_name) << std::endl;
		}
	}
	else if (command == "-dn")
	{
		bool result = XIBAO::TaskScheduler::DeleteTaskScheduler(config.notification_task_name);
		if (result)
		{
			std::cout << XIBAO::StringHelper::to_string(wstring(L"删除计划任务成功:") + config.app_name) << std::endl;
		}
	}
	else if (command == "-c")
	{
		create_task2();
	}
	else if (command == "-s")
	{
		wstring parameter = XIBAO::StringHelper::to_wstring(argv[2]);
		HRESULT hr = XIBAO::TaskScheduler::StartTaskScheduler(parameter);
		print_info(L"start task ", hr);
	}
	else if (command == "-cn")
	{
		wstring app_path = config.app_start_dir + L"/notification.exe";
		wstring task_name = config.notification_task_name;
		wstring param = wstring(L"start_by_task ") + config.app_start_dir + L"/config.json";
		HRESULT hr = XIBAO::Win7TaskScheduler::Create2MoreWin7(app_path, task_name, L"", config.app_start_dir, param, {}, L"", L"", XIBAO::Win7TaskScheduler::SYSTEM);
		print_info(L"install notification task ", hr);
	}
	else if (command == "-h")
	{
		std::cout << "usage: task.exe -d task_name\n"
			<< "task.exe -s task_name\n"
			<< "task.exe -n \n"
			<< "task.exe -c task_name\n" << std::endl;
		system("pause");
		return -1;
	}

	return 0;
}

