/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "systrayinfo.h"

namespace XIBAO
{

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

SysTrayInfo::SysTrayInfo()
{}

SysTrayInfo::SysTrayInfo(const SysTrayInfo &rhs)
{
	_CopyValue(rhs);
}

SysTrayInfo& SysTrayInfo::operator=(const SysTrayInfo &rhs)
{
	if (this == &rhs) { return *this; }
	_CopyValue(rhs);
	return *this;
}

SysTrayInfo::SysTrayInfo(SysTrayInfo && rhs)
{
	_CopyValue(rhs);
}

vector<SysTrayInfo::TrayInfo> SysTrayInfo::GetTrayInfo()
{
	// 转换本地格式，可能会乱码
	setlocale(LC_ALL, "chs");

	vector<TrayInfo> vecTrayInfo{};
	EnumNotifyWindow(FindTrayWnd(), vecTrayInfo);
	EnumNotifyWindow(FindNotifyIconOverflowWindow(), vecTrayInfo);

	return vecTrayInfo;
}

HWND SysTrayInfo::FindTrayWnd()
{
	HWND hWnd = NULL;
 
	hWnd = FindWindow(_T("Shell_TrayWnd"), NULL);
	hWnd = FindWindowEx(hWnd, NULL, _T("TrayNotifyWnd"), NULL);
	hWnd = FindWindowEx(hWnd, NULL, _T("SysPager"), NULL);
	hWnd = FindWindowEx(hWnd, NULL, _T("ToolbarWindow32"), NULL);
 
	return hWnd;
}
 
HWND SysTrayInfo::FindNotifyIconOverflowWindow()
{
	HWND hWnd = NULL;
 
	hWnd = FindWindow(_T("NotifyIconOverflowWindow"), NULL);
	hWnd = FindWindowEx(hWnd, NULL, _T("ToolbarWindow32"), NULL);
 
	return hWnd;
}

BOOL SysTrayInfo::IsWow64()
{
	BOOL bIsWow64 = FALSE;
 
	LPFN_ISWOW64PROCESS 
		fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(_T("kernel32")),"IsWow64Process");
 
	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			// handle error
		}
	}
	return bIsWow64;
}

bool SysTrayInfo::EnumNotifyWindow(HWND hWnd, vector<TrayInfo> &vecTrayInfo)
{
	DWORD dwProcessId = 0;
	GetWindowThreadProcessId(hWnd,&dwProcessId);
 
	HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | 
									PROCESS_VM_READ | PROCESS_VM_WRITE, 
									FALSE, dwProcessId);
	if (hProcess == NULL){
		return false;
	}

	LPVOID pBun = VirtualAllocEx(hProcess, 0, sizeof(RECT), 
									MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	LPVOID lAddress = VirtualAllocEx(hProcess, 0, 4096, 
									 MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (lAddress == NULL){
		return false;
	}

	DWORD lTextAdr	= 0;
	BYTE buff[1024] = {0};
	TCHAR ptb[256]	= {0};
	CString strFilePath;
	CString strTile;

	HWND hMainWnd = NULL;
	int nDataOffset = sizeof(TBBUTTON) - sizeof(INT_PTR) - sizeof(DWORD_PTR);
	int nStrOffset	= 18; 
	if (IsWow64()){
		nDataOffset += 4;
		nStrOffset += 6;
	}

	RECT rccc;
	GetWindowRect(hWnd,&rccc);
 
	//获取图标个数
	int lButton = SendMessage(hWnd, TB_BUTTONCOUNT, 0, 0);
	for (int i = 0; i < lButton; i++) {
		SendMessage(hWnd, TB_GETITEMRECT, i, (LPARAM)pBun);
		SendMessage(hWnd, TB_GETBUTTON, i, (LPARAM)lAddress);
		//读坐标
		ReadProcessMemory(hProcess, pBun, (LPVOID)ptb, sizeof(RECT), 0);
		//读文本地址
		ReadProcessMemory(hProcess, (LPVOID)((DWORD)lAddress + nDataOffset), &lTextAdr, 4, 0);
		if ( lTextAdr!=-1 ) {
			//读文本
			ReadProcessMemory(hProcess, (LPCVOID)lTextAdr, buff, 1024, 0);
			hMainWnd = (HWND)(*((DWORD*)buff));
			strFilePath = (WCHAR *)buff + nStrOffset;
			strTile = (WCHAR *)buff + nStrOffset + MAX_PATH;
			//_tprintf(_T("%s %s\n"),strTile,strFilePath);
		}
		LPRECT pRect = (LPRECT)ptb;
		OffsetRect(pRect,rccc.left,rccc.top);
//		_tprintf(_T("X:%d Y:%d "), pRect->right, pRect->bottom);
//		_tprintf(_T("%s %s\n"),strTile,strFilePath);
		wstring temptitle	= strTile;
		wstring filepath	= strFilePath;	
//		_tprintf(_T("X:%d Y:%d "), pRect->right, pRect->bottom);
//		_tprintf(_T("%s %s\n"),strTile,strFilePath);

		POINT point;
		point.x = pRect->right;
		point.y = pRect->bottom;
		vecTrayInfo.emplace_back(temptitle, filepath, point);
	}
	VirtualFreeEx(hProcess, pBun, 4096, MEM_DECOMMIT);
	VirtualFreeEx(hProcess, lAddress, 4096, MEM_RELEASE);
	CloseHandle(hProcess);
	return true;
}

void SysTrayInfo::_CopyValue(const SysTrayInfo &rhs)
{
}

SysTrayInfo::TrayInfo::TrayInfo()
	: mTitle(L""),
	  mFilePath(L""),
	  mPos()
{}

SysTrayInfo::TrayInfo::TrayInfo(const wstring &title, 
				 const wstring &filePath, 
				 const POINT &point)
				 :  mTitle(title),
					mFilePath(filePath),
					mPos(point)
{}

SysTrayInfo::TrayInfo::TrayInfo(const SysTrayInfo::TrayInfo &rhs)
{
	_CopyValue(rhs);
}

SysTrayInfo::TrayInfo& SysTrayInfo::TrayInfo::operator=(
	const SysTrayInfo::TrayInfo &rhs)
{
	if (this == &rhs) { return *this; }
	_CopyValue(rhs);
	return *this;
}

SysTrayInfo::TrayInfo::TrayInfo(SysTrayInfo::TrayInfo && rhs)
{
	_CopyValue(rhs);
}

wstring SysTrayInfo::TrayInfo::GetTitle() const
{
	return mTitle;
}

void SysTrayInfo::TrayInfo::SetTitle(const wstring &title)
{
	mTitle = title;	
}

wstring SysTrayInfo::TrayInfo::GetFilePath() const
{
	return mFilePath;
}
void SysTrayInfo::TrayInfo::SetFilePath(const wstring &filePath)
{
	mFilePath = filePath;
}

POINT SysTrayInfo::TrayInfo::GetPos() const
{
	return mPos;
}

void SysTrayInfo::TrayInfo::SetPos(const POINT &point)
{
	mPos = point;
}

void SysTrayInfo::TrayInfo::_CopyValue(const SysTrayInfo::TrayInfo &rhs)
{
	mPos		= rhs.mPos;
	mTitle		= rhs.mTitle;
	mFilePath	= rhs.mFilePath;
}

}