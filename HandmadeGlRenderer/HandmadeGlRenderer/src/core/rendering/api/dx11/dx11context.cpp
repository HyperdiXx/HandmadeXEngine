#include "dx11context.h"



XEngine::DX11Context::DX11Context()
{

}

XEngine::DX11Context::~DX11Context()
{

}

void XEngine::DX11Context::initD3D(HWND hwnd, int width, int height, const bool vsync, DXGI_FORMAT FrameBufferFormat)
{
    mHwnd = hwnd;

    HRESULT result;
    IDXGIFactory* pFactory;
    IDXGIAdapter* pAdapter;
    IDXGIOutput* pAdapterOutput;
    unsigned numModes;
   
    misvsync = vsync;

    result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
    if (FAILED(result))
    {
        return;
    }

    // Use the factory to create an adapter for the primary graphics interface (video card).
    result = pFactory->EnumAdapters(0, &pAdapter);
    if (FAILED(result))
    {
        return;
    }

   
    result = pAdapter->EnumOutputs(0, &pAdapterOutput);
    if (FAILED(result))
    {
        return;
    }

    // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
    result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    if (FAILED(result))
    {
        return;
    }

    // Create a list to hold all the possible display modes for this monitor/video card combination.
    DXGI_MODE_DESC* displayModeList;
    displayModeList = new DXGI_MODE_DESC[numModes];
    if (!displayModeList)
    {
        return;
    }

    // Now fill the display mode list structures.
    result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
    if (FAILED(result))
    {
        return;
    }

    // Now go through all the display modes and find the one that matches the screen width and height.
    // When a match is found store the numerator and denominator of the refresh rate for that monitor.
    unsigned numerator = 0;
    unsigned denominator = 0;
    for (unsigned i = 0; i < numModes; i++)
    {
        if (displayModeList[i].Width == (unsigned int)width)
        {
            if (displayModeList[i].Height == (unsigned int)height)
            {
                numerator = displayModeList[i].RefreshRate.Numerator;
                denominator = displayModeList[i].RefreshRate.Denominator;
            }
        }
    }

    if (numerator == 0 && denominator == 0)
    {
        char info[127];
        numerator = displayModeList[numModes / 2].RefreshRate.Numerator;
        denominator = displayModeList[numModes / 2].RefreshRate.Denominator;
        sprintf_s(info, "Specified resolution (%ux%u) not found: Using (%ux%u) instead\n",
            width, height,
            displayModeList[numModes / 2].Width, displayModeList[numModes / 2].Height);
        width = displayModeList[numModes / 2].Width;
        height = displayModeList[numModes / 2].Height;
        OutputDebugString(info);

        // also resize window
        SetWindowPos(hwnd, 0, 10, 10, width, height, SWP_NOZORDER);
    }

    DXGI_ADAPTER_DESC adapterDesc;
    result = pAdapter->GetDesc(&adapterDesc);
    if (FAILED(result))
    {
        return;
    }

    mvram = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

   /* size_t stringLength;
    int error;
    error = wcstombs_s(&stringLength, mGPU, 128, adapterDesc.Description, 128);
    if (error != 0)
    {
        return;
    }*/

    delete[] displayModeList;
    displayModeList = nullptr;
    pAdapterOutput->Release();
    pAdapterOutput = nullptr;
    pAdapter->Release();	
    pAdapter = nullptr;
    pFactory->Release();
    pFactory = nullptr;

    if (!initSwapChain(hwnd, false, width, height, numerator, denominator, DXGI_FORMAT_B8G8R8A8_UNORM))
    {
        return;
    }

   //mwndWidth = width;
    //mwndHeight = height;

}

void XEngine::DX11Context::clearColor()
{

}

void XEngine::DX11Context::end()
{

}

void XEngine::DX11Context::shutdown()
{

}

bool XEngine::DX11Context::initSwapChain(HWND hwnd, bool fullscreen, int scrWidth, int scrHeight, unsigned numerator, unsigned denominator, DXGI_FORMAT FrameBufferFormat)
{
    HRESULT result;


    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    D3D_FEATURE_LEVEL featureLevel;

    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));


    swapChainDesc.BufferCount = 2;
    swapChainDesc.BufferDesc.Width = scrWidth;
    swapChainDesc.BufferDesc.Height = scrHeight;
    swapChainDesc.BufferDesc.Format = FrameBufferFormat;	
    if (misvsync)
    {	
        swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
    }
    else
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    }
    swapChainDesc.OutputWindow = hwnd;	
    swapChainDesc.Windowed = true;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
 

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.Flags = 0;
    featureLevel = D3D_FEATURE_LEVEL_11_0;

#if defined( _DEBUG )
    UINT flags = D3D11_CREATE_DEVICE_DEBUG;

#else
    UINT flags = 0;
#endif

    // Create the swap chain, device, device context.
    result = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        &featureLevel,
        1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &mswapChain,
        &mdevice, NULL, &mdeviceContext);

    if (FAILED(result))
    {
        //Log::Error("D3DManager: Cannot create swap chain");
        return false;
    }

#ifdef _DEBUG
    if (SUCCEEDED(mdevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&mdebug)))
    {
        ID3D11InfoQueue* d3dInfoQueue = nullptr;
        if (SUCCEEDED(mdebug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
        {
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
            D3D11_MESSAGE_ID hide[] =
            {
                D3D11_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET,
                // Add more message IDs here as needed
            };

            D3D11_INFO_QUEUE_FILTER filter;
            memset(&filter, 0, sizeof(filter));
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
            d3dInfoQueue->Release();
        }
    }

    /*if (FAILED(mdeviceContext->QueryInterface(__uuidof(ID3DUserDefinedAnnotation), (void**)&mannotation)))
    {
        return false;
    }*/
#endif

    return true;
}
