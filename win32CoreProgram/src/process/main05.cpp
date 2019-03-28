//#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <windows.h>
#include <iostream>

using namespace std;

const int MAX_INFO_SIZE = 20;
HANDLE hStartEvent;

#define UM_MSG1 WM_USER+1
#define UM_MSG2 WM_USER+2

static UINT WrkThrd(LPVOID lpParam)
{
    DWORD dwThreadID = *(DWORD *)lpParam;
    MSG msg;
    PeekMessage(&msg, NULL, UM_MSG1, UM_MSG2, PM_NOREMOVE);

    if (!SetEvent(hStartEvent)) //set thread start event 
    {
        printf("set start event failed,errno:%d\n", ::GetLastError());
        return 1;
    }
    char * pInfo = NULL;
    while (GetMessage(&msg, 0, 0, 0)) //get msg from message queue
    {
        switch (msg.message)
        {
        case UM_MSG1:
            pInfo = (char *)msg.wParam;
            printf("recv %s\n", pInfo);
            delete[] pInfo;
            PostThreadMessage(GetCurrentThreadId(), UM_MSG2, 0, 0);
            Sleep(5000);
            break;
        case UM_MSG2:
            printf("recv UM_MSG2\n");
            break;
        }
    }
    return 0;
}

class Test
{
public:
	Test(int id)
	{
		this->id = id;
		cout << "ctor, this=" << this << " id=" << id<< endl;
	}

	~Test()
	{
		cout << "dtor, this=" << this << endl;
	}

private:
	int id;
};

wstring str2time(const wstring &strTime)
{
    struct tm sTime;
    swscanf_s(strTime.c_str(), L"%d-%d-%d %d:%d:%d", &sTime.tm_year, &sTime.tm_mon, &sTime.tm_mday, &sTime.tm_hour, &sTime.tm_min, &sTime.tm_sec, sizeof(tm));
    sTime.tm_year -= 1900;

    sTime.tm_mon -= 1;
    time_t ft = mktime(&sTime);
    wchar_t wcbuf[50] = { 0 };
    swprintf(wcbuf, sizeof(wcbuf), L"%lld", ft);
    return wcbuf;
}

#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

#ifdef WIN32
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif

std::string CreateGuid()
{
    GUID guid;
    CoCreateGuid(&guid);
    char buf[64] = { 0 };
    _snprintf_s(
        buf,
        sizeof(buf),
        "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1],
        guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);
    return std::string(buf);
}

std::string GuidToString(const GUID &guid)
{
    char buf[64] = { 0 };
#ifdef __GNUC__
    snprintf(
#else // MSVC
    _snprintf_s(
#endif
        buf,
        sizeof(buf),
        "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1],
        guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);
    return std::string(buf);
}


/********************************************************************
 This sample schedules a task to start on a daily basis. 
********************************************************************/

#define _WIN32_DCOM

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <comdef.h>
#include <wincred.h>
//  Include the task header file.
#include <taskschd.h>
#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "credui.lib")

using namespace std;


int __cdecl wmain(int argc, wchar_t *argv[])
{
//	wchar_t filename[MAX_PATH] = {0};
//	DWORD errorcode = GetModuleFileNameW(nullptr, filename, MAX_PATH*2);	
//	for (int i = 0; i < argc; ++i) {
//		// MessageBoxW(NULL, filename, L"title", MB_OK);
//
//		MessageBoxW(NULL, argv[i], L"title", MB_OK);
//
//	}

	for (int i = 0; i < argc; ++i) {
		wstring cmdline = argv[i];
		MessageBoxW(NULL, cmdline.c_str(), L"title", MB_OK);
	}	

	return 0;

    //  ------------------------------------------------------
    //  Initialize COM.
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if( FAILED(hr) )
    {
        printf("\nCoInitializeEx failed: %x", hr );
        return 1;
    }

    //  Set general COM security levels.
    hr = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        0,
        NULL);

    if( FAILED(hr) )
    {
        printf("\nCoInitializeSecurity failed: %x", hr );
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Create a name for the task.
    LPCWSTR wszTaskName = L"Daily Trigger Test Task";

    //  Get the windows directory and set the path to notepad.exe.
    wstring wstrExecutablePath = _wgetenv( L"WINDIR");
    wstrExecutablePath += L"\\SYSTEM32\\NOTEPAD.EXE";

    

    //  ------------------------------------------------------
    //  Create an instance of the Task Service. 
    ITaskService *pService = NULL;
    hr = CoCreateInstance( CLSID_TaskScheduler,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_ITaskService,
                           (void**)&pService );  
    if (FAILED(hr))
    {
        printf("Failed to create an instance of ITaskService: %x", hr);
        CoUninitialize();
        return 1;
    }
        
    //  Connect to the task service.
    hr = pService->Connect(_variant_t(), _variant_t(),
        _variant_t(), _variant_t());
    if( FAILED(hr) )
    {
        printf("ITaskService::Connect failed: %x", hr );
        pService->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.
    ITaskFolder *pRootFolder = NULL;
    hr = pService->GetFolder( _bstr_t( L"\\") , &pRootFolder );
    if( FAILED(hr) )
    {
        printf("Cannot get Root Folder pointer: %x", hr );
        pService->Release();
        CoUninitialize();
        return 1;
    }
    
    // If the same task exists, remove it.
    pRootFolder->DeleteTask( _bstr_t( wszTaskName), 0  );
    
    //  Create the task builder object to create the task.
    ITaskDefinition *pTask = NULL;
    hr = pService->NewTask( 0, &pTask );
    
    pService->Release();  // COM clean up.  Pointer is no longer used.
    if (FAILED(hr))
    {
        printf("Failed to CoCreate an instance of the TaskService class: %x", hr);
        pRootFolder->Release();
        CoUninitialize();
        return 1;
    }
            
    //  ------------------------------------------------------
    //  Get the registration info for setting the identification.
    IRegistrationInfo *pRegInfo= NULL;
    hr = pTask->get_RegistrationInfo( &pRegInfo );
    if( FAILED(hr) )
    {
        printf("\nCannot get identification pointer: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();        
        return 1;
    }
    
    hr = pRegInfo->put_Author( L"Author Name" );
    pRegInfo->Release();  // COM clean up.  Pointer is no longer used.
    if( FAILED(hr) )
    {
        printf("\nCannot put identification info: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
    
    //  ------------------------------------------------------
    //  Get the trigger collection to insert the daily trigger.
    ITriggerCollection *pTriggerCollection = NULL;
    hr = pTask->get_Triggers( &pTriggerCollection );
    if( FAILED(hr) )
    {
        printf("\nCannot get trigger collection: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
        
    //  Add the daily trigger to the task.
    ITrigger *pTrigger = NULL;    
    hr = pTriggerCollection->Create( TASK_TRIGGER_DAILY, &pTrigger );
    pTriggerCollection->Release();
    if( FAILED(hr) )
    {
        printf("\nCannot create the trigger: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }     
    
    IDailyTrigger *pDailyTrigger = NULL;
    hr = pTrigger->QueryInterface( 
        IID_IDailyTrigger, (void**) &pDailyTrigger );
    pTrigger->Release();
    if( FAILED(hr) )
    {
        printf("\nQueryInterface call on IDailyTrigger failed: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
    
    hr = pDailyTrigger->put_Id( _bstr_t( L"Trigger1" ) );
    if( FAILED(hr) )
        printf("\nCannot put trigger ID: %x", hr);

    //  Set the task to start daily at a certain time. The time 
    //  format should be YYYY-MM-DDTHH:MM:SS(+-)(timezone).
    //  For example, the start boundary below
    //  is January 1st 2005 at 12:05
    hr = pDailyTrigger->put_StartBoundary( _bstr_t(L"2005-01-01T12:05:00") );
    if( FAILED(hr) )
        printf("\nCannot put start boundary: %x", hr);
    
    //  Set the time when the trigger is deactivated.
    hr = pDailyTrigger->put_EndBoundary( _bstr_t(L"2007-05-02T12:05:00") );
    if( FAILED(hr) )
        printf("\nCannot put the end boundary: %x", hr);
 
    //  Define the interval for the daily trigger. An interval of 2 produces an
    //  every other day schedule
    hr = pDailyTrigger->put_DaysInterval( (short)2 );
    if( FAILED(hr) )
    {
        printf("\nCannot put days interval: %x", hr );
        pRootFolder->Release();
        pDailyTrigger->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    // Add a repetition to the trigger so that it repeats
    // five times.
    IRepetitionPattern *pRepetitionPattern = NULL;
    hr = pDailyTrigger->get_Repetition( &pRepetitionPattern );
    pDailyTrigger->Release();
    if( FAILED(hr) )
    {
        printf("\nCannot get repetition pattern: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
    
    hr = pRepetitionPattern->put_Duration( _bstr_t(L"PT4M"));
    if( FAILED(hr) )
    {
        printf("\nCannot put repetition duration: %x", hr );
        pRootFolder->Release();
        pRepetitionPattern->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    hr = pRepetitionPattern->put_Interval( _bstr_t(L"PT1M"));
    pRepetitionPattern->Release();
    if( FAILED(hr) )
    {
        printf("\nCannot put repetition interval: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }    
  

    //  ------------------------------------------------------
    //  Add an action to the task. This task will execute notepad.exe.     
    IActionCollection *pActionCollection = NULL;

    //  Get the task action collection pointer.
    hr = pTask->get_Actions( &pActionCollection );
    if( FAILED(hr) )
    {
        printf("\nCannot get task collection pointer: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
        
    //  Create the action, specifying that it is an executable action.
    IAction *pAction = NULL;
    hr = pActionCollection->Create( TASK_ACTION_EXEC, &pAction );
    pActionCollection->Release();
    if( FAILED(hr) )
    {
        printf("\nCannot create action: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    IExecAction *pExecAction = NULL;
    hr = pAction->QueryInterface( 
        IID_IExecAction, (void**) &pExecAction );
    pAction->Release();
    if( FAILED(hr) )
    {
        printf("\nQueryInterface call failed for IExecAction: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Set the path of the executable to notepad.exe.
    hr = pExecAction->put_Path( _bstr_t( wstrExecutablePath.c_str() ) );
    pExecAction->Release();
    if( FAILED(hr) )
    {
        printf("\nCannot put the executable path: %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Securely get the user name and password. The task will
    //  be created to run with the credentials from the supplied 
    //  user name and password.
    CREDUI_INFO cui;
    TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH] = L"";
    TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH] = L"";
    BOOL fSave;
    DWORD dwErr;

    cui.cbSize = sizeof(CREDUI_INFO);
    cui.hwndParent = NULL;
    //  Ensure that MessageText and CaptionText identify
    //  what credentials to use and which application requires them.
    cui.pszMessageText = TEXT("Account information for task registration:");
    cui.pszCaptionText = TEXT("Enter Account Information for Task Registration");
    cui.hbmBanner = NULL;
    fSave = FALSE;

    //  Create the UI asking for the credentials.
    dwErr = CredUIPromptForCredentials(
        &cui,                             //  CREDUI_INFO structure
        TEXT(""),                         //  Target for credentials
        NULL,                             //  Reserved
        0,                                //  Reason
        pszName,                          //  User name
        CREDUI_MAX_USERNAME_LENGTH,       //  Max number for user name
        pszPwd,                           //  Password
        CREDUI_MAX_PASSWORD_LENGTH,       //  Max number for password
        &fSave,                           //  State of save check box
        CREDUI_FLAGS_GENERIC_CREDENTIALS |  //  Flags
        CREDUI_FLAGS_ALWAYS_SHOW_UI |
        CREDUI_FLAGS_DO_NOT_PERSIST);  

    if(dwErr)
    {
        cout << "Did not get credentials." << endl;    
        CoUninitialize();
        return 1;      
    }
    
    //  ------------------------------------------------------
    //  Save the task in the root folder.
    IRegisteredTask *pRegisteredTask = NULL;
    hr = pRootFolder->RegisterTaskDefinition(
            _bstr_t( wszTaskName ),
            pTask,
            TASK_CREATE_OR_UPDATE, 
            _variant_t(_bstr_t(pszName)), 
            _variant_t(_bstr_t(pszPwd)), 
            TASK_LOGON_PASSWORD,
            _variant_t(L""),
            &pRegisteredTask);
    if( FAILED(hr) )
    {
        printf("\nError saving the Task : %x", hr );
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        SecureZeroMemory(pszName, sizeof(pszName));
        SecureZeroMemory(pszPwd, sizeof(pszPwd));
        return 1;
    }

    printf("\n Success! Task successfully registered. " );

    //  Clean up
    pRootFolder->Release();
    pTask->Release();
    pRegisteredTask->Release();
    CoUninitialize();
    SecureZeroMemory(pszName, sizeof(pszName));
    SecureZeroMemory(pszPwd, sizeof(pszPwd));
    return 0;
}


int main04(int argc, CHAR* argv[])
{
    cout <<CreateGuid() << endl;

    int i = 0;
    cin >> i;
    return 0;
}

int main03(int argc, CHAR* argv[])
{
    wstring timestamp = str2time(L"2013-08-01 0:0:0");

    cout << timestamp.c_str() << endl;

    int i = 0;
    cin >> i;
    return 0;
}


int main01(int argc, CHAR* argv[])
{

	Test *test = new Test(3);
	test->Test::Test(2);
	test->~Test();

	Test test1(3);
	test1.Test::Test(4);
	test1.~Test();

	return 0;
    MSG msg;
    //hStartEvent = ::CreateEvent(0, FALSE, FALSE, 0);
    //获取分辨率
    int m_nWindwMetricsX = ::GetSystemMetrics(SM_CXSCREEN);
    int m_nWindwMetricsY = ::GetSystemMetrics(SM_CYSCREEN);

    hStartEvent = ::CreateEvent(0, FALSE, FALSE, 0); //create thread start event
    if (hStartEvent == 0)
    {
        printf("create start event failed,errno:%d\n", ::GetLastError());
        return 1;
    }

    DWORD threadID = GetCurrentThreadId();
    DWORD threadsubID;
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WrkThrd, &threadID, 0, &threadsubID);
    if (!hThread)
    {
        printf("start thread failed,errno:%d\n", ::GetLastError());
        CloseHandle(hStartEvent);
    }

    ::WaitForSingleObject(hStartEvent, INFINITE);
    int count = 0;
    while (true)
    {
        char* pInfo = new char[MAX_INFO_SIZE]; //create dynamic msg
        sprintf_s(pInfo, MAX_INFO_SIZE, "msg_%d", ++count);
        if (!PostThreadMessage(threadsubID, UM_MSG1, (WPARAM)pInfo, 0))//post thread msg
        {
            printf("post message failed,errno:%d\n", ::GetLastError());
            delete[] pInfo;
        }
        Sleep(2000);
    }
    return 0;
}