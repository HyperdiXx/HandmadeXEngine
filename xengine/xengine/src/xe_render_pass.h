#pragma once

#include "xe_graphics_resource.h"
#include "xe_ecs.h"

namespace xe_scene
{
    struct Scene;
}

namespace xe_graphics
{ 
    class RenderPass
    {
    public:

        virtual ~RenderPass() {}

        virtual void init() = 0;
        virtual void clear() = 0;

        virtual void render() = 0;

        virtual void update(real32 dt) = 0;

        virtual void setScene(xe_scene::Scene *scene) = 0;
        virtual void setColorTexture(Texture2D *clrTex) = 0;
        virtual Texture2D *getColorTexture() = 0;
    private:
        
    };
}
