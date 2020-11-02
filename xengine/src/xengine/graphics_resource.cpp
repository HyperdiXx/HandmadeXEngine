
Shader Shader::create(const char *vertex_path, const char *pixel_path)
{
    Shader result = {};

    GraphicsDevice *device = getGDevice();

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

    GraphicsDevice *device = getGDevice();

    bool32 res = device->createShader(shader_path, &result);

    if (!res)
    {
        print_error("Failed to create shader!");
    }

    return result;
}

void Material::bind()
{
    auto &definitions = shaderProp.getProperties();
}

MaterialInstance::MaterialInstance(Material *material_ref)
{
    assert(material_ref);
    mat_ptr = material_ref;

    mat_ptr->addMaterialInstance(this);
}