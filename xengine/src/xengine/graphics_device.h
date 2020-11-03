#pragma once

#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#define MAX_COLOR_ATT 4

class RenderPass;

class GraphicsDevice
{
    friend class GraphicsContext;
public:
    
    virtual ~GraphicsDevice() {};

    virtual void setAPI() = 0;
    
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
    virtual bool32 createShader(const char* shader_path, Shader *Shader) = 0;
    
    virtual uint32 compileShader(SHADER_TYPE type, std::string &shader_source) = 0;
    virtual uint32 createShaderProgram(uint32 id_vs, uint32 id_pixel) = 0;
 
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

    virtual void setDrawBuffer(uint32 type) = 0;
    virtual void setDrawBuffers(uint32 count, void *pointer) = 0;
    virtual void setReadBuffer(uint32 type) = 0;
    virtual void checkError() = 0;

    virtual Texture2D& getTexture(uint32 number, const Framebuffer *fbo) = 0;
    virtual void checkFramebuffer() = 0;

    virtual void destroyTexture2D(Texture2D *tex) = 0;
    virtual void destroyFramebuffer(Framebuffer *fbo) = 0;
    virtual void destroyShader(uint32 id) = 0;
    virtual void destroyBuffer(VertexBuffer *vb) = 0;
    virtual void destroyBuffer(IndexBuffer *ib) = 0;
    
    virtual void loadBindings() = 0;

protected:
    API_TYPE api;
};
#endif // !GRAPHICS_DEVICE_H


