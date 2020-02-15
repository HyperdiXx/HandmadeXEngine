#include "xe_render.h"

#include "runtime/core/utility/log.h"

namespace xe_render
{
    xe_graphics::graphics_device *graphics_device = nullptr;

    xe_graphics::shader *simple_shader = nullptr;
    xe_graphics::shader *model_shader = nullptr;
    
    void init_render()
    {
        xe_ecs::camera_component camera = get_camera();

        load_shaders();
    }

    void load_shaders()
    {
        xe_graphics::graphics_device *device = get_device();

        simple_shader = new xe_graphics::shader();
        model_shader = new xe_graphics::shader();

        device->create_shader("shaders/simple2d.vs", "shaders/simple2d.fs", simple_shader);
        device->create_shader("shaders/simplemodel.vs", "shaders/simplemodel.fs", model_shader);

        xe_utility::info("Shaders was loaded!!!");
    }

    void clear()
    {

    }

    xe_ecs::camera_component& get_camera() 
    {
        static xe_ecs::camera_component camera;
        return camera;
    };
    
    void set_device(xe_graphics::graphics_device *device)
    {
        graphics_device = device;
    }

    xe_graphics::graphics_device* get_device() { return graphics_device; }

    xe_graphics::shader *get_simple_shader()
    {
        return simple_shader;
    }

    xe_graphics::shader *get_model_shader()
    {
        return model_shader;
    }
     
    bool32 create_quad(xe_graphics::quad *q)
    {       
        real32 vertices[] =
        {
              0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
              0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
             -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
             -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
        };

        uint32 indices[] =
        {
           0, 1, 3,
           1, 2, 3
        };

        graphics_device->create_vertex_array(&q->vertex_array);
        graphics_device->create_vertex_buffer(vertices, 20, &q->vertex_buffer);
        graphics_device->create_index_buffer(indices, 6, &q->index_buffer);
        
        using namespace xe_graphics;

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list = 
        {
            { "aPos", ElementType::Float3, },
            { "aUV",  ElementType::Float2, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(&q->vertex_buffer, &buffer_layout);
        graphics_device->add_vertex_buffer(&q->vertex_array, &q->vertex_buffer);
        graphics_device->set_index_buffer(&q->vertex_array, &q->index_buffer);

        return true;
    }
    

}

