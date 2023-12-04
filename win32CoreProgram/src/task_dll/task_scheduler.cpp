#include <stdio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>

#include "task_scheduler.h"
#include "win7taskscheduler.h"

using std::string;
using std::wstring;

void __cdecl CreateTaskScheduler()
{
  printf("create task scheduler");
  OutputDebugStringW(L"我是好人");
}

void __cdecl DeleteTaskScheduler(wchar_t *app_name)
{
  OutputDebugStringW(app_name);
}

void __cdecl StartTaskScheduler(wchar_t *app_name)
{
  OutputDebugStringW(app_name);
  HRESULT hr = XIBAO::Win7TaskScheduler::StartTaskScheduler(app_name);
  if (S_OK == hr)
  {
    OutputDebugStringW((wstring(L"start task scheduler successful:") + wstring(app_name)).c_str());
  }
  else
  {
    std::stringstream ss;
    ss << std::hex << hr;
    OutputDebugStringW((wstring(L"start task scheduler error:") + wstring(app_name)).c_str());
    OutputDebugStringA((string("error code:") + ss.str()).c_str());
  }
}

