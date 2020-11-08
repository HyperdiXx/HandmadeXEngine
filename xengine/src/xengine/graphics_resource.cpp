
internal
bool32 isSamplerType(ShaderUniformType t)
{
    return t == ShaderUniformType::Sampler2D || t == ShaderUniformType::Sampler3D;
}

Shader Shader::create(const char *vertex_path, const char *pixel_path)
{
    Shader result = {};

    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createShader(vertex_path, pixel_path, &result);

    if (!res)
    {
        print_error("Failed to create shader!");
    }

    return result;
}

Shader Shader::create(const char *shader_path)
{
    Shader result = {};

    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createShader(shader_path, &result);

    if (!res)
    {
        print_error("Failed to create shader!");
    }

    return result;
}

Texture2D Texture2D::create(const char *path)
{
    Texture2D result = {};

    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createTexture2D(path, &result);

    if (!res)
    {
        print_error("Failed to create texture2D!");
    }

    return result;
}

Texture2D Texture2D::create(uint32 width, uint32 height, PIXEL_FORMAT type, PIXEL_INTERNAL_FORMAT internal_type)
{
    return Texture2D();//create(width, height, type, internal_type, PIXEL_TYPE::PTUBYTE);
}

Texture2D Texture2D::create(uint32 width, uint32 height, PIXEL_FORMAT type, PIXEL_INTERNAL_FORMAT internal_type, PIXEL_TYPE plx_type, TextureSampler &sampler)
{
    return create(width, height, TEXTURE_TYPE::COLOR, type, internal_type, plx_type, 0, sampler);
}

Texture2D Texture2D::create(uint32 width, uint32 height, TEXTURE_TYPE tex_type, PIXEL_FORMAT type, PIXEL_INTERNAL_FORMAT internal_type, PIXEL_TYPE plx_type, uint32 mip_count, TextureSampler &sampler)
{
    Texture2D result = {};
    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createTexture2D(tex_type, type, internal_type, plx_type, width, height, mip_count, sampler, &result);

    if (!res)
    {
        print_error("Failed to create texture2D!");
    }

    return result;
}

VertexBuffer VertexBuffer::create(DRAW_TYPE draw_type, void *vertices, uint32 size)
{
    VertexBuffer result = {};

    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createVertexBuffer(vertices, size, draw_type, &result);

    if (!res)
    {
        print_error("Failed to create vertex buffer!");
    }

    return result;
}

IndexBuffer IndexBuffer::create(uint32 *indices, uint32 size)
{
    IndexBuffer result = {};

    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createIndexBuffer(indices, size, &result);

    if (!res)
    {
        print_error("Failed to create index buffer!");
    }

    return result;
}

VertexArray VertexArray::create()
{
    VertexArray result = {};

    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createVertexArray(&result);

    if (!res)
    {
        print_error("Failed to create vertex array!");
    }

    return result;
}

Framebuffer Framebuffer::create()
{
    Framebuffer result = {};

    return result;
}

Framebuffer Framebuffer::create(const FramebufferDesc &desc, const FramebufferSpecs &specs)
{
    Framebuffer result = {};
    
    GraphicsDevice *device = Render::getDevice();

    bool32 res = device->createFramebuffer(desc, specs, &result);

    if (!res)
    {
        print_error("Failed to create framebuffer!");
    }

    return result;
}

Framebuffer Framebuffer::create(Texture2D *color, Texture2D *depth)
{
    Framebuffer result = {};

    return result;
}

Framebuffer Framebuffer::create(Texture2D *color, const FramebufferSpecs &specs)
{
    Framebuffer result = {};

    return result;
}

void Material::bind()
{
    GraphicsContext *context = Render::getContext();
    context->bindShader(shaderRef);
}

void Material::unbind()
{
    GraphicsContext *context = Render::getContext();
    context->unbindShader();
}

void Material::activate()
{
    GraphicsContext *context = Render::getContext();

    auto &definitions = shaderProp.getProperties();

    for (const auto &prop : definitions)
    {
        context->setShaderBuffer(&prop);
    }   

    for (uint32 i = 0; i < textures.size(); ++i)
    {
        Texture2D *tex = getTexture(i);
        context->activateTexture(i);
        context->bindTexture(tex->desc.texture_type, tex);
    }
}

void Material::set(const std::string &property_name, ShaderUniformType type, const void* data)
{
    GraphicsContext *context = Render::getContext();

    ShaderUniformProperty *prop = getProperty(property_name);

    if (prop)
    {
        prop->value = data;
    }
    else
    {
        auto &definitions = shaderProp.getProperties();

        bool32 isTexture = isSamplerType(type);
        
        ShaderUniformProperty n_prop = {};
        n_prop.name = property_name;
        n_prop.type = type;        
        n_prop.location = context->getBufferLocation(shaderRef->rhi.getID(), property_name.c_str());
        
        if (!isTexture)
        {
            n_prop.value = data;
        }        

        definitions.emplace_back(n_prop);
    }   
}

ShaderUniformProperty *Material::getProperty(const std::string &name)
{
    ShaderUniformProperty *result = nullptr;
    auto &properties = shaderProp.getProperties();

    for (auto &prop : properties)
    {
        if (prop.name == name)
        {
            result = &prop;
        }
    }

    return result;
}

MaterialInstance::MaterialInstance(Material *material_ref)
{
    assert(material_ref);
    mat_ptr = material_ref;

    mat_ptr->addMaterialInstance(this);
}

void GPUResourceManager::addResource(VertexBuffer vb)
{
    //bool32 isSuits = isCorrectType(vb, GPUResourceType::VertexBuffer);

    //if (isSuits)
    //{
        vb_handler.emplace_back(vb);
    //}
}

bool32 GPUResourceManager::isCorrectType(GPUResourceType hand, GPUResourceType type)
{
    return hand == type;
}

CountedHandler &GPUResourceManager::getResource(uint32 index, GPUResourceType type)
{
   
    switch (type)
    {
    case GPUResourceType::VertexBuffer:
    {
        return vb_handler[index];
    } break;
    default:
        break;
    }
}