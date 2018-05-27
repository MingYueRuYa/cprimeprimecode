// chapter_5.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "clipborad.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

TCHAR szDefaultText[] = TEXT("Default Text");

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

#ifdef UNICODE
#define CF_TCHAR CF_UNICODETEXT
#else
#define CF_TCHAR CF_TEXT
#endif //UNICODE

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
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MENU);// MAKEINTRESOURCE(IDC_CHAPTER_5);
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
	RECT rect;
	LPWSTR pGlobal;

    TCHAR szBuffer[1024] = {0};
    static int cxClient, cyClient;

	static LPWSTR pText;
	BOOL bEnable;
	HGLOBAL hGlobal;

	switch (message)
	{
	case WM_CREATE:
		SendMessage(hWnd, WM_COMMAND, ID_EDIT_RESET, 0);
		break;
	case WM_INITMENUPOPUP:
		EnableMenuItem((HMENU)wParam, ID_EDIT_PASTE, 
						IsClipboardFormatAvailable(CF_TCHAR) ? 
						MF_ENABLED : MF_GRAYED);
		bEnable = pText ? MF_ENABLED : MF_GRAYED;

		EnableMenuItem((HMENU)wParam, ID_EDIT_CUT, bEnable);
		EnableMenuItem((HMENU)wParam, ID_EDIT_COPY, bEnable);
		EnableMenuItem((HMENU)wParam, ID_EDIT_DELETE, bEnable);

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
		case ID_EDIT_PASTE:
			OpenClipboard(hWnd);
			if ((hGlobal = GetClipboardData(CF_TCHAR))) {
				pGlobal = (LPWSTR)GlobalLock(hGlobal);
				if (pText) {
					free(pText);
					pText = NULL;
				}
				pText = (LPWSTR)malloc(GlobalSize(hGlobal));
				lstrcpy(pText, pGlobal);
				GlobalUnlock(hGlobal);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			CloseClipboard();
			break;
		case ID_EDIT_CUT:
		case ID_EDIT_COPY:
			if (!pText) {
				return 0;
			}
			hGlobal = GlobalAlloc(GHND | GMEM_SHARE, 
									(lstrlen(pText)+1)*sizeof(TCHAR));
			
			pGlobal = (LPWSTR)GlobalLock(hGlobal);
			lstrcpy(pGlobal, pText);

			OpenClipboard(hWnd);
			EmptyClipboard();
			SetClipboardData(CF_TCHAR, hGlobal);
			CloseClipboard();
			if (LOWORD(wParam) == ID_EDIT_COPY) {
				return 0;
			}
			break;
		case ID_EDIT_DELETE:
			if (pText) {
				free(pText);
				pText = NULL;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_EDIT_RESET:
			if (pText) {
				free(pText);
				pText = NULL;
			}
			pText = (LPWSTR)malloc((lstrlen(szDefaultText)+1)*sizeof TCHAR);
			lstrcpy(pText, szDefaultText);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
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
		GetClientRect(hWnd, &rect);
		if (NULL != pText) {
			DrawText(hdc, pText, -1, &rect, DT_EXPANDTABS | DT_WORDBREAK);
		}
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
