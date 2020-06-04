#include "xe_render.h"

#include "xe_ecs.h"
#include "xe_assets.h"

#include "xe_core.h"
#include "xe_utility.h"

#include "xe_gui.h"
#include "xe_config.h"

#include "xe_memory.h"

#include <xenpch.h>

#include <thread>

namespace xe_render
{
    static glm::vec4 clear_color; 
    static glm::vec3 default_text_color = glm::vec3(1.0f, 1.0f, 1.0f);
    static glm::vec3 default_cube_color = glm::vec3(0.0f, 1.0f, 0.0f);
    static glm::vec4 default_line_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    static uint32 default_line_width = 5;
    static real32 default_text_scale = 1.0f;

    static bool32 enable_shadows = false;

    xe_graphics::graphics_device *graphics_device = nullptr;

    std::unordered_map<const char*, xe_graphics::shader> shaders;
    std::unordered_map<const char*, xe_graphics::texture2D> textures;

    xe_graphics::render_pass *active_render_pass = nullptr;
    xe_graphics::framebuffer *active_framebuffer = nullptr;

    xe_graphics::vertex_array quad_vao;
    xe_graphics::sphere sphere_vao;
    xe_graphics::cube cube_vao;
    xe_graphics::line line_vao;
    
    std::map<GLchar, xe_graphics::character> characters_map;

    xe_graphics::skybox *skybox_obj;

    using namespace xe_graphics;

    void init_render_gl()
    {
        bool32 loaded_shaders = false;
        bool32 loaded_tex = false;
        bool32 loaded_font = false;

        if (!load_shaders())
            xe_utility::error("Failed to init shader module!");

        /*std::thread l_shaders([&loaded_shaders]()
        {
            loaded_shaders = load_shaders();
        });*/

        /*std::thread l_fre_tex([&loaded_tex]() 
        {
            loaded_tex = load_free_textures();        
        });       

        std::thread l_font([&loaded_font]()
        {
            loaded_font = load_font("assets/fonts/arial.ttf");
        });/*/

        if(!load_free_textures())
            xe_utility::error("Failed to init textures module!");

        if (!load_font("assets/fonts/arial.ttf"))
            xe_utility::error("Failed to init font module!");

        init_common_gpu_objects();           
    }

    void init_render_dx11()
    {


    }

    void init_gui()
    {
        xe_gui::init_imgui_impl();        
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
            
        shader *texture_shader = get_shader("simple_tex");

        graphics_device->bind_shader(texture_shader);
        graphics_device->set_int("tex_diff", 0, texture_shader);

        shader *pbr = get_shader("pbr");

        graphics_device->bind_shader(pbr);
        graphics_device->set_int("irradiance_map", 0, pbr);
        graphics_device->set_int("prefilter_map", 1, pbr);
        graphics_device->set_int("brdf_LUT", 2, pbr);

        graphics_device->set_int("albedo_map", 3, pbr);
        graphics_device->set_int("normal_map", 4, pbr);
        graphics_device->set_int("metallic_map", 5, pbr);
        graphics_device->set_int("roughness_map", 6, pbr);
        graphics_device->set_int("ao_map", 7, pbr);
        
        shader *equ_to_cubemap = get_shader("equirect");

        graphics_device->bind_shader(equ_to_cubemap);
        graphics_device->set_int("equirectangular_map", 0, equ_to_cubemap);

        shader *animation = get_shader("skeletal_animation");
        graphics_device->bind_shader(animation);
        graphics_device->set_int("tex_diff", 0, animation);

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
            
            graphics_device->load_texture_gpu(TEXTURE_TYPE::COLOR, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_RED, (void**)face->glyph->bitmap.buffer);

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

        graphics_device->create_vertex_buffer(NULL, 24 * sizeof(real32), DRAW_TYPE::DYNAMIC, vb);

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

        shader *text_shader = &shaders["text"];

        graphics_device->bind_shader(text_shader);
        graphics_device->set_mat4("projection", ortho, text_shader);

        return true;
    }

    bool32 load_shaders()
    {
        xe_graphics::shader simple_shader = {};
        xe_graphics::shader model_shader = {};
        xe_graphics::shader gamma_correction_shader = {};
        xe_graphics::shader color_shader = {};
        xe_graphics::shader text_shader = {};
        xe_graphics::shader cubemap_shader = {};
        xe_graphics::shader post_proc_shader = {};
        xe_graphics::shader shadow_map_shader = {};
        xe_graphics::shader shadow_map_depth_shader = {};
        xe_graphics::shader pbr = {};
        xe_graphics::shader simple_texture = {};
        xe_graphics::shader background_shader = {};
        xe_graphics::shader brdf_shader = {};
        xe_graphics::shader prefilter_shader = {};
        xe_graphics::shader equirectangular_cubemap = {};
        xe_graphics::shader irradiance_shader = {};
        xe_graphics::shader water = {};
        xe_graphics::shader simple_color = {};
        xe_graphics::shader anim_model = {};

        std::string shader_names[8] = {};

        const char *shaders_dir = "shaders/glsl/";

        uint32 N = 9;

       bool32 res = false;

#ifdef GAPI_GL

        /*bool32 shader_res;

        for (uint16 i = 0; i < N; i++)
        {
            shader_res |= device->create_shader(shaders_dir + std::string("simple2d.vs"), std::string(shaders_dir + "simple2d.vs").c_str(), &simple_shader);
        }*/

        res = graphics_device->create_shader("shaders/glsl/simple_pos.vs", "shaders/glsl/filledsimple2d.fs", &simple_color);
        
        res |= graphics_device->create_shader("shaders/glsl/anim_model3d.vs", "shaders/glsl/simple2d.fs", &anim_model);        
        res |= graphics_device->create_shader("shaders/glsl/simple2d.vs", "shaders/glsl/simple2d.fs", &simple_shader);
        res |= graphics_device->create_shader("shaders/glsl/simple_model.vs", "shaders/glsl/simple2d.fs", &simple_texture);
        res |= graphics_device->create_shader("shaders/glsl/model3d.vs", "shaders/glsl/base3d.fs", &model_shader);
        res |= graphics_device->create_shader("shaders/glsl/model3d.vs", "shaders/glsl/water.fs", &water);
        res |= graphics_device->create_shader("shaders/glsl/quad.vs", "shaders/glsl/gamma_correction.fs", &gamma_correction_shader);
        res |= graphics_device->create_shader("shaders/glsl/simple_model.vs", "shaders/glsl/color.fs", &color_shader);
        res |= graphics_device->create_shader("shaders/glsl/text.vs", "shaders/glsl/text.fs", &text_shader);
        res |= graphics_device->create_shader("shaders/glsl/cube_map.vs", "shaders/glsl/cube_map.fs", &cubemap_shader);
        res |= graphics_device->create_shader("shaders/glsl/shadow_map.vs", "shaders/glsl/shadow_map.fs", &shadow_map_shader);
        res |= graphics_device->create_shader("shaders/glsl/shadow_map_extract.vs", "shaders/glsl/shadow_map_extract.fs", &shadow_map_depth_shader);
        res |= graphics_device->create_shader("shaders/glsl/quad.vs", "shaders/glsl/post_proc.fs", &post_proc_shader);
        res |= graphics_device->create_shader("shaders/glsl/pbr/pbr.vs", "shaders/glsl/pbr/pbr.fs", &pbr);
        res |= graphics_device->create_shader("shaders/glsl/pbr/background.vs", "shaders/glsl/pbr/background.fs", &background_shader);
        res |= graphics_device->create_shader("shaders/glsl/pbr/brdf.vs", "shaders/glsl/pbr/brdf.fs", &brdf_shader);
        res |= graphics_device->create_shader("shaders/glsl/pbr/cubemap.vs", "shaders/glsl/pbr/pref.fs", &prefilter_shader);
        res |= graphics_device->create_shader("shaders/glsl/pbr/cubemap.vs", "shaders/glsl/pbr/equ_to_cubemap.fs", &equirectangular_cubemap);
        res |= graphics_device->create_shader("shaders/glsl/pbr/cubemap.vs", "shaders/glsl/pbr/irradiance.fs", &irradiance_shader);

#endif

#ifdef GAPI_DX11



#endif

        shaders["simple_pos"] = simple_color;
        shaders["simple2d"] = simple_shader;
        shaders["simple_tex"] = simple_texture;
        shaders["base3d"] = model_shader;
        shaders["gc"] = gamma_correction_shader;
        shaders["text"] = text_shader;
        shaders["cubemap"] = cubemap_shader;
        shaders["color"] = color_shader;
        shaders["shadow_map"] = shadow_map_shader;
        shaders["shadow_depth"] = shadow_map_depth_shader;
        shaders["post_proc"] = post_proc_shader;
        shaders["pbr"] = pbr;
        shaders["background"] = background_shader;
        shaders["brdf"] = brdf_shader;
        shaders["prefilter"] = prefilter_shader;
        shaders["equirect"] = equirectangular_cubemap;
        shaders["irradiance"] = irradiance_shader;
        shaders["water"] = water;
        shaders["skeletal_animation"] = anim_model;
       
        if (!res)
        {
            xe_utility::error("loading shader");
            return false;
        }
    
        xe_utility::info("Shaders loaded!!!");
        return true;
    }

    bool32 load_free_textures()
    {
        texture2D wood_texture = {};
        texture2D water_texture = {};

        // pbr

        texture2D albedo_iron = {};
        texture2D normal_iron = {};
        texture2D metallic_iron = {};
        texture2D roughness_iron = {};
        texture2D ao_iron = {}; 

        texture2D albedo_plastic = {};
        texture2D normal_plastic = {};
        texture2D metallic_plastic = {};
        texture2D roughness_plastic = {};
        texture2D ao_plastic = {};

        texture2D albedo_grass = {};
        texture2D normal_grass = {};
        texture2D metallic_grass = {};
        texture2D roughness_grass = {};
        texture2D ao_grass = {};

        texture2D albedo_gold = {};
        texture2D normal_gold = {};
        texture2D metallic_gold = {};
        texture2D roughness_gold = {};
        texture2D ao_gold = {};

        texture2D albedo_wall = {};
        texture2D normal_wall = {};
        texture2D metallic_wall = {};
        texture2D roughness_wall = {};
        texture2D ao_wall = {};

        // hdr env map
        texture2D hdr = {};

        texture2D cerberus_d = {};
        texture2D cerberus_n = {};
        texture2D cerberus_r = {};
        texture2D cerberus_m = {};
        texture2D cerberus_ao = {};

        texture2D gun_diff = {};

        graphics_device->create_texture2D("assets/cerberus/albedo.tga", &cerberus_d);
        graphics_device->create_texture2D("assets/cerberus/normal.tga", &cerberus_n);
        graphics_device->create_texture2D("assets/cerberus/roughness.tga", &cerberus_r);
        graphics_device->create_texture2D("assets/cerberus/metallic.tga", &cerberus_m);
        graphics_device->create_texture2D("assets/cerberus/ao.tga", &cerberus_ao);

        graphics_device->create_texture2D("assets/pbr/rusted_iron/albedo.png", &albedo_iron);
        graphics_device->create_texture2D("assets/pbr/rusted_iron/normal.png", &normal_iron);
        graphics_device->create_texture2D("assets/pbr/rusted_iron/metallic.png", &metallic_iron);
        graphics_device->create_texture2D("assets/pbr/rusted_iron/roughness.png", &roughness_iron);
        graphics_device->create_texture2D("assets/pbr/rusted_iron/ao.png", &ao_iron);        
       
        graphics_device->create_texture2D("assets/pbr/grass/albedo.png", &albedo_grass);
        graphics_device->create_texture2D("assets/pbr/grass/normal.png", &normal_grass);
        graphics_device->create_texture2D("assets/pbr/grass/metallic.png", &metallic_grass);
        graphics_device->create_texture2D("assets/pbr/grass/roughness.png", &roughness_grass);
        graphics_device->create_texture2D("assets/pbr/grass/ao.png", &ao_grass);

        graphics_device->create_texture2D("assets/pbr/wall/albedo.png", &albedo_wall);
        graphics_device->create_texture2D("assets/pbr/wall/normal.png", &normal_wall);
        graphics_device->create_texture2D("assets/pbr/wall/metallic.png", &metallic_wall);
        graphics_device->create_texture2D("assets/pbr/wall/roughness.png", &roughness_wall);
        graphics_device->create_texture2D("assets/pbr/wall/ao.png", &ao_wall);

        graphics_device->create_texture2D("assets/pbr/plastic/albedo.png", &albedo_plastic);
        graphics_device->create_texture2D("assets/pbr/plastic/normal.png", &normal_plastic);
        graphics_device->create_texture2D("assets/pbr/plastic/metallic.png", &metallic_plastic);
        graphics_device->create_texture2D("assets/pbr/plastic/roughness.png", &roughness_plastic);
        graphics_device->create_texture2D("assets/pbr/plastic/ao.png", &ao_plastic);

        graphics_device->create_texture2D("assets/pbr/gold/albedo.png", &albedo_gold);
        graphics_device->create_texture2D("assets/pbr/gold/normal.png", &normal_gold);
        graphics_device->create_texture2D("assets/pbr/gold/metallic.png", &metallic_gold);
        graphics_device->create_texture2D("assets/pbr/gold/roughness.png", &roughness_gold);
        graphics_device->create_texture2D("assets/pbr/gold/ao.png", &ao_gold);

        graphics_device->create_texture2D("assets/m1911/m1911_color.png", &gun_diff);

        graphics_device->create_texture2D("assets/hdr/barce_3k.hdr", TEXTURE_TYPE::HDR, false, &hdr);

        bool32 loaded = graphics_device->create_texture2D("assets/get.png", &wood_texture);        
        graphics_device->create_texture2D("assets/water-texture.jpg", &water_texture);

        if (!loaded)
        {
            xe_utility::error("Failed to load free texture");
            return false;
        }

        textures["gun_diff"] = gun_diff;

        textures["wood"] = wood_texture;
        textures["water"] = water_texture;

        textures["albedo_iron"] = albedo_iron;
        textures["normal_iron"] = normal_iron;
        textures["metallic_iron"] = metallic_iron;
        textures["roughness_iron"] = roughness_iron;
        textures["ao_iron"] = ao_iron;

        textures["albedo_grass"] = albedo_grass;
        textures["normal_grass"] = normal_grass;
        textures["metallic_grass"] = metallic_grass;
        textures["roughness_grass"] = roughness_grass;
        textures["ao_grass"] = ao_grass;

        textures["albedo_wall"] = albedo_wall;
        textures["normal_wall"] = normal_wall;
        textures["metallic_wall"] = metallic_wall;
        textures["roughness_wall"] = roughness_wall;
        textures["ao_wall"] = ao_wall;

        textures["albedo_gold"] = albedo_gold;
        textures["normal_gold"] = normal_gold;
        textures["metallic_gold"] = metallic_gold;
        textures["roughness_gold"] = roughness_gold;
        textures["ao_gold"] = ao_gold;

        textures["albedo_plastic"] = albedo_plastic;
        textures["normal_plastic"] = normal_plastic;
        textures["metallic_plastic"] = metallic_plastic;
        textures["roughness_plastic"] = roughness_plastic;
        textures["ao_plastic"] = ao_plastic;

        textures["hdr_env"] = hdr;

        textures["cerberus_d"] = cerberus_d;
        textures["cerberus_n"] = cerberus_n;
        textures["cerberus_r"] = cerberus_r;
        textures["cerberus_m"] = cerberus_m;
        textures["cerberus_ao"] = cerberus_ao;

        xe_utility::info("Free textures loaded!!!");
        return true;
    }

    void clear()
    {
        // @Clear destroy free textures

        std::unordered_map<const char*, xe_graphics::texture2D>::iterator it = textures.begin();
        for (uint32 i = 0; i < textures.size(); ++i)
        {
            graphics_device->destroy_texture2D(&it->second);
        }

        xe_gui::clear_context();
    }

    xe_ecs::camera2d_component& get_camera2D() 
    {
        static xe_ecs::camera2d_component camera2D;
        
        viewport vp = graphics_device->get_viewport();        
        camera2D.width = vp.width;
        camera2D.height = vp.height;

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

    xe_graphics::shader *get_shader(const char *name)
    {
        return &shaders[name];
    }

    xe_graphics::texture2D *get_texture2D_resource(const char *name)
    {
        return &textures[name];
    }
    
    bool32 create_mesh(xe_assets::mesh *meh, xe_graphics::vertex *vertex_type, bool32 calculate_tspace)
    {
        vertex *vert = vertex_type;

        meh->vao.buffers.push_back(new vertex_buffer());
        meh->vao.ib = new index_buffer();

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list;

        if (calculate_tspace)
        {
            init_list = 
            {
                { "aPos",       ElementType::Float3, },                
                { "aNormal",    ElementType::Float3, },
                { "aTangent",   ElementType::Float3, },
                { "aBitangent", ElementType::Float3, },
                { "aUV",        ElementType::Float2, }
            };
        }
        else
        {
            init_list =
            {
                { "aPos",       ElementType::Float3, },
                { "aNormal",    ElementType::Float3, },
                { "aUV",        ElementType::Float2, }
            };
        }

        graphics_device->create_vertex_array(&meh->vao);
        graphics_device->bind_vertex_array(&meh->vao);

        graphics_device->create_vertex_buffer(&meh->vertices_fl[0], meh->vertices_fl.size() * sizeof(real32), DRAW_TYPE::STATIC, meh->vao.buffers[0]);
        graphics_device->create_index_buffer(&meh->indices[0], meh->indices.size(), meh->vao.ib);

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(meh->vao.buffers[0], &buffer_layout);
        graphics_device->add_vertex_buffer(&meh->vao, meh->vao.buffers[0]);
        graphics_device->set_index_buffer(&meh->vao, meh->vao.ib);

        //glGenVertexArrays(1, &meh->vao);
        //glGenBuffers(1, &meh->vbo);
        //glGenBuffers(1, &meh->ibo);

        //device->bind_vertex_array(&meh->vao);
        //device->bind_buffer(meh->vao.buffers[0]);
        //glBufferData(GL_ARRAY_BUFFER, meh->vertices_tab.size() * sizeof(pos_normal_tb_uv), &meh->vertices_tab[0], GL_STATIC_DRAW);
        
        //device->bind_buffer(meh->vao.ib);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, meh->indices.size() * sizeof(uint32), &meh->indices[0], GL_STATIC_DRAW);

        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pos_normal_tb_uv), (void*)0);

        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pos_normal_tb_uv), (void*)offsetof(pos_normal_tb_uv, normal));

        // @tangent & @bitangent
        //glEnableVertexAttribArray(2);
        //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(pos_normal_tb_uv), (void*)offsetof(pos_normal_tb_uv, tangent));

        //glEnableVertexAttribArray(3);
        //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(pos_normal_tb_uv), (void*)offsetof(pos_normal_tb_uv, bitangent));

        //glEnableVertexAttribArray(4);
        //glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(pos_normal_tb_uv), (void*)offsetof(pos_normal_tb_uv, uv));

        //else
        /*{
            glBufferData(GL_ARRAY_BUFFER, meh->vertices.size() * sizeof(pos_normal_uv), &meh->vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meh->ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, meh->indices.size() * sizeof(uint32), &meh->indices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pos_normal_uv), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pos_normal_uv), (void*)offsetof(pos_normal_uv, normal));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(pos_normal_uv), (void*)offsetof(pos_normal_uv, uv));
        }*/

        graphics_device->unbind_vertex_array();
        graphics_device->destroy_buffer(meh->vao.buffers[0]);
        graphics_device->destroy_buffer(meh->vao.ib);

        return true;       
    }

    bool32 create_line_mesh(glm::vec3 &start, glm::vec3 &end, xe_graphics::line *line_com)
    {
        std::vector<real32> array_vertex;

        array_vertex.push_back(start.x);
        array_vertex.push_back(start.y);
        array_vertex.push_back(start.z);
        array_vertex.push_back(end.x);
        array_vertex.push_back(end.y);
        array_vertex.push_back(end.z);

        line_com->va = alloc_mem xe_graphics::vertex_array();        
        line_com->va->buffers.push_back(alloc_mem xe_graphics::vertex_buffer());

        line_com->vertex_count = array_vertex.size();

        graphics_device->create_vertex_array(line_com->va);
        graphics_device->bind_vertex_array(line_com->va);

        graphics_device->create_vertex_buffer(&array_vertex[0], line_com->vertex_count * sizeof(real32), DRAW_TYPE::STATIC, line_com->va->buffers[0]);
        
        using namespace xe_graphics;

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list =
        {
            { "aPos",    ElementType::Float3, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(line_com->va->buffers[0], &buffer_layout);
        graphics_device->add_vertex_buffer(line_com->va, line_com->va->buffers[0]);

        return true;
    }

    bool32 create_line_mesh(xe_graphics::line *line_com)
    {
        glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 end= glm::vec3(1.0f, 1.0f, 0.0f);
        return create_line_mesh(start, end, line_com);
    }

    bool32 create_cubemap(std::vector<const char*> paths, xe_graphics::cubemap *cube)
    {        
        for (uint32 i = 0; i < paths.size(); ++i)
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

        uint32 indices[] = 
        {
            0, 1, 3,
            1, 2, 3
        };
        
        int vertex_size = sizeof(vertices) / sizeof(vertices[0]); 
        int indices_size = sizeof(indices) / sizeof(indices[0]);

        q->vertex_array = alloc_mem xe_graphics::vertex_array;
        q->vertex_array->buffers.push_back(alloc_mem xe_graphics::vertex_buffer);
        q->vertex_array->ib = alloc_mem xe_graphics::index_buffer;
        
        graphics_device->create_vertex_array(q->vertex_array);
        graphics_device->bind_vertex_array(q->vertex_array);

        graphics_device->create_vertex_buffer(vertices, vertex_size * sizeof(real32), DRAW_TYPE::STATIC, q->vertex_array->buffers[0]);
        graphics_device->create_index_buffer(indices, indices_size, q->vertex_array->ib);
        
        using namespace xe_graphics;

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list = 
        {
            { "aPos",    ElementType::Float3, },
            { "aUV",     ElementType::Float2, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(q->vertex_array->buffers[0], &buffer_layout);        
        graphics_device->add_vertex_buffer(q->vertex_array, q->vertex_array->buffers[0]);
        graphics_device->set_index_buffer(q->vertex_array, q->vertex_array->ib);
        
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
        graphics_device->create_vertex_buffer(skybox_vertices, vertex_size * sizeof(real32), DRAW_TYPE::STATIC, sky->vb);

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list =
        {
            { "aPos",    ElementType::Float3, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(sky->vb, &buffer_layout);
        graphics_device->add_vertex_buffer(sky->va, sky->vb);

        sky->cubemap = alloc_mem cubemap();

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
            void *texture_data = xe_core::load_texture_from_disc(final_path.c_str(), cubemap_texture->desc.width, cubemap_texture->desc.height, channels, 0, false);
            
            graphics_device->load_texture_gpu(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap_texture->desc.width, cubemap_texture->desc.height, GL_RGB, GL_RGB, texture_data);
       
            xe_core::delete_data(texture_data);
        }

        graphics_device->set_texture_wrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_device->set_texture_wrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_device->set_texture_wrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

        graphics_device->set_texture_sampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
        graphics_device->set_texture_sampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
        
        cube->id = cubemap_texture->id;

        shader *cubemap_shader = &shaders["cubemap"];
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
        graphics_device->set_texture2D_fbo(GL_DEPTH_ATTACHMENT, TEXTURE_TYPE::DEPTH, shadow->depth_fbo.depth_texture);
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

            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
            graphics_device->set_texture_wrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            graphics_device->set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

            graphics_device->set_texture2D_fbo(GL_COLOR_ATTACHMENT0 + i, TEXTURE_TYPE::COLOR, &color_attach[i]);

            //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, &color_attach->desc[i], 0);
        }

        graphics_device->create_render_buffer(1, &shadow->depth_fbo);

        //unsigned int rboDepth;
        //glGenRenderbuffers(1, &rboDepth);
        
        graphics_device->bind_renderbuffer(&shadow->depth_fbo);

        //glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

         //glDrawBuffers(2, attachments);

        uint32 attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };        
        graphics_device->set_draw_buffers(2, attachments);

        graphics_device->check_framebuffer();
        graphics_device->unbind_framebuffer();        
        
        //unsigned int pingphongFBO[2];
        //unsigned int pingcolorBuffer[2];

        framebuffer p_fbo[2];
        texture2D p_color_buffer[2];
            
        //glGenFramebuffers(2, pingphongFBO);
        //glGenTextures(2, pingcolorBuffer);

        for (uint16 i = 0; i < 2; ++i)
        {
            graphics_device->create_framebuffer(1, p_fbo + i);
        }

        for (uint16 j = 0; j < 2; ++j)
        {
            graphics_device->create_texture(1, p_color_buffer + j);
        }

        for (uint16 i = 0; i < 2; ++i)
        {
            graphics_device->bind_framebuffer(p_fbo + i);
            graphics_device->bind_texture(TEXTURE_TYPE::COLOR, p_color_buffer + i);
            
            //glBindFramebuffer(GL_FRAMEBUFFER, pingphongFBO[i]);
            //glBindTexture(GL_TEXTURE_2D, pingcolorBuffer[i]);
  
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
           
            graphics_device->add_color_texture2D(p_color_buffer + i, i, p_fbo + i);
            //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingcolorBuffer[i], 0);

            graphics_device->check_framebuffer();
        }

        return true;
    }

    bool32 create_sphere(xe_graphics::sphere *sphre)
    {        
        sphre->vertex_array = new xe_graphics::vertex_array();
        sphre->vertex_array->buffers.push_back(new xe_graphics::vertex_buffer());
        sphre->vertex_array->ib = new xe_graphics::index_buffer();

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<uint32> indices;

        for (uint32 y = 0; y <= 64; ++y)
        {
            for (uint32 x = 0; x <= 64; ++x)
            {
                real32 xSegment = (real32)x / (real32)64;
                real32 ySegment = (real32)y / (real32)64;
                real32 xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                real32 yPos = std::cos(ySegment * PI);
                real32 zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool32 odd_row = false;
        for (int y = 0; y < 64; ++y)
        {
            if (!odd_row)
            {
                for (int x = 0; x <= 64; ++x)
                {
                    indices.push_back(y       * (64 + 1) + x);
                    indices.push_back((y + 1) * (64 + 1) + x);
                }
            }
            else
            {
                for (int x = 64; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (64 + 1) + x);
                    indices.push_back(y       * (64 + 1) + x);
                }
            }
            odd_row = !odd_row;
        }
        
        std::vector<real32> data;
        for (int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);

            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }

            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }

        graphics_device->create_vertex_array(sphre->vertex_array);
        graphics_device->bind_vertex_array(sphre->vertex_array);

        graphics_device->create_vertex_buffer(&data[0], data.size() * sizeof(real32), DRAW_TYPE::STATIC, sphre->vertex_array->buffers[0]);
        graphics_device->create_index_buffer(&indices[0], indices.size(), sphre->vertex_array->ib);

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list =
        {
            { "aPos",       ElementType::Float3, },
            { "aUV",        ElementType::Float2, },
            { "aNormal",    ElementType::Float3, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(sphre->vertex_array->buffers[0], &buffer_layout);
        graphics_device->add_vertex_buffer(sphre->vertex_array, sphre->vertex_array->buffers[0]);
        graphics_device->set_index_buffer(sphre->vertex_array, sphre->vertex_array->ib);

        sphre->vertex_array->ib->count = indices.size();

        return true;
    }

    bool32 create_cube(xe_graphics::cube *cube)
    {
        real32 data[] = 
        {
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, 
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 
         
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, 
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 
            
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,          
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, 

            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, 
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, 
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 
           
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  
        };

        cube->vertex_array = new xe_graphics::vertex_array();
        cube->vertex_array->buffers.push_back(new xe_graphics::vertex_buffer());

        graphics_device->create_vertex_array(cube->vertex_array);
        graphics_device->bind_vertex_array(cube->vertex_array);

        uint32 size = sizeof(data) / sizeof(data[0]);

        graphics_device->create_vertex_buffer(&data[0], size * sizeof(real32), DRAW_TYPE::STATIC, cube->vertex_array->buffers[0]);

        buffer_layout buffer_layout = {};

        std::initializer_list<xe_graphics::buffer_element> init_list =
        {
            { "aPos",       ElementType::Float3, },
            { "aNormal",    ElementType::Float3, },
            { "aUV",        ElementType::Float2, }
        };

        graphics_device->create_buffer_layout(init_list, &buffer_layout);
        graphics_device->set_vertex_buffer_layout(cube->vertex_array->buffers[0], &buffer_layout);
        graphics_device->add_vertex_buffer(cube->vertex_array, cube->vertex_array->buffers[0]);
        
        return true;
    }

    void draw_full_quad()
    {
        graphics_device->bind_vertex_array(&quad_vao);
        graphics_device->draw_array(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 6);
        graphics_device->unbind_vertex_array();
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture)
    {
        if (texture != nullptr)
            graphics_device->bind_texture(TEXTURE_TYPE::COLOR, texture);

        glm::mat4 model = IDENTITY_MATRIX;
        
        graphics_device->bind_shader(shd);
        
        model = glm::translate(model, glm::vec3(300, 200, 0));
        model = glm::scale(model, glm::vec3(100, 100, 100));
        xe_ecs::camera2d_component camera2d = get_camera2D();

        glm::mat4 view_projection = camera2d.get_view_projection();
        graphics_device->set_mat4("mvp", view_projection * model, shd);

        graphics_device->bind_vertex_array(q->vertex_array);        
        graphics_device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);
        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_quad(xe_ecs::entity *ent, xe_graphics::shader *shd, xe_graphics::texture2D *texture)
    {
        using namespace xe_ecs;
        quad_component* mesh = ent->find_component<quad_component>();
        transform_component *tr = ent->find_component<transform_component>();
        
        if (mesh == nullptr)
            return;

        graphics_device->bind_shader(shd);

        if (texture != nullptr)
            graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture);

        glm::mat4 model_matrix = tr->model_matrix;

        model_matrix = glm::translate(model_matrix, tr->position);
        model_matrix = glm::scale(model_matrix, tr->scale);
        
        xe_ecs::camera2d_component camera2d = get_camera2D();

        glm::mat4 view_projection = camera2d.get_view_projection();
        glm::mat4 mvp = view_projection * model_matrix;

        graphics_device->set_mat4("mvp", mvp, shd);

        graphics_device->bind_vertex_array(mesh->quad_mesh->vertex_array);

        graphics_device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);

        graphics_device->unbind_vertex_array();
        graphics_device->unbind_shader();
    }

    void draw_quad(const xe_graphics::quad *q, xe_graphics::shader *shd, xe_graphics::texture2D *texture, glm::mat4 &mod)
    {
        if (texture != nullptr)
            graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture);

        graphics_device->bind_shader(shd);

        xe_ecs::camera2d_component camera2d = get_camera2D();

        glm::mat4 view_projection = camera2d.get_view_projection();
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

        shader *text_shader = &shaders["text"];

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

    void draw_water_plane(xe_ecs::entity *ent)
    {
        shader *water = xe_render::get_shader("water");

        graphics_device->bind_shader(water);

        xe_ecs::water_component *water_comp = ent->find_component<xe_ecs::water_component>();
        xe_ecs::mesh_component *mesh = ent->find_component<xe_ecs::mesh_component>();
        xe_ecs::transform_component *transform = ent->find_component<xe_ecs::transform_component>();

        glm::mat4 model_matrix = transform->model_matrix;

        model_matrix = glm::translate(model_matrix, transform->position);
        model_matrix = glm::scale(model_matrix, transform->scale);

        xe_ecs::camera3d_component cam = get_camera3D();

        glm::mat4 view_matrix = cam.get_view_matrix();
        glm::mat4 proj_matrix = cam.get_projection_matrix();

        glm::mat4 mvp = proj_matrix * view_matrix * model_matrix;

        graphics_device->set_mat4("mvp", mvp, water);
        graphics_device->set_mat4("model", model_matrix, water);

        graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, water_comp->water_tex);
        draw_model(mesh->model_asset, water);
    }

    void draw_skybox()
    {
        graphics_device->set_depth_func(GL_LEQUAL);
        shader *cubemap_shader = xe_render::get_shader("cubemap");

        graphics_device->bind_shader(cubemap_shader);
        
        xe_ecs::camera3d_component camera = get_camera3D();
        
        glm::mat4 view = glm::mat4(glm::mat3(camera.get_view_matrix()));

        graphics_device->set_mat4("view", view, cubemap_shader);
        graphics_device->set_mat4("projection", camera.get_projection_matrix(), cubemap_shader);
        
        graphics_device->bind_vertex_array(skybox_obj->va);

        graphics_device->activate_bind_texture(TEXTURE_TYPE::CUBEMAP, skybox_obj->cubemap);
 
        graphics_device->draw_array(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 36);

        graphics_device->set_depth_func(GL_LESS);
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
       
        //graphics_device->set_vec3("dir_light_color", glm::vec3(1.0, 0.0, 0.0), shd);
        graphics_device->set_vec3("light_pos", glm::vec3(4.0, 4.0, 0.0), shd);
        graphics_device->set_vec3("cam_pos", camera.pos, shd);

        if (enable_shadows)
        {
            real32 near_p = 1.0f;
            real32 far_p = 7.5f;

            glm::mat4 light_projection_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_p, far_p);
            glm::vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
            glm::mat4 light_view_matrix = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            glm::mat4 light_space_matrix = light_projection_matrix * light_view_matrix;

            shd = xe_render::get_shader("base3d");
            graphics_device->bind_shader(shd);
            graphics_device->set_mat4("light_space_matrix", light_space_matrix, shd);
            graphics_device->set_bool("shadows_enabled", true, shd);
        }
        else
        {
            graphics_device->set_bool("shadows_enabled", false, shd);
        }
    }

    void apply_dir_light(xe_graphics::shader *shd, xe_ecs::dir_light *directional_light, xe_ecs::transform_component *transform)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

        glm::vec3 light_color = glm::vec3(1.0f);
        
        if (directional_light)
        {
            light_color = directional_light->color;
        }

        device->bind_shader(shd);
        device->set_vec3("dir_light_color", light_color, shd);
        device->set_vec3("light_pos", transform->position, shd);
    }

    void apply_spot_light(xe_graphics::shader * shd, xe_ecs::spot_light * directional_light, xe_ecs::transform_component * transform)
    {


    }

    void apply_point_light(xe_graphics::shader * shd, xe_ecs::point_light * directional_light, xe_ecs::transform_component * transform)
    {

    }

    void draw_model(xe_assets::model *mod, xe_graphics::shader *shd)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();

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

    void draw_cube(xe_graphics::texture2D *texture_diff)
    {
        if (texture_diff)
            graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture_diff);
        draw_cube();
    }

    void draw_cube()
    {
        if (!cube_vao.vertex_array)
        {
            create_cube(&cube_vao);
        }

        graphics_device->bind_vertex_array(cube_vao.vertex_array);
        graphics_device->draw_array(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 36);
        graphics_device->unbind_vertex_array();
    }

    void draw_animated_model(xe_assets::AnimatedModel *anim_model, const glm::mat4 &transform)
    {
        shader *animation_shader = xe_render::get_shader("skeletal_animation");
        xe_graphics::graphics_device *device = xe_render::get_device();
        device->bind_shader(animation_shader);        

        xe_graphics::texture2D *texture = xe_render::get_texture2D_resource("gun_diff");

        if (texture != nullptr)
        {
            device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture);           
        }

        xe_ecs::camera3d_component &camera = get_camera3D();

        for (xe_assets::AnimatedNode& mesh : anim_model->anim_meshes)
        {         
            for (size_t i = 0; i < anim_model->bone_transformation.size(); i++)
            {
                std::string uniformName = std::string("u_bones[") + std::to_string(i) + std::string("]");
                device->set_mat4(uniformName, anim_model->bone_transformation[i], animation_shader);
            }

            glm::mat4 ide_model = IDENTITY_MATRIX;
            ide_model = transform * mesh.transform;
            
            device->set_mat4("model", ide_model, animation_shader);
            device->set_mat4("vp", camera.get_view_projection(), animation_shader);
            device->bind_vertex_array(&anim_model->va);
            device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, mesh.index_count, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * mesh.start_index));
        }

        device->unbind_shader();
    }

    void update_anim(xe_assets::AnimatedModel *anim_model)
    {        
       
        
    }

    void draw_line(xe_ecs::entity *ent)
    {
        if (!line_vao.va)
        {
            create_line_mesh(&line_vao);
        }

        using namespace xe_ecs;

        line_mesh_component *line = ent->find_component<line_mesh_component>();

        if (line)
        {
            shader *simple_color = get_shader("simple_pos");
            glm::mat4 model = IDENTITY_MATRIX;
            camera3d_component& cam = get_camera3D();
            
            glm::mat4 mvp = cam.get_projection_matrix() * cam.get_view_matrix() * model;

            graphics_device->bind_shader(simple_color);
            graphics_device->set_mat4("mvp", mvp, simple_color);
            graphics_device->set_vec4("u_color", default_line_color, simple_color);

            graphics_device->bind_vertex_array(line->line_co->va);
            graphics_device->set_line_width(default_line_width);
            graphics_device->draw_array(PRIMITIVE_TOPOLOGY::LINE, 0, line->line_co->vertex_count);
            graphics_device->unbind_vertex_array();
        }
    }

    void draw_ent(xe_ecs::entity *ent)
    {
        using namespace xe_ecs;

        ENTITY_TYPE type = ent->get_type();
        
        switch (type)
        {
        case ENTITY_TYPE::ENT_STATIC_OBJECT:
        case ENTITY_TYPE::ENT_DIR_LIGHT:
            draw_ent_static(ent);
            break;
        case ENTITY_TYPE::ENT_ANIMATED_OBJECT:
            
            break;
        case ENTITY_TYPE::ENT_PRIMITIVE_OBJECT:
            draw_ent_primitive(ent);
            break;
        case ENTITY_TYPE::ENT_WATER:
            draw_water_plane(ent);
            break;
        case ENTITY_TYPE::ENT_LINE:
            draw_line(ent);
            break;
        default:
            xe_utility::debug("Entity type not declared!");
            break;
        }

    }

    void draw_ent_static(xe_ecs::entity *ent)
    {
        using namespace xe_ecs;
        
        xe_graphics::graphics_device *device = xe_render::get_device();

        mesh_component *model = ent->find_component<mesh_component>();
        
        shader *shader_to_draw = nullptr;
        
        if (model)
            shader_to_draw = xe_render::get_shader("base3d");

        if (model->draw_with_color)
            shader_to_draw = xe_render::get_shader("color");

        transform_component *transform = ent->find_component<transform_component>();

        if (transform)
        {
            device->bind_shader(shader_to_draw);

            if (model->draw_with_color)
            {
                device->set_vec3("color", default_cube_color, shader_to_draw);
            }
           
            apply_transform(transform, shader_to_draw);

            /*if (model->diffuse_texture != nullptr)
            {
                device->set_int("tex_diff1", 0, shader_to_draw);
                device->activate_bind_texture(TEXTURE_TYPE::COLOR, model->diffuse_texture);
            }*/

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

        if (transform)
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

    void draw_ent_primitive(xe_ecs::entity *ent)
    {
        using namespace xe_ecs;
        sphere_component *sphere = ent->find_component<sphere_component>();

        if (sphere)
        {
            transform_component *transform = ent->find_component<transform_component>();
            shader *shd = xe_render::get_shader("color");

            graphics_device->bind_shader(shd);
            graphics_device->set_vec3("color", default_cube_color, shd);

            if (sphere->diffuse)
            {
                shd = xe_render::get_shader("simple_tex");
                graphics_device->bind_shader(shd);
                graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, sphere->diffuse);
            }
      
            apply_transform(transform, shd);

            draw_sphere();
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

        device->bind_vertex_array(&msh->vao);
        device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE, msh->indices.size(), GL_UNSIGNED_INT, 0);
    }

    void draw_sphere(xe_graphics::texture2D *texture_diff)
    {
        if (texture_diff)
            graphics_device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture_diff);
        draw_sphere();
    }

    void draw_sphere()
    {
        if (!sphere_vao.vertex_array)
        {            
            create_sphere(&sphere_vao);
        }

        graphics_device->bind_vertex_array(sphere_vao.vertex_array);
        graphics_device->draw_indexed(PRIMITIVE_TOPOLOGY::TRIANGLE_STRIP, sphere_vao.vertex_array->ib->count, GL_UNSIGNED_INT, 0);
        graphics_device->unbind_vertex_array();
    }
}

