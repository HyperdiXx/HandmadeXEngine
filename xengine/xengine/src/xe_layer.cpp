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

