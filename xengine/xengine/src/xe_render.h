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
    class AnimatedModel;
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

    void init_gui();

    bool32 init_common_gpu_objects();
    bool32 load_font(const char *path);
    bool32 load_shaders();
    bool32 load_free_textures();

    void clear();

    void set_device(xe_graphics::graphics_device *device);
    void set_render_pass(xe_graphics::render_pass *pass);
    void set_active_framebuffer(xe_graphics::framebuffer *fbo);
    
    xe_graphics::graphics_device* get_device();

    xe_graphics::shader *get_shader(const char* name);
    xe_graphics::texture2D *get_texture2D_resource(const char* name);

    xe_ecs::camera2d_component& get_camera2D();
    xe_ecs::camera3d_component& get_camera3D();
    
    bool32 create_quad(xe_graphics::quad *q);
    bool32 create_full_quad();
    bool32 create_skybox(xe_graphics::skybox *sky);
    bool32 create_cubemap(xe_graphics::cubemap *cube);
    bool32 create_shadow_maps(xe_graphics::shadow_map *shadow);
    bool32 create_sphere(xe_graphics::sphere *sphre);
    bool32 create_cube(xe_graphics::cube *cube);
    bool32 create_mesh(xe_assets::mesh *meh, xe_graphics::vertex *vertex_type, bool32 calculate_tspace);
    
    bool32 create_line_mesh(glm::vec3 &start, glm::vec3 &end,  xe_graphics::line *line_com);
    bool32 create_line_mesh(xe_graphics::line *line_com);

    void draw_full_quad();
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture);
    void draw_quad(xe_ecs::entity *ent, xe_graphics::shader *shd, xe_graphics::texture2D *texture);
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4& mod);
    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd);    
    void draw_mesh(xe_assets::mesh *mshs, xe_graphics::shader *shd);
   
    void draw_sphere(xe_graphics::texture2D *texture_diff);
    void draw_sphere();

    void draw_cube(xe_graphics::texture2D *texture_diff);
    void draw_cube();

    void draw_animated_model(xe_assets::AnimatedModel *anim_model, const glm::mat4 &transform);
    void update_anim(xe_assets::AnimatedModel *anim_model);

    void draw_line(xe_ecs::entity *ent);

    void draw_ent(xe_ecs::entity *ent);
    void draw_ent_static(xe_ecs::entity *ent);
    void draw_ent_with_shader(xe_ecs::entity *ent, xe_graphics::shader *shd);
    void draw_ent_primitive(xe_ecs::entity *ent);

    void draw_text(const std::string &text, glm::vec2& pos, glm::vec3& color);
    void draw_text(const std::string &text, glm::vec2& pos);
    void draw_text(const std::string &text, real32 x, real32 y);

    void draw_water_plane(xe_ecs::entity *ent);

    void draw_skybox();
    void draw_shadow_maps();

    void apply_shadow_map(xe_graphics::shadow_map *shadow);

    void apply_transform(xe_ecs::transform_component *transform, xe_graphics::shader *shd);
    void apply_dir_light(xe_graphics::shader *shd, xe_ecs::dir_light *directional_light, xe_ecs::transform_component *transform);
    void apply_spot_light(xe_graphics::shader *shd, xe_ecs::spot_light *directional_light, xe_ecs::transform_component *transform);
    void apply_point_light(xe_graphics::shader *shd, xe_ecs::point_light *directional_light, xe_ecs::transform_component *transform);
}
#endif // !XENGINE_RENDERING_H
