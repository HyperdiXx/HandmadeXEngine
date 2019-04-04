#include "windowWin.h"

using namespace XEngine;
using namespace Rendering;

WindowDX::WindowDX() :  
            misMouseCaptured(false), isRunning(true)
{
    //mappName = "XEngine";
    mhInstance = GetModuleHandle(NULL);
}

WindowDX::~WindowDX()
{

}

void WindowDX::initEngine()
{
    WNDCLASS wnd = {};

    wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wnd.lpfnWndProc = WndProc;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hInstance = mhInstance;
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wnd.lpszClassName = L"XEngine";


    if (RegisterClass(&wnd))
    {
        mhwnd = CreateWindowEx(
            0,
            wnd.lpszClassName,
            wnd.lpszClassName,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            1280,
            720,
            0,
            0,
            mhInstance,
            0
        );

    }
    
    if (mhwnd == NULL)
    {
        MessageBox(NULL, (LPCWSTR)"CreateWindowEx() failed", (LPCWSTR)"Error", MB_OK);
        PostQuitMessage(0);
        return;
    }




}

void WindowDX::update()
{
    MSG msg = {};

    ZeroMemory(&msg, sizeof(MSG));

    while (isRunning)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);		
        }

        if (msg.message == WM_QUIT)
        {
            isRunning = false;
        }
        else
        {
            //TODO: actual data
        }



    }



}

void WindowDX::shutdown()
{
    DestroyWindow(mhwnd);
    mhwnd = NULL;

    UnregisterClass(mappName, mhInstance);
    mhInstance = NULL;

    gInstance = NULL;
}

void WindowDX::resizeWindow(int w, int h)
{
    mwindowHeight = h;
    mwindowWidth = w;
}

LRESULT WindowDX::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT res;

    switch (msg)
    {



    default:
    {
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    }

    return (res);
}

namespace XEngine
{
    namespace Rendering
    {
        LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
        {
            switch (umessage)
            {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_QUIT:
                PostQuitMessage(0);
                return 0;
            default:
                return gInstance->MessageHandler(hwnd, umessage, wparam, lparam);
            }
        }
    }
    
}
