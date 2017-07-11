//#define _CRT_SECURE_NO_WARNINGS

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


int main(int argc, CHAR* argv[])
{
    MSG msg;
    //hStartEvent = ::CreateEvent(0, FALSE, FALSE, 0);

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