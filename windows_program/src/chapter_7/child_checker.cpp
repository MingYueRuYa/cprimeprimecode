// chapter_5.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "chapter_7.h"

#define MAX_LOADSTRING 100
int idFocus = 0;

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
TCHAR szChildClass[MAX_LOADSTRING] = TEXT("childclass");    // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM                MyChildRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ChildWndProc(HWND, UINT, WPARAM, LPARAM);
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
	MyChildRegisterClass(hInstance);

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

ATOM MyChildRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = ChildWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(long);
    wcex.hInstance  = hInstance;
    wcex.hIcon      = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHAPTER_5));
    wcex.hCursor    = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;//MAKEINTRESOURCE(IDC_CHAPTER_5);
    wcex.lpszClassName  = szChildClass;
    wcex.hIconSm        = NULL; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
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

const int DIVISIONS_WIDTH   = 5;
const int DIVISIONS_HEIGHT  = 5;

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    switch (message) {
    case WM_CREATE:
        SetWindowLong(hWnd, 0, 0);
        break;
    case WM_KEYDOWN:
        if (wParam != VK_RETURN && wParam != VK_SPACE) {
            SendMessage(GetParent(hWnd), message, wParam, lParam);
            return 0;
        }
        // 直落
    case WM_LBUTTONDOWN:
        SetWindowLong(hWnd, 0, 1 ^ GetWindowLong(hWnd, 0));
        SetFocus(hWnd);
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_SETFOCUS:
        idFocus = GetWindowLong(hWnd, GWL_ID);
    case WM_KILLFOCUS:
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        
        GetClientRect(hWnd, &rect);
        Rectangle(hdc, 0, 0, rect.right, rect.bottom);

        if (GetWindowLong(hWnd, 0)) {
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, rect.right, rect.bottom);
            MoveToEx(hdc, 0, rect.bottom, NULL);
            LineTo(hdc, rect.right, 0);
        }

        if (hWnd == GetFocus()) {
            rect.left   += rect.right/10;
            rect.top    += rect.bottom/10;
            rect.right  -= rect.left;
            rect.bottom -= rect.top;

            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            SelectObject(hdc, CreatePen(PS_DASH, 0, 0));
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
        }

        EndPaint(hWnd, &ps);
        break;
    default:    
        break;
    } 

    return DefWindowProc(hWnd, message, wParam, lParam);
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
    static BOOL fState[DIVISIONS_WIDTH][DIVISIONS_HEIGHT];
    static int cxBlock, cyBlock;
    static HWND hwndChild[DIVISIONS_WIDTH][DIVISIONS_HEIGHT];
    int x, y;
    RECT rect;

    TCHAR szBuffer[1024] = {0};
    static int cxClient, cyClient;
    static POINT apt[4];

	switch (message)
	{
    case WM_CREATE: //创建主窗口
        // 创建25个子窗口
        for (x=0; x<DIVISIONS_WIDTH; ++x) {
            for (y=0; y<DIVISIONS_HEIGHT; ++y) {
                 hwndChild[x][y] = CreateWindow(szChildClass, NULL, 
                                            WS_CHILDWINDOW | WS_VISIBLE,
                                            0, 0, 0, 0, hWnd, (HMENU)(y<<8|x), 
                                            hInst, NULL);
            }
        }
        SetFocus(hwndChild[0][0]);
        break;
    case WM_SIZE:
        cxBlock = LOWORD(lParam)/DIVISIONS_WIDTH;
        cyBlock = HIWORD(lParam)/DIVISIONS_HEIGHT;
        for (x=0; x<DIVISIONS_WIDTH; ++x) {
            for (y=0; y<DIVISIONS_HEIGHT; ++y) {
                ::MoveWindow(hwndChild[x][y], x*cxBlock, y*cyBlock, 
                             cxBlock, cyBlock, TRUE);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        /*
        x = LOWORD(lParam)/cxBlock;
        y = HIWORD(lParam)/cyBlock;

        if (x < DIVISIONS_WIDTH && y < DIVISIONS_HEIGHT) {
            fState[x][y] ^= 1;
            rect.left   = x * cxBlock;
            rect.top    = y * cyBlock;
            rect.right  = (x+1)*cxBlock;
            rect.bottom = (y+1)*cyBlock;
            InvalidateRect(hWnd, &rect, FALSE);
        }
        */
        break;
    case WM_SETFOCUS:
        // SetFocus(GetDlgItem(hWnd, idFocus));
        break;
    case WM_KEYDOWN:
        x = idFocus & 0xFF;
        y = idFocus >> 8;
        switch (wParam) {
        case VK_UP:     y--;        break; 
        case VK_DOWN:   y++;        break;
        case VK_LEFT:   x--;        break;
        case VK_RIGHT:  x++;        break;
        case VK_HOME:   x = y = 0;  break;
        case VK_END:    x=DIVISIONS_WIDTH-1; y=DIVISIONS_HEIGHT-1; break;
        default:
            return 0;
        }

        x = (x+DIVISIONS_WIDTH)%DIVISIONS_WIDTH;
        y = (y+DIVISIONS_HEIGHT)%DIVISIONS_HEIGHT;
        
        idFocus = y << 8 | x;
        SetFocus(GetDlgItem(hWnd, idFocus));

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

        /*
        for (int x=0; x<DIVISIONS_WIDTH; x++) {
            for (int y=0; y<DIVISIONS_HEIGHT; y++) {
                Rectangle(hdc, x*cxBlock, y*cyBlock, 
                          (x+1)*cxBlock, (y+1)*cyBlock);

                if (fState[x][y]) {
                    MoveToEx(hdc, x*cxBlock, y*cyBlock, NULL);
                    LineTo(hdc, (x+1)*cxBlock, (y+1)*cyBlock);
                    MoveToEx(hdc, x*cxBlock, (y+1)*cyBlock, NULL);
                    LineTo(hdc, (x+1)*cxBlock, y*cyBlock);
                }
            }
        }
        */

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
