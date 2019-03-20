#pragma once

#ifndef DX11
#define DX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


#include <d3d11.h>
#include <directxmath.h>



using namespace DirectX;



struct __declspec(dllexport) DirectX11
{
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11DepthStencilState* depthStencilState;
    ID3D11DepthStencilView* depthStencilView;
    ID3D11RasterizerState* rasterState;
    IDXGISwapChain* swapChain;
    ID3D11Texture2D* depthStencilBuffer;
};

void __declspec(dllexport) InitDX11(HWND hwnd, DirectX11 *dx, int width, int height, float screenNear, float screenFar);




#endif // !DX1


