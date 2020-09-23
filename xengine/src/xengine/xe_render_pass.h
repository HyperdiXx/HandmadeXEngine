#pragma once

#ifndef XE_RENDER_PASS_H
#define XE_RENDER_PASS_H

#include <vector>

namespace xe_scene
{
    struct Scene;
}

namespace xe_graphics
{
    struct Framebuffer;
    struct Shader;

    class RenderPassData
    {
    public:
        RenderPassData() = default;
        ~RenderPassData() {};

        void setFramebuffer(Framebuffer *data);
        void setShader(Shader *shd);

        inline Framebuffer *getPassFramebuffer() { return fbo; };
        inline Shader *getPassShader() { return shd; }
    private:
        Framebuffer *fbo;
        Shader *shd;

        std::vector<RenderPassData*> sub_passes;
    };

    class RenderPass
    {
    public:
        virtual ~RenderPass() {};

        virtual void init() = 0;
        virtual void applyPass() = 0;

        virtual const RenderPassData &getRenderPassData() const = 0;
    };
}

#endif // !XE_RENDER_PASS_H
