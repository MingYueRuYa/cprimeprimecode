/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "registerhelper.h"
#include "servicesmanager.h"

#include <memory>

using std::pair;
using std::unique_ptr;

#define GUARD_SERVICE(pointer)                                  \
  std::unique_ptr<void, void (*)(void*)> p##pointer(            \
      pointer, [](void* handle) {                               \
        ::CloseServiceHandle((SC_HANDLE)handle);                \
      });

namespace XIBAO {

void WINAPI ServicesManager::_ServiceMain(
    _In_ DWORD dwArgc,
    _In_reads_(dwArgc) _Deref_pre_z_ LPWSTR* lpszArgv) throw() {
  SINGLETON_INSTANCE(ServicesManager).ServiceMain(dwArgc, lpszArgv);
}

void WINAPI ServicesManager::_ServiceCtrlHandler(DWORD Opcode) {
  SINGLETON_INSTANCE(ServicesManager).ServiceCtrlHandler(Opcode);
}

ServicesManager::SMErrorCode ServicesManager::RemoveService(
    const wstring& serviceName) {
  if (SM_SUCCESS != HaltService(serviceName)) {
    return SM_FAILED;
  }

  SMErrorCode errorcode = SM_SUCCESS;
  SC_HANDLE scmanager = 0;
  scmanager = ::OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
  GUARD_SERVICE(scmanager);
  if (0 == scmanager) {
    return static_cast<SMErrorCode>(GetLastError());
  }

  SC_HANDLE scservice = ::OpenServiceW((SC_HANDLE)pscmanager.get(),
                                       serviceName.c_str(), SERVICE_ALL_ACCESS);
  GUARD_SERVICE(scservice);
  if (0 == scservice) {
    return static_cast<SMErrorCode>(GetLastError());
  }

  if (0 == ::DeleteService((SC_HANDLE)pscservice.get())) {
    return static_cast<SMErrorCode>(GetLastError());
  }

  DeleteServiceReg(serviceName);
  return errorcode;
}

ServicesManager::SMErrorCode ServicesManager::HaltService(
    const wstring& serviceName) {
  SMErrorCode errorcode = SM_SUCCESS;
  SC_HANDLE scmanager = 0, scservice = 0;
  scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
  if (0 == scmanager) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  scservice =
      ::OpenServiceW(scmanager, serviceName.c_str(), SERVICE_ALL_ACCESS);
  if (0 == scservice) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  SERVICE_STATUS status;
  ::ZeroMemory(&status, sizeof(status));
  if (!::QueryServiceStatus(scservice, &status)) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  if (SERVICE_RUNNING == status.dwCurrentState) {
    if (!::ControlService(scservice, SERVICE_CONTROL_STOP, &status)) {
      errorcode = static_cast<SMErrorCode>(GetLastError());
      goto CloseSCHandle;
    }

    while (::QueryServiceStatus(scservice, &status)) {
      ::Sleep(status.dwWaitHint);
      if (SERVICE_STOPPED == status.dwCurrentState) {
        break;
      }  // if
    }    // while
  }

  ::CloseServiceHandle(scmanager);
  ::CloseServiceHandle(scservice);
  return errorcode;

CloseSCHandle:
  ::CloseServiceHandle(scmanager);
  ::CloseServiceHandle(scservice);
  return errorcode;
}

ServicesManager::SMErrorCode ServicesManager::QueryServiceStatus(
    const wstring& serviceName,
    DWORD& servicestatus) {
  SMErrorCode errorcode = SM_SUCCESS;
  SC_HANDLE scmanager = 0, scservice = 0;
  scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
  if (0 == scmanager) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  scservice =
      ::OpenServiceW(scmanager, serviceName.c_str(), SERVICE_ALL_ACCESS);
  if (0 == scservice) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  SERVICE_STATUS status;
  ::ZeroMemory(&status, sizeof(status));
  if (!::QueryServiceStatus(scservice, &status)) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  ::CloseServiceHandle(scmanager);
  ::CloseServiceHandle(scservice);
  servicestatus = status.dwCurrentState;
  return errorcode;

CloseSCHandle:
  ::CloseServiceHandle(scmanager);
  ::CloseServiceHandle(scservice);
  return errorcode;
}

DWORD ServicesManager::DeleteServiceReg(const wstring& wstrServiceName) {
  wstring subkey =
      wstring(L"SYSTEM\\CurrentControlSet\\Services\\") + wstrServiceName;
  RegisterHelper reghelper(HKEY_LOCAL_MACHINE, subkey, KEY_ALL_ACCESS);
  return reghelper.DeleteKey();
}

ServicesManager::~ServicesManager() {}

ServicesManager::SMErrorCode ServicesManager::Start(
    const wstring& servicename) {
  mCurServiceName = servicename;
  WCHAR appname[MAX_PATH * 4] = {0};
  wcscpy_s(appname, _countof(appname), mCurServiceName.c_str());
  SERVICE_TABLE_ENTRYW DispatchTable[] = {
      {appname, ServicesManager::_ServiceMain}, {NULL, NULL}};
  StartServiceCtrlDispatcher(DispatchTable);
  return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::InstallService(
    const wstring& wstrServiceName) {
  SMErrorCode errcode = _FindServiceWrap(wstrServiceName);
  if (SM_SERVICEWRAP_EXIST != errcode) {
    return errcode;
  }

  shared_ptr<ServiceWrap> serwrap = nullptr;
  errcode = GetServiceWrap(wstrServiceName, serwrap);
  if (SM_SUCCESS != errcode) {
    return errcode;
  }

  wstring serdesc = serwrap->GetServiceDesc();
  wstring wstrname = serwrap->GetAppAbsPath();
  LPCTSTR strappname = wstrname.c_str();
  // 注册表写入信息
  serwrap->SetRegInfo();

  SC_HANDLE scmanager = 0, scservice = 0;
  scmanager = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
  if (NULL == scmanager) {
    errcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  scservice = ::CreateServiceW(
      scmanager, wstrServiceName.c_str(), wstrServiceName.c_str(),
      SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START,
      SERVICE_ERROR_NORMAL, strappname, NULL, NULL, NULL, NULL, NULL);

  if (NULL == scservice) {
    errcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  WCHAR chDes[MAX_PATH * 4] = {0};
  wcscpy_s(chDes, _countof(chDes), serdesc.c_str());

  SERVICE_DESCRIPTION servicedesc;
  servicedesc.lpDescription = chDes;
  if (0 == ChangeServiceConfig2W(scservice, SERVICE_CONFIG_DESCRIPTION,
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
    const wstring& wstrName,
    DWORD argc,
    LPCWSTR* argv) {
  // 将此段代码移动到servicewrap里面
  SMErrorCode errorcode = SM_SUCCESS;
  SC_HANDLE scmanager = 0, scservice = 0;
  scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
  if (0 == scmanager) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  scservice = ::OpenServiceW(scmanager, wstrName.c_str(), SERVICE_ALL_ACCESS);
  if (0 == scservice) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  SERVICE_STATUS status;
  ::ZeroMemory(&status, sizeof(status));
  if (!::QueryServiceStatus(scservice, &status)) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  // 如果正在运行状态
  if (status.dwCurrentState == SERVICE_RUNNING) {
    // 先停止，再启动
    if (!::ControlService(scservice, SERVICE_CONTROL_STOP, &status)) {
      errorcode = static_cast<SMErrorCode>(GetLastError());
      goto CloseSCHandle;
    }

    while (::QueryServiceStatus(scservice, &status)) {
      ::Sleep(status.dwWaitHint);

      if (SERVICE_STOPPED == status.dwCurrentState) {
        break;
      }  // if
    }    // while
  }      // if

  // 启动服务
  if (!::StartServiceW(scservice, argc, argv)) {
    errorcode = static_cast<SMErrorCode>(GetLastError());
    goto CloseSCHandle;
  }

  // 等待服务启动
  while (::QueryServiceStatus(scservice, &status)) {
    ::Sleep(status.dwWaitHint);
    if (SERVICE_RUNNING == status.dwCurrentState) {
      break;
    }  // if
  }    // while

  ::CloseServiceHandle(scmanager);
  ::CloseServiceHandle(scservice);
  return errorcode;

CloseSCHandle:
  ::CloseServiceHandle(scmanager);
  ::CloseServiceHandle(scservice);
  return errorcode;
}

ServicesManager::SMErrorCode ServicesManager::PauseService(
    const wstring& serviceName) {
  return SM_FAILED;
}

ServicesManager::SMErrorCode ServicesManager::ResumeService(
    const wstring& serviceName) {
  return SM_FAILED;
}

void ServicesManager::ServiceMain(_In_ DWORD dwArgc,
                                  _In_reads_(dwArgc)
                                      _Deref_pre_z_ LPWSTR* lpszArgv) {
  shared_ptr<ServiceWrap> servicewrap = nullptr;
  if (ServicesManager::SM_SUCCESS !=
      SINGLETON_INSTANCE(ServicesManager)
          .GetServiceWrap(mCurServiceName.c_str(), servicewrap)) {
    return;
  }

  servicewrap->ServiceMain(dwArgc, lpszArgv);
  servicewrap->DoTask();
}

void ServicesManager::ServiceCtrlHandler(DWORD Opcode) {
  shared_ptr<ServiceWrap> servicewrap = nullptr;
  if (SM_SUCCESS != GetServiceWrap(mCurServiceName.c_str(), servicewrap)) {
    return;
  }

  servicewrap->ServiceCtrlHandler(Opcode);
}

ServicesManager::SMErrorCode ServicesManager::AddServiceWrap(
    shared_ptr<ServiceWrap> serviceWrap) {
  if (SM_SERVICEWRAP_EXIST == _FindServiceWrap(serviceWrap->GetServiceName())) {
    return SM_SERVICEWRAP_EXIST;
  }

  mServiceMap.insert(pair<wstring, shared_ptr<ServiceWrap>>(
      serviceWrap->GetServiceName(), serviceWrap));

  return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::DeleteServiceWrap(
    shared_ptr<ServiceWrap> serviceWrap) {
  if (SM_SERVICEWRAP_NOT_EXIST ==
      _FindServiceWrap(serviceWrap->GetServiceName())) {
    return SM_SERVICEWRAP_NOT_EXIST;
  }

  mServiceMap.erase(serviceWrap->GetServiceName());

  return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::DeleteService(
    const wstring& wstrName) {
  SMErrorCode errorcode = HaltService(wstrName);
  if (SM_SUCCESS != errorcode) {
    return errorcode;
  }

  DWORD dwerrorcode = DeleteServiceReg(wstrName);
  if (0 != dwerrorcode) {
    return SM_FAILED;
  }

  shared_ptr<ServiceWrap> delservice;
  errorcode = GetServiceWrap(wstrName, delservice);
  if (SM_SUCCESS != errorcode) {
    return errorcode;
  }

  errorcode = DeleteServiceWrap(delservice);
  if (SM_SUCCESS != errorcode) {
    return errorcode;
  }

  return HaltService(wstrName);
}

ServicesManager::SMErrorCode ServicesManager::GetServiceWrap(
    const wstring& ServiceName,
    shared_ptr<ServiceWrap>& serviceWrap) {
  if (mServiceMap.empty()) {
    return SM_SERVICEMAP_EMPTY;
  }

  if (SM_SERVICEWRAP_NOT_EXIST == _FindServiceWrap(ServiceName)) {
    return SM_SERVICEWRAP_NOT_EXIST;
  }

  map<wstring, shared_ptr<ServiceWrap>>::iterator ifind =
      mServiceMap.find(ServiceName);
  serviceWrap = (ifind->second);

  return SM_SUCCESS;
}

ServicesManager::SMErrorCode ServicesManager::_FindServiceWrap(
    const wstring& wstrServiceName) {
  map<wstring, shared_ptr<ServiceWrap>>::iterator ifind =
      mServiceMap.find(wstrServiceName);
  return ifind == mServiceMap.end() ? SM_SERVICEWRAP_NOT_EXIST
                                    : SM_SERVICEWRAP_EXIST;
}

}  // namespace XIBAO
