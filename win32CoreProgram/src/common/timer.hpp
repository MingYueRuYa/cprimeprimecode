/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef timer_hpp
#define timer_hpp

#include <chrono>

using std::chrono::hours;
using std::chrono::seconds;
using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

namespace XIBAO {

/*! \brief common::stringhelper
	\author liushixiong (liushixiongcpp@163.cn)
	\version 0.01
	\description 测试代码执行的时间间隔
	\date 2018-12-18 14:59:04
*/
class Timer 
{
public:
	Timer() : mBegin(high_resolution_clock::now()) {}
	~Timer() {}
	Timer(const Timer &right) = default;
	Timer &operator=(const Timer &right) = default;

	void reset() { mBegin = high_resolution_clock::now(); }

	// 毫秒
	int64_t elapsed() const
	{
		return duration_cast<milliseconds>(
					high_resolution_clock::now()-mBegin).count();
	}

	// 微妙
	int64_t elapsed_micro() const
	{
		return duration_cast<microseconds>(
			high_resolution_clock::now()-mBegin).count();
	}

	int64_t elapsed_nano() const
	{
		return duration_cast<nanoseconds>(
			high_resolution_clock::now()-mBegin).count();
	}

	int64_t elapsed_seconds() const
	{
		return duration_cast<seconds>(
			high_resolution_clock::now()-mBegin).count();
	}

	int64_t elapsed_minutes() const
	{
		return duration_cast<seconds>(
			high_resolution_clock::now()-mBegin).count();
	}

	int64_t elapsed_hours() const
	{
		return duration_cast<hours>(
			high_resolution_clock::now()-mBegin).count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> mBegin;
};

}; // namespace XIBAO

#endif // timer_hpp
