#include <windows.h>
#include <tchar.h>

// 窗口过程回调函数
LRESULT CALLBACK WndProc(HWND hHwnd, 
						 UINT message,
						 WPARAM wParam,
						 LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPreInstance,
                   LPTSTR szlpCmdLine,
                   int nShowCmd)
{
    HWND hwnd; //窗口句柄
    MSG msg;    //消息
    WNDCLASS wc;    // 窗口类

    //1.设计一个窗口类
    wc.style = 0;
    wc.lpfnWndProc  = (WNDPROC)WndProc;
    wc.cbClsExtra   = 0;
    wc.cbWndExtra   = 0;
    wc.hInstance    = hInstance;
    wc.hIcon        = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor      = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = _T("MyWndClass");

    // 2.注册窗口类
    RegisterClass(&wc);

    // 3.创建窗口
    hwnd = CreateWindow(_T("MyWndClass"),
                        _T("Hello SDK Application"), 
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL, 
                        NULL,
                        hInstance,
                        NULL);

    // 4.显示和更新窗口
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // 5.进入消息循环
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  //转发到窗口过程
    }    

    return 0;
}

LRESULT CALLBACK WndProc(HWND hHwnd,
                         UINT message, 
                         WPARAM wParam, 
                         LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    switch (message) {

    case WM_PAINT:
        hdc = BeginPaint(hHwnd, &ps);
        GetClientRect(hHwnd, &rect);
        // Ellipse(hdc, 0, 0, 200, 200);
        // DrawText(hdc, _T("Hello, Windows!"), -1, &rect,
        //         DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        TextOut(hdc, 100, 100, TEXT("hello"), 5);
        SetMapMode(hdc, MM_ISOTROPIC);
        // 自定义模式
        // 1.先要设置逻辑坐标范围
        // 2.再设置设备坐标范围
        SetWindowExtEx(hdc, 4, 4, NULL);
        SetViewportExtEx(hdc, 8, 8, NULL);
        TextOut(hdc, 100, 100, TEXT("hello"), 5);
        EndPaint(hHwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProc(hHwnd, message, wParam, lParam);
}