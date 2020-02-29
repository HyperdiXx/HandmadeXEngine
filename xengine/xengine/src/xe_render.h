#pragma once

#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

#include "xe_graphics_device.h"

namespace xe_ecs
{
    class camera2d_component;
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
    void load_shaders();
  
    void set_device(xe_graphics::graphics_device *device);
    void set_render_pass(xe_graphics::render_pass *pass);

    xe_graphics::graphics_device* get_device();
    xe_graphics::shader* get_simple_shader();
    xe_graphics::shader* get_model_shader();
    xe_ecs::camera2d_component& get_camera();
    
    bool32 create_quad(xe_graphics::quad *q);

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam);
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4& mod, XEngine::OrthoCamera *cam);
    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd, XEngine::PerspectiveCamera* camera);
    void draw_mesh(xe_assets::mesh *mshs, xe_graphics::shader *shd);
}
#endif // !XENGINE_RENDERING_H
