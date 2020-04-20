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



int main( void )
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