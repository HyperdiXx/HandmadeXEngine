#pragma once

#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include "xengine\xe_render_pass.h"

class RenderPass2D : public xe_graphics::RenderPass
{
public:
    
    RenderPass2D();
    virtual ~RenderPass2D();

    void init() override;  
    void applyPass() override;

    const xe_graphics::RenderPassData &getRenderPassData() const override;
    
private:
    xe_graphics::RenderPassData pass_info;
    xe_ecs::Entity main_ent;
};

class RenderPass3D : public xe_graphics::RenderPass
{
public:  
    RenderPass3D();
    virtual ~RenderPass3D();
    
    void init() override;
    void applyPass() override;

    const xe_graphics::RenderPassData &getRenderPassData() const override;
private:   
    xe_graphics::RenderPassData pass_info;
    xe_scene::Scene *current_scene;
};

class GammaCorrectionPass : public xe_graphics::RenderPass
{
public:

    GammaCorrectionPass();
    virtual ~GammaCorrectionPass();

    void init() override;
    void applyPass() override;

    const xe_graphics::RenderPassData &getRenderPassData() const override;
private:
    xe_graphics::RenderPassData pass_info;
    xe_scene::Scene *current_scene;
};

class ShadowMapPass : public xe_graphics::RenderPass
{
public:

    ShadowMapPass();
    virtual ~ShadowMapPass();

    void init() override;
    void applyPass() override;

    const xe_graphics::RenderPassData &getRenderPassData() const override;
private:
    xe_graphics::ShadowMap *shadow;
    xe_graphics::RenderPassData pass_info;
    glm::vec3 light_pos = glm::vec3(-2.0f, 4.0f, -2.0f);
};

#endif // !RENDER_PASS_H

