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

int main(int argc, CHAR* argv[])
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