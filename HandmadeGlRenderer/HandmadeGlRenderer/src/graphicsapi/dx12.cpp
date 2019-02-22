#include "dx12.h"



void DX12InitDevice(ID3D12Device *device, IDXGIFactory2 *dxgi_factory, HWND &hwnd, IDXGISwapChain1* swap_chain, ID3D12CommandQueue *graph_que, D3D12_COMMAND_QUEUE_DESC &graphics_desc)
{
    HRESULT hResult;

    hResult = CreateDXGIFactory(IID_PPV_ARGS(&dxgi_factory));
    CheckSucceeded(hResult);

    hResult = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
    CheckSucceeded(hResult);

    hResult = device->CreateCommandQueue(&graphics_desc, IID_PPV_ARGS(&graph_que));
    CheckSucceeded(hResult);

    DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};

    swap_chain_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.BufferCount = 3;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    hResult = dxgi_factory->CreateSwapChainForHwnd(graph_que, hwnd, &swap_chain_desc, 0, 0, &swap_chain);
    CheckSucceeded(hResult);

}