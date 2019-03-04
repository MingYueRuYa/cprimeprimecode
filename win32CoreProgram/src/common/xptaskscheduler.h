/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef xptaskscheduler_h
#define xptaskscheduler_h

#include <windows.h>
#include <initguid.h>
#include <ole2.h>
#include <mstask.h>
#include <msterr.h>
#include <objidl.h>

namespace XIBAO
{
class XPTaskScheduler
{
public:
	XPTaskScheduler() {}
	~XPTaskScheduler() {}

	static int DeleteTaskForXP(LPCWSTR taskname)
	{
		HRESULT hr = ERROR_SUCCESS;
		ITaskScheduler *pITS;

		hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			return false;
		}

		LPCWSTR pwszTaskName;
		pwszTaskName = taskname;

		hr = CoCreateInstance(CLSID_CTaskScheduler,
							   NULL,
							   CLSCTX_INPROC_SERVER,
							   IID_ITaskScheduler,
							   (void **) &pITS);
		pITS->Delete(pwszTaskName);
		pITS->Release();

		CoUninitialize();
		return true;
	}

	static int CreateTaskForXP(LPCWSTR sztTaskName, 
					LPCWSTR szApppath, 
					LPCWSTR szAppWorkDir, 
					LPCWSTR szDescription, 
					LPCWSTR szParameter, 
					int hour, int min)
	{
		HRESULT hr = ERROR_SUCCESS;
		ITaskScheduler *pITS;

		hr = CoInitialize(NULL);
		if (FAILED(hr)) { return false; }

		LPCWSTR pwszTaskName;
		pwszTaskName = sztTaskName;

		hr = CoCreateInstance(CLSID_CTaskScheduler,
							   NULL,
							   CLSCTX_INPROC_SERVER,
							   IID_ITaskScheduler,
							   (void **) &pITS);
		pITS->Delete(pwszTaskName);

		if (FAILED(hr)) { goto Failed; }

		ITask *pITask;
		IPersistFile *pIPersistFile;

		hr = pITS->NewWorkItem(pwszTaskName,
							 CLSID_CTask,
							 IID_ITask,
							 (IUnknown**)&pITask);

		pITask->SetComment(szDescription);
		pITask->SetParameters(szParameter);
		pITask->SetWorkingDirectory(szAppWorkDir);
		pITask->SetApplicationName(szApppath);
		pITask->SetFlags(TASK_FLAG_RUN_ONLY_IF_LOGGED_ON);

		//设定任务
		WCHAR szUserName[MAX_PATH] = L"";
		DWORD dwSize = MAX_PATH;
		GetUserName(szUserName, &dwSize);

		pITask->SetAccountInformation(szUserName, NULL);
	  
		pITS->Release();                               // Release object
		if (FAILED(hr)) { goto Failed; }
	  
		hr = pITask->QueryInterface(IID_IPersistFile,
								  (void **)&pIPersistFile);
		if (FAILED(hr)) { goto Failed; }
	  
		hr = pIPersistFile->Save(NULL, TRUE);
		pIPersistFile->Release();
		if (FAILED(hr)) { goto Failed; }
	  
		ITaskTrigger*   pITaskTrig = NULL;
		IPersistFile*   pIFile     = NULL;
		TASK_TRIGGER    rTrigger;
		WORD            wTrigNumber;

		hr = pITask->CreateTrigger ( &wTrigNumber, &pITaskTrig );
		if (FAILED(hr)) { goto Failed; }

		ZeroMemory ( &rTrigger, sizeof (TASK_TRIGGER) );

		SYSTEMTIME wtm;
		GetLocalTime(&wtm);

		rTrigger.cbTriggerSize = sizeof (TASK_TRIGGER);
		rTrigger.wBeginYear    = wtm.wYear;
		rTrigger.wBeginMonth   = wtm.wMonth;
		rTrigger.wBeginDay     = wtm.wDay;
		rTrigger.wStartHour    = hour;
		rTrigger.wStartMinute  = min;
		DAILY daily;
		daily.DaysInterval = 1;
		rTrigger.Type.Daily = daily;
		rTrigger.TriggerType = TASK_TIME_TRIGGER_DAILY;

		hr = pITaskTrig->SetTrigger ( &rTrigger );
		if (FAILED(hr)) { goto Failed; }

		hr = pITask->QueryInterface ( IID_IPersistFile, (void **) &pIFile );
		if (FAILED(hr)) { goto Failed; }

		hr = pIFile->Save ( NULL, FALSE );
		if (FAILED(hr)) { goto Failed; }
	  
		hr = pITask->Release();
		if (FAILED(hr)) { goto Failed; }

		return true;

Failed:
		CoUninitialize();
		return false;
	}
};

};

#endif // xptaskscheduler_h