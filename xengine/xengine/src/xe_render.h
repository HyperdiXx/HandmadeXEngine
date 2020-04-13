#pragma once

#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

#include "xe_graphics_device.h"

namespace xe_ecs
{
    class entity;
    class camera2d_component;
    class camera3d_component;
    class dir_light;
    class spot_light;
    class point_light;
    class transform_component;
}

namespace xe_assets
{
    struct model;
    struct mesh;
}

namespace XEngine
{
    class PerspectiveCamera;
    class OrthoCamera;
}

namespace xe_render
{
    static const glm::mat4 IDENTITY_MATRIX = glm::mat4(1.0f);

    namespace ftgl 
    {
        struct texture_atlas_t;
        struct texture_font_t;
    }

    void init_render_gl();
    void init_render_dx11();

    bool32 init_common_gpu_objects();
    bool32 load_font(const char *path);
    bool32 load_shaders();

    void clear();

    void set_device(xe_graphics::graphics_device *device);
    void set_render_pass(xe_graphics::render_pass *pass);
    void set_active_framebuffer(xe_graphics::framebuffer *fbo);
    
    xe_graphics::graphics_device* get_device();
    xe_graphics::shader* get_simple_shader();
    xe_graphics::shader* get_model_shader();
    xe_graphics::shader* get_gamma_correction_shader();
    xe_graphics::shader* get_post_proc_shader();
    xe_graphics::shader* get_color_shader();
    xe_graphics::shader* get_shadow_map_shader();
    xe_graphics::shader* get_shadow_map_depth_shader();

    xe_ecs::camera2d_component& get_camera2D();
    xe_ecs::camera3d_component& get_camera3D();
    
    bool32 create_quad(xe_graphics::quad *q);
    bool32 create_full_quad();
    bool32 create_skybox(xe_graphics::skybox *sky);
    bool32 create_cubemap(xe_graphics::cubemap *cube);
    bool32 create_shadow_maps(xe_graphics::shadow_map *shadow);

    void draw_full_quad();
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam);
    void draw_quad(xe_ecs::entity *ent, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam);
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4& mod, XEngine::OrthoCamera *cam);
    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd, XEngine::PerspectiveCamera* camera);    
    void draw_mesh(xe_assets::mesh *mshs, xe_graphics::shader *shd);

    void draw_ent(xe_ecs::entity *ent);
    void draw_ent(xe_ecs::entity *ent, glm::vec3 *color);
    void draw_ent_with_shader(xe_ecs::entity *ent, xe_graphics::shader *shd);

    void draw_text(const std::string &text, glm::vec2& pos, glm::vec3& color);
    void draw_text(const std::string &text, glm::vec2& pos);
    void draw_text(const std::string &text, real32 x, real32 y);

    void draw_skybox();
    void draw_shadow_maps();

    void apply_shadow_map(xe_graphics::shadow_map *shadow);

    void apply_transform(xe_ecs::transform_component *transform, xe_graphics::shader *shd);
    void apply_dir_light(xe_graphics::shader *shd, xe_ecs::dir_light *directional_light, xe_ecs::transform_component *transform);
    void apply_spot_light(xe_graphics::shader *shd, xe_ecs::spot_light *directional_light, xe_ecs::transform_component *transform);
    void apply_point_light(xe_graphics::shader *shd, xe_ecs::point_light *directional_light, xe_ecs::transform_component *transform);
}
#endif // !XENGINE_RENDERING_H
