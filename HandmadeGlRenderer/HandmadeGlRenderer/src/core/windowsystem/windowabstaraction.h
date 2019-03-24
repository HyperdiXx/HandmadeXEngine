#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN

#include "dx12.h"
#include "dx11.h"

static bool Running = true;

namespace XEngine
{
    struct Win32Window
    {
        HWND hwnd;
        UINT Msg;
        WPARAM wParam;
        LPARAM lParam;
        HINSTANCE hInstance;
        HINSTANCE hPrevInstance;
        PWSTR cmd_line;
        int cmd_show;
    };

    void DXInitEngineWindow(Win32Window *window);
    IDXGISwapChain1* getSwapChain1(IDXGISwapChain1 *sc);
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
