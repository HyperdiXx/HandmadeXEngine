#pragma once

#include "xe_graphics_device.h"
#include "xe_platform.h"

#include "xe_render.h"

#include <d3d11_3.h>
#include <DXGI1_3.h>

namespace xe_graphics
{
    class GraphicsDeviceDX11 : public GraphicsDevice
    {
    public:
        GraphicsDeviceDX11(HWND window, bool32 vsync = true, bool32 fullscreen = false);
        virtual ~GraphicsDeviceDX11();

        void clear(int flags) override;
        void clearColor(real32 r, real32 g, real32 b, real32 a) override;
        void setViewport(int32 x, int32 y, int32 width, int32 height) override;
        void enable(int type) override;
        void disable(int type) override;
        void setBlendFunc(int src, int dst) override;
        void setDepthFunc(int type) override;
        void setCullMode(int type) override;
        void setDepth(bool32 type) override;
        void setLineWidth(uint32 line_width) override;

        void drawArray(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count) override;
        void drawIndexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void *ind) override;

        void activateBindTexture(TEXTURE_TYPE type, const Texture2D *texture) override;
        void activateBindTexture(TEXTURE_TYPE type, const Cubemap *texture) override;
        void activateTexture(uint32 index) override;
        void bindTexture(TEXTURE_TYPE type, const Texture2D *tetxture) override;
        void bindShader(const Shader *shader) override;
        void bindBuffer(const VertexBuffer *vb) override;
        void bindBuffer(const IndexBuffer *ib) override;
        void bindVertexArray(const VertexArray *va) override;
        void bindFramebuffer(const Framebuffer *fbo) override;
        void bindRenderbuffer(const Framebuffer *fbo) override;
        void bindForRead(const Framebuffer *fbo) override;
        void bindForWrite(const Framebuffer *fbo) override;

        void addColorTexture2D(Texture2D *texture, uint32 color_attachment_id, Framebuffer *fbo) override;
        void addDepthTexture2D(Texture2D *depth, Framebuffer *fbo) override;
        void addDepthTexture2D(uint32 w, uint32 h, Framebuffer *fbo) override;
        void setDepthBufferAttachment(const Framebuffer *fbo) override;
        void setDepthBufferAttachment(uint32 w, uint32 h, const Framebuffer *fbo) override;
        Texture2D& getTexture(uint32 number, const Framebuffer *fbo) override;
        void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, Texture2D *texture) override;
        void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture) override;
        void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture, uint32 mip) override;
        void setRenderbuffer(int depth_component, uint32 width, uint32 height) override;
        void setFramebufferRenderbufferAttachment(const Framebuffer *fbo) override;

        void checkFramebuffer() override;

        void unbindTexture(TEXTURE_TYPE texture) override;
        void unbindVertexArray() override;
        void unbindShader() override;
        void unbindFramebuffer() override;
        void unbindBuffer(BUFFER_TYPE type) override;

        void setBool(const std::string &name, bool value, Shader *shd) override;
        void setInt(const std::string &namee, int32 value, Shader *shd) override;
        void setFloat(const std::string& name, real32 value, Shader *shd) override;
        void setVec2(const std::string &name, const glm::vec2 &value, Shader *shd) override;
        void setVec2(const std::string &name, real32 x, real32 y, Shader *shd) override;
        void setVec3(const std::string &name, const glm::vec3 &value, Shader *shd) override;
        void setVec3(const std::string &name, real32 x, real32 y, real32 z, Shader *shd) override;
        void setVec4(const std::string &name, const glm::vec4 &value, Shader *shd) override;
        void setVec4(const std::string &name, real32 x, real32 y, real32 z, real32 w, Shader *shd) override;
        void setMat2(const std::string &name, const glm::mat2 &mat, Shader *shd) override;
        void setMat3(const std::string &name, const glm::mat3 &mat, Shader *shd) override;
        void setMat4(const std::string &name, const glm::mat4 &mat, Shader *shd) override;

        bool32 createTexture(Texture2D *texture) override;
        bool32 createTexture(uint32 count, Texture2D *texture) override;
        bool32 createTexture2D(const char *path, Texture2D *texture) override;
        bool32 createTexture2D(const char *path, TEXTURE_TYPE tex_type, Texture2D *texture) override;
        bool32 createTexture2D(const char *path, TEXTURE_TYPE tex_type, bool32 gen_mip, Texture2D *texture) override;
        bool32 createTexture2D(const char *path, const char *dir, Texture2D *texture) override;
        bool32 createTexture2D(uint32 width, uint32 height, Texture2D* texture) override;
        bool32 createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, bool32 generate_mipmap, Texture2D* texture) override;
        bool32 createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, bool32 generate_mipmap, Texture2D* texture) override;
        bool32 createShader(const char* vertex, const char* fragment, Shader *shader) override;
        bool32 createFramebuffer(const uint32 count, Framebuffer *fbo) override;
        bool32 createRenderbuffer(const uint32 count, Framebuffer *fbo) override;
        bool32 createVertexBuffer(void *vertices, uint32 size, DRAW_TYPE draw_type, VertexBuffer *vb) override;
        bool32 createIndexBuffer(uint32* indices, uint32 size, IndexBuffer *ib) override;
        bool32 createVertexArray(VertexArray *va) override;
        bool32 createBufferLayout(std::initializer_list<BufferElement>& element, BufferLayout *buf_layout) override;
        bool32 setVertexBufferLayout(VertexBuffer *vb, BufferLayout *buf_layout) override;
        bool32 addVertexBuffer(VertexArray *va, VertexBuffer *vb) override;
        bool32 setIndexBuffer(VertexArray *va, IndexBuffer *ib) override;

        void setTextureWrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler) override;
        void setTextureSampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler) override;

        void loadTextureGpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void* image) override;
        void loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, const void* image) override;
        void loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, int data_type, const void* image) override;
        void generateTextureMipmap(TEXTURE_TYPE texture_t) override;

        void destroyTexture2D(Texture2D *tex) override;
        void destroyFramebuffer(Framebuffer *fbo) override;
        void destroyShader(uint32 id) override;
        void destroyBuffer(VertexBuffer *vb) override;
        void destroyBuffer(IndexBuffer*ib) override;

        void setDrawBuffer(uint32 type) override;
        void setDrawBuffers(uint32 count, void *pointer) override;
        void setReadBuffer(uint32 type) override;

        void checkError() override;
        void loadBindings() override;

        void startExecution() override;
        void endExecution() override;

    public:

        inline static GraphicsDeviceDX11* get_context() 
        {            
            return (GraphicsDeviceDX11*)xe_render::getDevice();
        };
        
        inline static ID3D11Device *get_api_device() { return get_context()->device; };
        inline static ID3D11DeviceContext *get_api_device_context() { return get_context()->device_context; };
    
    private:        
        ID3D11Device* device;
        ID3D11DeviceContext* device_context;
        IDXGISwapChain* swap_chain;
        ID3D11RenderTargetView* render_target_view;
        ID3D11Texture2D* back_buffer;
        ID3D11DepthStencilState* depth_stencil_state;
        ID3D11DepthStencilView* depth_stencil_view;
        ID3D11RasterizerState* raster_state;

        int gpu_memory;
    };
}