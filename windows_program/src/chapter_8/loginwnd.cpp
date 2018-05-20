// chapter_5.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "chapter_8.h"

#define MAX_LOADSTRING 100

#define ID_USERNAME_EDIT	1
#define ID_PASSWORD_EDIT	2
#define ID_USERNAME_LABEL	3
#define ID_PASSWORD_LABEL	4
#define ID_LOGIN_BUTTON		5
#define ID_CANCEL_BUTTON	6

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
      CW_USEDEFAULT, 0, 420, 220, NULL, NULL, hInstance, NULL);

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

    TCHAR szBuffer[1024] = {0};
    static int cxClient, cyClient;
    static POINT apt[4];

	static HWND hwndUserNameEdit;
	static HWND hwndPasswdEdit;
	static HWND hwndUserNameLabel;
	static HWND hwndPasswdLabel;
	static HWND hwndLoginButton;
	static HWND hwndCancelButton;
	static int cxChar, cyChar;


	switch (message)
	{
	case WM_CREATE:
	hwndUserNameLabel = CreateWindow(TEXT("static"), TEXT("请输入用户名："),
									WS_CHILD|WS_VISIBLE|SS_LEFT, 0, 0, 0, 0,
									hWnd, (HMENU)ID_USERNAME_LABEL, 
									((LPCREATESTRUCT)lParam)->hInstance, NULL);
	hwndUserNameEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL,
									WS_CHILD|WS_VISIBLE|SS_LEFT, 0, 0, 0, 0,
									hWnd, (HMENU)ID_USERNAME_EDIT, 
									((LPCREATESTRUCT)lParam)->hInstance, NULL);
	hwndPasswdLabel = CreateWindow(TEXT("static"), TEXT("请输入密码："),
									WS_CHILD|WS_VISIBLE|SS_LEFT, 0, 0, 0, 0,
									hWnd, (HMENU)ID_PASSWORD_LABEL, 
									((LPCREATESTRUCT)lParam)->hInstance, NULL);
	hwndPasswdEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL,
									WS_CHILD | WS_VISIBLE | 
									SS_LEFT | ES_PASSWORD, 
									0, 0, 0, 0,
									hWnd, (HMENU)ID_PASSWORD_EDIT, 
									((LPCREATESTRUCT)lParam)->hInstance, NULL);

	hwndLoginButton = CreateWindow(TEXT("button"), TEXT("登陆"),
								WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 0, 0, 0, 0,
								hWnd, (HMENU)ID_LOGIN_BUTTON, 
								((LPCREATESTRUCT)lParam)->hInstance, NULL);

	hwndCancelButton = CreateWindow(TEXT("button"), TEXT("取消"),
								WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 0, 0, 0, 0,
								hWnd, (HMENU)ID_CANCEL_BUTTON, 
								((LPCREATESTRUCT)lParam)->hInstance, NULL);

	cxChar = HIWORD(GetDialogBaseUnits());
	cyChar = LOWORD(GetDialogBaseUnits());
		break;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
	
		MoveWindow(hwndUserNameLabel, 3*cxChar, 3*cyChar, 
				   20*cxChar, 3*cyChar, TRUE);

		MoveWindow(hwndUserNameEdit, 3*cxChar, 6*cyChar, 
				   20*cxChar, 3*cyChar, TRUE);

		MoveWindow(hwndPasswdLabel, 3*cxChar, 9*cyChar, 
				   20*cxChar, 3*cyChar, TRUE);
		MoveWindow(hwndPasswdEdit, 3*cxChar, 12*cyChar, 
				   20*cxChar, 3*cyChar, TRUE);

		MoveWindow(hwndLoginButton, 3*cxChar, 16*cyChar, 
				   6*cxChar, 3*cyChar, TRUE);
		MoveWindow(hwndCancelButton, 10*cxChar, 16*cyChar, 
				   6*cxChar, 3*cyChar, TRUE);


		return 0;
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

		EndPaint(hWnd, &ps);
    }
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
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
