/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef python_bak_file_h
#define python_bak_file_h

#include "registerhelper.h"

#include <set>
#include <string>

using std::wstring;
using XIBAO::RegisterHelper;

#define test_python_task_backup

namespace python_bak_file 
{

wstring GetPythonInterpreterPath()
{
	RegisterHelper reghelper(HKEY_CURRENT_USER, L"Software\\Python\\PythonCore",
		KEY_ALL_ACCESS);
	std::set<wstring> setkey;
	DWORD errorcode = reghelper.TraverseKey(setkey);
	if (errorcode != NO_ERROR || setkey.empty()) { return L""; }


    wstring sub_path = wstring(L"Software\\Python\\PythonCore\\") + 
                                *setkey.begin() + L"\\InstallPath";
    reghelper = RegisterHelper(HKEY_CURRENT_USER, sub_path, KEY_ALL_ACCESS);

    wstring exe_path;
    DWORD error_code = reghelper.GetSZ(L"ExecutablePath", exe_path);
    if (0 != error_code) { return L""; }
    return exe_path;
}

bool InstallService()
{
    wstring python_path = GetPythonInterpreterPath();

    wchar_t path[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, path);

    wstring task_name   = L"py_backup_task";
    wstring task_desc   = L"定时备份文件";
    wstring work_dir    = path;
    wstring parameter   = L".\\py_script\\backup_file.py";
    vector<pair<int, int>> backup_time = 
                            {pair<int, int>(18, 30), pair<int, int>(12, 30)};

    XIBAO::TaskScheduler task(python_path, task_name, task_desc, work_dir,
                               parameter, backup_time); 
    // 在创建服务时如果创建失败，可能是被杀软拦截，关闭杀软在尝试
    return task.CreateTaskSheduler();
}

}


#endif // python_bak_file_h
