#include "render_pass.h"

#include "xe_render_pass.h"
#include "xe_render.h"
#include "xe_assets.h"
#include "xe_config.h"

#include "xe_scene.h"
#include "xe_gui.h"

#include "xe_utility.h"

#include "app_state.h"

#include "xe_gizmo.h"

using namespace xe_ecs;

RenderPass2D::RenderPass2D()
{

}

RenderPass2D::~RenderPass2D()
{
}

void RenderPass2D::init()
{
    
}

void RenderPass2D::applyPass()
{
}

const xe_graphics::RenderPassData & RenderPass2D::getRenderPassData() const
{
    return pass_info;
}

GammaCorrectionPass::GammaCorrectionPass()
{
}

GammaCorrectionPass::~GammaCorrectionPass()
{
}

void GammaCorrectionPass::init()
{
    xe_graphics::GraphicsDevice *device = xe_render::getDevice();
    xe_graphics::Shader *gamma_correction_shader = xe_render::getShader("gc");
    pass_info.setShader(gamma_correction_shader);
    device->bindShader(gamma_correction_shader);
    device->setInt("tex_diff", 0, gamma_correction_shader);
}

void GammaCorrectionPass::applyPass()
{
    xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    device->bindShader(pass_info.getPassShader());

    xe_graphics::Texture2D *color_texture = pass_info.getPassFramebuffer()->color_textures[0];

    if (color_texture != nullptr)
    {
        device->activateBindTexture(xe_graphics::TEXTURE_TYPE::COLOR, color_texture);
    }

    xe_render::drawFullquad();

    device->unbindTexture(xe_graphics::TEXTURE_TYPE::COLOR);
    device->unbindShader();
}
 
const xe_graphics::RenderPassData & GammaCorrectionPass::getRenderPassData() const
{
    return pass_info;
}

ShadowMapPass::ShadowMapPass()
{
}

ShadowMapPass::~ShadowMapPass()
{
}

void ShadowMapPass::init()
{
    // @Refactor: initialization here
    shadow = new xe_graphics::ShadowMap();

    bool32 shadow_map_inited = xe_render::createShadowMaps(shadow);

    if (!shadow_map_inited)
        printf("Failed to create shadow map!\n");

    xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    xe_graphics::Shader *depth_shader = xe_render::getShader("shadow_depth");
    xe_graphics::Shader *shadow_map_shader = xe_render::getShader("shadow_map");

    device->bindShader(shadow_map_shader);
    device->setInt("diff_tex", 0, shadow_map_shader);
    device->setInt("shadow_map", 1, shadow_map_shader);
}

void ShadowMapPass::applyPass()
{
    xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    device->bindFramebuffer(&shadow->depth_fbo);
    device->setViewport(0, 0, shadow->width_map, shadow->height_map);

    device->clear(GL_DEPTH_BUFFER_BIT);

    xe_render::applyShadowMap(shadow);

    glm::mat4 light_view_matrix = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 light_space_matrix = light_view_matrix * shadow->light_projection_matrix;

    xe_graphics::Shader *depth_shader = xe_render::getShader("shadow_depth");
    device->bindShader(depth_shader);
    device->setMat4("light_space_matrix", light_space_matrix, depth_shader);

    //TODO : set entities to draw
    /*for (uint16 i = 0; i < current_scene->entities.size(); ++i)
    {
        Entity *current_ent = current_scene->entities[i];

        xe_render::drawEntWithShader(current_ent, depth_shader);
    }*/

    device->unbindFramebuffer();
}
 
const xe_graphics::RenderPassData & ShadowMapPass::getRenderPassData() const
{
    return pass_info;
}

/*void PbrPass::init()
{
    using namespace xe_graphics;

    GraphicsDevice *device = xe_render::getDevice();

    constexpr int env_map_size = 1024;
    constexpr int irradiance_map_size = 32;
    constexpr int brdf_lut_size = 256;

    glm::mat4 projection_matrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);

    glm::mat4 views_to_capture[] =
    {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f),  glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec3(0.0f, -1.0f,  0.0f))
    };

    device->enable(GL_DEPTH_TEST);
    device->setDepthFunc(GL_LEQUAL);
    device->enable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    device->createFramebuffer(1, &fbo);
    device->createRenderbuffer(1, &fbo);

    device->bindFramebuffer(&fbo);
    device->bindRenderbuffer(&fbo);
    device->setRenderbuffer(GL_DEPTH_COMPONENT24, env_map_size, env_map_size);
    device->setFramebufferRenderbufferAttachment(&fbo);

    device->createTexture(&env_cubemap);
    device->bindTexture(xe_graphics::TEXTURE_TYPE::CUBEMAP, &env_cubemap);

    for (uint32 i = 0; i < 6; ++i)
    {
        device->loadTextureGpu(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, env_map_size, env_map_size, GL_RGB16F, GL_RGB, GL_FLOAT, nullptr);
    }

    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

    Shader *equ_to_cubemap = xe_render::getShader("equirect");

    device->bindShader(equ_to_cubemap);
    device->setMat4("projection", projection_matrix, equ_to_cubemap);

    Texture2D *hdr_tex = xe_render::getTexture2DResource("hdr_env");

    device->activateBindTexture(TEXTURE_TYPE::COLOR, hdr_tex);

    device->setViewport(0, 0, env_map_size, env_map_size);
    device->bindFramebuffer(&fbo);

    for (uint32 i = 0; i < 6; ++i)
    {
        device->setMat4("view", views_to_capture[i], equ_to_cubemap);
        device->setTexture2DFbo(GL_COLOR_ATTACHMENT0, TEXTURE_TYPE::CUBEMAP_POSITIVE, i, &env_cubemap);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, env_cubemap.id, 0);
        //device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        xe_render::drawCube();
    }

    device->unbindFramebuffer();

    device->bindTexture(TEXTURE_TYPE::CUBEMAP, &env_cubemap);
    device->generateTextureMipmap(TEXTURE_TYPE::CUBEMAP);

    device->createTexture(&irr_map);
    device->bindTexture(TEXTURE_TYPE::CUBEMAP, &irr_map);

    for (uint32 i = 0; i < 6; ++i)
    {
        device->loadTextureGpu(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradiance_map_size, irradiance_map_size, GL_RGB16F, GL_RGB, GL_FLOAT, nullptr);
        //glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, irradiance_map_size, irradiance_map_size, 0, GL_RGB, GL_FLOAT, nullptr);
    }

    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

    device->bindFramebuffer(&fbo);
    device->bindRenderbuffer(&fbo);
    device->setRenderbuffer(GL_DEPTH_COMPONENT24, irradiance_map_size, irradiance_map_size);

    Shader *irradiance = xe_render::getShader("irradiance");

    device->bindShader(irradiance);
    device->setInt("environment_map", 0, irradiance);
    device->setMat4("projection", projection_matrix, irradiance);

    device->activateBindTexture(TEXTURE_TYPE::COLOR, &env_cubemap);

    device->setViewport(0, 0, irradiance_map_size, irradiance_map_size);
    device->bindFramebuffer(&fbo);

    for (uint32 i = 0; i < 6; ++i)
    {
        device->setMat4("view", views_to_capture[i], irradiance);
        device->setTexture2DFbo(GL_COLOR_ATTACHMENT0, TEXTURE_TYPE::CUBEMAP_POSITIVE, i, &irr_map);
        device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        xe_render::drawCube();
    }

    device->unbindFramebuffer();

    device->createTexture(&prefilter_map);
    device->bindTexture(TEXTURE_TYPE::CUBEMAP, &prefilter_map);

    for (uint32 i = 0; i < 6; i++)
    {
        device->loadTextureGpu(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, brdf_lut_size, brdf_lut_size, GL_RGB16F, GL_RGB, GL_FLOAT, nullptr);
        //glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, brdf_lut_size, brdf_lut_size, 0, GL_RGB, GL_FLOAT, nullptr);
    }

    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

    device->generateTextureMipmap(TEXTURE_TYPE::CUBEMAP);

    Shader *prefilter = xe_render::getShader("prefilter");

    device->bindShader(prefilter);
    device->setInt("environment_map", 0, prefilter);
    device->setMat4("projection", projection_matrix, prefilter);

    device->activateBindTexture(TEXTURE_TYPE::CUBEMAP, &env_cubemap);
    device->bindFramebuffer(&fbo);

    uint32 max_mip_levels = 5;
    for (uint32 mip = 0; mip < max_mip_levels; ++mip)
    {
        uint32 mip_width = brdf_lut_size * std::pow(0.5, mip);
        uint32 mip_height = brdf_lut_size * std::pow(0.5, mip);

        device->bindRenderbuffer(&fbo);
        device->setRenderbuffer(GL_DEPTH_COMPONENT24, mip_width, mip_height);

        device->setViewport(0, 0, mip_width, mip_height);

        real32 roughness = (real32)mip / (real32)(max_mip_levels - 1);
        device->setFloat("roughness", roughness, prefilter);

        for (uint32 i = 0; i < 6; ++i)
        {
            device->setMat4("view", views_to_capture[i], prefilter);
            device->setTexture2DFbo(GL_COLOR_ATTACHMENT0, TEXTURE_TYPE::CUBEMAP_POSITIVE, i, &prefilter_map, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            xe_render::drawCube();
        }
    }

    device->unbindFramebuffer();

    device->createTexture(&brdf_lut);
    device->bindTexture(TEXTURE_TYPE::COLOR, &brdf_lut);

    device->loadTextureGpu(TEXTURE_TYPE::COLOR, env_map_size, env_map_size, GL_RG16F, GL_RG, GL_FLOAT, nullptr);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, env_map_size, env_map_size, 0, GL_RG, GL_FLOAT, 0);

    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
    device->setTextureWrapping(TEXTURE_TYPE::CUBEMAP, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
    device->setTextureSampling(TEXTURE_TYPE::CUBEMAP, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

    device->bindFramebuffer(&fbo);
    device->bindRenderbuffer(&fbo);
    device->setRenderbuffer(GL_DEPTH_COMPONENT24, env_map_size, env_map_size);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdf_lut.id, 0);

    device->setViewport(0, 0, env_map_size, env_map_size);

    Shader *brdf = xe_render::getShader("brdf");

    device->bindShader(brdf);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    xe_render::drawFullquad();

    device->unbindFramebuffer();

    Shader *pbr = xe_render::getShader("pbr");
    Shader *back = xe_render::getShader("background");

    Camera3DComponent camera = xe_render::getCamera3D();

    device->bindShader(pbr);
    device->setMat4("projection", camera.get_projection_matrix(), pbr);

    glm::vec3 light_pos[] =
    {
        glm::vec3(-10.0f,  0.0f, 10.0f),
        glm::vec3(-10.0f,  0.0f, 10.0f),
        glm::vec3(10.0f, 0.0f, 10.0f),
        glm::vec3(10.0f,  0.0f, 10.0f),
    };

    glm::vec3 light_colors[] =
    {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };


    for (uint32 i = 0; i < sizeof(light_pos) / sizeof(light_pos[0]); ++i)
    {
        device->setVec3("light_positions[" + std::to_string(i) + "]", light_pos[i], pbr);
        device->setVec3("light_colors[" + std::to_string(i) + "]", light_colors[i], pbr);
    }

    device->bindShader(back);
    device->setMat4("projection", camera.get_projection_matrix(), back);

    Viewport vp = device->getViewport();

    device->setViewport(0, 0, vp.width, vp.height);
}

void PbrPass::clear()
{
    xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    device->destroyFramebuffer(&fbo);

    device->destroyTexture2D(&env_cubemap);
    device->destroyTexture2D(&irr_map);
    device->destroyTexture2D(&brdf_lut);
}

void PbrPass::render()
{
    using namespace xe_graphics;

    xe_graphics::Shader *pbr_shader = xe_render::getShader("pbr");
    xe_graphics::GraphicsDevice *device = xe_render::getDevice();
    Camera3DComponent camera3d = xe_render::getCamera3D();

    device->bindShader(pbr_shader);

    glm::mat4 view = camera3d.get_view_matrix();

    device->setMat4("view", view, pbr_shader);
    device->setVec3("cam_pos", camera3d.pos, pbr_shader);

    // bind pre-computed IBL data

    device->activateTexture(0);
    device->bindTexture(TEXTURE_TYPE::CUBEMAP, &irr_map);

    device->activateTexture(1);
    device->bindTexture(TEXTURE_TYPE::CUBEMAP, &prefilter_map);

    device->activateTexture(2);
    device->bindTexture(TEXTURE_TYPE::COLOR, &brdf_lut);

    /*texture2D *iron_albedo = xe_render::get_texture2D_resource("albedo_iron");
    texture2D *iron_normal = xe_render::get_texture2D_resource("normal_iron");
    texture2D *iron_metallic = xe_render::get_texture2D_resource("metallic_iron");
    texture2D *iron_roughness = xe_render::get_texture2D_resource("roughness_iron");
    texture2D *iron_ao = xe_render::get_texture2D_resource("ao_iron");

    device->activate_texture(3);
    device->bind_texture(TEXTURE_TYPE::COLOR, iron_albedo);
    device->activate_texture(4);
    device->bind_texture(TEXTURE_TYPE::COLOR, iron_normal);
    device->activate_texture(5);
    device->bind_texture(TEXTURE_TYPE::COLOR, iron_metallic);
    device->activate_texture(6);
    device->bind_texture(TEXTURE_TYPE::COLOR, iron_roughness);
    device->activate_texture(7);
    device->bind_texture(TEXTURE_TYPE::COLOR, iron_ao);

    glm::mat4 model_matrix = glm::mat4(1.0);

    model_matrix = glm::translate(model_matrix, glm::vec3(-3.0, 0.0, -10.0f));
    device->set_mat4("model", model_matrix, pbr_shader);
    xe_render::draw_sphere();

    model_matrix = glm::translate(model_matrix, glm::vec3(-8.0, 0.0, -2.0f));
    device->set_mat4("model", model_matrix, pbr_shader);
    xe_render::draw_sphere();

    model_matrix = glm::translate(model_matrix, glm::vec3(3.0, 0.0, -5.0f));
    device->set_mat4("model", model_matrix, pbr_shader);
    xe_render::draw_sphere();

    Texture2D *albedo_cerberus = xe_render::getTexture2DResource("cerberus_d");
    Texture2D *normal_cerberus = xe_render::getTexture2DResource("cerberus_n");
    Texture2D *metallic_cerberus = xe_render::getTexture2DResource("cerberus_m");
    Texture2D *rougnhess_cerberus = xe_render::getTexture2DResource("cerberus_r");
    Texture2D *ao_cerberus = xe_render::getTexture2DResource("cerberus_ao");

    device->activateTexture(3);
    device->bindTexture(TEXTURE_TYPE::COLOR, albedo_cerberus);
    device->activateTexture(4);
    device->bindTexture(TEXTURE_TYPE::COLOR, normal_cerberus);
    device->activateTexture(5);
    device->bindTexture(TEXTURE_TYPE::COLOR, metallic_cerberus);
    device->activateTexture(6);
    device->bindTexture(TEXTURE_TYPE::COLOR, rougnhess_cerberus);
    device->activateTexture(7);
    device->bindTexture(TEXTURE_TYPE::COLOR, ao_cerberus);

    glm::mat4 model_matrix = xe_render::IDENTITY_MATRIX;

    model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, -2.0f));
    device->setMat4("model", model_matrix, pbr_shader);

    //application::ApplicationState *appState = application::getAppState();

    //xe_assets::Model *cerberus = appState->getStaticModelByName("Cerberus");
    //xe_render::drawModel(cerberus, pbr_shader);

    Shader *back = xe_render::getShader("background");

    device->bindShader(back);
    device->setMat4("view", view, back);

    device->activateTexture(0);
    device->bindTexture(TEXTURE_TYPE::CUBEMAP, &env_cubemap);

    //device->bind_texture(TEXTURE_TYPE::CUBEMAP, &irr_map);
    //device->bind_texture(TEXTURE_TYPE::CUBEMAP, &prefilter_map);

    xe_render::drawCube();
}*/

RenderPass3D::RenderPass3D()
{
}

RenderPass3D::~RenderPass3D()
{
}

void RenderPass3D::init()
{
}

void RenderPass3D::applyPass()
{
}

const xe_graphics::RenderPassData & RenderPass3D::getRenderPassData() const
{
    return pass_info;
}
