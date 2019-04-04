#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

#include "dx12.h"
#include "dx11.h"

static bool Running = true;

namespace XEngine
{
    namespace Rendering
    {
        class WindowDX
        {
        public:
            WindowDX();
            ~WindowDX();

            void initEngine();
            void update();
            void shutdown();

            void resizeWindow(int w, int h);

            LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
        private:
            LPCWSTR	mappName;
            HINSTANCE	mhInstance;
            HWND	mhwnd;
            int		mwindowWidth, mwindowHeight;
            bool	misMouseCaptured;
            bool	isRunning;
            POINT	mcapturePosition;
        };

        static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
        static WindowDX* gInstance = 0;

    }
   
}
