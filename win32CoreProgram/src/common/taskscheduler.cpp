/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "taskscheduler.h"
#include "oshelper.h"
#include "xptaskscheduler.h"
#include "win7taskscheduler.h"

#include <string>
#include <memory>

using std::to_wstring;

namespace XIBAO
{
	bool TaskScheduler::DeleteTaskScheduler(const wstring &taskName)
	{
		//TODO com初始化必须放在外面整理，原理还未知
		CoInitialize(NULL);
		bool result = false;
		wstring osname = L"";
		OSHelper::Version osversion = OSHelper::GetOSVersion(osname);
		if (OSHelper::VERSION_XP >= osversion) {
			for (int i = 0; i<10; ++i) {
				wstring taskname = taskName + L"_" + to_wstring(i);
				result = XPTaskScheduler::DeleteTaskForXP(taskname.c_str());
				if (!result) { return false; }
			}
		}
		else if (OSHelper::VERSION_WIN7 <= osversion) {
			result = Win7TaskScheduler::Delete2MoreWin7(taskName);
		}
		CoUninitialize();
		return result;
	}

TaskScheduler::TaskScheduler()
	:	mAppPath(L""),
		mTaskName(L""),
		mTaskDescription(L""),
		mAppWorkDir(L""),
		mParameter(L""),
		mVecTime({})
{
}

TaskScheduler::TaskScheduler(const wstring &appPath, 
					const wstring &taskName,
					const wstring &taskDescription, 
					const wstring &workDir,
					const wstring &parameter, 
					const vector<pair<int, int>> vecTime,
					int taskmode)
					:	mAppPath(appPath),
						mTaskName(taskName),
						mTaskDescription(taskDescription),
						mAppWorkDir(workDir),
						mParameter(parameter),
						mVecTime(vecTime),
						mode(taskmode)
{
}

TaskScheduler::TaskScheduler(const TaskScheduler &rhs)
{
	_CopyValue(rhs);
}

TaskScheduler& TaskScheduler::operator= (const TaskScheduler &rhs)
{
	if (this == &rhs)  { return *this; }

	_CopyValue(rhs);

	return *this;
}

TaskScheduler::TaskScheduler(TaskScheduler &&rhs)
{
	_CopyValue(rhs);
}

TaskScheduler::~TaskScheduler()
{
}

HRESULT TaskScheduler::CreateTaskScheduler()
{
	bool result = false;
	wstring osname = L"";
	OSHelper::Version osversion = OSHelper::GetOSVersion(osname);
	if (OSHelper::VERSION_XP >= osversion) {
		for(int i = 0; i < mVecTime.size(); ++i) {
			wstring taskname = mTaskName + L"_" + to_wstring(i);
			result = XPTaskScheduler::CreateTaskForXP(taskname.c_str(),
													  mAppPath.c_str(),
													  mAppWorkDir.c_str(),
													  mTaskDescription.c_str(),
													  mParameter.c_str(),
													  mVecTime[i].first, 
													  mVecTime[i].second);
			if (! result) { return false; }
		}
	} else if (OSHelper::VERSION_WIN7 <=  osversion) {
		result = Win7TaskScheduler::Create2MoreWin7(mAppPath,
													mTaskName,
													mTaskDescription,
													mAppWorkDir, 
													mParameter, 
													mVecTime,
													mUserName,
													mPassword,
													mode);
	}

	return result;
}

bool TaskScheduler::DeleteTaskScheduler()
{
	////TODO com初始化必须放在外面整理，原理还未知
	//CoInitialize(NULL);
	//bool result = false;
	//wstring osname = L"";
	//OSHelper::Version osversion = OSHelper::GetOSVersion(osname);
	//if (OSHelper::VERSION_XP >= osversion) {
	//	for (int i = 0; i<10; ++i) {
	//		wstring taskname = mTaskName + L"_" + to_wstring(i);
	//		result = XPTaskScheduler::DeleteTaskForXP(taskname.c_str());
	//		if (!result) { return false; }
	//	}
	//} else if (OSHelper::VERSION_WIN7 <=  osversion) {
	//	result = Win7TaskScheduler::Delete2MoreWin7(mTaskName);
	//}
	//CoUninitialize();
	//return result;

	return TaskScheduler::DeleteTaskScheduler(this->mTaskName);
}

void TaskScheduler::SetAppPath(const wstring &appPath)
{
	 mAppPath = appPath;
}

wstring TaskScheduler::GetAppPath()
{
	return mAppPath;
}

void TaskScheduler::SetTaskName(const wstring &taskName)
{
	mTaskName = taskName;
}

wstring TaskScheduler::GetTaskName()
{
	return mTaskName;
}

void TaskScheduler::SetTaskDescription(const wstring &taskDescription)
{
	mTaskDescription = taskDescription;
}

wstring TaskScheduler::GetTaskDescription()
{
	return mTaskDescription;
}

void TaskScheduler::SetWorkDir(const wstring &workDir)
{
	mAppWorkDir = workDir;
}

wstring TaskScheduler::GetWorkDir()
{
	return mAppWorkDir;
}

void TaskScheduler::SetParameter(const wstring &parameter)
{
	mParameter = parameter;
}

wstring TaskScheduler::GetParameter()
{
	return mParameter;
}

void TaskScheduler::SetTimeVec(const vector<pair<int, int>> &vecTime)
{
	mVecTime = vecTime;
}

vector<pair<int, int>> TaskScheduler::GetTimeVec()
{
	return mVecTime;
}

void TaskScheduler::SetName(const wstring &userName)
{
	this->mUserName = userName;
}

wstring TaskScheduler::GetName()
{
	return this->mUserName;
}

void TaskScheduler::SetPasswd(const wstring& passwd)
{
	this->mPassword = passwd;
}

wstring TaskScheduler::GetPasswd()
{
	return this->mPassword;
}

void TaskScheduler::SetTaskMode(int mode)
{
  this->mode = mode;
}

int TaskScheduler::GetTaskMode() const
{
  return this->mode;
}

void TaskScheduler::_CopyValue(const TaskScheduler &rhs)
{
	mVecTime			= rhs.mVecTime;
	mAppPath			= rhs.mAppPath;
	mTaskName			= rhs.mTaskName;
	mParameter			= rhs.mParameter;
	mAppWorkDir			= rhs.mAppWorkDir;
	mTaskDescription	= rhs.mTaskDescription;
}

};