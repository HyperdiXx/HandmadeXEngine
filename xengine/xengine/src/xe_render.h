#pragma once

#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

#include "xe_graphics_device.h"

struct aabb;

namespace xe_ecs
{
    class Entity;
    class Camera2DComponent;
    class Camera3DComponent;
    class DirLight;
    class SpotLight;
    class PointLight;
    class TransformComponent;
}

namespace xe_assets
{
    struct Mesh;
    struct Model;
    class AnimModel;
}

namespace xe_render
{
    static const glm::mat4 IDENTITY_MATRIX = glm::mat4(1.0f);

    namespace ftgl 
    {
        struct texture_atlas_t;
        struct texture_font_t;
    }

    void initRenderGL();
    void initRenderDX11();

    void initGui();

    bool32 initCommonGpuResources();
    bool32 loadFont(const char *path);
    bool32 loadShaders();
    bool32 loadFreeTextures();

    void clear();

    void setDevice(xe_graphics::GraphicsDevice *device);
    void setRenderPass(xe_graphics::RenderPass *pass);
    void setActiveFramebuffer(xe_graphics::Framebuffer *fbo);
    
    xe_graphics::GraphicsDevice* getDevice();

    xe_graphics::Shader *getShader(const char* name);
    xe_graphics::Texture2D *getTexture2DResource(const char* name);

    xe_ecs::Camera2DComponent& getCamera2D();
    xe_ecs::Camera3DComponent& getCamera3D();
    
    bool32 createQuad(xe_graphics::Quad *q);
    bool32 createQuad();

    bool32 createFullquad();
    bool32 createSkybox(xe_graphics::Skybox *sky);
    bool32 createCubemap(xe_graphics::Cubemap *cube);
    bool32 createShadowMaps(xe_graphics::ShadowMap *shadow);
    bool32 createSphere(xe_graphics::Sphere *sphre);
    bool32 createCube(xe_graphics::Cube *cube);
    bool32 createMesh(xe_assets::Mesh *meh, xe_graphics::Vertex *vertex_type, bool32 calculate_tspace);
    
    bool32 createLineMesh(glm::vec3 &start, glm::vec3 &end,  xe_graphics::Line *line_com);
    bool32 createLineMesh(xe_graphics::Line *line_com);

    bool32 createLinesBuffer();

    void drawFullquad();
    void drawQuad(xe_graphics::Quad *q);
    void drawQuad(xe_graphics::Quad *q, const glm::vec4 &color);
    void drawQuad(xe_graphics::Quad *q, xe_graphics::Shader *shd, xe_graphics::Texture2D *texture);
    void drawQuad(xe_ecs::Entity *ent, xe_graphics::Shader *shd, xe_graphics::Texture2D *texture);
    void drawQuad(const xe_graphics::Quad *q, xe_graphics::Shader *shd, xe_graphics::Texture2D *texture, glm::mat4& mod);
    void drawModel(xe_assets::Model *mod, xe_graphics::Shader *shd, const glm::mat4 &transform = glm::mat4(1.0f));
    void drawModel(xe_assets::AnimModel *mod, xe_graphics::Shader *shd, const glm::mat4 &transform = glm::mat4(1.0f));

    void drawModel(xe_assets::Model *mod, const glm::mat4 &transform = glm::mat4(1.0f));
    void drawModel(xe_assets::AnimModel *mod, const glm::mat4 &transform = glm::mat4(1.0f));

    void drawMesh(xe_assets::Mesh *mshs, xe_graphics::Shader *shd);
   
    void drawSphere(xe_graphics::Texture2D *texture_diff);
    void drawSphere();

    void drawCube(xe_graphics::Texture2D *texture_diff);
    void drawCube();

    void drawLine(xe_ecs::Entity *ent);

    void drawLine(real32 x, real32 y, real32 x_end, real32 y_end);
    void drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end);

    void drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end, xe_graphics::Color4RGBA color);
    void drawLine(real32 x, real32 y, real32 z, real32 x_end, real32 y_end, real32 z_end, xe_graphics::Color3RGB color);

    void drawLine(real32 x, real32 y, real32 x_end, real32 y_end, xe_graphics::Color4RGBA color);
    void drawLine(real32 x, real32 y, real32 x_end, real32 y_end, xe_graphics::Color3RGB color);

    void drawLines();

    void drawEnt(xe_ecs::Entity *ent);
    void drawEntStatic(xe_ecs::Entity *ent);
    void drawEntWithShader(xe_ecs::Entity *ent, xe_graphics::Shader *shd);
    void drawEntPrimitive(xe_ecs::Entity *ent);

    void drawText(const std::string &text, glm::vec2& pos, glm::vec3& color);
    void drawText(const std::string &text, glm::vec2& pos);
    void drawText(const std::string &text, real32 x, real32 y);

    void drawWaterPlane(xe_ecs::Entity *ent);

    void drawSkybox();
    void drawShadowMaps();

    void drawAABB(const aabb& bb);

    void applyShadowMap(xe_graphics::ShadowMap *shadow);

    void applyTransform(xe_ecs::TransformComponent *transform, xe_graphics::Shader *shd);
    void applyDirLight(xe_graphics::Shader *shd, xe_ecs::DirLight *directional_light, xe_ecs::TransformComponent *transform);
    void applySpotLight(xe_graphics::Shader *shd, xe_ecs::SpotLight *directional_light, xe_ecs::TransformComponent *transform);
    void applyPointLight(xe_graphics::Shader *shd, xe_ecs::PointLight *directional_light, xe_ecs::TransformComponent *transform);

    void beginFrame();
    void endFrame();

    glm::vec3 convertToVec3(xe_graphics::Color3RGB color);
    glm::vec4 convertToVec4(xe_graphics::Color4RGBA color);
}
#endif // !XENGINE_RENDERING_H
