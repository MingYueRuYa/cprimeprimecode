#pragma once

#define EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


  EXPORT int __cdecl CreateTaskScheduler(const wchar_t *appPath,
							const wchar_t *taskName,
							const wchar_t *taskDescription,
							const wchar_t *appWorkDir,
							const wchar_t *parameter,
							const wchar_t *userName,
							const wchar_t *passwd,
              int hour,
              int mins,
							int mode);
  EXPORT int __cdecl StartTaskScheduler(wchar_t *app_name);
  EXPORT int __cdecl DeleteTaskScheduler(wchar_t *app_name);


#ifdef __cplusplus
}
#endif // __cplusplus
