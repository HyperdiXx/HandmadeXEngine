#include "xe_render_pass.h"

namespace xe_graphics
{
    void RenderPassData::setFramebuffer(Framebuffer *data)
    {
        this->fbo = data;
    }

    void RenderPassData::setShader(Shader *shd)
    {
        this->shd = shd;
    }
}
