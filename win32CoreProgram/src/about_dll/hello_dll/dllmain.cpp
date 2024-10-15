// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <thread>
#include <string>
#include <sstream>

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  std::stringstream ss;
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    OutputDebugStringW(L"process attach");
    break;
  case DLL_THREAD_ATTACH:
    ss << "thread attach" << " id:" << std::this_thread::get_id();
    OutputDebugStringA(ss.str().c_str());
    //OutputDebugStringA("thread attach");
    break;
  case DLL_THREAD_DETACH:
    ss << "thread detach" << " id:" << std::this_thread::get_id();
    OutputDebugStringA(ss.str().c_str());
    //OutputDebugStringA("thread detach");
    break;
  case DLL_PROCESS_DETACH:
    OutputDebugStringW(L"process detach");
    break;
  }
  return TRUE;
}

