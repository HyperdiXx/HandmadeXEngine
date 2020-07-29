#pragma once

#include "xe_graphics_resource.h"

#include <glm/glm.hpp>

#define MAX_COLOR_ATT 4

namespace xe_graphics
{
    class RenderPass;

    class GraphicsDevice
    {

    public:
        virtual ~GraphicsDevice() {};

        virtual void clear(int flags) = 0;
        virtual void clearColor(real32 r, real32 g, real32 b, real32 a) = 0;
        virtual void setViewport(int32 x, int32 y, int32 width, int32 height) = 0;
        virtual void enable(int type) = 0;
        virtual void disable(int type) = 0;
        virtual void setBlendFunc(int src, int dst) = 0;
        virtual void setDepthFunc(int type) = 0;
        virtual void setCullMode(int type) = 0;
        virtual void setDepth(bool32 type) = 0;
        virtual void setLineWidth(uint32 line_width) = 0;

        virtual void drawArray(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count) = 0;
        virtual void drawIndexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void *ind) = 0;

        virtual void pushDataToBuffer(BUFFER_TYPE type, uint32 offset, uint64 size, void *data) = 0;

        virtual void activateBindTexture(TEXTURE_TYPE type, const Texture2D *texture) = 0;
        virtual void activateBindTexture(TEXTURE_TYPE type, const Cubemap *texture) = 0;
        virtual void activateTexture(uint32 index) = 0;
        virtual void bindTexture(TEXTURE_TYPE type, const Texture2D *texture) = 0;
        virtual void bindTexture(TEXTURE_TYPE type, uint32 index) = 0;
        virtual void bindShader(const Shader *Shader) = 0;
        virtual void bindBuffer(const VertexBuffer *vb) = 0;
        virtual void bindBuffer(const IndexBuffer *ib) = 0;
        virtual void bindVertexArray(const VertexArray *va) = 0;
        virtual void bindFramebuffer(const Framebuffer *fbo) = 0;
        virtual void bindRenderbuffer(const Framebuffer *fbo) = 0;
        virtual void bindForRead(const Framebuffer *fbo) = 0;
        virtual void bindForWrite(const Framebuffer *fbo) = 0;

        virtual void addColorTexture2D(Texture2D *texture, uint32 color_attachment_id, Framebuffer *fbo) = 0;
        virtual void addDepthTexture2D(Texture2D *depth, Framebuffer *fbo) = 0;
        virtual void addDepthTexture2D(uint32 w, uint32 h, Framebuffer *fbo) = 0;
        virtual void setDepthBufferAttachment(const Framebuffer *fbo) = 0;
        virtual void setDepthBufferAttachment(uint32 w, uint32 h, const Framebuffer *fbo) = 0;
        virtual void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, Texture2D *texture) = 0;
        virtual void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture) = 0;
        virtual void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture, uint32 mip) = 0;
        virtual void setRenderbuffer(int depth_compoentn, uint32 width, uint32 height) = 0;
        virtual void setFramebufferRenderbufferAttachment(const Framebuffer *fbo) = 0;

        virtual Texture2D& getTexture(uint32 number, const Framebuffer *fbo) = 0;
        virtual void checkFramebuffer() = 0;

        virtual void unbindTexture(TEXTURE_TYPE texture) = 0;
        virtual void unbindVertexArray() = 0;
        virtual void unbindShader() = 0;
        virtual void unbindFramebuffer() = 0;
        virtual void unbindBuffer(BUFFER_TYPE type) = 0;

        // Shader
        virtual void setBool(const std::string &name, bool value, Shader *shd) = 0;
        virtual void setInt(const std::string &namee, int32 value, Shader* shd) = 0;
        virtual void setFloat(const std::string& name, real32 value, Shader* shd) = 0;
        virtual void setVec2(const std::string &name, const glm::vec2 &value, Shader* shd) = 0;
        virtual void setVec2(const std::string &name, real32 x, real32 y, Shader* shd) = 0;
        virtual void setVec3(const std::string &name, const glm::vec3 &value, Shader* shd) = 0;
        virtual void setVec3(const std::string &name, real32 x, real32 y, real32 z, Shader* shd) = 0;
        virtual void setVec4(const std::string &name, const glm::vec4 &value, Shader* shd) = 0;
        virtual void setVec4(const std::string &name, real32 x, real32 y, real32 z, real32 w, Shader* shd) = 0;
        virtual void setMat2(const std::string &name, const glm::mat2 &mat, Shader* shd) = 0;
        virtual void setMat3(const std::string &name, const glm::mat3 &mat, Shader* shd) = 0;
        virtual void setMat4(const std::string &name, const glm::mat4 &mat, Shader* shd) = 0;

        virtual void startExecution() = 0;
        virtual void endExecution() = 0;
       
        virtual bool32 createTexture(Texture2D *texture) = 0;
        virtual bool32 createTexture(uint32 count, Texture2D *texture) = 0;
        virtual bool32 createTexture2D(const char *path, Texture2D* texture) = 0;
        virtual bool32 createTexture2D(const char *path, TEXTURE_TYPE tex_type, Texture2D *texture) = 0;
        virtual bool32 createTexture2D(const char *path, TEXTURE_TYPE tex_type, uint32 samples, bool32 gen_mip, Texture2D *texture) = 0;
        virtual bool32 createTexture2D(const char *path, const char* dir, Texture2D* texture) = 0;
        virtual bool32 createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, bool32 generate_mipmap, Texture2D* texture) = 0;
        virtual bool32 createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, uint32 samples, bool32 generate_mipmap, Texture2D* texture) = 0;
        virtual bool32 createTexture2D(uint32 width, uint32 height, Texture2D* texture) = 0;
        
        virtual bool32 createShader(const char* vertex, const char* fragment, Shader* Shader) = 0;
        
        virtual bool32 createFramebuffer(const uint32 count, Framebuffer *fbo) = 0;
        virtual bool32 createRenderbuffer(const uint32 count, Framebuffer *fbo) = 0;
        
        virtual bool32 createVertexBuffer(void *vertices, uint32 size, DRAW_TYPE draw_type, VertexBuffer *vb) = 0;
        
        virtual bool32 createIndexBuffer(uint32* indices, uint32 size, IndexBuffer *ib) = 0;
        virtual bool32 createIndexBuffer(Index *indices, uint32 size, IndexBuffer *ib) = 0;
        
        virtual bool32 createVertexArray(VertexArray *va) = 0;
        virtual bool32 createBufferLayout(std::initializer_list<BufferElement>& element, BufferLayout *buf_layout) = 0;
        virtual bool32 setVertexBufferLayout(VertexBuffer *vb, BufferLayout *buf_layout) = 0;
        virtual bool32 addVertexBuffer(VertexArray *va, VertexBuffer *vb) = 0;
        virtual bool32 setIndexBuffer(VertexArray *va, IndexBuffer *ib) = 0;

        virtual void setTextureWrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler) = 0;
        virtual void setTextureSampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler) = 0;

        virtual void loadTextureGpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void* image) = 0;
        virtual void loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, const void* image) = 0;
        virtual void loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, int data_type, const void* image) = 0;

        virtual void generateTextureMipmap(TEXTURE_TYPE texture_t) = 0;
        
        virtual void destroyTexture2D(Texture2D *tex) = 0;
        virtual void destroyFramebuffer(Framebuffer *fbo) = 0;
        virtual void destroyShader(uint32 id) = 0;
        virtual void destroyBuffer(VertexBuffer *vb) = 0;
        virtual void destroyBuffer(IndexBuffer *ib) = 0;

        virtual void setDrawBuffer(uint32 type) = 0;
        virtual void setDrawBuffers(uint32 count, void *pointer) = 0;
        virtual void setReadBuffer(uint32 type) = 0;
        virtual void checkError() = 0;

        virtual void loadBindings() = 0;

        inline bool32 getIsFullscreen() const { return fullscreen; }
        inline bool32 getIsVsync() const { return vsync; }
        inline Viewport& getViewport() { return vp; }
        
    protected:
        bool32 fullscreen = false;
        bool32 vsync = true;
        real32 clear_color_v[4];

        Viewport vp = {};
    };
}
