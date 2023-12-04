#pragma once

#define EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


  EXPORT void __cdecl CreateTaskScheduler();
  EXPORT void __cdecl DeleteTaskScheduler(wchar_t *app_name);
  EXPORT void __cdecl StartTaskScheduler(wchar_t *app_name);


#ifdef __cplusplus
}
#endif // __cplusplus
