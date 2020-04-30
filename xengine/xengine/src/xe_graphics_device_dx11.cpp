#include "xe_graphics_device_dx11.h"

#include "xe_utility.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"Dxgi.lib")
#pragma comment(lib,"dxguid.lib")

namespace xe_graphics
{
    graphics_device_dx11::graphics_device_dx11(HWND window, bool32 vsync, bool32 fullscreen)
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
            xe_utility::error("Failed to create back buffer texture2D!");
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
        
        set_viewport(vp.x, vp.y, vp.width, vp.height);
        
        real32 fov = 45.0f, aspect_ratio = vp.width / vp.height;

        /*using namespace DirectX;
        
        projection = XMMatrixPerspectiveFovLH(fov, aspect_ratio, 0.005f, 500.0f);

        world = XMMatrixIdentity();

        ortho = XMMatrixOrthographicLH(vp.width, vp.height, vp.min_depth, vp.max_depth);*/
    }

    graphics_device_dx11::~graphics_device_dx11()
    {

    }

    void graphics_device_dx11::clear(int flags)
    {
        device_context->ClearRenderTargetView(render_target_view, clear_color_v);
        device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
    }

    void graphics_device_dx11::clear_color(real32 r, real32 g, real32 b, real32 a)
    {       
        clear_color_v[0] = r;
        clear_color_v[1] = g;
        clear_color_v[2] = b;
        clear_color_v[3] = a;
    }

    void graphics_device_dx11::set_viewport(int32 x, int32 y, int32 width, int32 height)
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

    void graphics_device_dx11::enable(int type)
    {
    }

    void graphics_device_dx11::disable(int type)
    {
    }

    void graphics_device_dx11::set_blend_func(int src, int dst)
    {
    }

    void graphics_device_dx11::set_depth_func(int type)
    {
    }

    void graphics_device_dx11::set_cull_mode(int type)
    {
    }

    void graphics_device_dx11::set_depth(bool32 type)
    {
    }

    void graphics_device_dx11::draw_array(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count)
    {
    }

    void graphics_device_dx11::draw_indexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void * ind)
    {
    }

    void graphics_device_dx11::activate_bind_texture(TEXTURE_TYPE type, const texture2D * texture)
    {
    }

    void graphics_device_dx11::activate_bind_texture(TEXTURE_TYPE type, const cubemap * texture)
    {
    }

    void graphics_device_dx11::activate_texture(uint32 index)
    {
    }

    void graphics_device_dx11::bind_texture(TEXTURE_TYPE type, const texture2D * texture)
    {
    }

    void graphics_device_dx11::bind_shader(const shader * shader)
    {
    }

    void graphics_device_dx11::bind_buffer(const vertex_buffer * vb)
    {
    }

    void graphics_device_dx11::bind_buffer(const index_buffer * ib)
    {
    }

    void graphics_device_dx11::bind_vertex_array(const vertex_array * va)
    {
    }

    void graphics_device_dx11::bind_framebuffer(const framebuffer * fbo)
    {
    }

    void graphics_device_dx11::bind_renderbuffer(const framebuffer * fbo)
    {
    }

    void graphics_device_dx11::bind_for_read(const framebuffer * fbo)
    {
    }

    void graphics_device_dx11::bind_for_write(const framebuffer * fbo)
    {
    }

    void graphics_device_dx11::add_color_texture2D(texture2D * texture, uint32 color_attachment_id, framebuffer * fbo)
    {
    }

    void graphics_device_dx11::add_depth_texture2D(texture2D * depth, framebuffer * fbo)
    {
    }

    void graphics_device_dx11::add_depth_texture2D(uint32 w, uint32 h, framebuffer * fbo)
    {
    }

    void graphics_device_dx11::set_depth_buffer_attachment(const framebuffer * fbo)
    {
    }

    void graphics_device_dx11::set_depth_buffer_attachment(uint32 w, uint32 h, const framebuffer * fbo)
    {
    }

    void graphics_device_dx11::set_texture2D_fbo(uint32 attach_type, TEXTURE_TYPE tex_type, texture2D *texture)
    {

    }

    void graphics_device_dx11::set_texture2D_fbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, texture2D *texture)
    {
    }

    void graphics_device_dx11::set_texture2D_fbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, texture2D * texture, uint32 mip)
    {

    }

    texture2D &graphics_device_dx11::get_texture(uint32 number, const framebuffer *fbo)
    {
        if (fbo && number >= 0 <= MAX_COLOR_ATT)
            return *fbo->color_textures[number];
    }

    void graphics_device_dx11::check_framebuffer()
    {
    }

    void graphics_device_dx11::unbind_texture(TEXTURE_TYPE texture)
    {
    }

    void graphics_device_dx11::unbind_vertex_array()
    {
    }

    void graphics_device_dx11::unbind_shader()
    {
    }

    void graphics_device_dx11::unbind_framebuffer()
    {
    }

    void graphics_device_dx11::unbind_buffer(BUFFER_TYPE type)
    {
    }

    void graphics_device_dx11::set_bool(const std::string & name, bool value, shader * shd)
    {
    }

    void graphics_device_dx11::set_int(const std::string & namee, int32 value, shader * shd)
    {
    }

    void graphics_device_dx11::set_float(const std::string & name, real32 value, shader * shd)
    {
    }

    void graphics_device_dx11::set_vec2(const std::string & name, const glm::vec2 & value, shader * shd)
    {
    }

    void graphics_device_dx11::set_vec2(const std::string & name, real32 x, real32 y, shader * shd)
    {
    }

    void graphics_device_dx11::set_vec3(const std::string & name, const glm::vec3 & value, shader * shd)
    {
    }

    void graphics_device_dx11::set_vec3(const std::string & name, real32 x, real32 y, real32 z, shader * shd)
    {
    }

    void graphics_device_dx11::set_vec4(const std::string & name, const glm::vec4 & value, shader * shd)
    {
    }

    void graphics_device_dx11::set_vec4(const std::string & name, real32 x, real32 y, real32 z, real32 w, shader * shd)
    {
    }

    void graphics_device_dx11::set_mat2(const std::string & name, const glm::mat2 & mat, shader * shd)
    {
    }

    void graphics_device_dx11::set_mat3(const std::string & name, const glm::mat3 & mat, shader * shd)
    {
    }

    void graphics_device_dx11::set_mat4(const std::string & name, const glm::mat4 & mat, shader * shd)
    {
    }

    void graphics_device_dx11::set_draw_buffer(uint32 type)
    {
    }

    void graphics_device_dx11::set_draw_buffers(uint32 count, void * pointer)
    {
    }

    void graphics_device_dx11::set_read_buffer(uint32 type)
    {
    }

    void graphics_device_dx11::check_error()
    {
    }

    void graphics_device_dx11::start_execution()
    {
        device_context->ClearRenderTargetView(render_target_view, clear_color_v);
        device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void graphics_device_dx11::end_execution()
    {
        swap_chain->Present(vsync, 0);
    }

    bool32 graphics_device_dx11::create_texture(texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture(uint32 count, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(const char * path, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(const char * path, TEXTURE_TYPE tex_type, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(const char * path, TEXTURE_TYPE tex_type, bool32 gen_mip, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(const char * path, const char * dir, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(const char * path, const char * dir, TEXTURE_TYPE type, bool32 generate_mipmap, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(const char * path, const char * dir, TEXTURE_TYPE type, uint32 i, bool32 generate_mipmap, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_texture2D(uint32 width, uint32 height, texture2D * texture)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_shader(const char * vertex, const char * fragment, shader * shader)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_framebuffer(const uint32 count, framebuffer * fbo)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_render_buffer(const uint32 count, framebuffer * fbo)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_vertex_buffer(real32 * vertices, uint32 size, DRAW_TYPE draw_type, vertex_buffer * vb)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_index_buffer(uint32 * indices, uint32 size, index_buffer * ib)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_vertex_array(vertex_array * va)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout * buf_layout)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::set_vertex_buffer_layout(vertex_buffer * vb, buffer_layout * buf_layout)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::add_vertex_buffer(vertex_array * va, vertex_buffer * vb)
    {
        return bool32();
    }

    bool32 graphics_device_dx11::set_index_buffer(vertex_array * va, index_buffer * ib)
    {
        return bool32();
    }

    void graphics_device_dx11::set_texture_wrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler)
    {
    }

    void graphics_device_dx11::set_texture_sampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler)
    {
    }

    void graphics_device_dx11::load_texture_gpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void* image)
    {
    }

    void graphics_device_dx11::load_texture_gpu(int texture_t, int width, int height, int internal_format, int data_format, const void* image)
    {
    }

    void graphics_device_dx11::generate_texture_mipmap(TEXTURE_TYPE texture_t)
    {
    }

    void graphics_device_dx11::destroy_texture2D(texture2D * tex)
    {
    }

    void graphics_device_dx11::destroy_framebuffer(framebuffer * fbo)
    {
    }

    void graphics_device_dx11::destroy_shader(uint32 id)
    {
    }

}

