#pragma once



#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;


namespace XEngine
{
    namespace DX11
    {
        struct DirectX11
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
    }
}