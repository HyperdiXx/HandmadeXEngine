#pragma once

#ifndef GRAPHICS_DEVICE_GL_H
#define GRAPHICS_DEVICE_GL_H

class GraphicsDeviceGL : public GraphicsDevice
{
public:
    GraphicsDeviceGL() {};
    GraphicsDeviceGL(HWND window, bool32 vsync = true, bool32 fullscreen = false);
    virtual ~GraphicsDeviceGL();

    void setAPI() override;

    bool32 createTexture(Texture2D *texture) override;
    bool32 createTexture(uint32 count, Texture2D *texture) override;
    bool32 createTexture2D(const char *path, Texture2D *texture) override;
    bool32 createTexture2D(const char *path, TEXTURE_TYPE tex_type, Texture2D *texture) override;
    bool32 createTexture2D(const char *path, TEXTURE_TYPE tex_type, uint32 samples, bool32 gen_mip, Texture2D *texture) override;
    bool32 createTexture2D(const char *path, const char *dir, Texture2D *texture) override;
    bool32 createTexture2D(uint32 width, uint32 height, Texture2D* texture) override;
    bool32 createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, bool32 generate_mipmap, Texture2D* texture) override;
    bool32 createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, uint32 samples, bool32 generate_mipmap, Texture2D* texture) override;

    bool32 createShader(const char* vertex, const char* fragment, Shader *Shader) override;
    bool32 createShader(const char* shader_path, Shader *Shader) override;

    uint32 compileShader(SHADER_TYPE type, std::string &shader_source) override;
    uint32 createShaderProgram(uint32 id_vs, uint32 id_pixel) override;

    bool32 createFramebuffer(const uint32 count, Framebuffer *fbo) override;
    bool32 createRenderbuffer(const uint32 count, Framebuffer *fbo) override;

    bool32 createVertexBuffer(void *vertices, uint32 size, DRAW_TYPE draw_type, VertexBuffer *vb) override;

    bool32 createIndexBuffer(uint32* indices, uint32 size, IndexBuffer *ib) override;
    bool32 createIndexBuffer(Index *indices, uint32 size, IndexBuffer *ib) override;

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

    void addColorTexture2D(Texture2D *texture, uint32 color_attachment_id, Framebuffer *fbo) override;
    void addDepthTexture2D(Texture2D *depth, Framebuffer *fbo) override;
    void addDepthTexture2D(uint32 w, uint32 h, Framebuffer *fbo) override;
    void setDepthBufferAttachment(const Framebuffer *fbo) override;
    void setDepthBufferAttachment(uint32 w, uint32 h, const Framebuffer *fbo) override;
    void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, Texture2D *texture) override;
    void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture) override;
    void setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D *texture, uint32 mip) override;
    void setRenderbuffer(int depth_compoentn, uint32 width, uint32 height) override;
    void setFramebufferRenderbufferAttachment(const Framebuffer *fbo) override;

    void setDrawBuffer(uint32 type) override;
    void setDrawBuffers(uint32 count, void *pointer) override;
    void setReadBuffer(uint32 type) override;
    void checkError() override;

    Texture2D& getTexture(uint32 number, const Framebuffer *fbo) override;
    void checkFramebuffer() override;

    void destroyTexture2D(Texture2D *tex) override;
    void destroyFramebuffer(Framebuffer *fbo) override;
    void destroyShader(uint32 id) override;
    void destroyBuffer(VertexBuffer *vb) override;
    void destroyBuffer(IndexBuffer *ib) override;

    void loadBindings() override;

private:

};
#endif // !GRAPHICS_DEVICE_GL_H

