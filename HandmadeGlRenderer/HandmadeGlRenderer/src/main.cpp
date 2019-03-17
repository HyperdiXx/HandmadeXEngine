
/*
    The Rendering Engine as Part of XEngine.
    OpenGL API 4.5


    Features: Camera, ImGUI, Textures, MultiTextures, Lighting, Redering Interfaces, FrameBuffers, Cubemap, MSAA, ForwardShading, DefferedShading, Stencil, Blending, PostProcess,
    FaceCulling, Instancing, DynamicShadowMapping + DirLight, OmniLightsShadows, NormalMapping, ParallaxMapping,  Antialiasing, Gamma Correctiom
    TODO(vlad): Assimp, Logger, 
        
        
        Bloom,
        HDR, SSAO, PBR

        DX11 ...
        DX12 ...
*/




#include <thread>
#include <future>

#include "application/app.h"

//#include "graphicsapi/dx12.h"
#include <windows.h>

#define OPENGL


#ifdef DX

static bool Running = true;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t* nameWindow = L"XEngine";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = nameWindow;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        nameWindow,
        L"XEngine",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       
        NULL,       
        hInstance,  
        NULL        
    );

    if (hwnd == NULL)
    {

    }

    ShowWindow(hwnd, nCmdShow);


    static ID3D12Device* device;
    static IDXGIFactory2* dxgi_factory;
    static IDXGISwapChain1* swap_chain;
    static ID3D12CommandQueue *graphics_que;
    static D3D12_COMMAND_QUEUE_DESC graphics_command_que_desc = {};
    static ID3D12CommandAllocator *commandAllocator;
    static ID3D12RootSignature* rootSignature;
    static ID3D12Debug* debug;

    graphics_command_que_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    HRESULT hResult;

    hResult = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
    CheckSucceeded(hResult);

    debug->EnableDebugLayer();

    hResult = CreateDXGIFactory(IID_PPV_ARGS(&dxgi_factory));
    CheckSucceeded(hResult);

    hResult = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
    CheckSucceeded(hResult);

    hResult = device->CreateCommandQueue(&graphics_command_que_desc, IID_PPV_ARGS(&graphics_que));
    CheckSucceeded(hResult);

    DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};

    swap_chain_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.BufferCount = 3;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    hResult = dxgi_factory->CreateSwapChainForHwnd(graphics_que, hwnd, &swap_chain_desc, 0, 0, &swap_chain);
    CheckSucceeded(hResult);
    
    hResult = device->CreateCommandAllocator(graphics_command_que_desc.Type, IID_PPV_ARGS(&commandAllocator));
    CheckSucceeded(hResult);

    UINT compiler_flag = 0;

    /*ID3DBlob *vertex_shader, *pixel_shader;
    hResult = D3DCompileFromFile(L"E:\\HandmadeXEngine\\HandmadeGlRenderer\\HandmadeGlRenderer\\src\\shaders\\triangle.hlsl", 0, 0, "vs_main", "vs_5_0", compiler_flag, 0, &vertex_shader, 0);
    CheckSucceeded(hResult);
    hResult = D3DCompileFromFile(L"E:\\HandmadeXEngine\\HandmadeGlRenderer\\HandmadeGlRenderer\\src\\shaders\\triangle.hlsl", 0, 0, "ps_main", "ps_5_0", compiler_flag, 0, &pixel_shader, 0);
    CheckSucceeded(hResult);*/

    CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc = {};
    root_signature_desc.Init(0, 0, 0, 0, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);


    ID3DBlob *root_signature_blob;
    ID3DBlob *root_signature_error_blob;

    hResult = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &root_signature_blob, &root_signature_error_blob);
    CheckSucceeded(hResult);

    device->CreateRootSignature(0, root_signature_blob->GetBufferPointer(), root_signature_blob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
    CheckSucceeded(hResult);

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_sate_desc = {};
    pipeline_sate_desc.pRootSignature = rootSignature;
    pipeline_sate_desc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    pipeline_sate_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    pipeline_sate_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    pipeline_sate_desc.SampleMask = UINT_MAX;
    pipeline_sate_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pipeline_sate_desc.NumRenderTargets = 1;
    pipeline_sate_desc.RTVFormats[0] = swap_chain_desc.Format;
    pipeline_sate_desc.SampleDesc.Count = 1;
  



    ID3D12PipelineState *pipeline_state;

    hResult = device->CreateGraphicsPipelineState(&pipeline_sate_desc, IID_PPV_ARGS(&pipeline_state));
    CheckSucceeded(hResult);

    // Run the message loop.

    while(Running)
    {
        MSG msg = { };
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ID3D12GraphicsCommandList *command_list;
        device->CreateCommandList(0, graphics_command_que_desc.Type, commandAllocator, 0, IID_PPV_ARGS(&command_list));
        CheckSucceeded(hResult);
        
        ID3D12CommandList *command_lists[] = { command_list };

        command_list->Close();
        graphics_que->ExecuteCommandLists(1, command_lists);

        swap_chain->Present(0, 0);
        command_list->Release();

    }
    
    return (0);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    default:
        res = DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }
    return (res);
}

#endif


#ifdef OPENGL
int main(int argc, char** argv)
{
    XEngine::OpenGLRunEngineWin32();

    return (0);
}

#endif


