#pragma once

#ifndef UNICODE
#define UNICODE
#endif 


#include <windows.h>

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
        PWSTR CmdLine;
        int CMDN;
    };


    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
}
