// chapter_5.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "chapter_6.h"

#define MAX_LOADSTRING 100
#define MAX_MSG 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CHAPTER_5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHAPTER_5));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHAPTER_5));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CHAPTER_5);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

    TEXTMETRIC tm;
    static int cxClient, cyClient;
    static int cxChar, cyChar;
    static int count;
    static PMSG pmsg;

    static TCHAR szTop[] = TEXT("Message        Key       Char     Repeat Scan Ext ALT Prev Tran");
    static TCHAR szUnd[] = TEXT("_______        ___       ___      ______ ____ ___ ___ ____ ____");

    static TCHAR *szMessage[] = {
        TEXT("WM_KEYDOWN"),
        TEXT("WM_KEYUP"),
        TEXT("WM_CHAR"),
        TEXT("WM_DEADCHAR"),
        TEXT("WM_SYSKEYDOWN"),
        TEXT("WM_SYSCHAR"),
        TEXT("WM_SYSDEADCHAR")
    };

	static TCHAR *szYes = TEXT("Yes");
	static TCHAR *szNo	= TEXT("No");
	static TCHAR *szDown	= TEXT("Down"); 
	static TCHAR *szUp		= TEXT("Up"); 

    TCHAR  szBuffer[128], szKeyName[32];
    int iType;

    static TCHAR *szFormat[2] = {
        TEXT("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
        TEXT("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s")
    };

	switch (message)
	{
    case WM_CREATE:
        count = 0;
        hdc = GetDC(hWnd);
        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cyChar = tm.tmHeight;
        ReleaseDC(hWnd, hdc);
        if (pmsg) { free(pmsg); }

        pmsg = (PMSG)malloc(sizeof(MSG)*MAX_MSG);
        break;
    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_KEYUP:
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
		for (int i = min(count, MAX_MSG); i > 0; i--) {
			pmsg[i] = pmsg[i-1];
		}

		pmsg[0].hwnd	= hWnd;
		pmsg[0].message = message;
		pmsg[0].wParam	= wParam;
		pmsg[0].lParam	= lParam;

		count++;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
    {
		hdc = BeginPaint(hWnd, &ps);
        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, 0, 0, szTop, lstrlen(szTop));
        TextOut(hdc, 0, 0, szUnd, lstrlen(szUnd));

        for (int i=0; i<min(MAX_MSG,count); ++i) {
            iType = pmsg[i].message == WM_CHAR || 
                    pmsg[i].message == WM_SYSCHAR ||
                    pmsg[i].message == WM_DEADCHAR ||
                    pmsg[i].message == WM_SYSDEADCHAR;

            GetKeyNameText(pmsg[i].lParam, szKeyName, 
                           sizeof(szKeyName)/sizeof(TCHAR));

            TextOut(hdc, 0, (i+1)*cyChar, szBuffer,
                    wsprintf(szBuffer, szFormat[iType], 
                             szMessage[pmsg[i].message-WM_KEYFIRST],
                             pmsg[i].wParam, 
                             (PSTR)(iType ? TEXT("") : szKeyName),
                             (TCHAR)(iType ? pmsg[i].wParam : ' '),
							 LOWORD(pmsg[i].lParam),
							 HIWORD(pmsg[i].lParam) & 0x00ff,
							 0x01000000 & pmsg[i].lParam ? szYes : szNo,
							 0x20000000 & pmsg[i].lParam ? szYes : szNo,
							 0x40000000 & pmsg[i].lParam ? szYes : szNo,
							 0x80000000 & pmsg[i].lParam ? szYes : szNo
                             )
                    );

        }

		EndPaint(hWnd, &ps);
    }
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		// 释放内存导致异常
        // free(pmsg);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
