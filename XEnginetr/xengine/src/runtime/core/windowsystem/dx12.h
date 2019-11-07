#pragma once

#ifndef DX12
#define DX12

#include "../utility/assert.h"

#include <d3d12.h>
#include "../d3dx12.h"
#include <dxgi1_2.h>
#include <d3dcompiler.h>


#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib") 


void DX12InitDevice(ID3D12Device *device, IDXGIFactory2 *dxgi_factory, HWND &hwnd, IDXGISwapChain1* swap_chain, ID3D12CommandQueue *graph_que, D3D12_COMMAND_QUEUE_DESC &graphics_desc);




#endif // !DX12



