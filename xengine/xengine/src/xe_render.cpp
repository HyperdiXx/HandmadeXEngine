#include "xe_render.h"

#include "runtime/core/utility/log.h"

#include <glad/glad.h>

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
        real32 vertices[] = {
                  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
                 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };
        
        int vertex_size = sizeof(vertices) / sizeof(vertices[0]); 
        int indices_size = sizeof(indices) / sizeof(indices[0]);

        q->vertex_array = new xe_graphics::vertex_array;
        q->vertex_buffer = new xe_graphics::vertex_buffer;
        q->index_buffer = new xe_graphics::index_buffer;
        
        graphics_device->create_vertex_array(q->vertex_array);
        graphics_device->create_vertex_buffer(vertices, vertex_size, q->vertex_buffer);
        graphics_device->create_index_buffer(indices, indices_size, q->index_buffer);
        
        using namespace xe_graphics;

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list = 
        {
            { "aPos",    ElementType::Float3, },
            { "aUV",     ElementType::Float2, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(q->vertex_buffer, &buffer_layout);        
        graphics_device->add_vertex_buffer(q->vertex_array, q->vertex_buffer);
        graphics_device->set_index_buffer(q->vertex_array, q->index_buffer);
        
        return true;
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture)
    {
        if (texture != nullptr)
            graphics_device->bind_texture2d(texture);

        graphics_device->bind_shader(shd);
        
        graphics_device->bind_vertex_array(q->vertex_array);
        
        graphics_device->draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //graphics_device->unbind_vertex_array();

        //graphics_device->unbind_shader();
    }   
}

