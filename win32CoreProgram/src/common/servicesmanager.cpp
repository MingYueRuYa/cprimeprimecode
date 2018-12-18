/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"
#include "servicesmanager.h"

using std::pair;

namespace XIBAO {

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
	mCurServiceName = servicename;
	WCHAR appname[MAX_PATH*4] = {0};
	wcscpy_s(appname, _countof(appname), mCurServiceName.c_str());
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

	wstring serdesc		= serwrap->GetServiceDesc();
	wstring wstrname	= serwrap->GetAppAbsPath();
	LPCTSTR strappname	= wstrname.c_str();

	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == scmanager) {
		errcode = static_cast<SMErrorCode>(GetLastError());
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
		errcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	WCHAR chDes[MAX_PATH*4] = {0};
	wcscpy_s(chDes, _countof(chDes), serdesc.c_str());

	SERVICE_DESCRIPTION servicedesc;
	servicedesc.lpDescription = chDes;
	if (0 == ChangeServiceConfig2W(scservice, 
									SERVICE_CONFIG_DESCRIPTION, 
									&servicedesc)) {
		errcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	CloseServiceHandle(scmanager);
	CloseServiceHandle(scservice);
	return errcode;

CloseSCHandle:
	CloseServiceHandle(scmanager);
	CloseServiceHandle(scservice);
	return errcode;	
}

ServicesManager::SMErrorCode ServicesManager::StartService(
										const wstring &wstrName)
{
	SMErrorCode errorcode = SM_SUCCESS;
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
	if (0 == scmanager) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	scservice = ::OpenServiceW(scmanager, 
								wstrName.c_str(),
								SERVICE_ALL_ACCESS);	
	if (0 == scservice) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	SERVICE_STATUS status;
	::ZeroMemory(&status, sizeof(status));
	if (! ::QueryServiceStatus(scservice, &status)) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	// �����������״̬
	if (status.dwCurrentState == SERVICE_RUNNING) {
		// ��ֹͣ��������
		if (! ::ControlService(scservice, SERVICE_CONTROL_STOP, &status)) {
			errorcode = static_cast<SMErrorCode>(GetLastError());
			goto CloseSCHandle;
		}

		while (::QueryServiceStatus(scservice, &status)) {
			::Sleep(status.dwWaitHint);

			if (SERVICE_STOPPED == status.dwCurrentState) {
				break;
			} // if
		} // while
	} // if

	// ��������
	if (! ::StartServiceW(scservice, NULL, NULL)) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	// �ȴ���������
	while (::QueryServiceStatus(scservice, &status)) {
		::Sleep(status.dwWaitHint);
		if (SERVICE_RUNNING == status.dwCurrentState) {
			break;
		} // if
	} // while

	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return errorcode;

CloseSCHandle:
	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return errorcode;
}

ServicesManager::SMErrorCode ServicesManager::StopService(
								const wstring &serviceName)
{
	SMErrorCode errorcode = SM_SUCCESS;
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
	if (0 == scmanager) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	scservice = ::OpenServiceW(scmanager, serviceName.c_str(),
								SERVICE_ALL_ACCESS);
	if (0 == scservice) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	SERVICE_STATUS status;
	::ZeroMemory(&status, sizeof(status));
	if (! ::QueryServiceStatus(scservice, &status)) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	if (SERVICE_RUNNING == status.dwCurrentState) {
		if (! ::ControlService(scservice, SERVICE_CONTROL_STOP, &status)) {
			errorcode = static_cast<SMErrorCode>(GetLastError());
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
	return errorcode;

CloseSCHandle:
	::CloseServiceHandle(scmanager);
	::CloseServiceHandle(scservice);
	return errorcode;
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
	SMErrorCode errorcode = SM_SUCCESS;

	return errorcode;
}

void ServicesManager::ServiceMain(
		_In_ DWORD dwArgc,
		_In_reads_(dwArgc) _Deref_pre_z_ LPTSTR* lpszArgv)
{
	ServiceWrap *servicewrap = nullptr;
	if (ServicesManager::SM_SUCCESS != 
			SINGLETON_INSTANCE(ServicesManager).GetServiceWrap(
										mCurServiceName.c_str(), servicewrap)
		) {
		return;
	}

	servicewrap->ServiceMain(dwArgc, lpszArgv);
	servicewrap->DoTask();
}

void ServicesManager::ServiceCtrlHandler(DWORD Opcode)
{
	ServiceWrap *servicewrap = nullptr;
	if (SM_SUCCESS != GetServiceWrap(mCurServiceName.c_str(), servicewrap)) {
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
	SMErrorCode errorcode = SM_SUCCESS;
	SC_HANDLE scmanager = 0, scservice = 0;
	scmanager = ::OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (0 == scmanager) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	scservice = ::OpenServiceW(scmanager, wstrServiceName.c_str(), 
								SERVICE_ALL_ACCESS);

	if (0 == scservice) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
		goto CloseSCHandle;
	}

	if (0 == ::DeleteService(scservice)) {
		errorcode = static_cast<SMErrorCode>(GetLastError());
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

}