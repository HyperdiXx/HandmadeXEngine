#pragma once

#include "xe_graphics_resource.h"
#include "xe_ecs.h"

namespace xe_scene
{
    struct scene;
}

namespace xe_graphics
{
    
    class render_pass
    {
    public:

        virtual ~render_pass() {}

        virtual void init() = 0;
        virtual void clear() = 0;

        virtual void render() = 0;

        virtual void update(real32 dt) = 0;

    private:
        
    };

    class render_pass2D : public render_pass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        const texture2D *get_result_texture() { return result_texture; };

        //inline XEngine::OrthoCamera& get_camera2d() { return camera2D; };
    private:
        //XEngine::OrthoCamera camera2D;
        texture2D *result_texture;
        shader* simple_shader;
        xe_ecs::entity main_ent;      
    };

    class render_pass3D : public render_pass
    {
    public:

        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        void set_scene(xe_scene::scene *scene) { current_scene = scene; };
       
        inline xe_graphics::texture2D& get_color_texture() { return color_texture; }
    private:            
        xe_graphics::framebuffer fbo;
        xe_graphics::texture2D color_texture;
        xe_scene::scene *current_scene;
    };

    class pbr_pass : public render_pass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;
    
    private:
        xe_graphics::framebuffer fbo;
        xe_graphics::texture2D env_cubemap;
        xe_graphics::texture2D irr_map;
        xe_graphics::texture2D prefilter_map;
        xe_graphics::texture2D brdf_lut;
        xe_graphics::texture2D color_texture;
        xe_scene::scene *current_scene;
    };

    class gamma_correction_pass : public render_pass
    {
    public:
        void init() override;
        void clear() override;

        void render() override;

        void update(real32 dt) override;

        void set_color_texture(texture2D *tex) { texture = tex; }
    private:
        shader* gmshd;
        texture2D *texture;
    };

    class shadow_map_pass
    {
    public:
        void init();
        void clear();

        void unload_resources();

        void render();

        void update(real32 dt);

        void bind_depth_texture() const;

        void set_scene(xe_scene::scene *active_sc) { current_scene = active_sc; };

    private:
        xe_graphics::shadow_map *shadow;
        xe_scene::scene *current_scene;

        glm::vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
    };
}
