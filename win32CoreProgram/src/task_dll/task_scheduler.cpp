#include <stdio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>

#include "task_scheduler.h"
#include "win7taskscheduler.h"
#include "taskscheduler.h"

using std::string;
using std::wstring;

void print_log(const wstring &action, HRESULT hr)
{
  if (S_OK == hr)
  {
    OutputDebugStringW(action.c_str());
  }
  else
  {
    std::stringstream ss;
    ss << std::hex << hr;
    OutputDebugStringW((action).c_str());
    OutputDebugStringA((string("error code:") + ss.str()).c_str());
  }
}

int __cdecl CreateTaskScheduler(const wchar_t *appPath,
							const wchar_t *taskName,
							const wchar_t *taskDescription,
							const wchar_t *appWorkDir,
							const wchar_t *parameter,
							const wchar_t *userName,
							const wchar_t *passwd,
              int hour,
              int mins,
							int mode)
{
  HRESULT hr = XIBAO::Win7TaskScheduler::Create2MoreWin7(appPath, taskName, taskDescription, appWorkDir, parameter, {}, userName, passwd, mode);
  print_log(wstring(L"create task scheduler"), hr);
  return hr;
}

int __cdecl StartTaskScheduler(wchar_t *app_name)
{
  HRESULT hr = XIBAO::Win7TaskScheduler::StartTaskScheduler(app_name);
  print_log(wstring(L"start task scheduler"), hr);
  return hr;
}

int __cdecl DeleteTaskScheduler(wchar_t *app_name)
{
  if (app_name == nullptr)
  {
    print_log(wstring(L"app name is null"), 1);
    return 1;
  }
  HRESULT hr = XIBAO::TaskScheduler::DeleteTaskScheduler(app_name);
  print_log(wstring(L"delete task scheduler"), hr);
  return hr;
}


