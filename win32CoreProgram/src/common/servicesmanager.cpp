/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"
#include "servicesmanager.h"

namespace XIBAO {

using std::pair;

// LPWSTR appname = L"service_manager_test";

void WINAPI ServicesManager::_ServiceMain(
		_In_ DWORD dwArgc,
		_In_reads_(dwArgc) _Deref_pre_z_ LPTSTR* lpszArgv) throw()
{
	SINGLETON_INSTANCE(ServicesManager).ServiceMain(dwArgc, lpszArgv);
}

void WINAPI ServicesManager::_ServiceCtrlHandler(DWORD Opcode)
{
	SINGLETON_INSTANCE(ServicesManager).ServiceCtrlHandler(Opcode);
}

ServicesManager::~ServicesManager()
{
}

ServicesManager::SMErrorCode ServicesManager::Start(const wstring &servicename)
{
	// mCurServiceName = servicename;
	WCHAR appname[1024] = {0};
	// wcscpy_s(appname, _countof(appname), mCurServiceName.c_str());
	wcscpy_s(appname, _countof(appname), servicename.c_str());
	SERVICE_TABLE_ENTRY DispatchTable[]={
		{appname, ServicesManager::_ServiceMain},
		{NULL, NULL}
	};   
	StartServiceCtrlDispatcher(DispatchTable);  
	return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::InstallService(
							const wstring &wstrServiceName)
{
	SMErrorCode errcode = _FindServiceWrap(wstrServiceName);
	if (SM_SERVICEWRAP_EXIST != errcode) {
		return errcode;
	}
	
	ServiceWrap *serwrap = nullptr;
	errcode	= GetServiceWrap(wstrServiceName, serwrap);
	if (SM_SUCCESS != errcode) {
		return errcode;
	}

	wstring wstrname	= serwrap->GetAppAbsPath();
	LPCTSTR strappname	= wstrname.c_str();
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == scmanager) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	scservice = ::CreateServiceW(scmanager, 
									wstrServiceName.c_str(), 
									wstrServiceName.c_str(),
									SERVICE_ALL_ACCESS,
									SERVICE_WIN32_OWN_PROCESS,
									SERVICE_AUTO_START,
									SERVICE_ERROR_NORMAL,
									strappname,
									NULL, NULL, NULL, NULL, NULL);

	if (NULL == scservice) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	SERVICE_DESCRIPTION servicedesc;
	servicedesc.lpDescription = L"Service Manager demo";
	if (0 == ChangeServiceConfig2W(scservice, 
									SERVICE_CONFIG_DESCRIPTION, 
									&servicedesc)) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	CloseServiceHandle(scmanager);
	CloseServiceHandle(scservice);
	return SM_SUCCESS;

CloseSCHandle:
	CloseServiceHandle(scmanager);
	CloseServiceHandle(scservice);
	return SM_FAILED;	
}

ServicesManager::SMErrorCode ServicesManager::StartService(
										const wstring &wstrName)
{
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
	if (0 == scmanager) {
		DWORD dwlasterror = GetLastError();
		return SM_FAILED;
	}

	scservice = ::OpenServiceW(scmanager, 
								wstrName.c_str(),
								SERVICE_ALL_ACCESS);	
	if (0 == scservice) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	SERVICE_STATUS status;
	::ZeroMemory(&status, sizeof(status));
	if (! ::QueryServiceStatus(scservice, &status)) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	// 如果正在运行状态
	if (status.dwCurrentState == SERVICE_RUNNING) {
		// 先停止，再启动
		if (! ::ControlService(scservice, SERVICE_CONTROL_STOP, &status)) {
			DWORD dwlasterror = GetLastError();
			goto CloseSCHandle;
		}

		while (::QueryServiceStatus(scservice, &status)) {
			::Sleep(status.dwWaitHint);

			if (SERVICE_STOPPED == status.dwCurrentState) {
				break;
			} // if
		} // while
	} // if

	// 启动服务
	if (! ::StartServiceW(scservice, NULL, NULL)) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	// 等待服务启动
	while (::QueryServiceStatus(scservice, &status)) {
		::Sleep(status.dwWaitHint);
		if (SERVICE_RUNNING == status.dwCurrentState) {
			break;
		} // if
	} // while

	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return SM_SUCCESS;

CloseSCHandle:
	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return SM_FAILED;
}

ServicesManager::SMErrorCode ServicesManager::StopService(
								const wstring &serviceName)
{
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
	if (0 == scmanager) {
		DWORD dwlasterror = GetLastError();
		return SM_FAILED;
	}

	scservice = ::OpenServiceW(scmanager, serviceName.c_str(),
								SERVICE_ALL_ACCESS);
	if (0 == scservice) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	SERVICE_STATUS status;
	::ZeroMemory(&status, sizeof(status));
	if (! ::QueryServiceStatus(scservice, &status)) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	if (SERVICE_RUNNING == status.dwCurrentState) {
		if (! ::ControlService(scservice, SERVICE_CONTROL_STOP, &status)) {
			DWORD dwlasterror = GetLastError();
			goto CloseSCHandle;
		}	

		while (::QueryServiceStatus(scservice, &status)) {
			::Sleep(status.dwWaitHint);
			if (SERVICE_STOPPED == status.dwCurrentState) {
				break;
			} // if
		} // while

	} // if

	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return SM_SUCCESS;

CloseSCHandle:
	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return SM_FAILED;
}

ServicesManager::SMErrorCode ServicesManager::PauseService(
							const wstring &serviceName)
{
	return SM_FAILED;
}

ServicesManager::SMErrorCode ServicesManager::ResumeService(
							const wstring &serviceName)
{
	return SM_FAILED;
}


ServicesManager::SMErrorCode ServicesManager::QueryServiceStatus(
							const wstring &serviceName)
{
	return SM_FAILED;
}

void ServicesManager::ServiceMain(
		_In_ DWORD dwArgc,
		_In_reads_(dwArgc) _Deref_pre_z_ LPTSTR* lpszArgv)
{
	ServiceWrap *servicewrap = nullptr;
	if (ServicesManager::SM_SUCCESS != 
			SINGLETON_INSTANCE(ServicesManager).GetServiceWrap(
										L"demo", servicewrap)
		) {
		return;
	}

	servicewrap->ServiceMain(dwArgc, lpszArgv);
	servicewrap->DoTask();
}

void ServicesManager::ServiceCtrlHandler(DWORD Opcode)
{
	ServiceWrap *servicewrap = nullptr;
	if (SM_SUCCESS != GetServiceWrap(L"demo", servicewrap)) {
		return;
	}

	servicewrap->ServiceCtrlHandler(Opcode);
}

ServicesManager::SMErrorCode ServicesManager::AddServiceWrap(
												const ServiceWrap &serviceWrap
											)
{		
	if (SM_SERVICEWRAP_EXIST == _FindServiceWrap(serviceWrap.GetServiceName())
		) {
		return SM_SERVICEWRAP_EXIST;
	}

	mServiceMap.insert(
			pair<wstring, ServiceWrap>(serviceWrap.GetServiceName(),
			ServiceWrap(serviceWrap))
		);

	return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::DeleteServiceWrap(
												const ServiceWrap &serviceWrap
											)
{
	if (SM_SERVICEWRAP_NOT_EXIST == _FindServiceWrap(
										serviceWrap.GetServiceName()
									)) {
		return SM_SERVICEWRAP_NOT_EXIST;
	}

	mServiceMap.erase(serviceWrap.GetServiceName());

	return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::DeleteService(
							const wstring &wstrName)
{
	SMErrorCode errorcode = StopService(wstrName);
	if (SM_SUCCESS != errorcode) {
		return errorcode;
	}
	
	return _DeleteService(wstrName);
}

void ServicesManager::Initialize()
{
	// AddServiceWrap(ServiceWrap(L"demo"));
}

ServicesManager::SMErrorCode ServicesManager::GetServiceWrap(
										const wstring &ServiceName, 
										ServiceWrap *&serviceWrap) {
	if (mServiceMap.empty()) {
		return SM_SERVICEMAP_EMPTY;
	}

	if (SM_SERVICEWRAP_NOT_EXIST == _FindServiceWrap(ServiceName)) {
		return SM_SERVICEWRAP_NOT_EXIST;
	}

	map<wstring, ServiceWrap>::iterator ifind = mServiceMap.find(ServiceName);
	serviceWrap = &(ifind->second);

	return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::_FindServiceWrap(
											const wstring &wstrServiceName
										)
{
	map<wstring, ServiceWrap>::iterator ifind = mServiceMap.find(
															wstrServiceName
														);
	
	return ifind == mServiceMap.end() ? 
				SM_SERVICEWRAP_NOT_EXIST : SM_SERVICEWRAP_EXIST;
}

ServicesManager::SMErrorCode ServicesManager::_DeleteService(
							const wstring &wstrServiceName)
{
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = ::OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (0 == scmanager) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	scservice = ::OpenServiceW(scmanager, wstrServiceName.c_str(), 
								SERVICE_ALL_ACCESS);

	if (0 == scservice) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	if (0 == ::DeleteService(scservice)) {
		DWORD dwlasterror = GetLastError();
		goto CloseSCHandle;
	}

	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return SM_SUCCESS;

CloseSCHandle:
	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return SM_FAILED;
}

}
