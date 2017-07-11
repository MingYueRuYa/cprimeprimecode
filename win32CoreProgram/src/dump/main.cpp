#include <windows.h>  
#include <DbgHelp.h>  
#include <tchar.h>

#pragma comment(lib, "dbghelp.lib")  

//我们的回调函数  
LONG __stdcall ExceptCallBack(EXCEPTION_POINTERS *pExcPointer)
{
    MessageBox(NULL, _T("程序崩溃！相关信息记录在D:\\Test.dmp文件中。"), NULL, MB_OK);

    //创建dump文件  
    HANDLE hFile = CreateFile(_T("D:\\Test.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    //向文件写下当前程序崩溃相关信息  
    MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;
    loExceptionInfo.ExceptionPointers = pExcPointer;
    loExceptionInfo.ThreadId = GetCurrentThreadId();
    loExceptionInfo.ClientPointers = TRUE;
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &loExceptionInfo, NULL, NULL);
    CloseHandle(hFile);

    return EXCEPTION_EXECUTE_HANDLER;
}

void WrongFun()
{
    //crash  
    int * p = NULL;
    *p = 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //设置崩溃回调函数  
    SetUnhandledExceptionFilter(ExceptCallBack);

    WrongFun();

    return 0;
}