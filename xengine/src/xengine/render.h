#pragma once

#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

namespace ftgl
{
    struct texture_atlas_t;
    struct texture_font_t;
}

struct RenderPassData
{
    std::string name;
    bool32 clearColor = true;
    bool32 clearDepth = false;
};

struct RenderPass
{
    Framebuffer *active_framebuffer;   
    RenderPassData data = {};
};

struct GraphicsVer
{
    const char *vendor;
    const char *renderer;
    const char *version;
};

#include "graphics_context.h"

struct GraphicsState
{
    const Matrix4x4 IDENTITY_MATRIX = createMat4x4();
    
    GPUResourceManager gpu_resources = {};
    RenderState render_state_batch = {};
    GraphicsVer gpu_version = {};

    std::unordered_map<std::string, Material> materials;

    Vec3  default_text_color = createVec3(1.0f, 1.0f, 1.0f);
    Vec3  default_cube_color = createVec3(0.0f, 1.0f, 0.0f);
    Vec4  default_line_color = createVec4(1.0f, 0.0f, 0.0f, 1.0f);

    Vec4 target_clear_color = createVec4(0.0f, 0.0f, 0.0f, 1.0f);

    uint32 default_line_width = 5;
    real32 default_text_scale = 1.0f;

    // Test triangle
    unsigned int VBO, VAO;

    VertexArray quad_vao;
    QuadMesh rect_vao;
    SphereMesh sphere_vao;
    CubeMesh cube_vao;
    LineMesh line_vao;

    Skybox *skybox_obj = nullptr;

    GraphicsDevice *graphics_device = nullptr;
    GraphicsContext *graphics_context = nullptr;

    RenderPass *active_render_pass = nullptr;
    Framebuffer *active_framebuffer = nullptr;

    Framebuffer deffered_buffer;

    bool32 enable_shadows = false;
    bool32 is_inited_triangle = false;
};

#include "render_commands.h"

class MeshFactory
{
public:

    MeshFactory() = default;
    ~MeshFactory() {};
    
    Array<real32> *createArrayOfVertices(GeometryType type);
private:
    
    void addCubePrimitive();

private:
    std::unordered_map<uint32, Array<real32>> primitive_vertices;
    std::unordered_map<uint32, Array<uint32>> primitive_indices;
    
    mutable bool32 is_init;
};

class Render
{
public:
    global void init(API_TYPE type = API_TYPE::OPENGL);
    global bool32 initRenderGL();
    global bool32 initRenderDX11();

    global void initGui();

    global bool32 initCommonGpuResources();
    //global bool32 loadFont(const char *path);
    global bool32 loadShaders();
    global bool32 loadFreeTextures();

    global void viewport(int32 w, int32 h);
    global void clear(uint32 flags);
    global void clearColor(real32 x, real32 y, real32 z, real32 a);

    global void shutdown();

    global void setDevice(GraphicsDevice *device);
    global void setContext(GraphicsContext *context);

    global void setRenderPass(RenderPass *pass);
    global void setActiveFramebuffer(Framebuffer *fbo);

    global Framebuffer *getActiveFramebuffer();
    global GraphicsDevice* getDevice();
    global GraphicsContext* getContext();
     
    global Shader *getShader(const char* name);
    global Texture2D *getTexture2DResource(const char* name);
    global Material *getMaterial(const char* name);

    global bool32 createQuad();

    global bool32 createFullquad();
    global bool32 createSkybox(Skybox *sky);
    global bool32 createCubemap(std::vector<const char*> paths, Cubemap *cube);
    global bool32 createCubemap(Cubemap *cube);
    global bool32 createShadowMaps(ShadowMap *shadow);
    global bool32 createSphere(SphereMesh *sphre);
    global bool32 createCube(CubeMesh *cube);
    
    global bool32 createMesh(Mesh *meh, Vertex *vertex_type, bool32 calculate_tspace);

    global bool32 createLineMesh(const Vec3 &start, const Vec3 &end, LineMesh *line_com);
    global bool32 createLineMesh(LineMesh *line_com);

    global bool32 createLinesBuffer();
    global bool32 createQuadBuffer();

    global bool32 createRenderPass(const RenderPassData data, RenderPass *rp);

    global void drawFullquad();

    global void drawQuad(const Vec2 &pos, const Vec2 &size, const Color4RGBA &color);
    global void drawQuad(const Vec3 &pos, const Vec2 &size, const Color4RGBA &color);
   
    global void drawQuad(real32 x, real32 y, real32 w, real32 h, const Color4RGBA &color);
    global void drawQuad(real32 x, real32 t, real32 w, real32 h, Texture2D *texture);

    //global void drawModel(Model *mod, Shader *shd, const Matrix4x4 &transform);
    global void drawModel(Model *mod, Material *mat, Matrix4x4 &transform);
    //void drawModel(AnimModel *mod, Shader *shd, const glm::mat4 &transform = glm::mat4(1.0f));

    //void drawModel(Model *mod, const Matrix4x4 &transform = createMat4x4(1.0f));
    //void drawModel(AnimModel *mod, const Matrix4x4 &transform = createMat4x44(1.0f));

    global void drawMesh(Mesh *mshs, Material *mat);

    global void drawSphere(Texture2D *texture_diff);
    global void drawSphere();

    global void drawCube(Texture2D *texture_diff);
    global void drawCube();

    global void drawTriangle();

    global void drawLine(real32 x, real32 y, real32 x_end, real32 y_end);
    global void drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end);

    global void drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end, Color4RGBA color);
    global void drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end, Color3RGB color);

    global void drawLine(real32 x, real32 y, real32 x_end, real32 y_end, Color4RGBA color);
    global void drawLine(real32 x, real32 y, real32 x_end, real32 y_end, Color3RGB color);

    global void drawLines();
    global void drawQuads();

    global void drawEnt(Entity *ent);
    global void drawEntStatic(Entity *ent);
    global void drawEntWithShader(Entity *ent, Shader *shd);
    global void drawEntPrimitive(Entity *ent);

    global void drawText(const std::string &text, Vec2& pos, Vec3& color);
    global void drawText(const std::string &text, Vec2& pos);
    global void drawText(const std::string &text, real32 x, real32 y);
    global void drawText(const std::string &text, real32 x, real32 y, real32 scale);
    global void drawText(const std::string &text, real32 x, real32 y, Vec3 &color, real32 scale);

    global void drawWaterPlane(Entity *ent);

    global void drawSkybox();
    global void drawShadowMaps();

    global void drawAABB(const AABB &bb, const Matrix4x4 &matrix);

    global void applyShadowMap(ShadowMap *shadow);

    global void applyTransform(TransformComponent *transform, Shader *shd);
    global void applyDirLight(Shader *shd, DirLightComponent *directional_light, TransformComponent *transform);
    global void applySpotLight(Shader *shd, SpotLightComponent *directional_light, TransformComponent *transform);
    global void applyPointLight(Shader *shd, PointLightComponent *directional_light, TransformComponent *transform);

    global void beginFrame(bool32 shouldClearScreen = true);
    global void beginRenderPass(const RenderPass *pass);

    global void setupRenderCommand(CommandType type);
    global void executeRenderCommand(CommandType type);

    global void executeCommands();

    global void endFrame();
    global void endRenderPass();

    global void addShader(const std::string &ac_name, Shader shr);
    global void addTexture(const std::string &ac_name, Texture2D tex);

    global void addMaterial(const std::string &mat_name, Material mat);

    template<typename T>
    global void pushCommand(T&& func)
    {
        auto render_cmd = [](void* ptr) {
            auto func_ptr = (T*)ptr;
            (*func_ptr)();

            func_ptr->~T();
        };

        auto storageBuffer = GetRenderCommandQueue().submit(render_cmd, sizeof(func));
        new (storageBuffer) T(std::forward<T>(func));
    }

private:

    global RenderCommandQueue& GetRenderCommandQueue();
};
#endif // !XENGINE_RENDERING_H
