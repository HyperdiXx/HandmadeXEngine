
Shader Shader::create(const char *vertex_path, const char *pixel_path)
{
    Shader result = {};

    GraphicsDevice *device = getGDevice();

    bool32 res = device->createShader(vertex_path, pixel_path, &result);

    if (!res)
    {
        print_error("Failed!");
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
        print_error("Failed!");
    }

    return result;
}
