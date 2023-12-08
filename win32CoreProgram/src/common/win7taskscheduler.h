/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef win7taskscheduler_h
#define win7taskscheduler_h

#include <vector>
#include <utility>
#include <string>

#include <assert.h>

#include <comdef.h>
#include <taskschd.h>

#pragma comment(lib, "taskschd.lib")

using std::pair;
using std::vector;
using std::wstring;
using std::to_wstring;

namespace XIBAO {


class Win7TaskScheduler{

public:
	enum TaskMode:int {
		Normal = 1, // 普通模式，用户只有登录进去才会触发
		LOGON_PASSWD, // 输入用户名和密码的模式，这种模式不用登录也能触发
		SYSTEM  // system权限登录
	};


public:
	Win7TaskScheduler() {}
	~Win7TaskScheduler() {}

private:
class ITaskServiceHelper
{
public:
	ITaskServiceHelper()		{	p = NULL;	}
	~ITaskServiceHelper()		{	if ( p ) p->Release();	}

	ITaskService * p;
};

class ITaskFolderHelper
{
public:
	ITaskFolderHelper()			{	p = NULL;	}
	~ITaskFolderHelper()		{	if ( p ) p->Release();	}

	ITaskFolder * p;
};

class ITaskDefinitionHelper
{
public:
	ITaskDefinitionHelper()		{	p = NULL;	}
	~ITaskDefinitionHelper()	{	if ( p ) p->Release();	}

	ITaskDefinition * p;
};

class IRegistrationInfoHelper
{
public:
	IRegistrationInfoHelper()	{	p = NULL;	}
	~IRegistrationInfoHelper()	{	if ( p ) p->Release();	}

	IRegistrationInfo * p;
};

class IPrincipalHelper
{
public:
	IPrincipalHelper()			{	p = NULL;	}
	~IPrincipalHelper()			{	if ( p ) p->Release();	}

	IPrincipal * p;
};

class ITaskSettingsHelper
{
public:
	ITaskSettingsHelper()		{	p = NULL;	}
	~ITaskSettingsHelper()		{	if ( p ) p->Release();	}

	ITaskSettings * p;
};

class ITriggerCollectionHelper
{
public:
	ITriggerCollectionHelper()	{	p = NULL;	}
	~ITriggerCollectionHelper()	{	if ( p ) p->Release();	}

	ITriggerCollection * p;
};

class ITriggerHelper
{
public:
	ITriggerHelper()			{	p = NULL;	}
	~ITriggerHelper()			{	if ( p ) p->Release();	}

	ITrigger * p;
};

class IDailyTriggerHelper
{
public:
	IDailyTriggerHelper()			{	p = NULL;	}
	~IDailyTriggerHelper()			{	if ( p ) p->Release();	}

	IDailyTrigger * p;
};

class IRegistrationTriggerHelper
{
public:
	IRegistrationTriggerHelper(){	p = NULL;	}
	~IRegistrationTriggerHelper(){	if ( p ) p->Release();	}

	IRegistrationTrigger * p;
};

class IActionCollectionHelper
{
public:
	IActionCollectionHelper()	{	p = NULL;	}
	~IActionCollectionHelper()	{	if ( p ) p->Release();	}

	IActionCollection * p;
};

class IActionHelper
{
public:
	IActionHelper()				{	p = NULL;	}
	~IActionHelper()			{	if ( p ) p->Release();	}

	IAction * p;
};

class IExecActionHelper
{
public:
	IExecActionHelper()			{	p = NULL;	}
	~IExecActionHelper()		{	if ( p ) p->Release();	}

	IExecAction * p;
};

class IRegisteredTaskHelper
{
public:
	IRegisteredTaskHelper()		{	p = NULL;	}
	~IRegisteredTaskHelper()	{	if ( p ) p->Release();	}

	IRegisteredTask * p;
};

#define DO( action )		\
	if( FAILED( action ) )	\
{						\
	assert( FALSE );	\
	return FALSE;		\
}

public:
static HRESULT Create2MoreWin7(const wstring &appPath,
							const wstring &taskName,
							const wstring &taskDescription,
							const wstring &appWorkDir,
							const wstring &parameter,
							const vector<pair<int, int>> &vecTime,
							const wstring &userName,
							const wstring &passwd,
							int mode)
{
	CoInitialize(NULL);

	HRESULT hr = 0;
	ITaskServiceHelper iService;

    hr = CoCreateInstance( CLSID_TaskScheduler,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_ITaskService,
						   (void**)&iService.p);
	
    //  Connect to the task service.
    DO( iService.p->Connect( _variant_t(), _variant_t(), _variant_t(), _variant_t()) )

    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.
	ITaskFolderHelper iRootFolder;
    DO( iService.p->GetFolder( _bstr_t( L"\\") , &iRootFolder.p ) )
    
	ITaskFolderHelper iNewFolder;
	IRegisteredTaskHelper iRegisteredTask;
	ITaskDefinitionHelper iTask;
	BOOL bTmp = FALSE;
    /*
	if(! appWorkDir.empty()){
		hr = iRootFolder.p->GetFolder(_bstr_t(appWorkDir.c_str()),&iNewFolder.p);
		if(hr  != S_OK){
			hr = iRootFolder.p->CreateFolder(_bstr_t(appWorkDir.c_str()),
				_variant_t(), &iNewFolder.p); //使用默认的安全描述符
			if(FAILED(hr))
			{
				return FALSE;
			}
		}

		hr = iNewFolder.p->GetTask(_bstr_t(taskName.c_str()),&iRegisteredTask.p);
		if(hr != S_OK) {
			return FALSE;
		}
	}
	else{
		hr = iRootFolder.p->GetTask(_bstr_t(taskName.c_str()),&iRegisteredTask.p);
	}
    */

	DO( iService.p->NewTask( 0, &iTask.p ) )
	// DO( iService->NewTask( 0, &iTask.p ) )

	IRegistrationInfoHelper info;
	DO(iTask.p->get_RegistrationInfo(&(info.p)))
	if (nullptr != info.p) { 
		(info.p)->put_Description(_bstr_t(taskDescription.c_str())); 
	}

	IActionCollectionHelper iActionCollection;
	DO( iTask.p->get_Actions( &iActionCollection.p ) )

	IActionHelper iAction;
	DO( iActionCollection.p->Create( TASK_ACTION_EXEC, &iAction.p ) )

	IExecActionHelper iExecAction;
	//  QI for the executable task pointer.
	DO( iAction.p->QueryInterface( 
		IID_IExecAction, (void**) &iExecAction.p ) )

		//  Set the path of the executable to notepad.exe.
	DO( iExecAction.p->put_Path( _bstr_t( appPath.c_str() ) ) )

	if(! parameter.empty())
	{
		DO( iExecAction.p->put_Arguments(_bstr_t(parameter.c_str())))
	}

	if(! appWorkDir.empty())
	{
		DO( iExecAction.p->put_WorkingDirectory(_bstr_t(appWorkDir.c_str())))
	}

	ITriggerCollectionHelper iTriggerCollection;
	DO( iTask.p->get_Triggers( &iTriggerCollection.p ) )

	ITaskSettingsHelper iTaskSettings; 
	DO( iTask.p->get_Settings(&iTaskSettings.p) )

	iTaskSettings.p->put_DisallowStartIfOnBatteries(VARIANT_BOOL(FALSE));
	iTaskSettings.p->put_StopIfGoingOnBatteries(VARIANT_BOOL(FALSE));

	{
		for (int i = 0; i < vecTime.size(); ++i) {
			ITriggerHelper iTrigger;
			DO( iTriggerCollection.p->Create( TASK_TRIGGER_DAILY,
												&iTrigger.p ) )

			IDailyTrigger *dailyTriger = nullptr;
			iTrigger.p->QueryInterface(IID_IDailyTrigger, 
										(void **)&dailyTriger);	
			if (nullptr != dailyTriger) {
				wstring triggerid = taskName + L"_" + to_wstring(i);
				dailyTriger->put_Id(_bstr_t(triggerid.c_str()));
				dailyTriger->put_DaysInterval(1);
				wstring strstarttime = L"2019-01-01T" + to_wstring(vecTime[i].first) + L":" + to_wstring(vecTime[i].second) + L":00";
				dailyTriger->put_StartBoundary(_bstr_t(strstarttime.c_str()));
				dailyTriger->put_EndBoundary(_bstr_t(L"2099-12-31T00:00:00"));
				dailyTriger->put_Enabled(true);
			}
		}
	}

	IPrincipalHelper iPrincipal;
	DO( iTask.p->get_Principal( &iPrincipal.p ) )
	DO(iPrincipal.p->put_RunLevel(TASK_RUNLEVEL_LUA))

		if (mode == TaskMode::SYSTEM)
		{

	hr = iRootFolder.p->RegisterTaskDefinition(
												_bstr_t(taskName.c_str()),
												iTask.p,
												TASK_CREATE_OR_UPDATE, 
												_variant_t(L"SYSTEM"),
												_variant_t(), 
												TASK_LOGON_SERVICE_ACCOUNT,
												_variant_t(L""),
												&iRegisteredTask.p);
	}
		else if (mode == TaskMode::LOGON_PASSWD)
		{
	hr = iRootFolder.p->RegisterTaskDefinition(
												_bstr_t(taskName.c_str()),
												iTask.p,
												TASK_CREATE_OR_UPDATE, 
												_variant_t(userName.c_str()),
												_variant_t(passwd.c_str()),
												TASK_LOGON_PASSWORD,
												_variant_t(L""),
												&iRegisteredTask.p);
		}
		else
		{
	hr = iRootFolder.p->RegisterTaskDefinition(
												_bstr_t(taskName.c_str()),
												iTask.p,
												TASK_CREATE_OR_UPDATE, 
												_variant_t(L""),
												_variant_t(L""),
												TASK_LOGON_INTERACTIVE_TOKEN,
												_variant_t(L""),
												&iRegisteredTask.p);
		}

	return hr;
}

static bool Delete2MoreWin7(const wstring &taskName)
{
	ITaskServiceHelper iService;
    HRESULT hr = CoCreateInstance( CLSID_TaskScheduler,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_ITaskService,
						   (void**)&iService.p );
        
    DO( iService.p->Connect(_variant_t(), 
							_variant_t(), 
							_variant_t(), 
							_variant_t()))

	ITaskFolderHelper iRootFolder;
    DO( iService.p->GetFolder( _bstr_t( L"\\") , &iRootFolder.p ) )
    
	IRegisteredTaskHelper iRegisteredTask;
	ITaskDefinitionHelper iTask;

	hr = iRootFolder.p->GetTask(_bstr_t(taskName.c_str()),&iRegisteredTask.p);
	if (S_OK != hr)
	{
		return hr;
	}
	hr = iRootFolder.p->DeleteTask(_bstr_t(taskName.c_str()),0);

	return hr;
}

static HRESULT StartTaskScheduler(const wchar_t *app_name)
{
	CoInitialize(NULL);

	ITaskService* pService = NULL;
	HRESULT hr = CoCreateInstance(CLSID_TaskScheduler, NULL, CLSCTX_INPROC_SERVER, IID_ITaskService, (void**)&pService);
	if (FAILED(hr))
	{
		CoUninitialize();
		return hr;
	}

	hr = pService->Connect(_variant_t(), _variant_t(), _variant_t(), _variant_t());
	if (FAILED(hr))
	{
		pService->Release();
		CoUninitialize();
		return hr;
	}

	ITaskFolder* pRootFolder = NULL;
	hr = pService->GetFolder(_bstr_t(L"\\"), &pRootFolder);
	if (FAILED(hr))
	{
		pService->Release();
		CoUninitialize();
		return hr;
	}

	IRegisteredTask* pTask = NULL;
	hr = pRootFolder->GetTask(_bstr_t(app_name), &pTask);
	if (FAILED(hr))
	{
		pRootFolder->Release();
		pService->Release();
		CoUninitialize();
		return hr;
	}

	IRunningTask* pRunningTask = NULL;
	hr = pTask->Run(_variant_t(), &pRunningTask);
	if (FAILED(hr))
	{
		pTask->Release();
		pRootFolder->Release();
		pService->Release();
		CoUninitialize();
		return hr;
	}

	pRunningTask->Release();
	pTask->Release();
	pRootFolder->Release();
	pService->Release();
	CoUninitialize();
	return S_OK;
}

};

};

#endif // win7taskscheduler_h