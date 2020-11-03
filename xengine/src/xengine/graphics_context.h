#pragma once

#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

class GraphicsContext
{
public:

    virtual ~GraphicsContext() {};

    virtual void clear(int flags) = 0;
    virtual void clearColor(real32 r, real32 g, real32 b, real32 a) = 0;
    virtual void clearColor(const Vec4& color) = 0;
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

    virtual void pushDataToBuffer(uint32 index, BUFFER_TYPE type, uint32 offset, uint64 size, void *data) = 0;

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

    virtual void unbindTexture(TEXTURE_TYPE texture) = 0;
    virtual void unbindVertexArray() = 0;
    virtual void unbindShader() = 0;
    virtual void unbindFramebuffer() = 0;
    virtual void unbindBuffer(BUFFER_TYPE type) = 0;

    // Shader
    virtual void setBool(const uint32 loc, bool value) = 0;
    virtual void setInt(const uint32 loc, int32 value) = 0;
    virtual void setFloat(const uint32 loc, real32 value) = 0;
    virtual void setVec2(const uint32 loc, const Vec2 &value) = 0;
    virtual void setVec2(const uint32 loc, real32 x, real32 y) = 0;
    virtual void setVec3(const uint32 loc, const Vec3 &value) = 0;
    virtual void setVec3(const uint32 loc, real32 x, real32 y, real32 z) = 0;
    virtual void setVec4(const uint32 loc, const Vec4 &value) = 0;
    virtual void setVec4(const uint32 loc, real32 x, real32 y, real32 z, real32 w) = 0;
    virtual void setMat2(const uint32 loc, const Matrix2x2 &mat) = 0;
    virtual void setMat3(const uint32 loc, const Matrix3x3 &mat) = 0;
    virtual void setMat4(const uint32 loc, const Matrix4x4 &mat) = 0;

    virtual int getBufferLocation(uint32 id, const char *name) = 0;
    virtual void setShaderBuffer(const ShaderUniformProperty *prop_type) = 0;

    virtual void startExecution() = 0;
    virtual void endExecution() = 0;

    inline bool32 getIsFullscreen() const { return fullscreen; }
    inline bool32 getIsVsync() const { return vsync; }
    inline Viewport& getViewport() { return vp; }

protected:
    Viewport vp = {};
    real32 clear_color_v[4];
    
    bool32 fullscreen = false;
    bool32 vsync = true;
};
#endif