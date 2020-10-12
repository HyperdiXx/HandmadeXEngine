
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include FT_PARAMETER_TAGS_H
//#include FT_MODULE_H

global GraphicsState graphics_state = {};
global RenderCommandQueue render_queue = {};

internal
Vec3 convertToVec3(Color3RGB color)
{
    return createVec3(color.x, color.y, color.z);
}

internal
Vec4 convertToVec4(Color4RGBA color)
{
    return createVec4(color.x, color.y, color.z, color.a);
}

internal
Vec4 convertToVec4(Color3RGB color)
{

}

/*internal Camera2DComponent& getCamera2D()
{
    static Camera2DComponent camera2D;

    Viewport vp = graphics_state.graphics_device->getViewport();
    camera2D.width = vp.width;
    camera2D.height = vp.height;

    return camera2D;
}

internal Camera3DComponent& getCamera3D()
{
    static xe_ecs::Camera3DComponent camera3D;
    return camera3D;
};*/

void Render::setDevice(GraphicsDevice *device)
{
    graphics_state.graphics_device = device;
}

void Render::setRenderPass(RenderPass *pass)
{
    graphics_state.active_render_pass = pass;
}

void Render::setActiveFramebuffer(Framebuffer *fbo)
{
    graphics_state.active_framebuffer = fbo;
}

Framebuffer *Render::getActiveFramebuffer()
{
    return graphics_state.active_framebuffer;
}

Shader *Render::getShader(const char *name)
{
    return &graphics_state.shaders[name];
}

Texture2D *Render::getTexture2DResource(const char *name)
{
    return &graphics_state.textures[name];
}

void Render::init(ApiType type)
{
    switch (type)
    {
    case ApiType::OPENGL:
    {
        graphics_state.graphics_device = new GraphicsDeviceGL();
    } break;
    default:
        break;
    }

    loadShaders();
    loadFreeTextures();
};

/*bool32 Render::loadFont(const char *path)
{
    FT_Library lib = {};
    FT_Face face = {};
 
    if (FT_Init_FreeType(&lib))
    {
        print_error("FREETYPE: Couldnt init free type lib");
    }

    if (FT_New_Face(lib, path, 0, &face))
    {
        print_error("FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int c = 0; c < 128; ++c)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            print_error("FREETYPE: Failed to load char");
            continue;
        }

        Texture2D texture_symbol = {};

        graphics_state.graphics_device->createTexture(&texture_symbol);
        graphics_state.graphics_device->bindTexture(TEXTURE_TYPE::COLOR, &texture_symbol);

        graphics_state.graphics_device->loadTextureGpu(TEXTURE_TYPE::COLOR, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_RED, (void**)face->glyph->bitmap.buffer);

        graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

        graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
        graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

        Character chacter =
        {
            texture_symbol.id,
            createVec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            createVec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        characters_map.insert(std::pair<GLchar, Character>(c, chacter));
    }

    graphics_state.graphics_device->unbindTexture(TEXTURE_TYPE::COLOR);
    FT_Done_Face(face);
    FT_Done_FreeType(lib);

    VertexArray *va = new VertexArray();
    VertexBuffer *vb = new VertexBuffer();
    graphics_state.graphics_device->createVertexArray(va);
    graphics_state.graphics_device->bindVertexArray(va);

    graphics_state.graphics_device->createVertexBuffer(NULL, 24 * sizeof(real32), DRAW_TYPE::DYNAMIC, vb);

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list =
    {
        { "aPos",    ElementType::Float4, },
    };

    graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    graphics_state.graphics_device->setVertexBufferLayout(vb, &buffer_layout);
    graphics_state.graphics_device->addVertexBuffer(va, vb);

    graphics_state.graphics_device->unbindBuffer(BUFFER_TYPE::VERTEX);
    graphics_state.graphics_device->unbindVertexArray();

    Matrix4x4 ortho = createMat4x4();

    //ortho = glm::ortho(0.0f, float(WINDOWS_WIDTH), 0.0f, float(WINDOWS_HEIGHT), -1.0f, 1.0f);

    Shader *text_shader = &shaders["text"];

    graphics_state.graphics_device->bindShader(text_shader);
    graphics_state.graphics_device->setMat4("projection", ortho, text_shader);

    return true;
}*/

void Render::addShader(const char *ac_name, Shader shr)
{
    shr.name = ac_name;
    graphics_state.shaders[ac_name] = shr;
}

void Render::addTexture(const char *ac_name, Texture2D tex)
{
    tex.name = ac_name;
    graphics_state.textures[ac_name] = tex;
}

bool32 Render::loadShaders()
{
    Shader simple_shader = {};
    Shader model_shader = {};
    Shader gamma_correction_shader = {};
    Shader color_shader = {};
    Shader text_shader = {};
    Shader cubemap_shader = {};
    Shader post_proc_shader = {};
    Shader shadow_map_shader = {};
    Shader shadow_map_depth_shader = {};
    Shader pbr = {};
    Shader simple_texture = {};
    Shader background_shader = {};
    Shader brdf_shader = {};
    Shader prefilter_shader = {};
    Shader equirectangular_cubemap = {};
    Shader irradiance_shader = {};
    Shader water = {};
    Shader simple_color = {};
    Shader anim_model = {};

    Shader lines = {};

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

    res = graphics_state.graphics_device->createShader("shaders/glsl/lines.vs", "shaders/glsl/lines.fs", &lines);

    res = graphics_state.graphics_device->createShader("shaders/glsl/simple_pos.vs", "shaders/glsl/filledsimple2d.fs", &simple_color);

    res |= graphics_state.graphics_device->createShader("shaders/glsl/anim_model3d.vs", "shaders/glsl/base3d.fs", &anim_model);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/simple2d.vs", "shaders/glsl/simple2d.fs", &simple_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/simple_model.vs", "shaders/glsl/simple2d.fs", &simple_texture);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/model3d.vs", "shaders/glsl/base3d.fs", &model_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/model3d.vs", "shaders/glsl/water.fs", &water);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/Quad.vs", "shaders/glsl/gamma_correction.fs", &gamma_correction_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/simple_model.vs", "shaders/glsl/color.fs", &color_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/text.vs", "shaders/glsl/text.fs", &text_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/cube_map.vs", "shaders/glsl/cube_map.fs", &cubemap_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/shadow_map.vs", "shaders/glsl/shadow_map.fs", &shadow_map_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/shadow_map_extract.vs", "shaders/glsl/shadow_map_extract.fs", &shadow_map_depth_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/Quad.vs", "shaders/glsl/post_proc.fs", &post_proc_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/pbr/pbr.vs", "shaders/glsl/pbr/pbr.fs", &pbr);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/pbr/background.vs", "shaders/glsl/pbr/background.fs", &background_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/pbr/brdf.vs", "shaders/glsl/pbr/brdf.fs", &brdf_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/pbr/cubemap.vs", "shaders/glsl/pbr/pref.fs", &prefilter_shader);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/pbr/cubemap.vs", "shaders/glsl/pbr/equ_to_cubemap.fs", &equirectangular_cubemap);
    res |= graphics_state.graphics_device->createShader("shaders/glsl/pbr/cubemap.vs", "shaders/glsl/pbr/irradiance.fs", &irradiance_shader);

#endif

#ifdef GAPI_DX11



#endif

    addShader("line", lines);
    addShader("simple_pos", simple_color);
    addShader("simple2d", simple_shader);
    addShader("simple_tex", simple_texture);
    addShader("base3d", model_shader);
    addShader("gc", gamma_correction_shader);
    addShader("text", text_shader);
    addShader("cubemap", cubemap_shader);
    addShader("color", color_shader);
    addShader("shadow_map", shadow_map_shader);
    addShader("shadow_depth", shadow_map_depth_shader);
    addShader("post_proc", post_proc_shader);
    addShader("pbr", pbr);
    addShader("background", background_shader);
    addShader("brdf", brdf_shader);
    addShader("prefilter", prefilter_shader);
    addShader("equirect", equirectangular_cubemap);
    addShader("irradiance", irradiance_shader);
    addShader("water", water);
    addShader("skeletal_animation", anim_model);

    if (!res)
    {
        print_error("Loading shaders!!!");
        return false;
    }

    print_info("Shaders loaded!!!");
    return true;
}

bool32 Render::loadFreeTextures()
{
    Texture2D wood_texture = {};
    Texture2D water_texture = {};

    // pbr

    Texture2D albedo_iron = {};
    Texture2D normal_iron = {};
    Texture2D metallic_iron = {};
    Texture2D roughness_iron = {};
    Texture2D ao_iron = {};

    Texture2D albedo_plastic = {};
    Texture2D normal_plastic = {};
    Texture2D metallic_plastic = {};
    Texture2D roughness_plastic = {};
    Texture2D ao_plastic = {};

    Texture2D albedo_grass = {};
    Texture2D normal_grass = {};
    Texture2D metallic_grass = {};
    Texture2D roughness_grass = {};
    Texture2D ao_grass = {};

    Texture2D albedo_gold = {};
    Texture2D normal_gold = {};
    Texture2D metallic_gold = {};
    Texture2D roughness_gold = {};
    Texture2D ao_gold = {};

    Texture2D albedo_wall = {};
    Texture2D normal_wall = {};
    Texture2D metallic_wall = {};
    Texture2D roughness_wall = {};
    Texture2D ao_wall = {};

    // hdr env map
    Texture2D hdr = {};

    Texture2D cerberus_d = {};
    Texture2D cerberus_n = {};
    Texture2D cerberus_r = {};
    Texture2D cerberus_m = {};
    Texture2D cerberus_ao = {};

    Texture2D gun_diff = {};
    Texture2D character_diff = {};

    graphics_state.graphics_device->createTexture2D("assets/cerberus/albedo.tga", &cerberus_d);
    graphics_state.graphics_device->createTexture2D("assets/cerberus/normal.tga", &cerberus_n);
    graphics_state.graphics_device->createTexture2D("assets/cerberus/roughness.tga", &cerberus_r);
    graphics_state.graphics_device->createTexture2D("assets/cerberus/metallic.tga", &cerberus_m);
    graphics_state.graphics_device->createTexture2D("assets/cerberus/ao.tga", &cerberus_ao);

    graphics_state.graphics_device->createTexture2D("assets/pbr/rusted_iron/albedo.png", &albedo_iron);
    graphics_state.graphics_device->createTexture2D("assets/pbr/rusted_iron/normal.png", &normal_iron);
    graphics_state.graphics_device->createTexture2D("assets/pbr/rusted_iron/metallic.png", &metallic_iron);
    graphics_state.graphics_device->createTexture2D("assets/pbr/rusted_iron/roughness.png", &roughness_iron);
    graphics_state.graphics_device->createTexture2D("assets/pbr/rusted_iron/ao.png", &ao_iron);

    graphics_state.graphics_device->createTexture2D("assets/pbr/grass/albedo.png", &albedo_grass);
    graphics_state.graphics_device->createTexture2D("assets/pbr/grass/normal.png", &normal_grass);
    graphics_state.graphics_device->createTexture2D("assets/pbr/grass/metallic.png", &metallic_grass);
    graphics_state.graphics_device->createTexture2D("assets/pbr/grass/roughness.png", &roughness_grass);
    graphics_state.graphics_device->createTexture2D("assets/pbr/grass/ao.png", &ao_grass);

    graphics_state.graphics_device->createTexture2D("assets/pbr/wall/albedo.png", &albedo_wall);
    graphics_state.graphics_device->createTexture2D("assets/pbr/wall/normal.png", &normal_wall);
    graphics_state.graphics_device->createTexture2D("assets/pbr/wall/metallic.png", &metallic_wall);
    graphics_state.graphics_device->createTexture2D("assets/pbr/wall/roughness.png", &roughness_wall);
    graphics_state.graphics_device->createTexture2D("assets/pbr/wall/ao.png", &ao_wall);

    graphics_state.graphics_device->createTexture2D("assets/pbr/plastic/albedo.png", &albedo_plastic);
    graphics_state.graphics_device->createTexture2D("assets/pbr/plastic/normal.png", &normal_plastic);
    graphics_state.graphics_device->createTexture2D("assets/pbr/plastic/metallic.png", &metallic_plastic);
    graphics_state.graphics_device->createTexture2D("assets/pbr/plastic/roughness.png", &roughness_plastic);
    graphics_state.graphics_device->createTexture2D("assets/pbr/plastic/ao.png", &ao_plastic);

    graphics_state.graphics_device->createTexture2D("assets/pbr/gold/albedo.png", &albedo_gold);
    graphics_state.graphics_device->createTexture2D("assets/pbr/gold/normal.png", &normal_gold);
    graphics_state.graphics_device->createTexture2D("assets/pbr/gold/metallic.png", &metallic_gold);
    graphics_state.graphics_device->createTexture2D("assets/pbr/gold/roughness.png", &roughness_gold);
    graphics_state.graphics_device->createTexture2D("assets/pbr/gold/ao.png", &ao_gold);

    graphics_state.graphics_device->createTexture2D("assets/m1911/m1911_color.png", &gun_diff);
    graphics_state.graphics_device->createTexture2D("assets/animated/character_diff.jpg", &character_diff);

    //graphics_state.graphics_device->createTexture2D("assets/hdr/barce_3k.hdr", TEXTURE_TYPE::HDR, false, &hdr);

    bool32 loaded = graphics_state.graphics_device->createTexture2D("assets/get.png", &wood_texture);
    graphics_state.graphics_device->createTexture2D("assets/water-texture.jpg", &water_texture);

    if (!loaded)
    {
        print_error("Failed to load free texture");
        return false;
    }

    addTexture("gun_diff", gun_diff);
    addTexture("girl_diffuse", character_diff);

    addTexture("wood", wood_texture);
    addTexture("water", water_texture);

    addTexture("albedo_iron", albedo_iron);
    addTexture("normal_iron", normal_iron);
    addTexture("metallic_iron", metallic_iron);
    addTexture("roughness_iron", roughness_iron);
    addTexture("ao_iron", ao_iron);

    addTexture("albedo_grass", albedo_grass);
    addTexture("normal_grass", normal_grass);

    addTexture("metallic_grass", metallic_grass);
    addTexture("roughness_grass", roughness_grass);
    addTexture("ao_grass", ao_grass);

    addTexture("albedo_wall", albedo_wall);
    addTexture("normal_wall", normal_wall);
    addTexture("metallic_wall", metallic_wall);
    addTexture("roughness_wall", roughness_wall);;
    addTexture("ao_wall", ao_wall);

    addTexture("albedo_gold", albedo_gold);
    addTexture("normal_gold", normal_gold);
    addTexture("metallic_gold", metallic_gold);
    addTexture("roughness_gold", roughness_gold);
    addTexture("ao_gold", ao_gold);

    addTexture("albedo_plastic", albedo_plastic);
    addTexture("normal_plastic", normal_plastic);
    addTexture("metallic_plastic", metallic_plastic);
    addTexture("roughness_plastic", roughness_plastic);
    addTexture("ao_plastic", ao_plastic);

    addTexture("hdr_env", hdr);
    addTexture("cerberus_d", cerberus_d);
    addTexture("cerberus_n", cerberus_n);
    addTexture("cerberus_r", cerberus_r);
    addTexture("cerberus_m", cerberus_m);
    addTexture("cerberus_ao", cerberus_ao);
  
    print_info("Free textures loaded!!!");
    return true;
}

bool32 Render::initRenderGL()
{
    bool32 loaded_shaders = false;
    bool32 loaded_tex = false;
    bool32 loaded_font = false;

    if (!loadShaders())
    {
        print_error("Failed to init shader module!");
    }
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

    if (!loadFreeTextures())
    {
        print_error("Failed to init textures module!");
    }

    /*if (!loadFont("assets/fonts/arial.ttf"))
    {
        print_error("Failed to init font module!");
    }*/

    initCommonGpuResources();

    return true;
}

bool32 Render::initRenderDX11()
{

    return true;
}

void Render::initGui()
{
    //@ Add from GUI Init
    //initImguiImpl();
}

bool32 Render::initCommonGpuResources()
{
    /*if (skybox_obj == nullptr)
    {
        skybox_obj = new Skybox();
    }

    bool32 is_skybox_created = createSkybox(skybox_obj);

    if (!is_skybox_created)
    {
        xe_utility::error("Failed to init skybox!");
        return false;
    }

    Shader *texture_shader = getShader("simple_tex");

    graphics_state.graphics_state.graphics_device->bindShader(texture_shader);
    graphics_state.graphics_state.graphics_device->setInt("tex_diff", 0, texture_shader);

    Shader *pbr = getShader("pbr");

    graphics_state.graphics_state.graphics_device->bindShader(pbr);
    graphics_state.graphics_state.graphics_device->setInt("irradiance_map", 0, pbr);
    graphics_state.graphics_state.graphics_device->setInt("prefilter_map", 1, pbr);
    graphics_state.graphics_state.graphics_device->setInt("brdf_LUT", 2, pbr);

    graphics_state.graphics_state.graphics_device->setInt("albedo_map", 3, pbr);
    graphics_state.graphics_state.graphics_device->setInt("normal_map", 4, pbr);
    graphics_state.graphics_state.graphics_device->setInt("metallic_map", 5, pbr);
    graphics_state.graphics_state.graphics_device->setInt("roughness_map", 6, pbr);
    graphics_state.graphics_state.graphics_device->setInt("ao_map", 7, pbr);

    Shader *equ_to_cubemap = getShader("equirect");

    graphics_state.graphics_state.graphics_device->bindShader(equ_to_cubemap);
    graphics_state.graphics_state.graphics_device->setInt("equirectangular_map", 0, equ_to_cubemap);

    Shader *animation = getShader("skeletal_animation");
    graphics_state.graphics_state.graphics_device->bindShader(animation);
    graphics_state.graphics_state.graphics_device->setInt("tex_diff1", 0, animation);
    //graphics_state.graphics_state.graphics_device->set_int("tex_norm1", 1, animation);


    createLinesBuffer();
    createQuadBuffer();*/

    return true;
}

void Render::clear(uint32 flags)
{
    Render::pushCommand([=]() 
    {
        graphics_state.graphics_device->clearColor(graphics_state.target_clear_color);
        graphics_state.graphics_device->clear(flags);
    });
}

void Render::clearColor(real32 x, real32 y, real32 z, real32 a)
{
    graphics_state.target_clear_color.x = x;
    graphics_state.target_clear_color.y = y;
    graphics_state.target_clear_color.z = z;
    graphics_state.target_clear_color.w = a;
}

void Render::shutdown()
{
    // @Clear destroy free textures

    std::unordered_map<const char*, Texture2D>::iterator it = graphics_state.textures.begin();
    for (uint32 i = 0; i < graphics_state.textures.size(); ++i)
    {
        graphics_state.graphics_device->destroyTexture2D(&it->second);
    }

    //clearContextGui();
}

/*internal bool32 createMesh(Mesh *meh, Vertex *vertex_type, bool32 calculate_tspace)
{
    Vertex *vert = vertex_type;

    meh->vao.buffers.push_back(new VertexBuffer());
    meh->vao.ib = new IndexBuffer();

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list;

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

    graphics_state.graphics_state.graphics_device->createVertexArray(&meh->vao);
    graphics_state.graphics_state.graphics_device->bindVertexArray(&meh->vao);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(&meh->vertices_fl[0], meh->vertices_fl.size() * sizeof(real32), DRAW_TYPE::STATIC, meh->vao.buffers[0]);

    // TODO: rework
    graphics_state.graphics_state.graphics_device->createIndexBuffer(&meh->indices[0], meh->indices.size(), meh->vao.ib);

    graphics_state.graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(meh->vao.buffers[0], &buffer_layout);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(&meh->vao, meh->vao.buffers[0]);
    graphics_state.graphics_state.graphics_device->setIndexBuffer(&meh->vao, meh->vao.ib);

    graphics_state.graphics_state.graphics_device->unbindVertexArray();
    graphics_state.graphics_state.graphics_device->destroyBuffer(meh->vao.buffers[0]);
    graphics_state.graphics_state.graphics_device->destroyBuffer(meh->vao.ib);

    return true;
}*/

bool32 Render::createLineMesh(const Vec3 &start, const Vec3 &end, LineMesh *line_com)
{
    /*std::vector<real32> array_vertex;

    array_vertex.push_back(start.x);
    array_vertex.push_back(start.y);
    array_vertex.push_back(start.z);
    array_vertex.push_back(end.x);
    array_vertex.push_back(end.y);
    array_vertex.push_back(end.z);

    line_com->va = alloc_mem VertexArray();
    line_com->va->buffers.push_back(alloc_mem VertexBuffer());

    line_com->vertex_count = array_vertex.size();

    graphics_state.graphics_state.graphics_device->createVertexArray(line_com->va);
    graphics_state.graphics_state.graphics_device->bindVertexArray(line_com->va);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(&array_vertex[0], line_com->vertex_count * sizeof(real32), DRAW_TYPE::STATIC, line_com->va->buffers[0]);

    using namespace xe_graphics;

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list =
    {
        { "aPos",    ElementType::Float3, }
    };

    graphics_state.graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(line_com->va->buffers[0], &buffer_layout);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(line_com->va, line_com->va->buffers[0]);*/

    return true;
}

bool32 Render::createLineMesh(LineMesh *line_com)
{
    Vec3 start = createVec3(0.0f, 0.0f, 0.0f);
    Vec3 end = createVec3(1.0f, 1.0f, 0.0f);
    return createLineMesh(start, end, line_com);
}

bool32 Render::createLinesBuffer()
{
    /*graphics_state.line_vb_base = alloc_mem LineVertexMesh[graphics_state.max_line_vert];

    graphics_state.graphics_state.graphics_device->createVertexArray(&graphics_state.line_vertex_array);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(nullptr, graphics_state.max_line_vert * sizeof(LineVertexMesh), DRAW_TYPE::DYNAMIC, &graphics_state.line_vertex_buffer);

    BufferLayout buffer_layout3 = {};

    std::initializer_list<BufferElement> init_list3 =
    {
        { "aPos",       ElementType::Float3, },
        { "aColor",     ElementType::Float4 }
    };

    graphics_state.graphics_state.graphics_device->createBufferLayout(init_list3, &buffer_layout3);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(&graphics_state.line_vertex_buffer, &buffer_layout3);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(&graphics_state.line_vertex_array, &graphics_state.line_vertex_buffer);

    uint32* line_ind = alloc_mem uint32[graphics_state.max_line_ind];
    for (uint32_t i = 0; i < graphics_state.max_line_ind; i++)
    {
        line_ind[i] = i;
    }

    IndexBuffer *ib = alloc_mem IndexBuffer();

    graphics_state.graphics_state.graphics_device->createIndexBuffer(line_ind, graphics_state.max_line_ind, ib);
    graphics_state.graphics_state.graphics_device->setIndexBuffer(&graphics_state.line_vertex_array, ib);

    free_mem[] line_ind;*/

    return true;
}

bool32 Render::createQuadBuffer()
{
    /*graphics_state.quad_vertex_data[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    graphics_state.quad_vertex_data[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
    graphics_state.quad_vertex_data[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
    graphics_state.quad_vertex_data[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

    graphics_state.quad_vb_base = alloc_mem QuadVertexMesh[graphics_state.max_quad_vert];

    graphics_state.graphics_state.graphics_device->createVertexArray(&graphics_state.quad_vertex_array);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(nullptr, graphics_state.max_quad_vert * sizeof(QuadVertexMesh), DRAW_TYPE::DYNAMIC, &graphics_state.quad_vertex_buffer);

    BufferLayout quad_buffer_layout = {};

    std::initializer_list<BufferElement> quad_init_list =
    {
        { "aPos",       ElementType::Float3, },
        { "aColor",     ElementType::Float4 }
    };

    graphics_state.graphics_state.graphics_device->createBufferLayout(quad_init_list, &quad_buffer_layout);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(&graphics_state.quad_vertex_buffer, &quad_buffer_layout);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(&graphics_state.quad_vertex_array, &graphics_state.quad_vertex_buffer);

    uint32* quad_ind = alloc_mem uint32[graphics_state.max_quad_indices];
    uint32 offset = 0;

    for (uint32 i = 0; i < graphics_state.max_quad_indices; i += 6)
    {
        quad_ind[i + 0] = offset + 0;
        quad_ind[i + 1] = offset + 1;
        quad_ind[i + 2] = offset + 2;

        quad_ind[i + 3] = offset + 2;
        quad_ind[i + 4] = offset + 3;
        quad_ind[i + 5] = offset + 0;

        offset += 4;
    }

    IndexBuffer *ib = alloc_mem IndexBuffer();

    graphics_state.graphics_state.graphics_device->createIndexBuffer(quad_ind, graphics_state.max_quad_indices, ib);
    graphics_state.graphics_state.graphics_device->setIndexBuffer(&graphics_state.quad_vertex_array, ib);

    free_mem[] quad_ind;*/

    return true;
}

bool32 Render::createRenderPass(const RenderPassData & data, RenderPass *rp)
{


    return true;
}

bool32 Render::createCubemap(std::vector<const char*> paths, Cubemap *cube)
{
    for (uint32 i = 0; i < paths.size(); ++i)
    {
        //graphics_state.graphics_state.graphics_device->createTexture2D(paths[i], cube->face_textures[i]);
    }

    return true;
}

bool32 Render::createQuad()
{
    /*real32 vertices[] =
    {
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };*/

    uint32 indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    //int vertex_size = sizeof(graphics_state.quad_vertex_data) / sizeof(graphics_state.quad_vertex_data[0]);
    //int indices_size = sizeof(indices) / sizeof(indices[0]);

    /*graphics_state.quad_vertex_array.buffers.push_back(alloc_mem VertexBuffer);
    graphics_state.quad_vertex_array.ib = alloc_mem IndexBuffer;

    graphics_state.graphics_state.graphics_device->createVertexArray(&graphics_state.quad_vertex_array);
    graphics_state.graphics_state.graphics_device->bindVertexArray(&graphics_state.quad_vertex_array);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(graphics_state.quad_vertex_data, vertex_size * sizeof(real32), DRAW_TYPE::STATIC, graphics_state.quad_vertex_array.buffers[0]);
    graphics_state.graphics_state.graphics_device->createIndexBuffer(indices, indices_size, graphics_state.quad_vertex_array.ib);

    using namespace xe_graphics;

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list =
    {
        { "aPos",    ElementType::Float3, },
        { "aUV",     ElementType::Float2, }
    };

    //graphics_state.graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    //graphics_state.graphics_state.graphics_device->setVertexBufferLayout(q->vertex_array->buffers[0], &buffer_layout);        
    //graphics_state.graphics_state.graphics_device->addVertexBuffer(q->vertex_array, q->vertex_array->buffers[0]);
    //graphics_state.graphics_state.graphics_device->setIndexBuffer(q->vertex_array, q->vertex_array->ib);
    */
    return true;
}

bool32 Render::createFullquad()
{
    glGenVertexArrays(1, &graphics_state.quad_vao.id);

    return true;
}

bool32 Render::createSkybox(Skybox *sky)
{
    /*real32 skybox_vertices[] =
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

    sky->va = new VertexArray();
    sky->vb = new VertexBuffer();

    graphics_state.graphics_state.graphics_device->createVertexArray(sky->va);
    graphics_state.graphics_state.graphics_device->createVertexBuffer(skybox_vertices, vertex_size * sizeof(real32), DRAW_TYPE::STATIC, sky->vb);

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list =
    {
        { "aPos",    ElementType::Float3, }
    };

    graphics_state.graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(sky->vb, &buffer_layout);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(sky->va, sky->vb);

    sky->cubemap = alloc_mem Cubemap();

    if (!createCubemap(sky->cubemap))
    {
        return false;
    }*/

    return true;
}

bool32 Render::createCubemap(Cubemap *cube)
{
    /*cube->face_textures.reserve(16);

    std::vector<const char*> skybox_faces;
    skybox_faces.push_back("lakes_rt.tga");
    skybox_faces.push_back("lakes_lf.tga");
    skybox_faces.push_back("lakes_up.tga");
    skybox_faces.push_back("lakes_dn.tga");
    skybox_faces.push_back("lakes_bk.tga");
    skybox_faces.push_back("lakes_ft.tga");

    Texture2D *cubemap_texture = new Texture2D();
    cubemap_texture->desc.texture_type = CUBEMAP;
    cubemap_texture->desc.dimension = TEXTURE_2D;

    graphics_state.graphics_state.graphics_device->createTexture(cubemap_texture);
    graphics_state.graphics_state.graphics_device->bindTexture(TEXTURE_TYPE::CUBEMAP, cubemap_texture);

    for (uint32 i = 0; i < skybox_faces.size(); i++)
    {
        int channels = 0;
        std::string final_path = "assets/skybox/" + std::string(skybox_faces[i]);
        void *texture_data = xe_core::loadTextureFromDisc(final_path.c_str(), cubemap_texture->desc.width, cubemap_texture->desc.height, channels, 0, false);

        graphics_state.graphics_state.graphics_device->loadTextureGpu(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap_texture->desc.width, cubemap_texture->desc.height, GL_RGB, GL_RGB, texture_data);

        xe_core::deleteData(texture_data);
    }

    graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

    graphics_state.graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
    graphics_state.graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

    cube->id = cubemap_texture->id;

    Shader *cubemap_shader = &shaders["cubemap"];
    graphics_state.graphics_state.graphics_device->bindShader(cubemap_shader);
    graphics_state.graphics_state.graphics_device->setInt("skybox", 0, cubemap_shader);
    */
    return true;
}

bool32 Render::createShadowMaps(ShadowMap *shadow)
{
    const uint32 SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
    const uint32 WIDTH = 1280, HEIGHT = 720;

    /*shadow->depth_fbo = {};

    shadow->width_map = SHADOW_WIDTH;
    shadow->height_map = SHADOW_HEIGHT;

    graphics_state.graphics_state.graphics_device->createFramebuffer(1, &shadow->depth_fbo);
    graphics_state.graphics_state.graphics_device->addDepthTexture2D(SHADOW_WIDTH, SHADOW_HEIGHT, &shadow->depth_fbo);

    real32 colorattach[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, colorattach);

    graphics_state.graphics_state.graphics_device->bindFramebuffer(&shadow->depth_fbo);
    graphics_state.graphics_state.graphics_device->setTexture2DFbo(GL_DEPTH_ATTACHMENT, TEXTURE_TYPE::DEPTH, shadow->depth_fbo.depth_texture);
    graphics_state.graphics_state.graphics_device->setDrawBuffer(GL_NONE);
    graphics_state.graphics_state.graphics_device->setReadBuffer(GL_NONE);
    graphics_state.graphics_state.graphics_device->unbindFramebuffer();

    Framebuffer hdr = {};
    graphics_state.graphics_state.graphics_device->createFramebuffer(1, &hdr);
    graphics_state.graphics_state.graphics_device->bindFramebuffer(&hdr);

    Texture2D color_attach[2];

    graphics_state.graphics_state.graphics_device->createTexture(2, color_attach);

    //unsigned int colorBuffers[2];
    //glGenTextures(2, colorBuffers);

    for (uint32 i = 0; i < 2; ++i)
    {
        graphics_state.graphics_state.graphics_device->bindTexture(TEXTURE_TYPE::COLOR, &color_attach[i]);
        graphics_state.graphics_state.graphics_device->loadTextureGpu(TEXTURE_TYPE::COLOR, WIDTH, HEIGHT, GL_RGB16F, GL_RGB, NULL);

        graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

        graphics_state.graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
        graphics_state.graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

        graphics_state.graphics_state.graphics_device->setTexture2DFbo(GL_COLOR_ATTACHMENT0 + i, TEXTURE_TYPE::COLOR, &color_attach[i]);

        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, &color_attach->desc[i], 0);
    }

    graphics_state.graphics_state.graphics_device->createRenderbuffer(1, &shadow->depth_fbo);

    graphics_state.graphics_state.graphics_device->bindRenderbuffer(&shadow->depth_fbo);

    uint32 attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    graphics_state.graphics_state.graphics_device->setDrawBuffers(2, attachments);

    graphics_state.graphics_state.graphics_device->checkFramebuffer();
    graphics_state.graphics_state.graphics_device->unbindFramebuffer();

    Framebuffer p_fbo[2];
    Texture2D p_color_buffer[2];

    //glGenFramebuffers(2, pingphongFBO);
    //glGenTextures(2, pingcolorBuffer);

    for (uint16 i = 0; i < 2; ++i)
    {
        graphics_state.graphics_state.graphics_device->createFramebuffer(1, p_fbo + i);
    }

    for (uint16 j = 0; j < 2; ++j)
    {
        graphics_state.graphics_state.graphics_device->createTexture(1, p_color_buffer + j);
    }

    for (uint16 i = 0; i < 2; ++i)
    {
        graphics_state.graphics_state.graphics_device->bindFramebuffer(p_fbo + i);
        graphics_state.graphics_state.graphics_device->bindTexture(TEXTURE_TYPE::COLOR, p_color_buffer + i);

        //glBindFramebuffer(GL_FRAMEBUFFER, pingphongFBO[i]);
        //glBindTexture(GL_TEXTURE_2D, pingcolorBuffer[i]);

        graphics_state.graphics_state.graphics_device->loadTextureGpu(TEXTURE_TYPE::COLOR, WIDTH, HEIGHT, GL_RGB16F, GL_RGB, NULL);

        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);

        graphics_state.graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
        graphics_state.graphics_state.graphics_device->setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

        graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
        graphics_state.graphics_state.graphics_device->setTextureWrapping(TEXTURE_TYPE::COLOR, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        //graphics_state.graphics_state.graphics_device->addColorTexture2D(p_color_buffer + i, i, p_fbo + i);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingcolorBuffer[i], 0);

        graphics_state.graphics_state.graphics_device->checkFramebuffer();
    }*/

    return true;
}

bool32 Render::createSphere(SphereMesh *sphre)
{
    sphre->vertex_array = new VertexArray();
    sphre->vertex_array->buffers.push_back(new VertexBuffer());
    sphre->vertex_array->ib = new IndexBuffer();

    std::vector<Vec3> positions = {};
    std::vector<Vec2> uv = {};
    std::vector<Vec3> normals = {};
    std::vector<uint32> indices = {};

    /*for (uint32 y = 0; y <= 64; ++y)
    {
        for (uint32 x = 0; x <= 64; ++x)
        {
            real32 xSegment = (real32)x / (real32)64;
            real32 ySegment = (real32)y / (real32)64;
            real32 xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            real32 yPos = std::cos(ySegment * PI);
            real32 zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(createVec3(xPos, yPos, zPos));
            uv.push_back(createVec2(xSegment, ySegment));
            normals.push_back(createVec3(xPos, yPos, zPos));
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

    std::vector<real32> data = {};
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

    graphics_state.graphics_state.graphics_device->createVertexArray(sphre->vertex_array);
    graphics_state.graphics_state.graphics_device->bindVertexArray(sphre->vertex_array);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(&data[0], data.size() * sizeof(real32), DRAW_TYPE::STATIC, sphre->vertex_array->buffers[0]);
    graphics_state.graphics_state.graphics_device->createIndexBuffer(&indices[0], indices.size(), sphre->vertex_array->ib);

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list =
    {
        { "aPos",       ElementType::Float3, },
        { "aUV",        ElementType::Float2, },
        { "aNormal",    ElementType::Float3, }
    };

    graphics_state.graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(sphre->vertex_array->buffers[0], &buffer_layout);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(sphre->vertex_array, sphre->vertex_array->buffers[0]);
    graphics_state.graphics_state.graphics_device->setIndexBuffer(sphre->vertex_array, sphre->vertex_array->ib);

    sphre->vertex_array->ib->count = indices.size();*/

    return true;
}

bool32 Render::createCube(CubeMesh *cube)
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

    cube->vertex_array = new VertexArray();
    cube->vertex_array->buffers.push_back(new VertexBuffer());

    /*graphics_state.graphics_state.graphics_device->createVertexArray(cube->vertex_array);
    graphics_state.graphics_state.graphics_device->bindVertexArray(cube->vertex_array);

    uint32 size = sizeof(data) / sizeof(data[0]);

    graphics_state.graphics_state.graphics_device->createVertexBuffer(&data[0], size * sizeof(real32), DRAW_TYPE::STATIC, cube->vertex_array->buffers[0]);

    BufferLayout buffer_layout = {};

    std::initializer_list<BufferElement> init_list =
    {
        { "aPos",       ElementType::Float3, },
        { "aNormal",    ElementType::Float3, },
        { "aUV",        ElementType::Float2, }
    };

    graphics_state.graphics_state.graphics_device->createBufferLayout(init_list, &buffer_layout);
    graphics_state.graphics_state.graphics_device->setVertexBufferLayout(cube->vertex_array->buffers[0], &buffer_layout);
    graphics_state.graphics_state.graphics_device->addVertexBuffer(cube->vertex_array, cube->vertex_array->buffers[0]);*/

    return true;
}

void Render::drawFullquad()
{
    graphics_state.graphics_device->bindVertexArray(&graphics_state.quad_vao);
    graphics_state.graphics_device->drawArray(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 6);
    graphics_state.graphics_device->unbindVertexArray();
}

void Render::drawQuad(const Vec2 &pos, const Vec2 &size, const Color4RGBA &color)
{
    drawQuad({ pos.x, pos.y, 0.0f }, size, color);
}

void Render::drawQuad(const Vec3 &pos, const Vec2 &size, const Color4RGBA& color)
{
    /*if (graphics_state.quad_index_count >= RenderState::max_quads_count)
    {
        //FlushAndResetLines();
    }

    Matrix4x4 transform = translate(IDENTITY_MATRIX, pos) *
        scale(IDENTITY_MATRIX, { size.x, size.y, 1.0f });

    graphics_state.quads_count++;

    graphics_state.quad_vb_ptr->pos = transform * graphics_state.quad_vertex_data[0];
    graphics_state.quad_vb_ptr->color = color;
    graphics_state.quad_vb_ptr++;

    graphics_state.quad_vb_ptr->pos = transform * graphics_state.quad_vertex_data[1];
    graphics_state.quad_vb_ptr->color = color;
    graphics_state.quad_vb_ptr++;

    graphics_state.quad_vb_ptr->pos = transform * graphics_state.quad_vertex_data[2];
    graphics_state.quad_vb_ptr->color = color;
    graphics_state.quad_vb_ptr++;

    graphics_state.quad_vb_ptr->pos = transform * graphics_state.quad_vertex_data[3];
    graphics_state.quad_vb_ptr->color = color;
    graphics_state.quad_vb_ptr++;

    graphics_state.quad_index_count += 6;*/
}

void Render::drawQuad(real32 x, real32 y, real32 w, real32 h, const Color4RGBA& color)
{
    drawQuad({ x, y, 0.0f }, { w, h }, color);
}

void Render::drawQuad(real32 x, real32 t, real32 w, real32 h, Texture2D *texture)
{
    /*if (texture != nullptr)
    {
        graphics_state.graphics_state.graphics_device->bindTexture(TEXTURE_TYPE::COLOR, texture);
    }

    q->vertex_array = rect_vao.vertex_array;

    glm::mat4 model = IDENTITY_MATRIX;

    graphics_state.graphics_state.graphics_device->bindShader(shd);

    if (q->w == 0 || q->h == 0)
    {
        q->w = 10;
        q->h = 10;
    }

    model = glm::translate(model, glm::vec3(q->x, q->y, 0));
    model = glm::scale(model, glm::vec3(q->w, q->h, 1.0f));

    xe_ecs::Camera2DComponent& camera2d = getCamera2D();

    glm::mat4 view_projection = camera2d.get_view_projection();
    graphics_state.graphics_state.graphics_device->setMat4("mvp", view_projection * model, shd);

    graphics_state.graphics_state.graphics_device->bindVertexArray(q->vertex_array);
    graphics_state.graphics_state.graphics_device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);
    graphics_state.graphics_state.graphics_device->unbindVertexArray();
    graphics_state.graphics_state.graphics_device->unbindShader();*/


}

/*void drawQuad(Shader *shd, Texture2D *texture)
{
    using namespace xe_ecs;
    QuadComponent* mesh = ent->findComponent<QuadComponent>();
    TransformComponent *tr = ent->findComponent<TransformComponent>();

    if (mesh == nullptr)
        return;

    graphics_state.graphics_state.graphics_device->bindShader(shd);

    if (texture != nullptr)
        graphics_state.graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::COLOR, texture);

    glm::mat4 model_matrix = IDENTITY_MATRIX;

    model_matrix = glm::translate(model_matrix, tr->position);
    model_matrix = glm::scale(model_matrix, tr->scale);

    xe_ecs::Camera2DComponent& camera2d = getCamera2D();

    glm::mat4 view_projection = camera2d.get_view_projection();
    glm::mat4 mvp = view_projection * model_matrix;

    graphics_state.graphics_state.graphics_device->setMat4("mvp", mvp, shd);

    graphics_state.graphics_state.graphics_device->bindVertexArray(mesh->quad_mesh->vertex_array);

    graphics_state.graphics_state.graphics_device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);

    graphics_state.graphics_state.graphics_device->unbindVertexArray();
    graphics_state.graphics_state.graphics_device->unbindShader();
}*/

void Render::drawQuad(Shader *shd, Texture2D *texture, const Matrix4x4 &mod)
{
    /*if (texture != nullptr)
        graphics_state.graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::COLOR, texture);

    graphics_state.graphics_state.graphics_device->bindShader(shd);

    xe_ecs::Camera2DComponent camera2d = getCamera2D();

    glm::mat4 view_projection = camera2d.get_view_projection();
    glm::mat4 mvp = view_projection * mod;

    graphics_state.graphics_state.graphics_device->setMat4("mvp", mvp, shd);

    graphics_state.graphics_state.graphics_device->bindVertexArray(q->vertex_array);

    graphics_state.graphics_state.graphics_device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE, 6, GL_UNSIGNED_INT, 0);

    graphics_state.graphics_state.graphics_device->unbindVertexArray();
    graphics_state.graphics_state.graphics_device->unbindShader();*/
}

/*void Render::drawModel(Model *mod, Shader *shd, const Matrix4x4 &transform)
{
    GraphicsDevice *device = xe_render::getDevice();
    xe_assets::Node *root = mod->root;

    for (uint32 i = 0; i < root->children.size(); i++)
    {
        xe_assets::Node* curr_node = root->children[i];

        for (uint32 j = 0; j < curr_node->meshes.size(); j++)
        {
            xe_assets::Mesh *cur_mesh = curr_node->meshes.at(j);
            drawMesh(cur_mesh, shd);
        }
    }

    device->unbindShader();
}*/

/*void drawModel(xe_assets::AnimModel *mod, Shader *shd, const Matrix4x4 &transform)
{
    GraphicsDevice *device = xe_render::getDevice();
    device->bindShader(shd);

    Texture2D *texture_diff = xe_render::getTexture2DResource("girl_diffuse");
    Texture2D *texture_norm = xe_render::getTexture2DResource("girl_norm");

    if (texture_diff != nullptr && texture_norm != nullptr)
    {
        device->activateBindTexture(TEXTURE_TYPE::COLOR, texture_diff);
        //device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture_diff);
    }

    Camera3DComponent &camera = getCamera3D();

    for (xe_assets::AnimNode& mesh : mod->anim_meshes)
    {
        for (size_t i = 0; i < mod->bone_transformation.size(); i++)
        {
            std::string uniformName = std::string("u_bones[") + std::to_string(i) + std::string("]");
            device->setMat4(uniformName, mod->bone_transformation[i], shd);
        }

        glm::mat4 ide_model = IDENTITY_MATRIX;
        ide_model = transform * mesh.transform;

        device->setMat4("model", ide_model, shd);
        device->setMat4("vp", camera.get_view_projection(), shd);
        device->bindVertexArray(&mod->va);
        device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE, mesh.index_count, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * mesh.start_index));
    }

    device->unbindShader();
}*/

void Render::drawText(const std::string &text, real32 x, real32 y, Vec3 &color, real32 scale)
{
    graphics_state.graphics_device->enable(GL_BLEND);
    graphics_state.graphics_device->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader *text_shader = getShader("text");

    graphics_state.graphics_device->bindShader(text_shader);
    graphics_state.graphics_device->setVec3("color", color, text_shader);

    graphics_state.graphics_device->activateTexture(0);

    VertexArray va = {};
    va.id = 1;

    graphics_state.graphics_device->bindVertexArray(&va);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = graphics_state.characters_map.at(*c);

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

        graphics_state.graphics_device->bindTexture(TEXTURE_TYPE::COLOR, ch.texture_id);

        //glBindTexture(GL_TEXTURE_2D, ch.texture_id);

        glBindBuffer(GL_ARRAY_BUFFER, 1);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        graphics_state.graphics_device->unbindBuffer(BUFFER_TYPE::VERTEX);

        graphics_state.graphics_device->drawArray(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 6);

        x += (ch.advance >> 6) * scale;
    }

    graphics_state.graphics_device->unbindVertexArray();
    graphics_state.graphics_device->unbindTexture(TEXTURE_TYPE::COLOR);

    graphics_state.graphics_device->disable(GL_BLEND);
}

void Render::drawText(const std::string &text, Vec2 &pos, Vec3 &color)
{
    //drawText(text, pos.x, pos.y, color, default_text_scale);
}

void Render::drawText(const std::string &text, Vec2 &pos)
{
    drawText(text, pos.x, pos.y, graphics_state.default_text_color, graphics_state.default_text_scale);
}

void Render::drawText(const std::string &text, real32 x, real32 y)
{
    drawText(text, x, y, graphics_state.default_text_color, graphics_state.default_text_scale);
}

void Render::drawText(const std::string & text, real32 x, real32 y, real32 scale)
{
    //Vec3 text_color = convertToVec3(default_text_color);
    drawText(text, x, y, graphics_state.default_text_color, scale);
}

void Render::drawWaterPlane(Entity *ent)
{
    /*Shader *water = xe_render::getShader("water");

    graphics_state.graphics_state.graphics_device->bindShader(water);

    WaterComponent *water_comp = ent->findComponent<xe_ecs::WaterComponent>();
    MeshComponent *mesh = ent->findComponent<xe_ecs::MeshComponent>();
    TransformComponent *transform = ent->findComponent<xe_ecs::TransformComponent>();

    Matrix4x4 model_matrix = IDENTITY_MATRIX;

    model_matrix = translateMat(model_matrix, transform->position);
    model_matrix = scaleMat(model_matrix, transform->scale);

    Camera3DComponent cam = getCamera3D();

    Matrix4x4 view_matrix = cam.get_view_matrix();
    Matrix4x4 proj_matrix = cam.get_projection_matrix();

    Matrix4x4 mvp = proj_matrix * view_matrix * model_matrix;

    graphics_state.graphics_state.graphics_device->setMat4("mvp", mvp, water);
    graphics_state.graphics_state.graphics_device->setMat4("model", model_matrix, water);

    graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::COLOR, water_comp->water_tex);
    drawModel(mesh->model_asset, water);*/
}

void Render::drawSkybox()
{
    /*graphics_state.graphics_device->setDepthFunc(GL_LEQUAL);
    Shader *cubemap_shader = xe_render::getShader("cubemap");

    graphics_state.graphics_device->bindShader(cubemap_shader);

    Camera3DComponent camera = getCamera3D();

    Matrix4x4 view = createMat4(createMatrix3x3(camera.get_view_matrix()));

    graphics_state.graphics_device->setMat4("view", view, cubemap_shader);
    graphics_state.graphics_device->setMat4("projection", camera.get_projection_matrix(), cubemap_shader);

    graphics_state.graphics_device->bindVertexArray(skybox_obj->va);

    graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::CUBEMAP, skybox_obj->cubemap);

    graphics_state.graphics_device->drawArray(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 36);

    graphics_state.graphics_device->setDepthFunc(GL_LESS);*/
}

void Render::drawAABB(const AABB &bb, const Matrix4x4 &matrix)
{
    /*glm::vec4 min = { bb.min.x, bb.min.y, bb.min.z, 1.0f };
    glm::vec4 max = { bb.max.x, bb.max.y, bb.max.z, 1.0f };

    glm::vec4 corners[8] =
    {
        matrix * glm::vec4 { min.x, min.y, max.z, 1.0f},
        matrix * glm::vec4 { min.x, max.y, max.z, 1.0f},
        matrix * glm::vec4 { max.x, max.y, max.z, 1.0f},
        matrix * glm::vec4 { max.x, min.y, max.z, 1.0f},

        matrix * glm::vec4 { min.x, min.y, min.z, 1.0f},
        matrix * glm::vec4 { min.x, max.y, min.z, 1.0f},
        matrix * glm::vec4 { max.x, max.y, min.z, 1.0f},
        matrix * glm::vec4 { max.x, min.y, min.z, 1.0f}
    };

    for (uint32_t i = 0; i < 4; i++)
    {
        auto &corner = corners[i];
        auto &corner_next = corners[(i + 1) % 4];
        drawLine(corner.x, corner.y, corner.z, corner_next.x, corner_next.y, corner_next.z);
    }

    for (uint32_t i = 0; i < 4; i++)
    {
        auto &corner = corners[i + 4];
        auto &corner_next = corners[((i + 1) % 4) + 4];
        drawLine(corner.x, corner.y, corner.z, corner_next.x, corner_next.y, corner_next.z);
    }

    for (uint32_t i = 0; i < 4; i++)
    {
        auto &corner = corners[i];
        auto &corner_next = corners[i + 4];
        drawLine(corner.x, corner.y, corner.z, corner_next.x, corner_next.y, corner_next.z);
    }*/
}

void Render::applyShadowMap(ShadowMap *shadow)
{
    real32 near_p = 1.0f;
    real32 far_p = 7.5f;

    //shadow->light_projection_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_p, far_p);
}

void Render::applyTransform(TransformComponent *transform, Shader *shd)
{
    Matrix4x4 model_matrix = createMat4x4();

    /*model_matrix = glm::translate(model_matrix, transform->position);
    model_matrix = glm::scale(model_matrix, transform->scale);

    Camera3DComponent camera = getCamera3D();

    Matrix4x4 view_matrix = camera.get_view_matrix();
    Matrix4x4 proj_matrix = camera.get_projection_matrix();

    Matrix4x4 mvp = proj_matrix * view_matrix * model_matrix;

    graphics_state.graphics_device->setMat4("mvp", mvp, shd);
    graphics_state.graphics_device->setMat4("model", model_matrix, shd);

    //graphics_state.graphics_device->set_vec3("dir_light_color", glm::vec3(1.0, 0.0, 0.0), shd);
    graphics_state.graphics_device->setVec3("light_pos", glm::vec3(4.0, 4.0, 0.0), shd);
    graphics_state.graphics_device->setVec3("cam_pos", camera.pos, shd);

    if (enable_shadows)
    {
        real32 near_p = 1.0f;
        real32 far_p = 7.5f;

        Matrix4x4 light_projection_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_p, far_p);
        Vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
        Matrix4x4 light_view_matrix = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        Matrix4x4 light_space_matrix = light_projection_matrix * light_view_matrix;

        shd = getShader("base3d");
        graphics_state.graphics_device->bindShader(shd);
        graphics_state.graphics_device->setMat4("light_space_matrix", light_space_matrix, shd);
        graphics_state.graphics_device->setBool("shadows_enabled", true, shd);
    }
    else
    {
        graphics_state.graphics_device->setBool("shadows_enabled", false, shd);
    }*/    
}

void Render::applyDirLight(Shader *shd, DirLightComponent *directional_light, TransformComponent *transform)
{
    Vec3 light_color = createVec3(1.0f, 1.0f, 1.0f);

    if (directional_light)
    {
        light_color = directional_light->color;
    }

    //graphics_state.graphics_device->bindShader(shd);
    //graphics_state.graphics_device->setVec3("dir_light_color", light_color, shd);
    //graphics_state.graphics_device->setVec3("light_pos", transform->position, shd);
}

void Render::applySpotLight(Shader *shd, SpotLightComponent *spot_light, TransformComponent *transform)
{


}

void Render::applyPointLight(Shader *shd, PointLightComponent *point_light, TransformComponent *transform)
{

}

void Render::beginFrame(bool32 shouldClearScreen)
{
    if (shouldClearScreen)
    {
        //graphics_state.graphics_device->startExecution();
    }
}

void Render::setupRenderCommand(CommandType type)
{
    /*switch (type)
    {
    case CommandType::LINE_COMMAND:
    {
        graphics_state.line_index_count = 0;
        graphics_state.line_vb_ptr = graphics_state.line_vb_base;
    } break;
    case CommandType::QUAD_COMMAND:
    {
        graphics_state.quad_index_count = 0;
        graphics_state.quad_vb_ptr = graphics_state.quad_vb_base;
    } break;
    default:
        break;
    }*/
}
 
void Render::executeCommands()
{
    //executeCommand(CommandType::LINE_COMMAND);
    //executeCommand(CommandType::QUAD_COMMAND);

    render_queue.executeQueue();
}

void Render::executeCommand(CommandType type)
{
    /*uint32 dSize = 0;

    switch (type)
    {
    case xe_render::CommandType::LINE_COMMAND:
    {
        dSize = (uint8_t*)graphics_state.line_vb_ptr - (uint8_t*)graphics_state.line_vb_base;

        if (dSize)
        {
            uint32 offset = 0;
            graphics_state.graphics_device->bindBuffer(&graphics_state.line_vertex_buffer);
            graphics_state.graphics_device->pushDataToBuffer(BUFFER_TYPE::VERTEX, offset, dSize, graphics_state.line_vb_base);
            drawLines();
        }

    } break;
    case xe_render::CommandType::QUAD_COMMAND:
    {
        dSize = (uint8*)graphics_state.quad_vb_ptr - (uint8*)graphics_state.quad_vb_base;

        if (dSize)
        {
            uint32 offset = 0;
            graphics_state.graphics_device->bindBuffer(&graphics_state.quad_vertex_buffer);
            graphics_state.graphics_device->pushDataToBuffer(BUFFER_TYPE::VERTEX, offset, dSize, graphics_state.quad_vb_base);
            drawQuads();
        }
    } break;
    default:
        break;
    }*/

}

void Render::endFrame()
{
    //graphics_state.graphics_device->checkError();
    //graphics_state.graphics_device->endExecution();
}

/*void Render::drawModel(xe_assets::Model *mod, const glm::mat4 &transform)
{
    Shader *static_model_shader = xe_render::getShader("model3d");
    drawModel(mod, static_model_shader, transform);
}*/

/*void Render::drawModel(xe_assets::AnimModel *mod, const Matrix4x4 &transform)
{
    Shader *animation_shader = xe_render::getShader("skeletal_animation");
    drawModel(mod, animation_shader, transform);
}*/

void Render::drawCube(Texture2D *texture_diff)
{
    if (texture_diff)
    {
        graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::COLOR, texture_diff);
    }

    drawCube();
}

void Render::drawCube()
{
    if (!graphics_state.cube_vao.vertex_array)
    {
        createCube(&graphics_state.cube_vao);
    }

    graphics_state.graphics_device->bindVertexArray(graphics_state.cube_vao.vertex_array);
    graphics_state.graphics_device->drawArray(PRIMITIVE_TOPOLOGY::TRIANGLE, 0, 36);
    graphics_state.graphics_device->unbindVertexArray();
}

void Render::drawLine(Entity *ent)
{
    /*if (!line_vao.va)
    {
        createLineMesh(&line_vao);
    }

    using namespace xe_ecs;

    LineMeshComponent *line = ent->findComponent<LineMeshComponent>();

    if (line)
    {
        Shader *simple_color = getShader("simple_pos");
        glm::mat4 model = IDENTITY_MATRIX;
        Camera3DComponent& cam = getCamera3D();

        glm::mat4 mvp = cam.get_projection_matrix() * cam.get_view_matrix() * model;

        graphics_state.graphics_device->bindShader(simple_color);
        graphics_state.graphics_device->setMat4("mvp", mvp, simple_color);
        graphics_state.graphics_device->setVec4("u_color", convertToVec4(default_line_color), simple_color);

        graphics_state.graphics_device->bindVertexArray(line->line_co->va);
        graphics_state.graphics_device->setLineWidth(default_line_width);
        graphics_state.graphics_device->drawArray(PRIMITIVE_TOPOLOGY::LINE, 0, line->line_co->vertex_count);
        graphics_state.graphics_device->unbindVertexArray();
    }*/
}

void Render::drawLine(real32 x, real32 y, real32 x_end, real32 y_end)
{
    Color3RGB default_color = Color3RGB(1.0f, 0.0f, 0.0f);
    drawLine(x, y, x_end, y_end, default_color);
}

void Render::drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end)
{
    Color3RGB default_color = Color3RGB(1.0f, 0.0f, 0.0f);
    drawLine(x, y, z, x_end, y_end, z_end, default_color);
}

void Render::drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end, Color4RGBA color)
{
    /*if (graphics_state.line_index_count >= RenderState::max_line_ind)
    {
        //flushLines();
    }

    graphics_state.lines_count++;

    graphics_state.line_vb_ptr->pos = glm::vec3(x, y, z);
    graphics_state.line_vb_ptr->color = color;
    graphics_state.line_vb_ptr++;

    graphics_state.line_vb_ptr->pos = glm::vec3(x_end, y_end, z_end);
    graphics_state.line_vb_ptr->color = color;
    graphics_state.line_vb_ptr++;

    graphics_state.line_index_count += 2;*/
}

void Render::drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end, Color3RGB color)
{
    drawLine(x, y, z, x_end, y_end, z_end, Color4RGBA(color.x, color.y, color.z, 1.0f));
}

void Render::drawLine(real32 x, real32 y, real32 x_end, real32 y_end, Color4RGBA color)
{
    /*if (graphics_state.line_index_count >= RenderState::max_line_ind)
    {
        //flushLines();
    }

    graphics_state.lines_count++;

    graphics_state.line_vb_ptr->pos = glm::vec3(x, y, 0);
    graphics_state.line_vb_ptr->color = color;
    graphics_state.line_vb_ptr++;

    graphics_state.line_vb_ptr->pos = glm::vec3(x_end, y_end, 0);
    graphics_state.line_vb_ptr->color = color;
    graphics_state.line_vb_ptr++;

    graphics_state.line_index_count += 2;*/
}

void Render::drawLine(real32 x, real32 y, real32 x_end, real32 y_end, Color3RGB color)
{
    drawLine(x, y, x_end, y_end, Color4RGBA(color.x, color.y, color.z, 1.0f));
}

void Render::drawLines()
{
    /*Camera3DComponent& camera = getCamera3D();
    Shader *line = getShader("line");
    graphics_state.graphics_device->bindShader(line);

    graphics_state.graphics_device->setMat4("vp", camera.get_view_projection(), line);

    graphics_state.graphics_device->bindVertexArray(&graphics_state.line_vertex_array);
    graphics_state.graphics_device->setLineWidth(graphics_state.default_line_width);
    graphics_state.graphics_device->drawIndexed(PRIMITIVE_TOPOLOGY::LINE, graphics_state.line_index_count, GL_UNSIGNED_INT, 0);

    graphics_state.draw_calls++;*/
}

void Render::drawQuads()
{
    /*Camera2DComponent& camera2d = getCamera2D();
    Shader *shd = getShader("line");
    graphics_state.graphics_device->bindShader(shd);

    graphics_state.graphics_device->setMat4("vp", camera2d.get_view_projection(), shd);

    graphics_state.graphics_device->bindVertexArray(&graphics_state.quad_vertex_array);
    graphics_state.graphics_device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE, graphics_state.quad_index_count, GL_UNSIGNED_INT, 0);

    graphics_state.draw_calls++;*/
}

void Render::drawEnt(Entity *ent)
{
    /*switch (type)
    {
    case ENTITY_TYPE::ENT_STATIC_OBJECT:
    case ENTITY_TYPE::ENT_DIR_LIGHT:
        drawEntStatic(ent);
        break;
    case ENTITY_TYPE::ENT_ANIMATED_OBJECT:

        break;
    case ENTITY_TYPE::ENT_PRIMITIVE_OBJECT:
        drawEntPrimitive(ent);
        break;
    case ENTITY_TYPE::ENT_WATER:
        drawWaterPlane(ent);
        break;
    case ENTITY_TYPE::ENT_LINE:
        drawLine(ent);
        break;
    default:
        xe_utility::debug("Entity type not declared!");
        break;
    }*/

}

void Render::drawEntStatic(Entity *ent)
{
    /*MeshComponent *model = ent->findComponent<MeshComponent>();

    Shader *shader_to_draw = nullptr;

    if (model)
        shader_to_draw = xe_render::getShader("base3d");

    if (model->draw_with_color)
        shader_to_draw = xe_render::getShader("color");

    TransformComponent *transform = ent->findComponent<TransformComponent>();

    if (transform)
    {
        device->bindShader(shader_to_draw);

        if (model->draw_with_color)
        {
            device->setVec3("color", convertToVec3(default_cube_color), shader_to_draw);
        }

        glm::mat4 transformMatrix = applyTransform(transform, shader_to_draw);

        /*if (model->diffuse_texture != nullptr)
        {
            device->set_int("tex_diff1", 0, shader_to_draw);
            device->activate_bind_texture(TEXTURE_TYPE::COLOR, model->diffuse_texture);
        }*/

        /*MeshNode *root = model->model_asset->root;

        for (uint32 i = 0; i < root->children.size(); i++)
        {
            MeshNode* curr_node = root->children[i];

            for (uint32 j = 0; j < curr_node->meshes.size(); j++)
            {
                Mesh *cur_mesh = curr_node->meshes.at(j);
                drawMesh(cur_mesh, shader_to_draw);

                aabb &bb = cur_mesh->bounding_box;
                drawAABB(bb, transformMatrix);
            }
        }

        device->unbindShader();
    }*/
}

void Render::drawEntWithShader(Entity *ent, Shader *shd)
{   
    /*MeshComponent *model = ent->findComponent<MeshComponent>();

    Shader *shader_to_draw = shd;

    TransformComponent *transform = ent->findComponent<TransformComponent>();

    if (transform)
    {
        device->bindShader(shader_to_draw);

        applyTransform(transform, shader_to_draw);

        xe_assets::Node *root = model->model_asset->root;

        for (uint32 i = 0; i < root->children.size(); i++)
        {
            xe_assets::Node* curr_node = root->children[i];

            for (uint32 j = 0; j < curr_node->meshes.size(); j++)
            {
                xe_assets::Mesh *cur_mesh = curr_node->meshes.at(j);
                drawMesh(cur_mesh, shader_to_draw);
            }
        }

        device->unbindShader();
    }*/
}

void drawEntPrimitive(Entity *ent)
{
    /*SphereComponent *sphere = ent->findComponent<SphereComponent>();

    if (sphere)
    {
        TransformComponent *transform = ent->findComponent<TransformComponent>();
        Shader *shd = xe_render::getShader("color");

        graphics_state.graphics_device->bindShader(shd);
        graphics_state.graphics_device->setVec3("color", convertToVec3(default_cube_color), shd);

        if (sphere->diffuse)
        {
            shd = xe_render::getShader("simple_tex");
            graphics_state.graphics_device->bindShader(shd);
            graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::COLOR, sphere->diffuse);
        }

        applyTransform(transform, shd);

        drawSphere();
    }*/
}

/*void Render::drawMesh(xe_assets::Mesh *msh, Shader *shd)
{
    GraphicsDevice *device = xe_render::getDevice();

    uint32 diff_texture_num = 1;
    uint32 normal_texture_num = 1;
    uint32 specular_texture_num = 1;

    for (uint32 i = 0; i < msh->mesh_textures.size(); i++)
    {
        // @Refactor!!!
        Texture2D *mesh_texture = msh->mesh_textures[i].texture;
        device->activateTexture(i);

        std::string name = msh->mesh_textures[i].type;
        std::string num;

        if (name == "tex_diff")
            num = std::to_string(diff_texture_num++);
        else if (name == "tex_norm")
            num = std::to_string(normal_texture_num++);
        else if (name == "tex_spec")
            num = std::to_string(specular_texture_num++);

        device->setInt((name + num).c_str(), i, shd);
        device->bindTexture(TEXTURE_TYPE::COLOR, mesh_texture);
    }

    device->bindVertexArray(&msh->vao);
    device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE, msh->indices.size(), GL_UNSIGNED_INT, 0);
}*/

void Render::drawSphere(Texture2D *texture_diff)
{
    if (texture_diff)
        graphics_state.graphics_device->activateBindTexture(TEXTURE_TYPE::COLOR, texture_diff);
    drawSphere();
}

void Render::drawSphere()
{
    if (!graphics_state.sphere_vao.vertex_array)
    {
        createSphere(&graphics_state.sphere_vao);
    }

    graphics_state.graphics_device->bindVertexArray(graphics_state.sphere_vao.vertex_array);
    graphics_state.graphics_device->drawIndexed(PRIMITIVE_TOPOLOGY::TRIANGLE_STRIP, graphics_state.sphere_vao.vertex_array->ib->count, GL_UNSIGNED_INT, 0);
    graphics_state.graphics_device->unbindVertexArray();
}

RenderCommandQueue::RenderCommandQueue()
{
    command_buffer_ptr_base = new uint8_t[10 * 1024 * 1024];
    command_buffer_ptr = command_buffer_ptr_base;
    memset(command_buffer_ptr_base, 0, 10 * 1024 * 1024);
}

RenderCommandQueue::~RenderCommandQueue()
{
    free_mem[] command_buffer_ptr_base;
}

void *RenderCommandQueue::submit(RenderCommand func_ptr, uint32 size)
{
    *(RenderCommand*)command_buffer_ptr = func_ptr;
    command_buffer_ptr += sizeof(func_ptr);

    *(uint32*)command_buffer_ptr = size;
    command_buffer_ptr += sizeof(uint32);

    void* memory = command_buffer_ptr;
    command_buffer_ptr += size;

    command_count++;
    return memory;
}

void RenderCommandQueue::executeQueue()
{
    for (uint32 i = 0; i < command_count; ++i)
    {
        RenderCommand function = *(RenderCommand*)command_buffer_ptr_base;
        command_buffer_ptr_base += sizeof(RenderCommand);

        uint32_t size = *(uint32*)command_buffer_ptr_base;
        command_buffer_ptr_base += sizeof(uint32);
        function(command_buffer_ptr_base);
        command_buffer_ptr_base += size;
    }

    command_buffer_ptr = command_buffer_ptr_base;
    command_count = 0;
}

RenderCommandQueue& Render::GetRenderCommandQueue()
{
    return render_queue;
}