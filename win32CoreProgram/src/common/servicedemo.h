/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef xibao_servicedemo_h
#define xibao_servicedemo_h

#include <memory>

#include "servicewrap.h"

using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::enable_shared_from_this;

namespace XIBAO {

class ServiceWrapEx : public ServiceWrap
{
public:
	ServiceWrapEx(const wstring &wstrName, 
							const wstring &wstrAppAbsPath,
							const wstring &wstrDesc,
							bool running = true)
					: ServiceWrap(wstrName, wstrAppAbsPath,
									wstrDesc, running)
	{}

	virtual void DoTask() override
	{
		while (mStopped) {
			Sleep(3000);
#ifdef XIBAO_DEBUG_HELPER
			DebugHelper::OutputDebugStringW(L"liushixiong");
#endif // XIBAO_DEBUG_HELPER
		}
	}

	virtual std::shared_ptr<ServiceWrap> clone() override
	{
		return dynamic_pointer_cast<ServiceWrapEx>\
			(enable_shared_from_this<ServiceWrap>::shared_from_this());
	}

};

} // XIBAO

#endif // xibao_servicedemo_h