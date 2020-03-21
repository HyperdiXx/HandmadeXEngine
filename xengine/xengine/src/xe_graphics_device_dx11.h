#pragma once

#include "xe_graphics_device.h"
#include "xe_platform.h"

#include <d3d11_3.h>
#include <DXGI1_3.h>

namespace xe_graphics
{
    class graphics_device_dx11 : public graphics_device
    {
    public:
        graphics_device_dx11(HWND window, bool32 vsync = true, bool32 fullscreen = false);
        virtual ~graphics_device_dx11();




    private:        
        ID3D11Device* device;
        ID3D11DeviceContext* device_context;
        IDXGISwapChain* swap_chain;
        ID3D11RenderTargetView* render_target_view;
        ID3D11Texture2D* back_buffer;
        ID3D11DepthStencilState* depth_stencil_state;
        ID3D11DepthStencilView* depth_stencil_view;
        ID3D11RasterizerState* raster_state;

    };
}