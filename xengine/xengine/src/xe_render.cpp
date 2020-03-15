#include "xe_render.h"

#include "runtime/core/utility/log.h"
#include "xe_ecs.h"
#include "xe_assets.h"
#include "perspective_camera.h"
#include "ortho_camera.h"

#include <xenpch.h>

namespace xe_render
{
    static glm::vec4 clear_color;
    static xe_graphics::viewport main_view_port;
 
    static glm::vec3 default_text_color = glm::vec3(1.0f, 1.0f, 1.0f);
    static real32 default_text_scale = 1.0f;

    xe_graphics::graphics_device *graphics_device = nullptr;

    xe_graphics::shader *simple_shader = nullptr;
    xe_graphics::shader *model_shader = nullptr;
    xe_graphics::shader *gamma_correction_shader = nullptr;
    xe_graphics::shader *color = nullptr;
    xe_graphics::shader *text_shader = nullptr;
    
    xe_graphics::render_pass *active_render_pass = nullptr;
    xe_graphics::framebuffer *active_framebuffer = nullptr;

    xe_graphics::vertex_array quadVao;
    std::map<GLchar, xe_graphics::character> characters_map;

    using namespace xe_graphics;

    void init_render()
    {
        xe_ecs::camera2d_component camera = get_camera2D();

        if(!load_shaders())
            xe_utility::error("Failed to init shader module");

        if (!load_font("engineassets/fonts/arial.ttf"))
            xe_utility::error("Failed to init font module");
    }

    bool32 load_font(const char *path)
    {
        FT_Library lib;

        if (FT_Init_FreeType(&lib))
            xe_utility::error("FREETYPE: Couldnt init free type lib");

        FT_Face face;

        if (FT_New_Face(lib, path, 0, &face))
            xe_utility::error("FREETYPE: Failed to load font");

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (int c = 0; c < 128; ++c)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                xe_utility::error("FREETYPE: Failed to load char");
                continue;
            }

            //graphics_device->create_texture2D(face->glyph->bitmap.width, face->glyph->bitmap.rows, texture_sym);

            uint32 tex_id;

            glGenTextures(1, &tex_id);
            glBindTexture(GL_TEXTURE_2D, tex_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            character chacter =
            {
                tex_id,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            characters_map.insert(std::pair<GLchar, character>(c, chacter));
        }

        graphics_device->unbind_texture2d();
        FT_Done_Face(face);
        FT_Done_FreeType(lib);

        vertex_array *va = new vertex_array();
        vertex_buffer *vb = new vertex_buffer();
        graphics_device->create_vertex_array(va);
        graphics_device->bind_vertex_array(va);

        graphics_device->create_vertex_buffer(NULL, 24, DRAW_TYPE::DYNAMIC, vb);

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list =
        {
            { "aPos",    ElementType::Float4, },            
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(vb, &buffer_layout);
        graphics_device->add_vertex_buffer(va, vb);

        graphics_device->unbind_buffer(BUFFER_TYPE::VERTEX);
        graphics_device->unbind_vertex_array();

        glm::mat4 ortho = glm::mat4(1.0f);

        ortho = glm::ortho(0.0f, float(WINDOWWIDTH), 0.0f, float(WINDOWHEIGHT), -1.0f, 1.0f);

        graphics_device->bind_shader(text_shader);
        graphics_device->set_mat4("projection", ortho, text_shader);

        return true;
    }

    bool32 load_shaders()
    {
        xe_graphics::graphics_device *device = get_device();

        simple_shader = new xe_graphics::shader();
        model_shader = new xe_graphics::shader();
        gamma_correction_shader = new xe_graphics::shader();
        color = new xe_graphics::shader();
        text_shader = new xe_graphics::shader();

        bool32 res = device->create_shader("shaders/simple2d.vs", "shaders/simple2d.fs", simple_shader);
        res = device->create_shader("shaders/model3d.vs", "shaders/model3d.fs", model_shader);       
        res = device->create_shader("shaders/quad.vs", "shaders/gamma_correction.fs", gamma_correction_shader);
        res = device->create_shader("shaders/model3d.vs", "shaders/color.fs", color);
        res = device->create_shader("shaders/text.vs", "shaders/text.fs", text_shader);

        if (!res)
        {
            xe_utility::error("loading shader");
            return false;
        }
    
        xe_utility::info("Shaders was loaded!!!");
        return true;
    }

    void clear()
    {

    }

    xe_ecs::camera2d_component& get_camera2D() 
    {
        static xe_ecs::camera2d_component camera2D;
        return camera2D;
    }
    
    xe_ecs::camera3d_component& get_camera3D()
    {
        static xe_ecs::camera3d_component camera3D;
        return camera3D;
    };    
    
    void set_device(xe_graphics::graphics_device *device)
    {
        graphics_device = device;
    }

    void set_render_pass(xe_graphics::render_pass *pass)
    {
        active_render_pass = pass;
    }

    void set_active_framebuffer(xe_graphics::framebuffer *fbo)
    {
        active_framebuffer = fbo;
    }

    void set_clear_color(real32 r, real32 g, real32 b, real32 a)
    {

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

    xe_graphics::shader *get_gamma_correction_shader()
    {
        return gamma_correction_shader;
    }

    xe_graphics::shader * get_color_shader()
    {
        return color;
    }

    bool32 create_mesh(xe_assets::mesh *meh)
    {
        return bool32();
    }

    bool32 create_quad(xe_graphics::quad *q)
    {   
        real32 vertices[] = 
        {
                  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
                 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = 
        {
            0, 1, 3,
            1, 2, 3
        };
        
        int vertex_size = sizeof(vertices) / sizeof(vertices[0]); 
        int indices_size = sizeof(indices) / sizeof(indices[0]);

        q->vertex_array = new xe_graphics::vertex_array;
        q->vertex_buffer = new xe_graphics::vertex_buffer;
        q->index_buffer = new xe_graphics::index_buffer;
        
        graphics_device->create_vertex_array(q->vertex_array);
        graphics_device->create_vertex_buffer(vertices, vertex_size, DRAW_TYPE::STATIC, q->vertex_buffer);
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

    bool32 create_full_quad()
    {
        glGenVertexArrays(1, &quadVao.id);

        return true;
    }

    void draw_full_quad()
    {
        graphics_device->bind_vertex_array(&quadVao);
        graphics_device->draw_array(GL_TRIANGLES, 0, 6);
        graphics_device->unbind_vertex_array();
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
        graphics_device->set_mat4("mvp", view_projection * model, shd);

        graphics_device->bind_vertex_array(q->vertex_array);        
        graphics_device->draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_quad(xe_ecs::entity *ent, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam)
    {
        using namespace xe_ecs;
        quad_component* mesh = ent->find_component<quad_component>();
        transform_component *tr = ent->find_component<transform_component>();

        if (texture != nullptr)
            graphics_device->activate_bind_texture2d(texture);

        if (mesh == nullptr)
            return;

        graphics_device->bind_shader(shd);

        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, tr->position);
        model_matrix = glm::scale(model_matrix, tr->scale);

        glm::mat4 view_projection = cam->getViewProjection();
        glm::mat4 mvp = view_projection * model_matrix;

        graphics_device->set_mat4("mvp", mvp, shd);

        graphics_device->bind_vertex_array(mesh->quad_mesh->vertex_array);

        graphics_device->draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4 &mod, XEngine::OrthoCamera *cam)
    {
        if (texture != nullptr)
            graphics_device->activate_bind_texture2d(texture);

        graphics_device->bind_shader(shd);

        glm::mat4 view_projection = cam->getViewProjection();
        glm::mat4 mvp = view_projection * mod;

        graphics_device->set_mat4("mvp", mvp, shd);

        graphics_device->bind_vertex_array(q->vertex_array);

        graphics_device->draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_text(const std::string &text, real32 x, real32 y, glm::vec3 &color, real32 scale)
    {
        graphics_device->enable(GL_BLEND);
        graphics_device->set_blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        graphics_device->bind_shader(text_shader);
        graphics_device->set_vec3("color", color, text_shader);
        
        graphics_device->activate_texture2d(0);
        glBindVertexArray(1);
       
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {            
            character ch = characters_map.at(*c);

            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;

            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };

            //graphics_device->bind_texture2d();

            glBindTexture(GL_TEXTURE_2D, ch.textureID);

            glBindBuffer(GL_ARRAY_BUFFER, 1);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            graphics_device->draw_array(GL_TRIANGLES, 0, 6);

            x += (ch.Advance >> 6) * scale;
        }

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_texture2d();

        graphics_device->disable(GL_BLEND);
    }

    void draw_text(const std::string &text, glm::vec2 &pos)
    {
        draw_text(text, pos.x, pos.y, default_text_color, default_text_scale);
    }

    void draw_text(const std::string &text, real32 x, real32 y)
    {
        draw_text(text, x, y, default_text_color, default_text_scale);
    }

    void apply_transform(xe_ecs::transform_component *transform, xe_graphics::shader *shd, XEngine::PerspectiveCamera *camera)
    {
        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, transform->position);
        model_matrix = glm::scale(model_matrix, transform->scale);

        glm::mat4 view_matrix = camera->getViewMatrix();
        glm::mat4 proj_matrix = camera->getProjectionMatrix();

        glm::mat4 mvp = proj_matrix * view_matrix * model_matrix;

        graphics_device->set_mat4("mvp", mvp, shd);
        graphics_device->set_mat4("model", model_matrix, shd);
    }

    void apply_dir_light(xe_graphics::shader *shd, xe_ecs::dir_light *directional_light, xe_ecs::transform_component *transform)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        glm::vec3 light_color = glm::vec3(1.0f);
        real32 intens = 1.0f;

        if (directional_light)
        {
            light_color = directional_light->color;
            intens = directional_light->entensity;
        }

        device->bind_shader(shd);
        device->set_float("intensity", intens, shd);
        device->set_vec3("dir_light_color", light_color, shd);
        device->set_vec3("light_pos", transform->position, shd);
    }

    void apply_spot_light(xe_graphics::shader * shd, xe_ecs::spot_light * directional_light, xe_ecs::transform_component * transform)
    {
    }

    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd, XEngine::PerspectiveCamera *cam)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -5.0f, -10.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(0.4f, 0.4f, 0.4f));
        
        glm::mat4 view_matrix = cam->getViewMatrix();
        glm::mat4 proj_matrix = cam->getProjectionMatrix();

        glm::mat4 mvp = proj_matrix * view_matrix * model_matrix;

        device->bind_shader(shd);
        device->set_mat4("mvp", mvp, shd);
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
    }

    void draw_ent(xe_ecs::entity *ent, xe_graphics::shader *shd, XEngine::PerspectiveCamera *camera)
    {
        draw_ent(ent, shd, camera, nullptr);
    }

    void draw_ent(xe_ecs::entity *ent, xe_graphics::shader *shd, XEngine::PerspectiveCamera *camera, glm::vec3 *color)
    {
        using namespace xe_ecs;
        
        xe_graphics::graphics_device *device = xe_render::get_device();

        mesh_component *model = ent->find_component<mesh_component>();

        if (model != nullptr)
        {
            transform_component *transform = ent->find_component<transform_component>();

            if (transform != nullptr)
            {
                device->bind_shader(shd);

                if(color != nullptr)
                    device->set_vec3("color", *color, shd);
                
                apply_transform(transform, shd, camera);

                xe_assets::node *root = model->model_asset->root;

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
            }
        }
    }

    void draw_mesh(xe_assets::mesh *msh, xe_graphics::shader *shd)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        uint32 diff_texture_num = 1;
        uint32 normal_texture_num = 1;
        uint32 specular_texture_num = 1;

        for (uint32 i = 0; i < msh->mesh_textures.size(); i++)
        {
            // @Refactor!!!
            xe_graphics::texture2D *mesh_texture = msh->mesh_textures[i].texture;
            device->activate_texture2d(i);

            std::string name = msh->mesh_textures[i].type;
            std::string num;

            if (name == "tex_diff")
                num = std::to_string(diff_texture_num++);
            else if (name == "tex_norm")
                num = std::to_string(normal_texture_num++);
            else if (name == "tex_spec")
                num = std::to_string(specular_texture_num++);

            device->set_int((name + num).c_str(), i, shd);
            device->bind_texture2d(mesh_texture);
        }

        if (msh->vertices.size() > 0)
        {
            glBindVertexArray(msh->vao);
            device->draw_indexed(GL_TRIANGLES, msh->indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

