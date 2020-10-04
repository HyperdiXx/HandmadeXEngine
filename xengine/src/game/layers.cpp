
/*#include "xe_layer.h"

#include "xe_render.h"
#include "xe_gui.h"

#include "xe_ecs.h"
#include "xe_gizmo.h"
*/

    
internal void Layer2DInit()
{
    int gi = 0;
    int res = gi + 1;
}

internal void Layer2DUpdate(real32 dt)
{
    int updating = 0;
}

internal void Layer3DInit()
{
    int gi = 0;
    int res = gi + 1;
}

internal void Layer3DUpdate(real32 dt)
{
    int updating = 0;
}

internal void LayerGUIInit()
{
    int gi = 0;
    int res = gi + 1;
}

internal void LayerGUIUpdate(real32 dt)
{
    int updating = 0;
}

void GUILayer::init()
{

}

void GUILayer::render()
{
    //xe_gui::startFrame();
    //xe_gui::drawTopBar();
    //xe_gui::drawButton("Hi, XEngine!");
    //xe_gui::endFrame();

    //xe_gui::drawUI();
}

void GUILayer::update(real32 dt)
{
    /*if (xe_gui::makeButton(400.0f, 450.0f, 100.0f, 100.0f, "hello button 1"))
    {
        xe_render::drawText("Button pressed!", 1280 * 0.5f, 720 * 0.5f);
    }

    if (xe_gui::makeButton(20.0f, 400.0f, 50.0f, 50.0f, "hello button 2"))
    {
        xe_render::drawText("Button pressed!", 1280 * 0.5f, 720 * 0.5f);
    }

    if (xe_gui::makeButton(1020.0f, 250.0f, 100.0f, 100.0f, "hello button 3"))
    {
        xe_render::drawText("Button pressed!", 1280 * 0.5f, 720 * 0.5f);
    }*/
}

void Layer2D::init()
{
    /*xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    xe_graphics::Texture2D *water = xe_render::getTexture2DResource("water");
    xe_graphics::Shader *simple_shader = xe_render::getShader("simple2d");

    using namespace xe_ecs;

    Entity ent = {};

    ent.addComponent(new QuadComponent());
    ent.addComponent(new TransformComponent());
    ent.addComponent(new UpdateComponent());

    QuadComponent* mesh = ent.findComponent<QuadComponent>();
    TransformComponent *transform = ent.findComponent<TransformComponent>();

    transform->position = glm::vec3(200.0f, 200.0f, 0.0f);
    transform->scale = glm::vec3(100.0f, 100.0f, 100.0f);

    /*mesh->quad_mesh = new Quad();
    xe_render::createQuad(mesh->quad_mesh);

    device->bindShader(simple_shader);
    device->setInt("tex_diff", 0, simple_shader);*/
}

void Layer2D::render()
{
    /*using namespace xe_render;

    application::ApplicationState *app_state = application::getAppState();

    setupCommand(CommandType::QUAD);

    drawQuad(100, 100, 50, 50, xe_graphics::Color4RGBA(0.0f, 1.0f, 0.0f, 1.0f));
    drawQuad(100, 200, 50, 50, xe_graphics::Color4RGBA(1.0f, 0.0f, 0.0f, 1.0f));

    drawQuad(100, 300, 50, 50, xe_graphics::Color4RGBA(0.0f, 0.0f, 1.0f, 1.0f));
    drawQuad(100, 400, 50, 50, xe_graphics::Color4RGBA(1.0f, 1.0f, 1.0f, 1.0f));

    drawQuad(100, 500, 50, 50, xe_graphics::Color4RGBA(1.0f, 1.0f, 0.0f, 1.0f));
    drawQuad(100, 600, 50, 50, xe_graphics::Color4RGBA(1.0f, 0.0f, 1.0f, 1.0f));

    executeCommand(CommandType::QUAD);

    drawText("FPS: " + std::to_string(app_state->fps), 0, 0, 0.5f);*/
}

void Layer2D::update(real32 dt)
{
    /*UpdateComponent *updater = main_ent.findComponent<UpdateComponent>();

    if (!updater)
        return;

    TransformComponent *transform = main_ent.findComponent<TransformComponent>();

    transform->position += glm::vec3(0.0f, 1.0f, 0.0f) * dt * 12.f;
    transform->scale += glm::vec3(1.0f, 1.0f, 0.0f) * dt * 12.f;

    if (transform->position.y >= 720)
        transform->position.y = 0;

    if (transform->scale.x >= 200.0f || transform->scale.y >= 200.0f)
    {
        transform->scale.x = 100.f;
        transform->scale.y = 100.f;
    }*/
}

void Layer2D::addEntity(Entity ent)
{
    //entities.push_back(ent);
}

void Layer3D::init()
{
    /*xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    xe_graphics::Shader *model_shader = xe_render::getShader("base3d");
    xe_graphics::Shader *color_shader = xe_render::getShader("color");
    xe_graphics::Shader *pbr = xe_render::getShader("pbr");
    xe_graphics::Shader *water = xe_render::getShader("water");

    device->bindShader(water);
    device->setInt("tex_diff", 0, water);

    device->bindShader(model_shader);
    device->setInt("tex_diff", 0, model_shader);

    device->bindShader(color_shader);
    device->setVec3("color", glm::vec3(0.5f, 0.9f, 0.9f), color_shader);

    /*device->createTexture2D(1280, 720, &color_texture);

    device->createFramebuffer(1, &fbo);
    device->bindFramebuffer(&fbo);
    device->bindForWrite(&fbo);
    device->createRenderbuffer(1, &fbo);

    device->addColorTexture2D(&color_texture, 0, &fbo);
    device->addDepthTexture2D(1280, 720, &fbo);

    device->checkFramebuffer();
    device->unbindFramebuffer();

    xe_render::setActiveFramebuffer(&fbo);*/
}

void Layer3D::render()
{
    //using namespace xe_ecs;

    /*xe_graphics::GraphicsDevice *device = xe_render::getDevice();

    xe_graphics::Shader *color_shader = xe_render::getShader("color");
    xe_graphics::Shader *model_shader = xe_render::getShader("base3d");

    xe_graphics::Viewport vp = device->getViewport();

    /*device->bindFramebuffer(&fbo);
    device->setViewport(0, 0, vp.width, vp.height);
    device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    device->enable(GL_DEPTH_TEST);
    device->enable(GL_CULL_FACE);
    device->setCullMode(GL_BACK);

    xe_render::setupCommand(xe_render::CommandType::LINE);

    /*for (uint16 i = 0; i < current_scene->entities.size(); ++i)
    {
        Entity *current_ent = current_scene->entities[i];

        DirLight *light = current_ent->findComponent<DirLight>();
        TransformComponent *transform = current_ent->findComponent<TransformComponent>();

        if (light)
            xe_render::applyDirLight(model_shader, light, transform);

        xe_render::drawEnt(current_ent);
    }*/

    //device->disable(GL_CULL_FACE);

    /*xe_assets::AnimModel *girl = xe_scene::getAnimatedModelByName(current_scene, "Girl");
    xe_assets::AnimModel *gun = xe_scene::getAnimatedModelByName(current_scene, "Gun");

    //XD
    gun->update(0.016f);
    girl->update(0.016f);

    xe_render::drawModel(gun, glm::translate(xe_render::IDENTITY_MATRIX, { 0, 0, -10 }) * glm::scale(xe_render::IDENTITY_MATRIX, { 20, 20, 20 }));
    xe_render::drawModel(girl, glm::translate(xe_render::IDENTITY_MATRIX, { 5, -10, 0})
                                                    * glm::rotate(xe_render::IDENTITY_MATRIX, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f))
                                                    * glm::scale(xe_render::IDENTITY_MATRIX, glm::vec3(0.2f, 0.2f, 0.2f)));*/

                                                    //xe_render::drawLine(0.0f, 0.0f, 0.0f, -20.0f, 200.0f, -50.0f, xe_graphics::Color3RGB(1.0f, 1.0f, 0.0f));
                                                    //xe_render::drawLine(0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f, xe_graphics::Color3RGB(1.0f, 0.0f, 0.0f));
                                                    //xe_render::drawLine(0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, xe_graphics::Color3RGB(0.0f, 1.0f, 0.0f));

    /*application::ApplicationState *app_state = application::getAppState();

    if (app_state->activate_gizmo)
    {
        using namespace xe_gizmo;

        Camera3DComponent &camera3D = xe_render::getCamera3D();
        glm::vec3 default_pos = glm::vec3(0.0f, 0.0f, 0.0f);

        xe_gizmo::manipulateGizmo(default_pos, camera3D.get_view_matrix(), camera3D.get_projection_matrix(),
            (GizmoState::Mode)app_state->gizmo_mode, GizmoState::Axis::X, GizmoState::CoordSystem::GLOBAL);
    }

    xe_render::executeCommand(xe_render::CommandType::LINE);

    xe_render::drawSkybox();

    device->disable(GL_DEPTH_TEST);
    device->unbindFramebuffer();*/
}

void Layer3D::update(real32 dt)
{
    /*xe_ecs::Entity *light_ent = current_scene->directional_light;
    if (light_ent)
    {
        xe_ecs::TransformComponent *light_transform = light_ent->findComponent<xe_ecs::TransformComponent>();

        if (light_transform)
        {
            glm::vec3 &pos = light_transform->position;
            light_transform->setTranslation(pos.x + 12.2f * dt, pos.y, pos.z + 12.2f * dt);
        }
    }*/
}

void Layer3D::addEntity(Entity ent)
{
    //entities.push_back(ent);
}

