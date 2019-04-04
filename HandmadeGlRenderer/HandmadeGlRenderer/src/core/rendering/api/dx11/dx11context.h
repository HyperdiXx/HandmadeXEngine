#pragma once

#ifndef CONTEXTH
#define CONTEXTH

#include <d3d11.h>

#include <string>

namespace XEngine
{
    class DX11Context
    {
    public:
        DX11Context();
        ~DX11Context();

        void initD3D(HWND hwnd, int width, int height, const bool vsync, DXGI_FORMAT FrameBufferFormat);

        void clearColor();
        void end();

        void shutdown();

        inline const int getWidth() const { return mWidth; };
        inline const int getHeight() const { return mHeight; };

    private:
        bool initSwapChain(HWND hwnd, bool fullscreen, int scrWidth, int scrHeight, unsigned numerator, unsigned denominator, DXGI_FORMAT FrameBufferFormat);

    private:

        IDXGISwapChain *mswapChain;
        ID3D11Device *mdevice;
        ID3D11DeviceContext *mdeviceContext;
        HWND mHwnd;
        int mWidth, mHeight;
        int mvram;
        std::string mGPU[128];
        bool misvsync;

#ifdef _DEBUG
        ID3D11Debug *mdebug;
#endif
    };
}


#endif // !CONTEXTH


