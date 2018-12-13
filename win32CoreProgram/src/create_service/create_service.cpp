// create_service.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <windows.h>
#include "singleton.h"
#include "../common/commonpack.h"

using std::string;
using std::wstring;

using XIBAO::DebugHelper;
using XIBAO::StringHelper;
using XIBAO::ServiceWrap;

SERVICE_STATUS m_ServiceStatus; 
SERVICE_STATUS_HANDLE m_ServiceStatusHandle; 
BOOL bRunning=true; 
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv); 
void WINAPI ServiceCtrlHandler(DWORD Opcode); 
BOOL InstallService(); 
BOOL DeleteService(); 

// wstring appname = L"service_test";
LPWSTR appname = L"service_test";

using XIBAO::ServicesManager;

void DoTask() 
{
	DebugHelper::OutputDebugString("dotask.............");
}

#define SERVICE_NO_ERROR 0
#define OPEN_SCMANAGER_ERROR 2
#define OPEN_SERVICE_ERROR 3
#define QUERY_SERVICESTATUS_ERROR 4
#define STOP_SERVICE_ERROR 5
#define START_SERVICE_ERROR 6

int RestartService()
{
 
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // 打开apache服务。
    SC_HANDLE hSvc = ::OpenService(hSC, appname, 
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return OPEN_SERVICE_ERROR;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }

    //如果处于运行状态则停止服务
    if( status.dwCurrentState == SERVICE_RUNNING)
    {
        // 停止服务
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }
        // 等待服务停止
        while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_STOPPED)
            {
                break;
            }
        }
    }
   
	// LPCWSTR ch = L"1";
	// const WCHAR *ch = new WCHAR[10];
	LPCWSTR str[] = {L"abc", L"edf", L"ABC"};
    // 启动服务
    if( ::StartService( hSvc, 3, str) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return START_SERVICE_ERROR;
    }
    // 等待服务启动
    while( ::QueryServiceStatus( hSvc, &status) == TRUE)
    {
        ::Sleep( status.dwWaitHint);
        if( status.dwCurrentState == SERVICE_RUNNING)
        {          
            break;
        }
    }
   
    ::CloseServiceHandle( hSvc);
    ::CloseServiceHandle( hSC);
    return SERVICE_NO_ERROR;
}

int StopService()
{
	   // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // 打开apache服务。
    SC_HANDLE hSvc = ::OpenService(hSC, appname, 
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return OPEN_SERVICE_ERROR;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }

    //如果处于运行状态则停止服务
    if( status.dwCurrentState == SERVICE_RUNNING)
    {
        // 停止服务
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }
        // 等待服务停止
        while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_STOPPED)
            {
                break;
            }
        }
    }
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    if(argc>1) 
    { 
        if( wcscmp(argv[1],L"-i")==0) 
        { 
			SINGLETON_INSTANCE(ServicesManager).AddServiceWrap(
						ServiceWrap(L"demo", L"D:\\create_service.exe"));
			if (ServicesManager::SM_SUCCESS == 
				SINGLETON_INSTANCE(ServicesManager).InstallService(L"demo")) {
				SINGLETON_INSTANCE(ServicesManager).StartService(L"demo");
			}
        } 
        else if(wcscmp(argv[1],L"-d")==0) 
        { 
			SINGLETON_INSTANCE(ServicesManager).DeleteService(L"demo");
        }
        else 
        { 
            printf("\nUnknown Switch Usage\nFor Install use Servicetest -i\nFor UnInstall use Servicetest -d\n"); 
        } 
    } 
    else 
    { 
		Sleep(3000*5);
		SINGLETON_INSTANCE(ServicesManager).AddServiceWrap(
			ServiceWrap(L"demo", L"D:\\create_service.exe"));
		SINGLETON_INSTANCE(ServicesManager).Start(L"demo");
    } 
    
    return 0; 
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv) 
{ 

	// Sleep(30000);
	// XIBAO::DebugHelper::OutputDebugString(argv[1]);

//     DWORD status;  
//     DWORD specificError;  
      m_ServiceStatus.dwServiceType          = SERVICE_WIN32;  
      m_ServiceStatus.dwCurrentState         = SERVICE_START_PENDING;  
      m_ServiceStatus.dwControlsAccepted     = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;  
      m_ServiceStatus.dwWin32ExitCode        = 0;  
      m_ServiceStatus.dwServiceSpecificExitCode = 0;  
      m_ServiceStatus.dwCheckPoint           = 0;  
      m_ServiceStatus.dwWaitHint             = 0;  

      m_ServiceStatusHandle = RegisterServiceCtrlHandler(appname,ServiceCtrlHandler);   
      if (m_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)  
      {  
          return;  
      }      
      m_ServiceStatus.dwCurrentState         = SERVICE_RUNNING;  
      m_ServiceStatus.dwCheckPoint           = 0;  
      m_ServiceStatus.dwWaitHint             = 0;   
      if (!SetServiceStatus (m_ServiceStatusHandle,&m_ServiceStatus))  
      {  
      }  

    bRunning=true; 
    while(bRunning) 
    {    
		Sleep(3000); 
		//Place Your Code for processing here....   
		DoTask(); 
		// XIBAO::DebugHelper::OutputDebugString(argv[1]);
		DebugHelper::OutputDebugString(
			StringHelper::FormatString(L"%s\r\n", argv[0]));
		DebugHelper::OutputDebugString(
			StringHelper::FormatString(L"%s\r\n", argv[1]));
		DebugHelper::OutputDebugString(
			StringHelper::FormatString(L"%s\r\n", argv[2]));
		DebugHelper::OutputDebugString(
			StringHelper::FormatString(L"%s\r\n", argv[3]));

    } 
      return;  
} 

void WINAPI ServiceCtrlHandler(DWORD Opcode) 
{ 
      switch(Opcode)  
      {  
          case SERVICE_CONTROL_PAUSE:  
              // m_ServiceStatus.dwCurrentState = SERVICE_PAUSED;  
			  ::InterlockedExchange(&m_ServiceStatus.dwCurrentState, SERVICE_PAUSED);
			  ::SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
			  XIBAO::DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_PAUSE");
              break;  

          case SERVICE_CONTROL_CONTINUE:  
              // m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;  
			  XIBAO::DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_CONTINUE");
			  ::InterlockedExchange(&m_ServiceStatus.dwCurrentState, SERVICE_RUNNING);
			  ::SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
              break;  

          case SERVICE_CONTROL_STOP:  
              m_ServiceStatus.dwWin32ExitCode = 0;  
              m_ServiceStatus.dwCurrentState    = SERVICE_STOPPED;     
              m_ServiceStatus.dwCheckPoint      = 0;  
              m_ServiceStatus.dwWaitHint        = 0;     
              SetServiceStatus (m_ServiceStatusHandle,&m_ServiceStatus); 
			  bRunning=false; 
			  XIBAO::DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_STOP");
		break; 

          case SERVICE_CONTROL_INTERROGATE:  
              break;  
      }       
      return;  
} 
BOOL InstallService() 
{ 
	WCHAR strDir[1024] = {0}; 
    SC_HANDLE schSCManager,schService; 
//    GetCurrentDirectory(1024,strDir); 
//    lstrcat(strDir,L"\\create_service.exe");  
	lstrcat(strDir, L"J:\\code\\code_git\\cprimeprimecode\\win32CoreProgram\\build_vs2013\\Debug\\create_service.exe");
    schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);   

    if (schSCManager == NULL)  
    return false; 
      LPCTSTR lpszBinaryPathName=strDir; 

      schService = CreateService((struct SC_HANDLE__ *)schSCManager, appname, appname,             // service name to display  
          SERVICE_ALL_ACCESS,          // desired access  
          SERVICE_WIN32_OWN_PROCESS, // service type  
          SERVICE_AUTO_START,        // start type  
          SERVICE_ERROR_NORMAL,        // error control type  
          lpszBinaryPathName,          // service's binary  
          NULL,                        // no load ordering group  
          NULL,                        // no tag identifier  
          NULL,                        // no dependencies  
          NULL,                        // LocalSystem account  
          NULL);                       // no password  

     if (schService == NULL)  
          return false;   
    SERVICE_DESCRIPTION   sdBuf; 
    sdBuf.lpDescription   =   L"GT即时同步软件后台服务"; 
    ChangeServiceConfig2( schService, SERVICE_CONFIG_DESCRIPTION, &sdBuf); 

    CloseServiceHandle((struct SC_HANDLE__ *)schService);  
    return true; 
} 

BOOL DeleteService() 
{ 
    HANDLE schSCManager; 
    SC_HANDLE hService; 
    schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS); 

    if (schSCManager == NULL)  
        return false;  
    hService=OpenService((struct SC_HANDLE__ *)schSCManager, appname,SERVICE_ALL_ACCESS); 
    if (hService == NULL)  
        return false; 
    if(DeleteService(hService)==0) 
        return false; 
    if(CloseServiceHandle(hService)==0) 
        return false; 
    else 
        return true; 
} 
