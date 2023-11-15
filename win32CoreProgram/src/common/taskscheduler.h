/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef xibao_taskscheduler_h
#define xibao_taskscheduler_h

#include <assert.h>

#include <string>
#include <vector>
#include <utility>

using std::pair;
using std::vector;
using std::wstring;

namespace XIBAO
{

/*! \brief common::taskscheduler
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
 	\date 2019-2-25 16:12:04
	\description 创建计划任务
*/
class TaskScheduler{
public:
	static bool DeleteTaskScheduler(const wstring &taskName);

public:
	explicit TaskScheduler();
	TaskScheduler(const wstring &appPath, const wstring &taskName,
					const wstring &taskDescription, const wstring &workDir,
					const wstring &parameter, 
					const vector<pair<int, int>> vecTime);
	TaskScheduler(const TaskScheduler &rhs);
	TaskScheduler& operator= (const TaskScheduler &rhs);
	TaskScheduler(TaskScheduler &&rhs);
	~TaskScheduler();

	bool CreateTaskScheduler();
	bool DeleteTaskScheduler();

	void SetAppPath(const wstring &appPath);
	wstring GetAppPath();

	void SetTaskName(const wstring &taskName);
	wstring GetTaskName();

	void SetTaskDescription(const wstring &taskDescription);
	wstring GetTaskDescription();

	void SetWorkDir(const wstring &workDir);
	wstring GetWorkDir();

	void SetParameter(const wstring &parameter);
	wstring GetParameter();

	void SetTimeVec(const vector<pair<int, int>> &vecTime);
	vector<pair<int, int>> GetTimeVec();

private:
	void _CopyValue(const TaskScheduler &rhs);

private:
	wstring mAppPath;
	wstring mTaskName;
	wstring mTaskDescription;
	wstring mAppWorkDir;
	wstring mParameter;
	vector<pair<int, int>> mVecTime;

};

};

#endif // xibao_taskscheduler_h