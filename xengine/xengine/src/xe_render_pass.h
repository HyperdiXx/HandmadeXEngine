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

    class RenderPass2D : public RenderPass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        void setScene(xe_scene::Scene *scene) override {};
        void setColorTexture(Texture2D *clrTex) override { color_texture = clrTex;  };

        Texture2D *getColorTexture() override { return color_texture; };
    private:
        Texture2D *color_texture;
        Shader* simple_shader;
        xe_ecs::Entity main_ent;      
    };

    class RenderPass3D : public RenderPass
    {
    public:

        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        void setScene(xe_scene::Scene *scene) override { current_scene = scene; };
        void setColorTexture(Texture2D *clrTex) override { color_texture = *clrTex; };

        Texture2D *getColorTexture() override { return &color_texture; };

    private:            
        xe_graphics::Framebuffer fbo;
        xe_graphics::Texture2D color_texture;
        xe_scene::Scene *current_scene;
    };

    class PbrPass : public RenderPass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        void setScene(xe_scene::Scene *scene) override { current_scene = scene; };
        void setColorTexture(Texture2D *clrTex) override { color_texture = *clrTex; };

        Texture2D *getColorTexture() override { return &color_texture; };
    private:
        xe_graphics::Framebuffer fbo;
        xe_graphics::Texture2D env_cubemap;
        xe_graphics::Texture2D irr_map;
        xe_graphics::Texture2D prefilter_map;
        xe_graphics::Texture2D brdf_lut;
        xe_graphics::Texture2D color_texture;
        xe_scene::Scene *current_scene;
    };

    class GammaCorrectionPass : public RenderPass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        void setScene(xe_scene::Scene *scene) override { current_scene = scene; };
        void setColorTexture(Texture2D *clrTex) override { color_texture = clrTex; };

        Texture2D *getColorTexture() override { return color_texture; };

    private:
        Shader* gmshd;
        Texture2D *color_texture;
        xe_scene::Scene *current_scene;
    };

    class ShadowMapPass
    {
    public:
        void init();
        void clear();

        void unloadResources();

        void render();

        void update(real32 dt);

        void bindDepthTexture() const;

        void setScene(xe_scene::Scene *active_sc) { current_scene = active_sc; };

    private:
        xe_graphics::ShadowMap *shadow;
        xe_scene::Scene *current_scene;

        glm::vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
    };
}
