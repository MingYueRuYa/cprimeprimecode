/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "servicewrap.h"
#include "commonpack.h"

using XIBAO::DebugHelper;
using XIBAO::ServicesManager;

namespace XIBAO {
ServiceWrap::ServiceWrap(const wstring &wstrName, const wstring &wstrAppAbsPath,
                         const wstring &wstrDesc, bool running)
    : mRunning(running),
      mAppAbsPath(wstrAppAbsPath),
      mServiceName(wstrName),
      mServiceDesc(wstrDesc),
      mServiceStatusHandle(0) {
  memset(&mServiceStatus, 0, sizeof(SERVICE_STATUS));
}

ServiceWrap &ServiceWrap::operator=(const ServiceWrap &servicewrap) {
  if (this == &servicewrap) {
    return *this;
  }

  _CopyValue(servicewrap);
  return *this;
}

bool ServiceWrap::operator==(const ServiceWrap &servicewrap) {
  if (this == &servicewrap) {
    return true;
  }

  return 0 == mServiceName.compare(servicewrap.mServiceName) ? true : false;
}

ServiceWrap::ServiceWrap(const ServiceWrap &servicewrap) {
  _CopyValue(servicewrap);
}

ServiceWrap::~ServiceWrap() {}

void ServiceWrap::SetServiceStatusHandle(const SERVICE_STATUS_HANDLE &handle) {
  mServiceStatusHandle = handle;
}

SERVICE_STATUS_HANDLE ServiceWrap::GetServiceStatusHandle() const {
  return mServiceStatusHandle;
}

void ServiceWrap::SetServiceName(const wstring &wstrServiceName) {
  mServiceName = wstrServiceName;
}

wstring ServiceWrap::GetServiceName() const { return mServiceName; }

void ServiceWrap::SetAppAbsPath(const wstring &wstrAppAbsPath) {
  mAppAbsPath = wstrAppAbsPath;
}

wstring ServiceWrap::GetAppAbsPath() const { return mAppAbsPath; }

void ServiceWrap::SetStop(bool stop) { mRunning = stop; }

bool ServiceWrap::GetStop() const { return mRunning; }

void ServiceWrap::SetServiceDesc(const wstring &serviceDesc) {
  mServiceDesc = serviceDesc;
}

wstring ServiceWrap::GetServiceDesc() { return mServiceDesc; }

void ServiceWrap::ServiceMain(DWORD argc, LPWSTR *argv) {
  mServiceStatus.dwServiceType = SERVICE_WIN32;
  mServiceStatus.dwCurrentState = SERVICE_START_PENDING;
  mServiceStatus.dwWin32ExitCode = 0;
  mServiceStatus.dwWaitHint = 0;
  mServiceStatus.dwCheckPoint = 0;
  mServiceStatus.dwServiceSpecificExitCode = 0;
  mServiceStatus.dwControlsAccepted =
      SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;

  mServiceStatusHandle = RegisterServiceCtrlHandler(
      mServiceName.c_str(), ServicesManager::_ServiceCtrlHandler);
  if ((SERVICE_STATUS_HANDLE)0 == mServiceStatusHandle) {
    DWORD dwlasterror = GetLastError();
    DebugHelper::OutputDebugString("RegisterServiceCtrlHandler last error:%d",
                                   dwlasterror);
    return;
  }

  mServiceStatus.dwWaitHint = 0;
  mServiceStatus.dwCheckPoint = 0;
  mServiceStatus.dwCurrentState = SERVICE_RUNNING;
  if (!SetServiceStatus(mServiceStatusHandle, &mServiceStatus)) {
    DWORD dwlasterror = GetLastError();
    DebugHelper::OutputDebugString("SetServiceStatus last error:%d",
                                   dwlasterror);
    return;
  }

  while (0 == this->QueryServiceStatus()) {
    Sleep(mServiceStatus.dwWaitHint);
    if (SERVICE_RUNNING == mServiceStatus.dwCurrentState) {
      break;
    }  // if
    DebugHelper::OutputDebugString("wait service...");
  }
  Start(argc, argv);
}

void ServiceWrap::ServiceCtrlHandler(DWORD Opcode) {
  switch (Opcode) {
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

DWORD ServiceWrap::QueryServiceStatus() {
  DWORD errorcode = 0;
  SC_HANDLE scmanager = 0, scservice = 0;
  scmanager = ::OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
  if (0 == scmanager) {
    errorcode = GetLastError();
    goto CloseSCHandle;
  }

  scservice =
      ::OpenServiceW(scmanager, mServiceName.c_str(), SERVICE_ALL_ACCESS);
  if (0 == scservice) {
    errorcode = GetLastError();
    goto CloseSCHandle;
  }

  if (!::QueryServiceStatus(scservice, &mServiceStatus)) {
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

void ServiceWrap::SetRegInfo() {
  wstring subkey =
      wstring(L"SYSTEM\\CurrentControlSet\\Services\\") + mServiceName;
  RegisterHelper reghelper(HKEY_LOCAL_MACHINE, subkey, KEY_ALL_ACCESS);
  reghelper.SetMultiSZ(L"DependOnService", wstring(L"RPCSS"));
  reghelper.SetMultiSZ(L"Description", mServiceDesc);
  reghelper.SetSZ(L"DisplayName", mServiceName);
  reghelper.SetDWORD(L"ErrorControl", 0x0);
  reghelper.SetExpandSZ(L"ImagePath", mAppAbsPath);
  reghelper.SetSZ(L"ObjectName", wstring(L"LocalSystem"));
  reghelper.SetDWORD(L"Start", 0x02);
  reghelper.SetDWORD(L"Type", 0x110);
  reghelper.SetDWORD(L"WOW64", 0x14c);
}

void ServiceWrap::Start(DWORD argc, LPWSTR *argv) {
  DebugHelper::OutputDebugString(L"%s", argv[0]);
  for (int i = 1; i < argc; ++i) {
    DebugHelper::OutputDebugString(L"parameter:%d, %s", i, argv[i]);
  }
}

void ServiceWrap::Pause() {
  mRunning = false;
  ::InterlockedExchange(&mServiceStatus.dwCurrentState, SERVICE_PAUSED);
  ::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
  DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_PAUSE");
}

void ServiceWrap::Continue() {
  mRunning = true;
  DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_CONTINUE");
  ::InterlockedExchange(&mServiceStatus.dwCurrentState, SERVICE_RUNNING);
  ::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);
  while (0 == this->QueryServiceStatus()) {
    Sleep(mServiceStatus.dwWaitHint);
    if (SERVICE_RUNNING == mServiceStatus.dwCurrentState) {
      break;
    }  // if
  }

  // ¼ÌÐøÖ´ÐÐº¯Êý
  DoTask();
}

void ServiceWrap::Stop() {
  mRunning = false;
  DebugHelper::OutputDebugStringW(L"SERVICE_CONTROL_STOP");
  ::InterlockedExchange(&mServiceStatus.dwCurrentState, SERVICE_STOPPED);
  ::SetServiceStatus(mServiceStatusHandle, &mServiceStatus);

  while (0 == this->QueryServiceStatus()) {
    Sleep(mServiceStatus.dwWaitHint);
    if (SERVICE_STOPPED == mServiceStatus.dwCurrentState) {
      break;
    }  // if
  }
}

void ServiceWrap::Shutdown() { Stop(); }

void ServiceWrap::Interrogate() {}

void ServiceWrap::DoTask() {
  while (mRunning) {
    Sleep(1000 * 3);
    DebugHelper::OutputDebugString("service dotask....\r\n");
  }
}

shared_ptr<ServiceWrap> ServiceWrap::clone() {
  return enable_shared_from_this<ServiceWrap>::shared_from_this();
}

void ServiceWrap::_CopyValue(const ServiceWrap &servicewrap) {
  this->mRunning = servicewrap.mRunning;
  this->mAppAbsPath = servicewrap.mAppAbsPath;
  this->mServiceName = servicewrap.mServiceName;
  this->mServiceDesc = servicewrap.mServiceDesc;
  this->mServiceStatus = servicewrap.mServiceStatus;
  this->mServiceStatusHandle = servicewrap.mServiceStatusHandle;
}

};  // namespace XIBAO
