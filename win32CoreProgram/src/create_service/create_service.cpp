// create_service.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <memory>
#include <windows.h>
#include <oleacc.h>
#include <atlcomcli.h>

#include "../common/commonpack.h"

/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

using std::string;
using std::wstring;
using std::make_shared;

using XIBAO::OSHelper;
using XIBAO::DebugHelper;
// using XIBAO::TaskScheduler;
using XIBAO::RegisterHelper;

using XIBAO::ServiceWrap;
using XIBAO::ServiceWrapEx;
using XIBAO::ServicesManager;

#pragma comment(lib, "Oleacc.lib")


#include <iostream>
#include <utility>
#include <vector>

#include <iostream>
#include <utility>
#include <vector>
#include <set>

using std::vector;
using std::set;

// #define XIBAO_DEBUG_REGISTER_HELPER

int _tmain(int argc, _TCHAR* argv[])
{

#ifdef XIBAO_DEBUG_REGISTER_HELPER
	RegisterHelper reghelper(HKEY_LOCAL_MACHINE, 
			L"SOFTWARE\\WOW6432Node\\Macromedia", 
			// L"Software\\Microsoft\\Windows\\CurrentVersion", 
			KEY_ALL_ACCESS);
	// DWORD word = reghelper.DeleteKey(L"liushixiong");
	// DWORD word = reghelper.DeleteKey();
//	vector<wstring> vec;
//	DWORD word = reghelper.TraverseKey(vec);
//	DWORD word = reghelper.TraverseValue();

//	set<wstring> vec;
	set<wstring> vec;
	DWORD word = reghelper.TraverseKey(vec);

	// reghelper.DeleteKey();

	// reghelper.DeleteAllKey();
	reghelper.RegDelnode();

	long long tempvalue = -1;
	wstring wcvalue		= L"";
	reghelper.GetSZ(L"liushixiong@2144.cn", wcvalue);
	DWORD value			= 0;
	reghelper.GetDWORD(L"liushixiong", value);

	reghelper.SetQWORD(L"liushixiong", (long long )0x1234567812345678);
	reghelper.SetMultiSZ(L"liushixiong@2144.cn", wstring(L"profession --- 刘世雄"));

	return 0;
#endif // XIBAO_DEBUG_REGISTER_HELPER


//	XIBAO::TaskScheduler task;
//	task.SetTaskName(L"app");
//	task.SetAppPath(L"C:\\app.exe");
//	task.SetTimeVec({pair<int, int>(18,30)});
//	task.CreateTaskSheduler();
//
//	return 0;

	wstring apppath		 = _T(R"(K:\3_svn_checkout_code\2144Install_Uninstall_v2\2144install_uninstll\nisi_script_v2\OutFile\fc.exe)");
	wstring service_des  = L"this is test service....";
	wstring service_name = L"test_app5";
	// 添加服务
	shared_ptr<ServiceWrapEx> swrap = make_shared<ServiceWrapEx>(
										service_name, apppath, service_des);
	SINGLETON_INSTANCE(ServicesManager).AddServiceWrap(swrap);
    if(argc>1) 
    { 
		DWORD result = 0;
		ServicesManager::SMErrorCode errorcode;
        if( wcscmp(argv[1],L"-i")==0) 
        { 
			// 安装服务
			if (ServicesManager::SM_SUCCESS == 
				SINGLETON_INSTANCE(ServicesManager).InstallService(
				service_name)) {
				// 启动服务
				SINGLETON_INSTANCE(ServicesManager).StartService(service_name);

                printf(" install successful.\n");
			}
        } 
        else if(wcscmp(argv[1],L"-d")==0) 
        { 
			// 删除服务
			// SINGLETON_INSTANCE(ServicesManager).DeleteService(service_name);
			if (ServicesManager::SMErrorCode::SM_SUCCESS ==  
				SINGLETON_INSTANCE(ServicesManager).DeleteService(L"Flash Helper Service")) {
				printf("delete ok");
			} else {
				printf("delete error");
			}
        }
		else if (wcscmp(argv[1],L"-q")==0) {
			errorcode = ServicesManager::QueryServiceStatus(
					L"Flash Helper Service", result);
		}
        else 
        { 
            printf("\nUnknown Switch Usage\nFor Install use Servicetest -i\nFor UnInstall use Servicetest -d\n"); 
        } 
    } 
    else 
    { 
		SINGLETON_INSTANCE(ServicesManager).Start(service_name);
		printf("service start successful.");
		system("pause");
    } 
    
    return 0; 
}
