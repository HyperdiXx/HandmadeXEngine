#pragma once

#ifndef GRAPHICS_CONTEXT_GL_H
#define GRAPHICS_CONTEXT_GL_H

class GraphicsContextGL : public GraphicsContext
{
public:
    GraphicsContextGL() {};
    virtual ~GraphicsContextGL() {};

    void clear(int flags) override;
    void clearColor(real32 r, real32 g, real32 b, real32 a) override;
    void clearColor(const Vec4& color) override;
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

    void pushDataToBuffer(uint32 index, BUFFER_TYPE type, uint32 offset, uint64 size, void *data) override;

    void activateBindTexture(TEXTURE_TYPE type, const Texture2D *texture) override;
    void activateBindTexture(TEXTURE_TYPE type, const Cubemap *texture) override;
    void activateTexture(uint32 index) override;
    void bindTexture(TEXTURE_TYPE type, const Texture2D *tetxture) override;
    void bindTexture(TEXTURE_TYPE type, uint32 index);
    void bindShader(const Shader *Shader) override;
    void bindBuffer(const VertexBuffer *vb) override;
    void bindBuffer(const IndexBuffer *ib) override;
    void bindVertexArray(const VertexArray *va) override;
    void bindFramebuffer(const Framebuffer *fbo) override;
    void bindRenderbuffer(const Framebuffer *fbo) override;
    void bindForRead(const Framebuffer *fbo) override;
    void bindForWrite(const Framebuffer *fbo) override;

    void unbindTexture(TEXTURE_TYPE texture) override;
    void unbindVertexArray() override;
    void unbindShader() override;
    void unbindFramebuffer() override;
    void unbindBuffer(BUFFER_TYPE type) override;

    void setBool(const uint32 loc, bool value) override;
    void setInt(const uint32 loc, int32 value) override;
    void setFloat(const uint32 loc, real32 value) override;
    void setVec2(const uint32 loc, const Vec2 &value) override;
    void setVec2(const uint32 loc, real32 x, real32 y) override;
    void setVec3(const uint32 loc, const Vec3 &value) override;
    void setVec3(const uint32 loc, real32 x, real32 y, real32 z) override;
    void setVec4(const uint32 loc, const Vec4 &value) override;
    void setVec4(const uint32 loc, real32 x, real32 y, real32 z, real32 w) override;
    void setMat2(const uint32 loc, const Matrix2x2 &mat) override;
    void setMat3(const uint32 loc, const Matrix3x3 &mat) override;
    void setMat4(const uint32 loc, const Matrix4x4 &mat) override;

    int getBufferLocation(uint32 id, const char *name) override;
    void setShaderBuffer(const ShaderUniformProperty *prop_type) override;

    void startExecution() override;
    void endExecution() override;

private:
    GPUHandler last_bound_unit_texture;
    GPUHandler last_activated_texture;
    GPUHandler last_bound_unit_vao;
    GPUHandler last_bound_unit_vbuffer;
    GPUHandler last_bound_unit_ibuffer;
    GPUHandler last_bound_unit_fbo;
    GPUHandler last_bound_unit_shader;
};
#endif // !GRAPHICS_CONTEXT_GL

