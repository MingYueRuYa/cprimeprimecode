// chapter_5.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "chapter_8.h"

#define MAX_LOADSTRING 100

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

    TCHAR szBuffer[1024] = {0};
    static int cxClient, cyClient;
    static POINT apt[4];
	static HWND hwndEdit1;
	static HWND hwndEdit2;

	switch (message)
	{
	case WM_CREATE:
		hwndEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL,
								   WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|
								   ES_LEFT|ES_MULTILINE|ES_AUTOHSCROLL|
								   ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, (HMENU)1,
								   ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		hwndEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL,
								   WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|
								   ES_LEFT|ES_MULTILINE|ES_AUTOHSCROLL|
								   ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, (HMENU)2,
								   ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("清除"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 260, 80, 36,
			hWnd, (HMENU)11, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		CreateWindow(TEXT("button"), TEXT("Copy"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 300, 80, 36,
			hWnd, (HMENU)12, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		CreateWindow(TEXT("button"), TEXT("Paste"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 300, 80, 36,
			hWnd, (HMENU)13, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("Set Text"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 340, 80, 36,
			hWnd, (HMENU)14, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		CreateWindow(TEXT("button"), TEXT("Get Text"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 340, 80, 36,
			hWnd, (HMENU)15, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		break;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
		MoveWindow(hwndEdit1, 60, 60, 200, 160, TRUE);
		MoveWindow(hwndEdit2, 300, 60, 200, 160, TRUE);
        break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//
		if (wmId == 1) {
			switch (wmEvent) {
			case EN_MAXTEXT:
				break;
			case EN_ERRSPACE:
				break;
			case EN_UPDATE:
				GetWindowText(hwndEdit1, szBuffer, 1024);
				SetWindowText(hwndEdit2, szBuffer);
			}
		}

		if (wmId == 11) { // 清除
			switch (wmEvent) {
			case BN_CLICKED:
				// 清空选中的文字
				SendMessage(hwndEdit1, WM_CLEAR, 0, 0);
				break;
			case BN_SETFOCUS:
				break;
			}
		}

		if (wmId == 12) { // Copy
			switch (wmEvent) {
			case BN_CLICKED:
				// copy选中的文字
				SendMessage(hwndEdit1, WM_COPY, 0, 0);
				break;
			case BN_SETFOCUS:
				break;
			}
		}

		if (wmId == 13) { // Paste
			switch (wmEvent) {
			case BN_CLICKED:
				// paste选中的文字
				SendMessage(hwndEdit1, WM_PASTE, 0, 0);
				break;
			case BN_SETFOCUS:
				break;
			}
		}

		if (wmId == 14) { // set text
			switch (wmEvent) {
			case BN_CLICKED:
				SetWindowText(hwndEdit1, TEXT("This is a line"));
				break;
			case BN_SETFOCUS:
				break;
			}
		}

		if (wmId == 15) { // set text
			switch (wmEvent) {
			case BN_CLICKED:
				GetWindowText(hwndEdit1, szBuffer, 1024);
				SetWindowText(hwndEdit2, szBuffer);
				break;
			case BN_SETFOCUS:
				break;
			}
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
