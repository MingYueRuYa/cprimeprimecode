/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef systrayinfo_h
#define systrayinfo_h

#include <string>
#include <vector>

#include <locale.h>
#include <atlstr.h>
#include <windows.h>
#include <commctrl.h>

using std::vector;
using std::wstring;

namespace XIBAO
{
/*! \brief common::systrayinfo
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
	\description 获取系统托盘信息
 	\date 2019-3-8 15:21:42
*/
class SysTrayInfo
{
public:
	class TrayInfo
	{
	public:
		TrayInfo();	
		TrayInfo(const wstring &title, 
				 const wstring &filePath, 
				 const POINT &point);	
		TrayInfo(const TrayInfo &rhs);	
		TrayInfo& operator=(const TrayInfo &rhs);	
		TrayInfo(TrayInfo && rhs);
		~TrayInfo() = default;

		wstring GetTitle() const;
		void SetTitle(const wstring &title);

		wstring GetFilePath() const;
		void SetFilePath(const wstring &filePath);

		POINT GetPos() const;
		void SetPos(const POINT &point);

	private:
		void _CopyValue(const TrayInfo &rhs);

	private:
		wstring mTitle;
		wstring mFilePath;
		POINT mPos;

	};

public:
	SysTrayInfo();	
	SysTrayInfo(const SysTrayInfo &rhs);	
	SysTrayInfo& operator=(const SysTrayInfo &rhs);	
	SysTrayInfo(SysTrayInfo && rhs);
	~SysTrayInfo() = default;
	static vector<TrayInfo> GetTrayInfo();
	static HWND FindTrayWnd();
	static HWND FindNotifyIconOverflowWindow();
	static BOOL IsWow64();
	static bool EnumNotifyWindow(HWND hWnd, vector<TrayInfo> &vecTrayInfo);

private:
	void _CopyValue(const SysTrayInfo &rhs);

};

}

#endif // systrayinfo_h
