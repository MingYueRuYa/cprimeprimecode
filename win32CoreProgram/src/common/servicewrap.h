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
							bool running = true);
	ServiceWrap &operator=(const ServiceWrap &servicewrap);
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

	virtual void ServiceMain(DWORD argc, LPTSTR *argv);
	virtual void ServiceCtrlHandler(DWORD Opcode);  
	virtual void DoTask();

public:
	SERVICE_STATUS mServiceStatus;

private:
	void _CopyValue(const ServiceWrap &servicewrap);

protected:
	SERVICE_STATUS_HANDLE mServiceStatusHandle;
	wstring mServiceName;
	wstring mAppAbsPath;
	bool	mStopped;
};

}

#endif // servicewrap_h