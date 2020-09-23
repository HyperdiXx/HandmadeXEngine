#include "xe_graphics_device_dx11.h"

#include "xe_utility.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"Dxgi.lib")
#pragma comment(lib,"dxguid.lib")

namespace xe_graphics
{
    GraphicsDeviceDX11::GraphicsDeviceDX11(HWND window, bool32 vsync, bool32 fullscreen)
    {    
        this->fullscreen = fullscreen;
        this->vsync = vsync;
        
        this->vp = {};
        
        RECT rect = RECT();
        GetClientRect(window, &rect);
        this->vp.width = rect.right - rect.left;
        this->vp.height = rect.bottom - rect.top;

        int error;
        HRESULT res = E_FAIL;

        IDXGIAdapter* adapter;
        IDXGIFactory* factory;

        IDXGIOutput* adapterOutput;

        DXGI_MODE_DESC* displayModeList;
        DXGI_ADAPTER_DESC adapterDesc;
       
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;       
        ID3D11Texture2D* back_buffer_ptr;
        D3D11_TEXTURE2D_DESC depth_buffer_desc;        
        D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
        D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
        D3D11_RASTERIZER_DESC raster_desc;
        
        res = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
        if (FAILED(res))
        {
            xe_utility::error("Failed to create dxgi factory!");
        }

        res = factory->EnumAdapters(0, &adapter);
        if (FAILED(res))
        {
            xe_utility::error("Failed to create enum adapters!");
        }

        res = adapter->EnumOutputs(0, &adapterOutput);
        if (FAILED(res))
        {
            xe_utility::error("Failed to create adapter output!");
        }

        uint32 num_modes;
        res = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL);
        if (FAILED(res))
        {
            xe_utility::error("Failed to get number of display modes");
        }

        displayModeList = new DXGI_MODE_DESC[num_modes];
        if (!displayModeList)
        {
            xe_utility::error("Failed to init display list!");
        }

        res = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, displayModeList);
        if (FAILED(res))
        {
            xe_utility::error("Failed to fill display mode list str");
        }

        uint32 numerator = 0;
        uint32 denominator = 0;

        for (uint32 i = 0; i < num_modes; i++)
        {
            if (displayModeList[i].Width == (uint32)vp.width)
            {
                if (displayModeList[i].Height == (uint32)vp.height)
                {
                    numerator = displayModeList[i].RefreshRate.Numerator;
                    denominator = displayModeList[i].RefreshRate.Denominator;
                }
            }
        }

        res = adapter->GetDesc(&adapterDesc);
        if (FAILED(res))
        {
            xe_utility::error("Failed to load GPU desctiption!");
        }

        gpu_memory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

        delete[] displayModeList;
        displayModeList = nullptr;

        adapterOutput->Release();
        adapterOutput = nullptr;

        adapter->Release();
        adapter = nullptr;

        factory->Release();
        factory = nullptr;

        ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

        swap_chain_desc.BufferCount = 1;

        swap_chain_desc.BufferDesc.Width = vp.width;
        swap_chain_desc.BufferDesc.Height = vp.height;

        // 32-bit back buffer
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        if (vsync)
        {
            swap_chain_desc.BufferDesc.RefreshRate.Numerator = numerator;
            swap_chain_desc.BufferDesc.RefreshRate.Denominator = denominator;
        }
        else
        {
            swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
            swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        }

        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = window;

        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;

        if (fullscreen)
            swap_chain_desc.Windowed = false;
        else
            swap_chain_desc.Windowed = true;
        
        swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swap_chain_desc.Flags = 0;

        D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_1;

        res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &feature_level, 1,
            D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain, &device, NULL, &device_context);

        if (FAILED(res))
        {
            xe_utility::error("Failed to create Device and Swap chain!");
        }

        res = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_ptr);

        if (FAILED(res))
        {
            xe_utility::error("Failed to get back buffer ptr!");
        }

        res = device->CreateRenderTargetView(back_buffer_ptr, NULL, &render_target_view);

        if (FAILED(res))
        {
            xe_utility::error("Faile to create render target!");
        }

        back_buffer_ptr->Release();
        back_buffer_ptr = nullptr;

        ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
        
        depth_buffer_desc.Width = vp.width;
        depth_buffer_desc.Height = vp.height;
        depth_buffer_desc.MipLevels = 1;
        depth_buffer_desc.ArraySize = 1;
        depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depth_buffer_desc.SampleDesc.Count = 1;
        depth_buffer_desc.SampleDesc.Quality = 0;
        depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depth_buffer_desc.CPUAccessFlags = 0;
        depth_buffer_desc.MiscFlags = 0;

        res = device->CreateTexture2D(&depth_buffer_desc, NULL, &back_buffer);

        if (FAILED(res))
        {
            xe_utility::error("Failed to create back buffer Texture2D!");
        }

        ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));

        depth_stencil_desc.DepthEnable = true;
        depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

        depth_stencil_desc.StencilEnable = true;
        depth_stencil_desc.StencilReadMask = 0xFF;
        depth_stencil_desc.StencilWriteMask = 0xFF;

        depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        res = device->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state);

        if (FAILED(res))
        {
            xe_utility::error("Failed to create depth stencil state!");
        }

        device_context->OMSetDepthStencilState(depth_stencil_state, 1);

        ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));

        depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depth_stencil_view_desc.Texture2D.MipSlice = 0;
       
        res = device->CreateDepthStencilView(back_buffer, &depth_stencil_view_desc, &depth_stencil_view);
        if (FAILED(res))
        {
            xe_utility::error("Failed to create depth stencil buffer view");
        }

        device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
        
        setViewport(vp.x, vp.y, vp.width, vp.height);
        
        real32 fov = 45.0f, aspect_ratio = vp.width / vp.height;

        /*using namespace DirectX;
        
        projection = XMMatrixPerspectiveFovLH(fov, aspect_ratio, 0.005f, 500.0f);

        world = XMMatrixIdentity();

        ortho = XMMatrixOrthographicLH(vp.width, vp.height, vp.min_depth, vp.max_depth);*/
    }

    GraphicsDeviceDX11::~GraphicsDeviceDX11()
    {

    }

    void GraphicsDeviceDX11::clear(int flags)
    {
        device_context->ClearRenderTargetView(render_target_view, clear_color_v);
        device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
    }

    void GraphicsDeviceDX11::clearColor(real32 r, real32 g, real32 b, real32 a)
    {       
        clear_color_v[0] = r;
        clear_color_v[1] = g;
        clear_color_v[2] = b;
        clear_color_v[3] = a;
    }

    void GraphicsDeviceDX11::setViewport(int32 x, int32 y, int32 width, int32 height)
    {
        D3D11_VIEWPORT viewport_dx11;

        viewport_dx11.Width = (FLOAT)vp.width;
        viewport_dx11.Height = (FLOAT)vp.height;
        viewport_dx11.MinDepth = (FLOAT)vp.min_depth;
        viewport_dx11.MaxDepth = (FLOAT)vp.max_depth;
        viewport_dx11.TopLeftX = (FLOAT)vp.x;
        viewport_dx11.TopLeftY = (FLOAT)vp.y;

        device_context->RSSetViewports(1, &viewport_dx11);
    }

    void GraphicsDeviceDX11::enable(int type)
    {
    }

    void GraphicsDeviceDX11::disable(int type)
    {
    }

    void GraphicsDeviceDX11::setBlendFunc(int src, int dst)
    {
    }

    void GraphicsDeviceDX11::setDepthFunc(int type)
    {
    }

    void GraphicsDeviceDX11::setCullMode(int type)
    {
    }

    void GraphicsDeviceDX11::setDepth(bool32 type)
    {
    }

    void GraphicsDeviceDX11::setLineWidth(uint32 line_width)
    {
    }

    void GraphicsDeviceDX11::drawArray(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count)
    {
    }

    void GraphicsDeviceDX11::drawIndexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void * ind)
    {
    }

    void GraphicsDeviceDX11::activateBindTexture(TEXTURE_TYPE type, const Texture2D * texture)
    {
    }

    void GraphicsDeviceDX11::activateBindTexture(TEXTURE_TYPE type, const Cubemap * texture)
    {
    }

    void GraphicsDeviceDX11::activateTexture(uint32 index)
    {
    }

    void GraphicsDeviceDX11::bindTexture(TEXTURE_TYPE type, const Texture2D * texture)
    {
    }

    void GraphicsDeviceDX11::bindShader(const Shader *Shader)
    {
        //device_context->VSSetShader(//Shader);
    }

    void GraphicsDeviceDX11::bindBuffer(const VertexBuffer * vb)
    {
    }

    void GraphicsDeviceDX11::bindBuffer(const IndexBuffer * ib)
    {
    }

    void GraphicsDeviceDX11::bindVertexArray(const VertexArray * va)
    {
    }

    void GraphicsDeviceDX11::bindFramebuffer(const Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::bindRenderbuffer(const Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::bindForRead(const Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::bindForWrite(const Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::addColorTexture2D(Texture2D * texture, uint32 color_attachment_id, Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::addDepthTexture2D(Texture2D * depth, Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::addDepthTexture2D(uint32 w, uint32 h, Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::setDepthBufferAttachment(const Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::setDepthBufferAttachment(uint32 w, uint32 h, const Framebuffer * fbo)
    {
    }

    void GraphicsDeviceDX11::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, Texture2D *texture)
    {

    }

    void GraphicsDeviceDX11::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture)
    {
    }

    void GraphicsDeviceDX11::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D * texture, uint32 mip)
    {

    }

    void GraphicsDeviceDX11::setRenderbuffer(int depth_component, uint32 width, uint32 height)
    {
    }

    void GraphicsDeviceDX11::setFramebufferRenderbufferAttachment(const Framebuffer * fbo)
    {
    }

    Texture2D &GraphicsDeviceDX11::getTexture(uint32 number, const Framebuffer *fbo)
    {
        if (fbo && number >= 0 <= MAX_COLOR_ATT)
            return *fbo->color_textures[number];
    }

    void GraphicsDeviceDX11::checkFramebuffer()
    {
    }

    void GraphicsDeviceDX11::unbindTexture(TEXTURE_TYPE texture)
    {
    }

    void GraphicsDeviceDX11::unbindVertexArray()
    {
    }

    void GraphicsDeviceDX11::unbindShader()
    {
    }

    void GraphicsDeviceDX11::unbindFramebuffer()
    {
    }

    void GraphicsDeviceDX11::unbindBuffer(BUFFER_TYPE type)
    {
    }

    void GraphicsDeviceDX11::setBool(const std::string & name, bool value, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setInt(const std::string & namee, int32 value, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setFloat(const std::string & name, real32 value, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setVec2(const std::string & name, const glm::vec2 & value, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setVec2(const std::string & name, real32 x, real32 y, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setVec3(const std::string & name, const glm::vec3 & value, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setVec3(const std::string & name, real32 x, real32 y, real32 z, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setVec4(const std::string & name, const glm::vec4 & value, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setVec4(const std::string & name, real32 x, real32 y, real32 z, real32 w, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setMat2(const std::string & name, const glm::mat2 & mat, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setMat3(const std::string & name, const glm::mat3 & mat, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setMat4(const std::string & name, const glm::mat4 & mat, Shader * shd)
    {
    }

    void GraphicsDeviceDX11::setDrawBuffer(uint32 type)
    {
    }

    void GraphicsDeviceDX11::setDrawBuffers(uint32 count, void * pointer)
    {
    }

    void GraphicsDeviceDX11::setReadBuffer(uint32 type)
    {
    }

    void GraphicsDeviceDX11::checkError()
    {
    }

    void GraphicsDeviceDX11::loadBindings()
    {
    }

    void GraphicsDeviceDX11::startExecution()
    {
        device_context->ClearRenderTargetView(render_target_view, clear_color_v);
        device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void GraphicsDeviceDX11::endExecution()
    {
        swap_chain->Present(vsync, 0);
    }

    bool32 GraphicsDeviceDX11::createTexture(Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture(uint32 count, Texture2D * texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture2D(const char *path, Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture2D(const char *path, TEXTURE_TYPE tex_type, Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture2D(const char *path, TEXTURE_TYPE tex_type, uint32 samples, bool32 gen_mip, Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture2D(const char *path, const char *dir, Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture2D(const char *path, const char *dir, TEXTURE_TYPE type, bool32 generate_mipmap, Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createTexture2D(const char *path, const char *dir, TEXTURE_TYPE type, uint32 i, uint32 samples, bool32 generate_mipmap, Texture2D *texture)
    {
        return bool32();
    }

    bool32 GraphicsDeviceDX11::createTexture2D(uint32 width, uint32 height, Texture2D *texture)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createShader(const char *vertex, const char *fragment, Shader *shader)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createFramebuffer(const uint32 count, Framebuffer *fbo)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createRenderbuffer(const uint32 count, Framebuffer *fbo)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::createVertexBuffer(void *vertices, uint32 size, DRAW_TYPE draw_type, VertexBuffer *vb)
    {
        D3D11_BUFFER_DESC buffer_desc;
        D3D11_SUBRESOURCE_DATA bind_data;

        ID3D11Buffer *buffer_handle;
        ID3D11InputLayout* input_layout;

        ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));
        buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buffer_desc.ByteWidth = sizeof(real32) * size;
        buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        buffer_desc.MiscFlags = 0;
        buffer_desc.StructureByteStride = 0;


        HRESULT hr = device->CreateBuffer(&buffer_desc, &bind_data, &buffer_handle);

        if (!SUCCEEDED(hr))
        {
            //memcpy(, data, size);
            xe_utility::error("Failed to create vertex Buffer DX11");
            return false;
        }



        return true;
    }

    bool32 GraphicsDeviceDX11::createIndexBuffer(uint32 *indices, uint32 size, IndexBuffer *ib)
    {
        D3D11_BUFFER_DESC index_buffer_desc;

        ZeroMemory(&index_buffer_desc, sizeof(D3D11_BUFFER_DESC));
        index_buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
        index_buffer_desc.ByteWidth = size * sizeof(uint16);
        index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        index_buffer_desc.CPUAccessFlags = 0;
        index_buffer_desc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA bind_data;
        bind_data.pSysMem = indices;
        
        /*HRESULT hr = device->CreateBuffer(&index_buffer_desc, &bind_data, &ib->handle);

        if (!SUCCEEDED(hr))
        {
            xe_utility::error("Failed to create index Buffer DX11");
            return false;
        }*/

        return true;
    }

    bool32 GraphicsDeviceDX11::createVertexArray(VertexArray *va)
    {
        return bool32();
    }

    bool32 GraphicsDeviceDX11::createBufferLayout(std::initializer_list<BufferElement>& element, BufferLayout *buf_layout)
    {
        return bool32();
    }

    bool32 GraphicsDeviceDX11::setVertexBufferLayout(VertexBuffer *vb, BufferLayout *buf_layout)
    {
        vb->layout = *buf_layout;

        return true;
    }

    bool32 GraphicsDeviceDX11::addVertexBuffer(VertexArray *va, VertexBuffer *vb)
    {
        return true;
    }

    bool32 GraphicsDeviceDX11::setIndexBuffer(VertexArray *va, IndexBuffer *ib)
    {
        return true;
    }

    void GraphicsDeviceDX11::setTextureWrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler)
    {
    }

    void GraphicsDeviceDX11::setTextureSampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler)
    {
    }

    void GraphicsDeviceDX11::loadTextureGpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void* image)
    {
    }

    void GraphicsDeviceDX11::loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, const void* image)
    {
    }

    void GraphicsDeviceDX11::loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, int data_type, const void * image)
    {
    }

    void GraphicsDeviceDX11::generateTextureMipmap(TEXTURE_TYPE texture_t)
    {
    }

    void GraphicsDeviceDX11::destroyTexture2D(Texture2D *tex)
    {
    }

    void GraphicsDeviceDX11::destroyFramebuffer(Framebuffer *fbo)
    {
    }

    void GraphicsDeviceDX11::destroyShader(uint32 id)
    {
    }

    void GraphicsDeviceDX11::destroyBuffer(VertexBuffer *vb)
    {
    }

    void GraphicsDeviceDX11::destroyBuffer(IndexBuffer *ib)
    {
    }

}

