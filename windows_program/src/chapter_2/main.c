#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <wchar.h>
#include <stdarg.h>

// ASCII码字符集，双字节字符集，多字节字符集
int main01()
{
    char c = 'A';
    char str[] = "中国";
    int i = strlen(str);
    printf("%c\n", c);
    printf("%s\n", str);
    printf("长度:%d\n", i);
    getchar();
    return 0;
//    A
//    中国
//    长度 : 4
}

// unicode字符
int main02()
{
    wchar_t c = L'国';
    wchar_t str[] = L"中国";
    int  i = wcslen(str);
    setlocale(LC_ALL, "chs");
    wprintf(L"%lc\n", c);
    wprintf(L"%s\n", str);
    wprintf(L"长度：%d\n", i);
    getchar();

    return 0;
//    国
//    中国
//    长度：2
}

int main03()
{
    // 不要用
    // char c
    // wchar_t c;
    // CHAR c;
    // WCHAR c;

    TCHAR str[] = _T("中国");
    setlocale(LC_ALL, "chs");
    _tprintf(_T("%s\n"), str);
    getchar();
    return 0;
    // 中国
}

int my_printf(const char *szFormat, ...)
{
    va_list pArgs;
    va_start(pArgs, szFormat);

    int iReturn = vprintf(szFormat, pArgs);

    va_end(pArgs);

    return iReturn;
}

int main04()
{
    int a = 12;
    char szBuffer[100];
    int x = 100, y = 200, z = 300;
    printf("hello %d, %d, %d\n", x, y, z);
    my_printf("hello %d, %d\n", x, y);
    sprintf_s(szBuffer, sizeof szBuffer, "不安全的 hello %d\n", x);
    puts(szBuffer);
    getchar();
    return 0;
}

#include <windows.h>

int WINAPI WinMain01(HINSTANCE hInstance,
                   HINSTANCE hPreInstance,
                   PSTR szCmdLine,
                   int iCmdShow)
{
    int a = 12;
//    wchar_t szBuffer[100]; // wchar
//    swprintf(szBuffer, 100, L"hello %d", a);
//
//    MessageBoxW(NULL, szBuffer, L"hello unicode", MB_OK | MB_ICONINFORMATION);

    // 标准版
    TCHAR szBuffer[100];

    _sntprintf_s(szBuffer, 100, wcslen(_T("hello %d")), _T("hello %d"), a);

    MessageBox(NULL, szBuffer, _T("hello TCHAR"), MB_OK | MB_ICONINFORMATION);
    
    return 0;
}


int CDECL MessageBoxPrintf(TCHAR *szCaption, TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];
    va_list pArglist;

    va_start(pArglist, szFormat);
    _vsntprintf_s(szBuffer, sizeof szBuffer / sizeof(TCHAR), sizeof szBuffer / sizeof(TCHAR), szFormat, pArglist);

    va_end(pArglist);

    return MessageBox(NULL, szBuffer, szCaption, MB_OK | MB_ICONINFORMATION);
}

int WINAPI WinMain02(HINSTANCE hInstance,
                   HINSTANCE hPreInstance,
                   PSTR *szCmdLine,
                   int iCmdShow)
{
    int x = 100, y = 200, z = 300;
    int cxScreen, cyScreen;
    cxScreen = GetSystemMetrics(SM_CXSCREEN);
    cyScreen = GetSystemMetrics(SM_CYSCREEN);

    MessageBoxPrintf(_T("我的标题"), _T("hello %d, %d, %d"), x, y, z);
    MessageBoxPrintf(_T("屏幕大小"), _T("我的屏幕宽度是：%d, 高度:%d"), cxScreen, cyScreen);
    return 0;
}