/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef servicesmanager_h
#define servicesmanager_h

#include "singleton.h"
#include "servicewrap.h"

#include <map>
#include <string>
#include <memory>
#include <windows.h>

using std::map;
using std::wstring;
using std::shared_ptr;

namespace XIBAO {

/*! \brief common::servicesmanager
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
	\description 服务的控制，支持管理多个service状态，支持状态回调
 	\date 2018-12-3 15:24:32
 	\version 0.02
	\udpate: 导出静态函数，将静态函数注册到系统函数，通过单例找到SM
 	\date 2018-12-11 17:54:12
*/
class ServicesManager : SINGLETON_INHERIT(ServicesManager)
{
	DECLARE_PRIVATE_CONSTRUCTOR(ServicesManager, void)
	DECLARE_FRIEND_SINGLETON(ServicesManager)

public:
	typedef enum SMErrorCode{
		SM_FAILED = -100,
		SM_SERVICEWRAP_EXIST,
		SM_SERVICEWRAP_NOT_EXIST,
		SM_SERVICEMAP_EMPTY,
		//这里添加新的enum值
		SM_SUCCESS = 0,
	};

public:
	static void WINAPI _ServiceMain(
			_In_ DWORD dwArgc,
			_In_reads_(dwArgc) _Deref_pre_z_ LPTSTR* lpszArgv) throw();
	static void WINAPI _ServiceCtrlHandler(DWORD Opcode);

public:
	~ServicesManager();

public:
	// 开始
	SMErrorCode Start(const wstring &servicename);
	// 创建服务
	SMErrorCode InstallService(const wstring &wstrName);
	// 启动服务
	SMErrorCode StartService(const wstring &wstrName);
	// 关闭服务
	SMErrorCode StopService(const wstring &serviceName);
	// 中断服务
	SMErrorCode PauseService(const wstring &serviceName);
	// 恢复服务
	SMErrorCode ResumeService(const wstring &serviceName);
	// 查询服务状态
	SMErrorCode QueryServiceStatus(const wstring &serviceName);
	// service主函数
	void ServiceMain(
			_In_ DWORD dwArgc,
			_In_reads_(dwArgc) _Deref_pre_z_ LPTSTR* lpszArgv);
	void ServiceCtrlHandler(DWORD Opcode);
	SMErrorCode AddServiceWrap(shared_ptr<ServiceWrap> serviceWrap);
	SMErrorCode DeleteServiceWrap(shared_ptr<ServiceWrap> serviceWrap);
	SMErrorCode DeleteService(const wstring &wstrName);

private:
	SMErrorCode GetServiceWrap(const wstring &ServiceName, 
								shared_ptr<ServiceWrap> &serviceWrap);
	SMErrorCode _FindServiceWrap(const wstring &wstrServiceName);
	// 删除服务
	SMErrorCode _DeleteService(const wstring &wstrServiceName);

private:
	wstring	mCurServiceName;
	map<wstring, shared_ptr<ServiceWrap>> mServiceMap;

};

}

#endif // servicesmanager_h