#include "xe_render.h"

#include "runtime/core/utility/log.h"
#include "xe_ecs.h"
#include "xe_assets.h"
#include "perspective_camera.h"
#include "ortho_camera.h"

#include "xe_core.h"

#include <xenpch.h>

namespace xe_render
{
    static glm::vec4 clear_color;
    static xe_graphics::viewport main_view_port;
 
    static glm::vec3 default_text_color = glm::vec3(1.0f, 1.0f, 1.0f);
    static glm::vec3 default_cube_color = glm::vec3(0.0f, 1.0f, 0.0f);
    static real32 default_text_scale = 1.0f;
    static bool32 enable_shadows = true;

    xe_graphics::graphics_device *graphics_device = nullptr;

    xe_graphics::shader *simple_shader = nullptr;
    xe_graphics::shader *model_shader = nullptr;
    xe_graphics::shader *gamma_correction_shader = nullptr;
    xe_graphics::shader *post_proc_shader = nullptr;
    xe_graphics::shader *color_shader = nullptr;
    xe_graphics::shader *text_shader = nullptr;
    xe_graphics::shader *cubemap_shader = nullptr;
    xe_graphics::shader *shadow_map_shader = nullptr;
    xe_graphics::shader *shadow_map_depth_shader = nullptr;
    
    xe_graphics::render_pass *active_render_pass = nullptr;
    xe_graphics::framebuffer *active_framebuffer = nullptr;

    xe_graphics::vertex_array quad_vao;
    
    std::map<GLchar, xe_graphics::character> characters_map;

    xe_graphics::skybox *skybox_obj;

    using namespace xe_graphics;

    void init_render_gl()
    {
        xe_ecs::camera2d_component camera = get_camera2D();

        if(!load_shaders())
            xe_utility::error("Failed to init shader module!");

        if (!load_font("assets/fonts/arial.ttf"))
            xe_utility::error("Failed to init font module!");

        init_common_gpu_objects();           
    }

    void init_render_dx11()
    {


    }

    bool32 init_common_gpu_objects()
    {
        if (skybox_obj == nullptr)
            skybox_obj = new xe_graphics::skybox();
        
        bool32 is_skybox_created = create_skybox(skybox_obj);
        
        if (!is_skybox_created)
        {
            xe_utility::error("Failed to init skybox!");
            return false;
        }
            
        return true;
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

            texture2D texture_symbol = {};

            graphics_device->create_texture(&texture_symbol);
            graphics_device->bind_texture(TEXTURE_TYPE::COLOR, &texture_symbol);
            
            graphics_device->load_texture_gpu(TEXTURE_TYPE::COLOR, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_RED, face->glyph->bitmap.buffer);

            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

            character chacter =
            {
                texture_symbol.id,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            characters_map.insert(std::pair<GLchar, character>(c, chacter));
        }

        graphics_device->unbind_texture(TEXTURE_TYPE::COLOR);
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
        color_shader = new xe_graphics::shader();
        text_shader = new xe_graphics::shader();
        cubemap_shader = new xe_graphics::shader();
        post_proc_shader = new xe_graphics::shader();
        shadow_map_shader = new xe_graphics::shader();
        shadow_map_depth_shader = new xe_graphics::shader();

#ifdef GAPI_GL
        bool32 res = device->create_shader("shaders/glsl/simple2d.vs", "shaders/glsl/simple2d.fs", simple_shader);
        res = device->create_shader("shaders/glsl/model3d.vs", "shaders/glsl/model3d.fs", model_shader);       
        res = device->create_shader("shaders/glsl/quad.vs", "shaders/glsl/gamma_correction.fs", gamma_correction_shader);
        res = device->create_shader("shaders/glsl/model3d.vs", "shaders/glsl/color.fs", color_shader);
        res = device->create_shader("shaders/glsl/text.vs", "shaders/glsl/text.fs", text_shader);
        res = device->create_shader("shaders/glsl/cube_map.vs", "shaders/glsl/cube_map.fs", cubemap_shader);
        res = device->create_shader("shaders/glsl/shadow_map.vs", "shaders/glsl/shadow_map.fs", shadow_map_shader);
        res = device->create_shader("shaders/glsl/shadow_map_extract.vs", "shaders/glsl/shadow_map_extract.fs", shadow_map_depth_shader);
        res = device->create_shader("shaders/glsl/quad.vs", "shaders/glsl/post_proc.fs", post_proc_shader);
        
#endif
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

    xe_graphics::shader *get_post_proc_shader()
    {
        return post_proc_shader;
    }

    xe_graphics::shader *get_color_shader()
    {
        return color_shader;
    }

    xe_graphics::shader *get_shadow_map_shader()
    {
        return shadow_map_shader;
    }

    xe_graphics::shader *get_shadow_map_depth_shader()
    {
        return shadow_map_depth_shader;
    }

    bool32 create_mesh(xe_assets::mesh *meh)
    {
        return bool32();
    }

    bool32 create_cubemap(std::vector<const char*> paths, xe_graphics::cubemap *cube)
    {
        
        for (int i = 0; i < paths.size(); ++i)
        {
            graphics_device->create_texture2D(paths[i], cube->face_textures[i]);
        }

        return true;
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
        glGenVertexArrays(1, &quad_vao.id);

        return true;
    }

    bool32 create_skybox(xe_graphics::skybox *sky)
    {     
        real32 skybox_vertices[] = 
        {       
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        int vertex_size = sizeof(skybox_vertices) / sizeof(skybox_vertices[0]);

        sky->va = new xe_graphics::vertex_array();
        sky->vb = new xe_graphics::vertex_buffer();
        
        graphics_device->create_vertex_array(sky->va);
        graphics_device->create_vertex_buffer(skybox_vertices, vertex_size, DRAW_TYPE::STATIC, sky->vb);

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list =
        {
            { "aPos",    ElementType::Float3, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(sky->vb, &buffer_layout);
        graphics_device->add_vertex_buffer(sky->va, sky->vb);

        sky->cubemap = new cubemap();

        if (!create_cubemap(sky->cubemap))            
            return false;      

        return true;
    }

    bool32 create_cubemap(xe_graphics::cubemap *cube)
    {
        cube->face_textures.reserve(16);

        std::vector<const char*> skybox_faces;
        skybox_faces.push_back("right.jpg");
        skybox_faces.push_back("left.jpg");
        skybox_faces.push_back("top.jpg");
        skybox_faces.push_back("bottom.jpg");
        skybox_faces.push_back("front.jpg");
        skybox_faces.push_back("back.jpg");

        texture2D *cubemap_texture = new texture2D();
        cubemap_texture->desc.texture_type = CUBEMAP;
        cubemap_texture->desc.dimension = TEXTURE_2D;

        graphics_device->create_texture(cubemap_texture);
        graphics_device->bind_texture(TEXTURE_TYPE::CUBEMAP, cubemap_texture);

        for (uint32 i = 0; i < skybox_faces.size(); i++)
        {
            int channels = 0;
            std::string final_path = "assets/skybox/" + std::string(skybox_faces[i]);
            unsigned char *texture_data = xe_core::load_texture_from_disc(final_path.c_str(), cubemap_texture->desc.width, cubemap_texture->desc.height, channels, 0, false);
            if (texture_data)
                graphics_device->load_texture_gpu(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap_texture->desc.width, cubemap_texture->desc.height, GL_RGB, GL_RGB, texture_data);
            else
                xe_core::delete_data(texture_data);
           
            //cube->face_textures.push_back(cubemap_texture);
        }

        graphics_device->set_texture_wrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_device->set_texture_wrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_device->set_texture_wrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

        graphics_device->set_texture_sampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
        graphics_device->set_texture_sampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
        
        cube->id = cubemap_texture->id;

        graphics_device->bind_shader(cubemap_shader);
        graphics_device->set_int("skybox", 0, cubemap_shader);

        return true;
    }

    bool32 create_shadow_maps(xe_graphics::shadow_map *shadow)
    {
        const uint32 SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
        const uint32 WIDTH = 1280, HEIGHT = 720;

        shadow->depth_fbo = {};

        shadow->w = SHADOW_WIDTH;
        shadow->h = SHADOW_HEIGHT;

        graphics_device->create_framebuffer(1, &shadow->depth_fbo);
        graphics_device->add_depth_texture2D(SHADOW_WIDTH, SHADOW_HEIGHT, &shadow->depth_fbo);

        //unsigned int depthMap;
        //glGenTextures(1, &depthMap);
        //glBindTexture(GL_TEXTURE_2D, depthMap);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float colorattach[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, colorattach);

        graphics_device->bind_framebuffer(&shadow->depth_fbo);
        graphics_device->set_texture2D(GL_DEPTH_ATTACHMENT, shadow->depth_fbo.depth_texture);
        graphics_device->set_draw_buffer(GL_NONE);
        graphics_device->set_read_buffer(GL_NONE);
        graphics_device->unbind_framebuffer();

        //glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        //glDrawBuffer(GL_NONE);
        //glReadBuffer(GL_NONE);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

        framebuffer hdr = {};
        graphics_device->create_framebuffer(1, &hdr);
        graphics_device->bind_framebuffer(&hdr);

        //unsigned int hdrFBO;
        //glGenFramebuffers(1, &hdrFBO);
        //glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

        texture2D color_attach[2];

        graphics_device->create_texture(2, color_attach);

        //unsigned int colorBuffers[2];
        //glGenTextures(2, colorBuffers);

        for (uint32 i = 0; i < 2; ++i)
        {
            graphics_device->bind_texture(TEXTURE_TYPE::COLOR, &color_attach[i]);
            graphics_device->load_texture_gpu(TEXTURE_TYPE::COLOR, WIDTH, HEIGHT, GL_RGB16F, GL_RGB, NULL);

            //glBindTexture(GL_TEXTURE_2D, color_attach[i]->id);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);

            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

            graphics_device->set_texture2D(GL_COLOR_ATTACHMENT0 + i, &color_attach[i]);

            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, &color_attach->desc[i], 0);
        }

        graphics_device->create_render_buffer(1, &shadow->depth_fbo);

        //unsigned int rboDepth;
        //glGenRenderbuffers(1, &rboDepth);
        
        graphics_device->bind_renderbuffer(&shadow->depth_fbo);

        //glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

        unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, attachments);
        
        graphics_device->check_framebuffer();
        graphics_device->unbind_framebuffer();
        
        //if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        //std::cout << "Framebuffer not complete!" << std::endl;
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

        unsigned int pingphongFBO[2];
        unsigned int pingcolorBuffer[2];

        framebuffer p_fbo[2];
        texture2D p_color_buffer[2];
            
        glGenFramebuffers(2, pingphongFBO);
        glGenTextures(2, pingcolorBuffer);

        //graphics_device->create_framebuffer(2, p_fbo);
        //graphics_device->create_texture(2, p_color_buffer);

        for (uint16 i = 0; i < 2; ++i)
        {
            //graphics_device->bind_framebuffer(p_fbo + i);
            //graphics_device->bind_texture(TEXTURE_TYPE::COLOR, p_color_buffer + i);
            glBindFramebuffer(GL_FRAMEBUFFER, pingphongFBO[i]);
            glBindTexture(GL_TEXTURE_2D, pingcolorBuffer[i]);
  
            graphics_device->load_texture_gpu(TEXTURE_TYPE::COLOR, WIDTH, HEIGHT, GL_RGB16F, GL_RGB, NULL);

            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
            
            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
            
            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
           
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingcolorBuffer[i], 0);

            graphics_device->check_framebuffer();

            //if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            //   std::cout << "Framebuffer not complete\n";
        }

        return true;
    }

    void draw_full_quad()
    {
        graphics_device->bind_vertex_array(&quad_vao);
        graphics_device->draw_array(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 6);
        graphics_device->unbind_vertex_array();
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam)
    {
        if (texture != nullptr)
            graphics_device->bind_texture(TEXTURE_TYPE::COLOR, texture);

        glm::mat4 model = IDENTITY_MATRIX;
        
        graphics_device->bind_shader(shd);
        
        model = glm::translate(model, glm::vec3(300, 200, 0));
        model = glm::scale(model, glm::vec3(100, 100, 100));

        glm::mat4 view_projection = cam->getViewProjection();
        graphics_device->set_mat4("mvp", view_projection * model, shd);

        graphics_device->bind_vertex_array(q->vertex_array);        
        graphics_device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);
        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_quad(xe_ecs::entity *ent, xe_graphics::shader *shd, xe_graphics::texture2D *texture, XEngine::OrthoCamera *cam)
    {
        using namespace xe_ecs;
        quad_component* mesh = ent->find_component<quad_component>();
        transform_component *tr = ent->find_component<transform_component>();

        if (texture != nullptr)
            graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture);

        if (mesh == nullptr)
            return;

        graphics_device->bind_shader(shd);

        glm::mat4 model_matrix = tr->model_matrix;

        model_matrix = glm::translate(model_matrix, tr->position);
        model_matrix = glm::scale(model_matrix, tr->scale);

        glm::mat4 view_projection = cam->getViewProjection();
        glm::mat4 mvp = view_projection * model_matrix;

        graphics_device->set_mat4("mvp", mvp, shd);

        graphics_device->bind_vertex_array(mesh->quad_mesh->vertex_array);

        graphics_device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4 &mod, XEngine::OrthoCamera *cam)
    {
        if (texture != nullptr)
            graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture);

        graphics_device->bind_shader(shd);

        glm::mat4 view_projection = cam->getViewProjection();
        glm::mat4 mvp = view_projection * mod;

        graphics_device->set_mat4("mvp", mvp, shd);

        graphics_device->bind_vertex_array(q->vertex_array);

        graphics_device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_text(const std::string &text, real32 x, real32 y, glm::vec3 &color, real32 scale)
    {
        graphics_device->enable(GL_BLEND);
        graphics_device->set_blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        graphics_device->bind_shader(text_shader);
        graphics_device->set_vec3("color", color, text_shader);
        
        graphics_device->activate_texture(0);
        glBindVertexArray(1);
       
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {            
            character ch = characters_map.at(*c);

            GLfloat xpos = x + ch.bearing.x * scale;
            GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

            GLfloat w = ch.size.x * scale;
            GLfloat h = ch.size.y * scale;

            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };

            //graphics_device->bind_texture2d();

            glBindTexture(GL_TEXTURE_2D, ch.texture_id);

            glBindBuffer(GL_ARRAY_BUFFER, 1);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);            
            graphics_device->unbind_buffer(BUFFER_TYPE::VERTEX);
            
            graphics_device->draw_array(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 6);

            x += (ch.advance >> 6) * scale;
        }

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_texture(TEXTURE_TYPE::COLOR);

        graphics_device->disable(GL_BLEND);
    }

    void draw_text(const std::string &text, glm::vec2 &pos, glm::vec3 &color)
    {
        draw_text(text, pos.x, pos.y, color, default_text_scale);
    }

    void draw_text(const std::string &text, glm::vec2 &pos)
    {
        draw_text(text, pos.x, pos.y, default_text_color, default_text_scale);
    }

    void draw_text(const std::string &text, real32 x, real32 y)
    {
        draw_text(text, x, y, default_text_color, default_text_scale);
    }

    void draw_skybox()
    {
        glDepthFunc(GL_LEQUAL);
        graphics_device->bind_shader(cubemap_shader);
        
        xe_ecs::camera3d_component camera = get_camera3D();
        
        glm::mat4 view = glm::mat4(glm::mat3(camera.get_view_matrix()));

        graphics_device->set_mat4("view", view, cubemap_shader);
        graphics_device->set_mat4("projection", camera.get_projection_matrix(), cubemap_shader);
        
        graphics_device->bind_vertex_array(skybox_obj->va);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_obj->cubemap->id);

        //graphics_device->activate_bind_texture(TEXTURE_TYPE::CUBEMAP, skybox_obj->cubemap->id);

        graphics_device->draw_array(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 36);

        glDepthFunc(GL_LESS);
    }

    void apply_shadow_map(xe_graphics::shadow_map *shadow)
    {        
        real32 near_p = 1.0f;
        real32 far_p = 7.5f;

        shadow->light_projection_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_p, far_p);
    }

    void apply_transform(xe_ecs::transform_component *transform, xe_graphics::shader *shd)
    {
        glm::mat4 model_matrix = transform->model_matrix;

        model_matrix = glm::translate(model_matrix, transform->position);
        model_matrix = glm::scale(model_matrix, transform->scale);

        xe_ecs::camera3d_component camera = get_camera3D();

        glm::mat4 view_matrix = camera.get_view_matrix();
        glm::mat4 proj_matrix = camera.get_projection_matrix();

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

    void apply_point_light(xe_graphics::shader * shd, xe_ecs::point_light * directional_light, xe_ecs::transform_component * transform)
    {
    }

    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd, XEngine::PerspectiveCamera *cam)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        glm::mat4 model_matrix = IDENTITY_MATRIX;

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

    void draw_ent(xe_ecs::entity *ent)
    {
        using namespace xe_ecs;

        ENTITY_TYPE type = ent->get_type();

        switch (type)
        {
        case ENTITY_TYPE::ENT_STATIC_OBJECT_TEXTURED:
            draw_ent(ent, nullptr);
            break;
        case ENTITY_TYPE::ENT_STATIC_OBJECT_COLORED:
            draw_ent(ent, &default_cube_color);
            break;
        case ENTITY_TYPE::ENT_ANIMATED_OBJECT:
            break;
        default:
            xe_utility::debug("Entity type not declared!");
            break;
        }

    }

    void draw_ent(xe_ecs::entity *ent, glm::vec3 *color)
    {
        using namespace xe_ecs;
        
        xe_graphics::graphics_device *device = xe_render::get_device();

        mesh_component *model = ent->find_component<mesh_component>();

        shader *shader_to_draw = nullptr;
        
        if (model)
            shader_to_draw = xe_render::get_model_shader();

        transform_component *transform = ent->find_component<transform_component>();

        if (transform != nullptr)
        {
            if (color != nullptr)
            {
                shader_to_draw = xe_render::get_color_shader();
                device->bind_shader(shader_to_draw);
                device->set_vec3("color", *color, shader_to_draw);
            }

            /*else if (model->model_asset->model_textures.size() == 0)
            {
                shader_to_draw = xe_render::get_color_shader();
                device->bind_shader(shader_to_draw);
                device->set_vec3("color", default_cube_color, shader_to_draw);
            }*/

            if (enable_shadows)
                shader_to_draw = xe_render::get_shadow_map_shader();

            device->bind_shader(shader_to_draw);

            apply_transform(transform, shader_to_draw);

            if (enable_shadows)
            {
                real32 near_p = 1.0f;
                real32 far_p = 7.5f;

                glm::mat4 light_projection_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_p, far_p);
                glm::vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
                glm::mat4 light_view_matrix = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
                glm::mat4 light_space_matrix = light_view_matrix * light_projection_matrix;

                camera3d_component camera = get_camera3D();
                shader *shadow_shader = xe_render::get_shadow_map_shader();
                device->bind_shader(shadow_shader);
                device->set_vec3("view_pos", camera.pos, shadow_shader);
                device->set_vec3("light_pos", light_pos, shadow_shader);
                device->set_mat4("light_space_matrix", light_space_matrix, shadow_shader);
            }

            xe_assets::node *root = model->model_asset->root;

            for (uint32 i = 0; i < root->children.size(); i++)
            {
                xe_assets::node* curr_node = root->children[i];

                for (uint32 j = 0; j < curr_node->meshes.size(); j++)
                {
                    xe_assets::mesh *cur_mesh = curr_node->meshes.at(j);
                    draw_mesh(cur_mesh, shader_to_draw);
                }
            }

            device->unbind_shader();
        }           
    }

    void draw_ent_with_shader(xe_ecs::entity *ent, xe_graphics::shader *shd)
    {
        using namespace xe_ecs;
        
        xe_graphics::graphics_device *device = xe_render::get_device();

        mesh_component *model = ent->find_component<mesh_component>();

        shader *shader_to_draw = shd;

        transform_component *transform = ent->find_component<transform_component>();

        if (transform != nullptr)
        {           
            device->bind_shader(shader_to_draw);

            apply_transform(transform, shader_to_draw);

            xe_assets::node *root = model->model_asset->root;

            for (uint32 i = 0; i < root->children.size(); i++)
            {
                xe_assets::node* curr_node = root->children[i];

                for (uint32 j = 0; j < curr_node->meshes.size(); j++)
                {
                    xe_assets::mesh *cur_mesh = curr_node->meshes.at(j);
                    draw_mesh(cur_mesh, shader_to_draw);
                }
            }

            device->unbind_shader();
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
            device->activate_texture(i);

            std::string name = msh->mesh_textures[i].type;
            std::string num;

            if (name == "tex_diff")
                num = std::to_string(diff_texture_num++);
            else if (name == "tex_norm")
                num = std::to_string(normal_texture_num++);
            else if (name == "tex_spec")
                num = std::to_string(specular_texture_num++);

            device->set_int((name + num).c_str(), i, shd);
            device->bind_texture(TEXTURE_TYPE::COLOR, mesh_texture);
        }

        if (msh->vertices.size() > 0)
        {
            glBindVertexArray(msh->vao);
            device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, msh->indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

