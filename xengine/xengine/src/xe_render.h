#pragma once

#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

#include "xe_graphics_device.h"

namespace xe_ecs
{
    class camera2d_component;
    class camera3d_component;
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
    void init_render();
    void clear();
    bool32 load_shaders();
  
    void set_device(xe_graphics::graphics_device *device);
    void set_render_pass(xe_graphics::render_pass *pass);
    void set_active_framebuffer(xe_graphics::framebuffer *fbo);
    
    xe_graphics::graphics_device* get_device();
    xe_graphics::shader* get_simple_shader();
    xe_graphics::shader* get_model_shader();
    xe_graphics::shader* get_gamma_correction_shader();

    xe_ecs::camera2d_component& get_camera2D();
    xe_ecs::camera3d_component& get_camera3D();
    
    bool32 create_quad(xe_graphics::quad *q);
    bool32 create_full_quad();

    void draw_full_quad();
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam);
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4& mod, XEngine::OrthoCamera *cam);
    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd, XEngine::PerspectiveCamera* camera);
    void draw_mesh(xe_assets::mesh *mshs, xe_graphics::shader *shd);
}
#endif // !XENGINE_RENDERING_H
