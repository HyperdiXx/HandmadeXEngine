#include "xe_render.h"

#include "runtime/core/utility/log.h"
#include "xe_ecs.h"
#include "xe_assets.h"
#include "perspective_camera.h"
#include "ortho_camera.h"

#include <glad/glad.h>



namespace xe_render
{
    xe_graphics::graphics_device *graphics_device = nullptr;

    xe_graphics::shader *simple_shader = nullptr;
    xe_graphics::shader *model_shader = nullptr;
    
    xe_graphics::render_pass *active_render_pass = nullptr;
    xe_graphics::framebuffer *active_framebuffer = nullptr;
 
    using namespace xe_graphics;

    void init_render()
    {
        xe_ecs::camera2d_component camera = get_camera();

        load_shaders();
    }

    void load_shaders()
    {
        xe_graphics::graphics_device *device = get_device();

        simple_shader = new xe_graphics::shader();
        model_shader = new xe_graphics::shader();

        device->create_shader("shaders/simple2d.vs", "shaders/simple2d.fs", simple_shader);
        device->create_shader("shaders/model3d.vs", "shaders/model3d.fs", model_shader);

        xe_utility::info("Shaders was loaded!!!");
    }

    void clear()
    {

    }

    xe_ecs::camera2d_component& get_camera() 
    {
        static xe_ecs::camera2d_component camera;
        return camera;
    };
    
    void set_device(xe_graphics::graphics_device *device)
    {
        graphics_device = device;
    }

    void set_render_pass(xe_graphics::render_pass *pass)
    {
        active_render_pass = pass;
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

    bool32 create_mesh(xe_assets::mesh *meh)
    {
        return bool32();
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

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam)
    {
        if (texture != nullptr)
            graphics_device->bind_texture2d(texture);

        glm::mat4 model = glm::mat4(1.0f);
        graphics_device->bind_shader(shd);

        model = glm::translate(model, glm::vec3(300, 200, 0));
        model = glm::scale(model, glm::vec3(100, 100, 100));

        glm::mat4 view_projection = cam->getViewProjection();
        graphics_device->set_mat4("viewproj", view_projection, shd);
        graphics_device->set_mat4("model", model, shd);

        graphics_device->bind_vertex_array(q->vertex_array);
        
        graphics_device->draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4 &mod, XEngine::OrthoCamera *cam)
    {
        if (texture != nullptr)
            graphics_device->activate_bind_texture2d(texture);

        graphics_device->bind_shader(shd);

        glm::mat4 view_projection = cam->getViewProjection();
        graphics_device->set_mat4("viewproj", view_projection, shd);
        graphics_device->set_mat4("model", mod, shd);

        graphics_device->bind_vertex_array(q->vertex_array);

        graphics_device->draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd, XEngine::PerspectiveCamera *cam)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        device->enable(GL_DEPTH_TEST);

        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -5.0f, -10.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(0.4f, 0.4f, 0.4f));
        
        glm::mat4 view_matrix = cam->getViewMatrix();
        glm::mat4 proj_matrix = cam->getProjectionMatrix();

        device->bind_shader(shd);
        device->set_mat4("viewproj", proj_matrix * view_matrix, shd);
        device->set_mat4("model", model_matrix, shd);

        xe_assets::node *root = mod->root;

        for (uint32 i = 0; i < root->children.size(); i++)
        {
            xe_assets::node* curr_node = root->children[i];

            for (uint32 j = 0; j < curr_node->meshes.size(); j++)
            {
                xe_assets::mesh *cur_mesh = curr_node->meshes.at(j);
                draw_mesh(cur_mesh, shd);
            }
        }

        device->unbind_shader();

        device->disable(GL_DEPTH_TEST);
    }

    void draw_mesh(xe_assets::mesh *msh, xe_graphics::shader *shd)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        uint32 diffuseN = 1;
        uint32 normalN = 1;
        uint32 specularN = 1;

        for (uint32 i = 0; i < msh->mesh_textures.size(); i++)
        {
            // @Refactor!!!
            xe_graphics::texture2D *mesh_texture = msh->mesh_textures[i].texture;
            device->activate_texture2d(i);

            std::string name = msh->mesh_textures[i].type;
            std::string num;

            if (name == "tex_diff")
                num = std::to_string(diffuseN++);
            else if (name == "tex_norm")
                num = std::to_string(normalN++);
            else if (name == "tex_spec")
                num = std::to_string(specularN++);

            device->set_int((name + num).c_str(), i, shd);
            device->bind_texture2d(mesh_texture);
        }

        if (msh->vertices.size() > 0)
        {
            glBindVertexArray(msh->vao);
            device->draw_indexed(GL_TRIANGLES, msh->indices.size(), GL_UNSIGNED_INT, 0);
            //glBindVertexArray(0);
        }
    }
}

