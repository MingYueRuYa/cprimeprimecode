/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"
#include "servicewrap.h"
#include "commonpack.h"

using XIBAO::DebugHelper;
using XIBAO::ServicesManager;

namespace XIBAO
{
	ServiceWrap::ServiceWrap(const wstring &wstrName, 
								const wstring &wstrAppAbsPath,
								const wstring &wstrDesc,
								bool running)
		: mStopped(running),
		  mAppAbsPath(wstrAppAbsPath),
	  	  mServiceName(wstrName),
		  mServiceDesc(wstrDesc),
		  mServiceStatusHandle(0)		
	{
	}

	ServiceWrap& ServiceWrap::operator=(const ServiceWrap &servicewrap)
	{
		if (this == &servicewrap) {
			return *this;
		}

		_CopyValue(servicewrap);
		return *this;
	}

	ServiceWrap::ServiceWrap(const ServiceWrap &servicewrap)
	{
		_CopyValue(servicewrap);
	}

	ServiceWrap::~ServiceWrap()
	{
	}

	void ServiceWrap::SetServiceStatusHandle(const SERVICE_STATUS_HANDLE &handle)
	{
		mServiceStatusHandle = handle;
	}

	SERVICE_STATUS_HANDLE ServiceWrap::GetServiceStatusHandle() const 
	{
		return mServiceStatusHandle;
	}

	void ServiceWrap::SetServiceName(const wstring &wstrServiceName)
	{
		mServiceName = wstrServiceName;
	}

	wstring ServiceWrap::GetServiceName() const
	{
		return mServiceName;
	}

	void ServiceWrap::SetAppAbsPath(const wstring &wstrAppAbsPath)
	{
		mAppAbsPath = wstrAppAbsPath;
	}

	wstring ServiceWrap::GetAppAbsPath() const
	{
		return mAppAbsPath;
	}

	void ServiceWrap::SetStop(bool stop)
	{
		mStopped = stop;
	}

	bool ServiceWrap::GetStop() const
	{
		return mStopped;
	}

	void ServiceWrap::SetServiceDesc(const wstring &serviceDesc)
	{
		mServiceDesc = serviceDesc;
	}

	wstring ServiceWrap::GetServiceDesc()
	{
		return mServiceDesc;
	}

	void ServiceWrap::ServiceMain(DWORD argc, LPTSTR *argv)
	{
		mServiceStatus.dwServiceType          = SERVICE_WIN32;  
		mServiceStatus.dwCurrentState         = SERVICE_START_PENDING;  
		mServiceStatus.dwWin32ExitCode        = 0;  
		mServiceStatus.dwWaitHint             = 0;  
		mServiceStatus.dwCheckPoint           = 0;  
		mServiceStatus.dwServiceSpecificExitCode	= 0;  
		mServiceStatus.dwControlsAccepted			= 
							SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;  

		mServiceStatusHandle = RegisterServiceCtrlHandler(
									mServiceName.c_str(),
									ServicesManager::_ServiceCtrlHandler);   
		if ((SERVICE_STATUS_HANDLE)0 == mServiceStatusHandle) { 
			DWORD dwlasterror = GetLastError();
			return; 
		}      

		mServiceStatus.dwWaitHint             = 0;   
		mServiceStatus.dwCheckPoint           = 0;  
		mServiceStatus.dwCurrentState         = SERVICE_RUNNING;  
		if (! SetServiceStatus(mServiceStatusHandle, &mServiceStatus)) { 
			DWORD dwlasterror = GetLastError();
			return; 
		}  
	}

	void ServiceWrap::ServiceCtrlHandler(DWORD Opcode) 
	{
		switch(Opcode)  
		{  
			case SERVICE_CONTROL_PAUSE:  
				Pause();
			break;  
			case SERVICE_CONTROL_CONTINUE:  
				Continue();
			break;
			case SERVICE_CONTROL_STOP:  
				Stop();	
			break; 
			case SERVICE_CONTROL_SHUTDOWN:
				Shutdown();
			break;
			case SERVICE_CONTROL_INTERROGATE:  
				Interrogate();
			break;  
		}       
		return;  
	}

	DWORD ServiceWrap::QueryServiceStatus()
	{
		DWORD errorcode = 0;
		SC_HANDLE scmanager = 0, scservice = 0;
		scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
		if (0 == scmanager) {
			errorcode = GetLastError();
			goto CloseSCHandle;
		}

		scservice = ::OpenServiceW(scmanager, mServiceName.c_str(),
									SERVICE_ALL_ACCESS);
		if (0 == scservice) {
			errorcode = GetLastError();
			goto CloseSCHandle;
		}

		if (! ::QueryServiceStatus(scservice, &mServiceStatus)) {
			errorcode = GetLastError();
			goto CloseSCHandle;
		}

		::CloseServiceHandle(scmanager);
		::CloseServiceHandle(scservice);
		return errorcode;

CloseSCHandle:
		::CloseServiceHandle(scmanager);
		::CloseServiceHandle(scservice);
		return errorcode;
	}

	void ServiceWrap::SetRegInfo()
	{
	}

	void ServiceWrap::DelRegInfo()
	{
	}

	void ServiceWrap::Pause()
	{
		mStopped = false; 
		::InterlockedExchange(&mServiceStatus.dwCurrentState,
								SERVICE_PAUSED);
		::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
		DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_PAUSE");	
	}

	void ServiceWrap::Continue()
	{
		mStopped = true; 
		DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_CONTINUE");
		::InterlockedExchange(&mServiceStatus.dwCurrentState,
								SERVICE_RUNNING);
		::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
		while (0 == this->QueryServiceStatus()) {
			if (SERVICE_RUNNING == mServiceStatus.dwCurrentState) {
				break;
			} // if
		}

		// ����ִ�к���
		DoTask();
	}

	void ServiceWrap::Stop()
	{
		mStopped = false; 
		DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_STOP");
		::InterlockedExchange(&mServiceStatus.dwCurrentState,
								SERVICE_STOPPED);
		::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
	}

	void ServiceWrap::Shutdown()
	{
		Stop();
	}

	void ServiceWrap::Interrogate()
	{
	}

	void ServiceWrap::DoTask()
	{
		while (mStopped) {
			Sleep(1000*3);
			DebugHelper::OutputDebugString("service dotask....\r\n");
		}
	}

	void ServiceWrap::_CopyValue(const ServiceWrap &servicewrap)
	{
		this->mStopped				= servicewrap.mStopped;
		this->mAppAbsPath			= servicewrap.mAppAbsPath;
		this->mServiceName			= servicewrap.mServiceName;
		this->mServiceDesc			= servicewrap.mServiceDesc;
		this->mServiceStatus		= servicewrap.mServiceStatus;
		this->mServiceStatusHandle	= servicewrap.mServiceStatusHandle;
	}

};
