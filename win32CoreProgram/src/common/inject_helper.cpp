#include "stdafx.h"
#include "inject_helper.h"
#include <TlHelp32.h>

InjectHelper::InjectHelper(DWORD dwProcessID, PCWSTR pszLibFile)
  : _dwProcessId(dwProcessID), _pszLibFile(pszLibFile)
{
}

InjectHelper::~InjectHelper() {
  this->_eject();
}

bool InjectHelper::_inject() {

  bool bOk = false; // Assume that the function fails
  HANDLE hProcess = NULL, hThread = NULL;
  PWSTR pszLibFileRemote = NULL;

  __try {
    // Get a handle for the target process.
    hProcess = OpenProcess(
      PROCESS_QUERY_INFORMATION |   // Required by Alpha
      PROCESS_CREATE_THREAD |   // For CreateRemoteThread
      PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
      PROCESS_VM_WRITE,             // For WriteProcessMemory
      FALSE, _dwProcessId);
    if (hProcess == NULL) __leave;

    // Calculate the number of bytes needed for the DLL's pathname
    int cch = 1 + lstrlenW(_pszLibFile);
    int cb = cch * sizeof(wchar_t);

    // Allocate space in the remote process for the pathname
    pszLibFileRemote = (PWSTR)
      VirtualAllocEx(hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);
    if (pszLibFileRemote == NULL) __leave;

    // Copy the DLL's pathname to the remote process' address space
    if (!WriteProcessMemory(hProcess, pszLibFileRemote,
      (PVOID)_pszLibFile, cb, NULL)) __leave;

    // Get the real address of LoadLibraryW in Kernel32.dll
    PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
      GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
    if (pfnThreadRtn == NULL) __leave;

    // Create a remote thread that calls LoadLibraryW(DLLPathname)
    hThread = CreateRemoteThread(hProcess, NULL, 0,
      pfnThreadRtn, pszLibFileRemote, 0, NULL);
    if (hThread == NULL) __leave;

    // Wait for the remote thread to terminate
    WaitForSingleObject(hThread, INFINITE);

    bOk = TRUE; // Everything executed successfully
  }
  __finally { // Now, we can clean everything up

     // Free the remote memory that contained the DLL's pathname
    if (pszLibFileRemote != NULL)
      VirtualFreeEx(hProcess, pszLibFileRemote, 0, MEM_RELEASE);

    if (hThread != NULL)
      CloseHandle(hThread);

    if (hProcess != NULL)
      CloseHandle(hProcess);
  }

  return(bOk);
}

bool InjectHelper::_eject()
{
  BOOL bOk = FALSE; // Assume that the function fails
  HANDLE hthSnapshot = NULL;
  HANDLE hProcess = NULL, hThread = NULL;

  __try {
    // Grab a new snapshot of the process
    hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _dwProcessId);
    if (hthSnapshot == INVALID_HANDLE_VALUE) __leave;

    // Get the HMODULE of the desired library
    MODULEENTRY32W me = { sizeof(me) };
    BOOL bFound = FALSE;
    BOOL bMoreMods = Module32FirstW(hthSnapshot, &me);
    for (; bMoreMods; bMoreMods = Module32NextW(hthSnapshot, &me)) {
      bFound = (_wcsicmp(me.szModule, _pszLibFile) == 0) ||
        (_wcsicmp(me.szExePath, _pszLibFile) == 0);
      if (bFound) break;
    }
    if (!bFound) __leave;

    // Get a handle for the target process.
    hProcess = OpenProcess(
      PROCESS_QUERY_INFORMATION |
      PROCESS_CREATE_THREAD |
      PROCESS_VM_OPERATION,  // For CreateRemoteThread
      FALSE, _dwProcessId);
    if (hProcess == NULL) __leave;

    // Get the real address of FreeLibrary in Kernel32.dll
    PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
      GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");
    if (pfnThreadRtn == NULL) __leave;

    // Create a remote thread that calls FreeLibrary()
    hThread = CreateRemoteThread(hProcess, NULL, 0,
      pfnThreadRtn, me.modBaseAddr, 0, NULL);
    if (hThread == NULL) __leave;

    // Wait for the remote thread to terminate
    WaitForSingleObject(hThread, INFINITE);

    bOk = TRUE; // Everything executed successfully
  }
  __finally { // Now we can clean everything up

    if (hthSnapshot != NULL)
      CloseHandle(hthSnapshot);

    if (hThread != NULL)
      CloseHandle(hThread);

    if (hProcess != NULL)
      CloseHandle(hProcess);
  }

  return(bOk);
}

