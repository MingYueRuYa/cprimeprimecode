#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <Oleacc.h>
#pragma comment(lib,"Oleacc.lib")

BOOL IsRunasAdmin()
{
    BOOL bElevated = FALSE;
    HANDLE hToken = NULL;

    // Get current process token  
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
        return FALSE;

    TOKEN_ELEVATION tokenEle;
    DWORD dwRetLen = 0;

    // Retrieve token elevation information  
    if (GetTokenInformation(hToken, TokenElevation, &tokenEle, sizeof(tokenEle), &dwRetLen))
    {
        if (dwRetLen == sizeof(tokenEle))
        {
            bElevated = tokenEle.TokenIsElevated;
        }
    }

    CloseHandle(hToken);
    return bElevated;

}

int _tmain1()
{
    char sMess[256] = { 0 };
    time_t timestamp = time(0);
    sprintf_s(sMess, sizeof(sMess), "start=%I64d&end=%d&tabcount=%d", timestamp, 10, 1);

    printf("%s", sMess);

    getchar();

    bool flag = IsRunasAdmin();
    if (flag) {
        printf("ok");
    }
    else {
        printf("error");
    }
    getchar();
    return 0;
}
// Global variable.
HWINEVENTHOOK g_hook;

// Callback function that handles events.
//
void CALLBACK HandleWinEvent(HWINEVENTHOOK hook, DWORD event, HWND hwnd,  \
    LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
    IAccessible* pAcc = NULL;
    VARIANT varChild;
    HRESULT hr = AccessibleObjectFromEvent(hwnd, idObject, idChild, &pAcc, &varChild);
    if ((hr == S_OK) && (pAcc != NULL))
    {
        BSTR bstrName;
        pAcc->get_accName(varChild, &bstrName);
        if (event == EVENT_SYSTEM_MENUSTART)
        {
            printf("Begin: ");
        }
        else if (event == EVENT_SYSTEM_MENUEND)
        {
            printf("End:   ");
        }
        printf("%S\n", bstrName);
        SysFreeString(bstrName);
        pAcc->Release();
    }
}

// Initializes COM and sets up the event hook.
//
void InitializeMSAA()
{
    CoInitialize(NULL);
    g_hook = SetWinEventHook(
        EVENT_SYSTEM_DESKTOPSWITCH, EVENT_SYSTEM_DESKTOPSWITCH,  // Range of events (4 to 5).
        NULL,                                          // Handle to DLL.
        HandleWinEvent,                                // The callback.
        0, 0,              // Process and thread IDs of interest (0 = all)
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS); // Flags.
}

// Unhooks the event and shuts down COM.
//
//void ShutdownMSAA()
//{
//    //UnhookWinEvent(g_hook);
//    //CoUninitialize();
//}


int _tmainA()
{
    g_hook = NULL;
    InitializeMSAA();
    getchar();
    return 0;
}