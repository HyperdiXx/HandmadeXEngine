#include "windowabstaraction.h"

using namespace XEngine;

void Win32Window::DXInitEngineWindow(Win32Window *window)
{
    const wchar_t* nameWindow = L"XEngine";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = window->hInstance;
    wc.lpszClassName = nameWindow;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    window->hwnd = CreateWindowEx(
        0,
        nameWindow,
        L"XEngine",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        window->hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (window->hwnd == NULL)
    {

    }

    ShowWindow(window->hwnd, window->cmd_show);

    
    //swap_chain->Present(0, 0);

}

IDXGISwapChain1* Win32Window::getSwapChain1(IDXGISwapChain1 *sc)
{
    return sc;
}


LRESULT CALLBACK XEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT res = 0;
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            Running = false;
            OutputDebugStringA("WM_DESTROY\n");            
        }break;
        case WM_CLOSE:
        {
            Running = false;
            OutputDebugStringA("WM_CLOSE\n");
        }break;
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        }break;
        case WM_PAINT:
        {
            /*PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1 >> 2));
            EndPaint(hwnd, &ps);*/
        }break;
        default:
            res = DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
    }
    return (res);
}
