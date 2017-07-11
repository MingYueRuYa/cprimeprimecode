#include <windows.h>
#include <stdio.h>
#include <userenv.h>
#include <tchar.h>


#pragma comment(lib, "Advapi32.lib")

#pragma comment(lib, "Userenv.lib")

void MyError()
{

}

void main04()
{

    DWORD dwSessionId;
    HANDLE hToken = NULL;

    TOKEN_PRIVILEGES tp;
    PROCESS_INFORMATION pi;
    STARTUPINFOW si;

    // Initialize structures.
    ZeroMemory(&tp, sizeof(tp));
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);


    LPTSTR lpszUsername = _T("user\0");
    LPTSTR lpszDomain = _T(".");//"bgt\0";
    LPTSTR lpszPassword = _T("password\0");

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY
        | TOKEN_ADJUST_PRIVILEGES, &hToken)) {

        MyError();
    }



    // Look up the LUID for the TCB Name privilege.
    if (!LookupPrivilegeValue(NULL, SE_TCB_NAME, //SE_SHUTDOWN_NAME ,
        //SE_TCB_NAME,
        &tp.Privileges[0].Luid)) {
        MyError();
    }


    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes =
        SE_PRIVILEGE_ENABLED;//SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, 0)) {

        MyError();
    }


    if (LogonUser(lpszUsername, lpszDomain, lpszPassword,
        LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken) == 0)
    {
        MyError();
    }
    else
    {
        STARTUPINFO sInfo;
        PROCESS_INFORMATION ProcessInfo;
        memset(&sInfo, 0, sizeof(STARTUPINFO));
        sInfo.cb = sizeof(STARTUPINFO);
        sInfo.dwX = CW_USEDEFAULT;
        sInfo.dwY = CW_USEDEFAULT;
        sInfo.dwXSize = CW_USEDEFAULT;
        sInfo.dwYSize = CW_USEDEFAULT;


        bool bRet = CreateProcessAsUser(hToken,
            _T("c:\\windows\\system32\\notepad.exe"),
            NULL,
            NULL,
            NULL,
            TRUE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &sInfo,
            &ProcessInfo);

        if (bRet == 0)
            MyError();
    }
}