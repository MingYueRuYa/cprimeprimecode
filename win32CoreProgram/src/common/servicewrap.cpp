/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"
#include "servicewrap.h"
#include "commonpack.h"

namespace XIBAO
{
	ServiceWrap::ServiceWrap(const wstring &wstrName, 
								const wstring &wstrAppAbsPath, 
								bool running)
		: mServiceName(wstrName),
		  mAppAbsPath(wstrAppAbsPath),
		  mStopped(running),
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
				mStopped = false; 
				::InterlockedExchange(&mServiceStatus.dwCurrentState,
									SERVICE_PAUSED);
				::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
				XIBAO::DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_PAUSE");
			break;  
			case SERVICE_CONTROL_CONTINUE:  
				mStopped = true; 
				XIBAO::DebugHelper::OutputDebugStringW(
												L"SERVICE_CONTROL_CONTINUE"
											);
				::InterlockedExchange(&mServiceStatus.dwCurrentState,
									SERVICE_RUNNING);
				::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
				// ¼ÌÐøÖ´ÐÐº¯Êý
				DoTask();
			break;
			case SERVICE_CONTROL_STOP:  
				mStopped = false; 
				mServiceStatus.dwWin32ExitCode = 0;  
				mServiceStatus.dwCheckPoint      = 0;  
				mServiceStatus.dwWaitHint        = 0;     
				::InterlockedExchange(&mServiceStatus.dwCurrentState,
									SERVICE_STOPPED);
				SetServiceStatus(mServiceStatusHandle, &mServiceStatus); 
				XIBAO::DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_STOP");
			break; 
			case SERVICE_CONTROL_SHUTDOWN:
				mStopped = false; 
				mServiceStatus.dwWin32ExitCode	 = 0;  
				mServiceStatus.dwCheckPoint      = 0;  
				mServiceStatus.dwWaitHint        = 0;     
				::InterlockedExchange(&mServiceStatus.dwCurrentState,
										SERVICE_STOPPED);
				SetServiceStatus(mServiceStatusHandle, &mServiceStatus); 
			break;
			case SERVICE_CONTROL_INTERROGATE:  
			break;  
		}       
		return;  
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
		this->mServiceName			= servicewrap.mServiceName;
		this->mAppAbsPath			= servicewrap.mAppAbsPath;
		this->mServiceStatus		= servicewrap.mServiceStatus;
		this->mServiceStatusHandle	= servicewrap.mServiceStatusHandle;
	}

};

