#pragma once

#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include "xe_render_pass.h"

class SpecialRenderPass : public xe_graphics::RenderPass
{
public:

};

class RenderPass2D : public xe_graphics::RenderPass
{
public:
    void init() override;
    void clear() override;

    void render() override;

    void update(real32 dt) override;

    void setScene(xe_scene::Scene *scene) override {};
    void setColorTexture(xe_graphics::Texture2D *clrTex) override { color_texture = clrTex; };

    xe_graphics::Texture2D *getColorTexture() override { return color_texture; };
private:
    xe_graphics::Texture2D *color_texture;
    xe_graphics::Shader* simple_shader;
    xe_ecs::Entity main_ent;
};

class RenderPass3D : public xe_graphics::RenderPass
{
public:

    void init() override;
    void clear() override;

    void render() override;

    void update(real32 dt) override;

    void setScene(xe_scene::Scene *scene) override { current_scene = scene; };
    void setColorTexture(xe_graphics::Texture2D *clrTex) override { color_texture = *clrTex; };

    xe_graphics::Texture2D *getColorTexture() override { return &color_texture; };

private:
    xe_graphics::Framebuffer fbo;
    xe_graphics::Texture2D color_texture;
    xe_scene::Scene *current_scene;
};

class PbrPass : public xe_graphics::RenderPass
{
public:
    void init() override;
    void clear() override;

    void render() override;

    void update(real32 dt) override;

    void setScene(xe_scene::Scene *scene) override { current_scene = scene; };
    void setColorTexture(xe_graphics::Texture2D *clrTex) override { color_texture = *clrTex; };

    xe_graphics::Texture2D *getColorTexture() override { return &color_texture; };
private:
    xe_graphics::Framebuffer fbo;
    xe_graphics::Texture2D env_cubemap;
    xe_graphics::Texture2D irr_map;
    xe_graphics::Texture2D prefilter_map;
    xe_graphics::Texture2D brdf_lut;
    xe_graphics::Texture2D color_texture;
    xe_scene::Scene *current_scene;
};

class GammaCorrectionPass : public xe_graphics::RenderPass
{
public:
    void init() override;
    void clear() override;

    void render() override;

    void update(real32 dt) override;

    void setScene(xe_scene::Scene *scene) override { current_scene = scene; };
    void setColorTexture(xe_graphics::Texture2D *clrTex) override { color_texture = clrTex; };

    xe_graphics::Texture2D *getColorTexture() override { return color_texture; };

private:
    xe_graphics::Texture2D *color_texture;
    xe_graphics::Shader* gmshd;
    xe_scene::Scene *current_scene;
};

class ShadowMapPass
{
public:
    void init();
    void clear();

    void unloadResources();

    void render();

    void update(real32 dt);

    void bindDepthTexture() const;

    void setScene(xe_scene::Scene *active_sc) { current_scene = active_sc; };

private:
    xe_graphics::ShadowMap *shadow;
    xe_scene::Scene *current_scene;

    glm::vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
};

#endif // !RENDER_PASS_H

