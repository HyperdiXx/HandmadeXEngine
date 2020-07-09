#include "xe_layer.h"

#include "xe_render.h"
#include "xe_gui.h"

void xe_graphics::GUILayer::init()
{

}

void xe_graphics::GUILayer::render()
{
    xe_gui::startFrame();
    xe_gui::drawTopBar();
    xe_gui::drawButton("Hi, XEngine!");
    xe_gui::endFrame();

    xe_gui::drawUI();
}

void xe_graphics::GUILayer::update(real32 dt)
{
    if (xe_gui::makeButton(400.0f, 450.0f, 100.0f, 100.0f, "hello button 1"))
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
    }
}

void xe_graphics::Layer2D::init()
{
    GraphicsDevice *device = xe_render::getDevice();

    Texture2D *water = xe_render::getTexture2DResource("water");
    Shader *simple_shader = xe_render::getShader("simple2d");

    using namespace xe_ecs;

    Entity ent = {};

    ent.addComponent(new QuadComponent());
    ent.addComponent(new TransformComponent());
    ent.addComponent(new UpdateComponent());

    QuadComponent* mesh = ent.findComponent<QuadComponent>();
    TransformComponent *transform = ent.findComponent<TransformComponent>();

    transform->position = glm::vec3(200.0f, 200.0f, 0.0f);
    transform->scale = glm::vec3(100.0f, 100.0f, 100.0f);

    mesh->quad_mesh = new Quad();
    xe_render::createQuad(mesh->quad_mesh);

    device->bindShader(simple_shader);
    device->setInt("tex_diff", 0, simple_shader);
}

void xe_graphics::Layer2D::render()
{

}

void xe_graphics::Layer2D::update(real32 dt)
{

}

void xe_graphics::Layer2D::addEntity(xe_ecs::Entity* ent)
{
    entities.push_back(*ent);
}

void xe_graphics::Layer3D::init()
{

}

void xe_graphics::Layer3D::render()
{
}

void xe_graphics::Layer3D::update(real32 dt)
{
}
