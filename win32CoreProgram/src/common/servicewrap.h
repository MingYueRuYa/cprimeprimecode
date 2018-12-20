/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef servicewrap_h
#define servicewrap_h

#include <string>
#include <windows.h>

using std::wstring;

namespace XIBAO {

/*! \brief common::servicewrap
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
	\description 对服务状态的包装
 	\date 2018-12-4 15:00:09
*/
class ServiceWrap
{
public:
	explicit ServiceWrap(const wstring &wstrName, 
							const wstring &wstrAppAbsPath,
							const wstring &wstrDesc,
							bool running = true);
	ServiceWrap &operator=(const ServiceWrap &servicewrap);
	bool operator==(const ServiceWrap &servicewrap);
	ServiceWrap(const ServiceWrap &servicewrap);
	virtual ~ServiceWrap();
	
	void SetServiceStatusHandle(const SERVICE_STATUS_HANDLE &handle);
	SERVICE_STATUS_HANDLE GetServiceStatusHandle() const;

	void SetServiceName(const wstring &wstrServiceName);
	wstring GetServiceName() const;
	
	void SetAppAbsPath(const wstring &wstrAppAbsPath);
	wstring GetAppAbsPath() const;

	void SetStop(bool stop);
	bool GetStop() const;

	void SetServiceDesc(const wstring &serviceDesc);
	wstring GetServiceDesc();

	void ServiceMain(DWORD argc, LPTSTR *argv);
	void ServiceCtrlHandler(DWORD Opcode);  
	DWORD QueryServiceStatus();
	void SetRegInfo();
	void DelRegInfo();

	virtual void Pause();
	virtual void Continue();
	virtual void Stop();
	virtual void Shutdown();
	virtual void Interrogate();
	virtual void DoTask();

public:
	SERVICE_STATUS mServiceStatus;

protected:
	void _CopyValue(const ServiceWrap &servicewrap);

protected:
	bool	mStopped;
	wstring mAppAbsPath;
	wstring mServiceName;
	wstring mServiceDesc;
	SERVICE_STATUS_HANDLE mServiceStatusHandle;
};

}

#endif // servicewrap_h