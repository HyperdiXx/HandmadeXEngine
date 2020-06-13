#pragma once

#include "xe_graphics_resource.h"
#include "xe_ecs.h"

namespace xe_scene
{
    struct Scene;
}

namespace xe_graphics
{ 
    class Layer
    {
    public:

        virtual ~Layer() {}

        virtual void init() = 0;

        virtual void render() = 0;

        virtual void update(real32 dt) = 0;

    };

    class Layer2D : public Layer
    {

    };

    class Layer3D : public Layer
    {

    };

    class GUILayer : public Layer
    {
    public:

        void init() override;

        void render() override;

        void update(real32 dt) override;
    };

    class RenderPass
    {
    public:

        virtual ~RenderPass() {}

        virtual void init() = 0;
        virtual void clear() = 0;

        virtual void render() = 0;

        virtual void update(real32 dt) = 0;

    private:
        
    };

    class RenderPass2D : public RenderPass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        const Texture2D *getResultTexture() { return result_texture; };
    private:
        Texture2D *result_texture;
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

        void set_scene(xe_scene::Scene *scene) { current_scene = scene; };
       
        inline xe_graphics::Texture2D& get_color_texture() { return color_texture; }
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

        void setColorTexture(Texture2D *tex) { texture = tex; }
    private:
        Shader* gmshd;
        Texture2D *texture;
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
