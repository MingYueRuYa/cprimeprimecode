#if ( NTDDI_VERSION < NTDDI_LONGHORN )
#	error NTDDI_VERSION must be defined as NTDDI_LONGHORN or later
#endif

//////////////////////////////////////////////////////////////////
// if ASSERT was not defined already, lets define our own version,
// to use the CRT assert() 

#ifndef ASSERT
#	ifdef _DEBUG
#		include <assert.h>
#		define ASSERT(x) assert( x )
#		define ASSERT_HERE assert( FALSE )
#	else// _DEBUG
#		define ASSERT(x) 
#	endif//_DEBUG
#endif//ASSERT

///////////////////////////////////////////////////////////////////
// a handy macro to get the number of characters (not bytes!) 
// a string buffer can hold

#ifndef _tsizeof 
#	define _tsizeof( s )  (sizeof(s)/sizeof(s[0]))
#endif//_tsizeof

#include <comdef.h>
#include <taskschd.h>


//extern HRESULT 
//IsElevated( __out_opt BOOL * pbElevated = NULL );

/*
Use IsElevated() to determine whether the current process is elevated or not.

Parameters:

pbElevated
	[out] [optional] Pointer to a BOOL variable that, if non-NULL, receives the result.

	The possible values are:

	TRUE - the current process is elevated.
		This value indicates that either UAC is enabled, and the process was elevated by 
		the administrator, or that UAC is disabled and the process was started by a user 
		who is a member of the Administrators group.

	FALSE - the current process is not elevated (limited).
		This value indicates that either UAC is enabled, and the process was started normally, 
		without the elevation, or that UAC is disabled and the process was started by a standard user. 

Return Values
	If the function succeeds, and the current process is elevated, the return value is S_OK. 
	If the function succeeds, and the current process is not elevated, the return value is S_FALSE. 
	If the function fails, the return value is E_FAIL. To get extended error information, 
	call GetLastError().
*/

BOOL 
AddSystemTask(	
	__in		HWND	hwnd, 
	__in		LPCTSTR pszPath, 
	__in		LPCWSTR szTaskName,
	__in		BOOL bIsCheck = FALSE,
	__in_opt	LPCTSTR pszParameters	= NULL, 
	__in_opt	LPCTSTR pszDirectory	= NULL ,
	__in		BOOL bDeleteTask = FALSE,
	__in		BOOL bIsAdmin = TRUE);

/*
Use RunAsStdUser() to start a non-elevated process. If the current process is not elevated,
it calls ShellExecuteEx() to start the new process. If the current process is elevated,
it uses Vista Task Scheduler to create a non-elevated task. 

Parameters:

hwnd
	[in] Window handle to any message boxes that the system might produce while executing this function.

pszPath
	[in] Address of a null-terminated string that specifies the executable file that 
		should be used to start the process.

pszParameters
	[in] [optional] Address of a null-terminated string that contains the command-line parameters for 
		the process. If NULL, no parameters are passed to the process.

pszDirectory
	[in] [optional] Address of a null-terminated string that specifies the name of the working directory. 
		If NULL, the current directory is used as the working directory. .

Return Values
	If the function succeeds, the return value is TRUE. 
	If the function fails, the return value is FALSE. To get extended error information, 
	call GetLastError().

NOTE: For this function to work, the application must be marked with the asInvoker or 
highestAvailable attributes in its manifest. If the executable to be started is marked 
as requireAdministrator, it will be started elevated! 
*/

#define  IMPLEMENT_VISTA_TOOLS

#ifdef IMPLEMENT_VISTA_TOOLS

#include <atlcomcli.h>
# pragma comment(lib, "taskschd.lib")
# pragma comment(lib, "comsupp.lib")
# pragma comment(lib, "credui.lib")


//////////////////////////////////////////////////////////////////////
// RunAsStdUser is based on the MSDN sample "Registration Trigger Example" 
//
// First, some helper classes, to make the interfaces release themselves on exit.
// Sure, we could use the templates for that, but let's take it easy here. 

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

///////////////////////////////////////////////////////////////////
// DO is a handy macro that makes the code a bit more readable:
// it checks the result of action and returns if tehre is an error.
// Sure, we could also use throw/catch, etc., but lets keep things simple here.

#define DO( action )		\
	if( FAILED( action ) )	\
{						\
	ASSERT( FALSE );	\
	return FALSE;		\
}
/////////////////////////////////////////////
// now the function itself:

BOOL DeleteTaskForWin7(LPCTSTR szTaskName)
{
	CoInitialize(NULL);

	HRESULT hr = 0;

    LPCWSTR pszTaskName = szTaskName;
	ITaskServiceHelper iService;
    hr = CoCreateInstance( CLSID_TaskScheduler,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_ITaskService,
						   (void**)&iService.p );
        
    //  Connect to the task service.
    DO( iService.p->Connect( _variant_t(), _variant_t(), _variant_t(), _variant_t()) )

    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.

	ITaskFolderHelper iRootFolder;
	hr = iService.p->GetFolder( _bstr_t( L"\\") , &iRootFolder.p );

    // DO( iService.p->GetFolder( _bstr_t( L"\\") , &iRootFolder.p ) )
    // DO( iService.p->GetFolder( _bstr_t( pszDirectory) , &iRootFolder.p ) )
    
	ITaskFolderHelper iNewFolder;
	IRegisteredTaskHelper iRegisteredTask;
	ITaskDefinitionHelper iTask;

	hr = iRootFolder.p->GetTask(_bstr_t(pszTaskName),&iRegisteredTask.p);
	hr = iRootFolder.p->DeleteTask(_bstr_t(pszTaskName),0);

	CoUninitialize();

	return 1;
}


BOOL 
AddSystemTask(
	__in		HWND	hwnd, 
	__in		LPCTSTR pszPath, 
	__in		LPCWSTR szTaskName,
	__in		LPCWSTR szTaskDescription,
	__in		BOOL bIsCheck,// = FALSE
	__in_opt	LPCTSTR pszParameters, //	= NULL, 
	__in_opt	LPCTSTR pszDirectory ,// = NULL
	__in		BOOL bDeleteTask,//	= false 
	__in		BOOL bIsAdmin,
	__in_opt	LPCTSTR pszWorkDir)
{
	// If process is elevated, we ask Task Scheduler to start a task for us.
	// I wish Microsoft would have provided an easier way for starting a non-elevated task,
	// like another verb for ShellExecuteEx, but they chose not to. 
	// I hope they had good reasons for that.

	HRESULT hr = 0;

    //  Choose a name for the task.

    LPCWSTR pszTaskName = szTaskName;

    //  Create an instance of the Task Service. 
    
	ITaskServiceHelper iService;

    hr = CoCreateInstance( CLSID_TaskScheduler,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_ITaskService,
						   (void**)&iService.p );
        
    //  Connect to the task service.
    DO( iService.p->Connect( _variant_t(), _variant_t(), _variant_t(), _variant_t()) )

    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.

	ITaskFolderHelper iRootFolder;

    DO( iService.p->GetFolder( _bstr_t( L"\\") , &iRootFolder.p ) )
    // DO( iService.p->GetFolder( _bstr_t( pszDirectory) , &iRootFolder.p ) )
    
	ITaskFolderHelper iNewFolder;
	IRegisteredTaskHelper iRegisteredTask;
	ITaskDefinitionHelper iTask;
	BOOL bTmp = FALSE;
	if(pszDirectory != NULL){
		hr = iRootFolder.p->GetFolder(_bstr_t(pszDirectory),&iNewFolder.p);
		if(hr  != S_OK){
			hr = iRootFolder.p->CreateFolder(_bstr_t(pszDirectory),
				_variant_t(), &iNewFolder.p); //使用默认的安全描述符
			if(FAILED(hr))
			{
				return FALSE;
			}
		}

		hr = iNewFolder.p->GetTask(_bstr_t(pszTaskName),&iRegisteredTask.p);
		if(hr != S_OK) {
			return FALSE;
		}
		if(bDeleteTask == TRUE){
			hr = iNewFolder.p->DeleteTask(_bstr_t(pszTaskName),0);
			if(hr == S_OK) {
				return TRUE;
			}
			return FALSE;
		}
	}
	else{
		hr = iRootFolder.p->GetTask(_bstr_t(pszTaskName),&iRegisteredTask.p);
		if(hr != S_OK && bIsCheck) {
			return FALSE;
		}
		if(bDeleteTask == TRUE){
			hr = iRootFolder.p->DeleteTask(_bstr_t(pszTaskName),0);
			if(hr == S_OK) {
				return TRUE;
			}
			return FALSE;
		}
	}

	if(hr == S_FALSE){
		if(bIsCheck){
			return FALSE;
		}

		DO( iService.p->NewTask( 0, &iTask.p ) )
	}else{
		if(bIsCheck){
			DO ( iRegisteredTask.p->get_Definition(&iTask.p))
			IActionCollectionHelper iActionCollection;

			DO( iTask.p->get_Actions( &iActionCollection.p ) )

			IActionHelper iAction;
			DO (iActionCollection.p->get_Item(1,&iAction.p))

			CComQIPtr<IExecAction> exec_act(iAction.p);
			CComBSTR exe_path2;
			hr = exec_act->get_Path(&exe_path2);
			CComBSTR exe_path3(pszPath);
			if(exe_path3 != exe_path2 ) 
			{
				return FALSE;
			}
			return TRUE;
		}else{
			iRootFolder.p->DeleteTask( _bstr_t( pszTaskName), 0  );
			DO( iService.p->NewTask( 0, &iTask.p ) )
		}
	}
	IRegistrationInfoHelper info;
	DO(iTask.p->get_RegistrationInfo(&(info.p)))
	if (nullptr != info.p) { 
		(info.p)->put_Description(_bstr_t(szTaskDescription)); 
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
	DO( iExecAction.p->put_Path( _bstr_t( pszPath ) ) )

	if( pszParameters )
	{
		DO( iExecAction.p->put_Arguments( _bstr_t( pszParameters ) ) )
	}

	if(pszWorkDir)
	{
		DO( iExecAction.p->put_WorkingDirectory( _bstr_t(pszWorkDir) ) )
	}

	ITriggerCollectionHelper iTriggerCollection;

	DO( iTask.p->get_Triggers( &iTriggerCollection.p ) )

	ITaskSettingsHelper iTaskSettings; 

	DO( iTask.p->get_Settings(&iTaskSettings.p) )

	iTaskSettings.p->put_DisallowStartIfOnBatteries(VARIANT_BOOL(FALSE));
	iTaskSettings.p->put_StopIfGoingOnBatteries(VARIANT_BOOL(FALSE));

	ITriggerHelper iTrigger;
	DO( iTriggerCollection.p->Create( TASK_TRIGGER_DAILY, &iTrigger.p ) )

	IDailyTrigger *dailyTriger = nullptr;
	iTrigger.p->QueryInterface(IID_IDailyTrigger, (void **)&dailyTriger);	
	if (nullptr != dailyTriger) {
		dailyTriger->put_Id(_bstr_t(L"trigger 1"));
		dailyTriger->put_DaysInterval(1);
		dailyTriger->put_StartBoundary(_bstr_t(L"2019-01-01T15:12:00"));
		dailyTriger->put_EndBoundary(_bstr_t(L"2099-01-01T14:55:00"));
		dailyTriger->put_Enabled(true);
	}

	ITriggerHelper iTrigger1;
	DO( iTriggerCollection.p->Create( TASK_TRIGGER_DAILY, &iTrigger1.p ) )
	IDailyTrigger *dailyTriger1 = nullptr;
	iTrigger1.p->QueryInterface(IID_IDailyTrigger, (void **)&dailyTriger1);	
	if (nullptr != dailyTriger) {
		dailyTriger1->put_Id(_bstr_t(L"trigger 2"));
		dailyTriger1->put_DaysInterval(1);
		dailyTriger1->put_StartBoundary(_bstr_t(L"2019-01-01T15:14:00"));
		dailyTriger1->put_EndBoundary(_bstr_t(L"2099-01-01T14:55:00"));
		dailyTriger1->put_Enabled(true);
	}

	IPrincipalHelper iPrincipal;

	DO( iTask.p->get_Principal( &iPrincipal.p ) )

	if (bIsAdmin)
	{
		DO(iPrincipal.p->put_RunLevel(TASK_RUNLEVEL_HIGHEST))
			//OutputDebugStringA("TASK_RUNLEVEL_HIGHEST");
	}
	else {
		DO(iPrincipal.p->put_RunLevel(TASK_RUNLEVEL_LUA))

			//OutputDebugStringA("TASK_RUNLEVEL_LUA");
	}
		
		

	hr = iRootFolder.p->RegisterTaskDefinition(
	_bstr_t( pszTaskName ),
	iTask.p,
	TASK_CREATE_OR_UPDATE, 
	_variant_t(), 
	_variant_t(), 
	TASK_LOGON_INTERACTIVE_TOKEN,
	_variant_t(L""),
	&iRegisteredTask.p);

	if(hr == S_OK) return TRUE;
	return FALSE;
}


#endif// IMPLEMENT_VISTA_TOOLS