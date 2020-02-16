
#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

#include "xe_ecs.h"
#include "xe_graphics_device.h"

namespace xe_render
{
    void init_render();
    void clear();
    void load_shaders();

    xe_ecs::camera_component& get_camera();
    
    void set_device(xe_graphics::graphics_device *device);
    xe_graphics::graphics_device* get_device();
    xe_graphics::shader* get_simple_shader();
    xe_graphics::shader* get_model_shader();

    bool32 create_quad(xe_graphics::quad *q);
    
    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture);



}
#endif // !XENGINE_RENDERING_H
