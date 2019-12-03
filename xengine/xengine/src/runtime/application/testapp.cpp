#include "testapp.h"


TestApp::TestApp()
{
    window = new XEngine::GLWindow("Game", 1280, 720);
}

TestApp::~TestApp()
{
}

void TestApp::run()
{
    if (window != nullptr)
    {
        while (!window->isClosed())
        {
            onUpdate(1.0f);
            onDraw();
            onPostUpdate();
        }
    }

    onShutdown();
}

void TestApp::onDraw()
{
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TestApp::onUpdate(float dt)
{

}

void TestApp::onPostUpdate()
{
    window->update();
}


void TestApp::onShutdown()
{
    if (window != nullptr)
    {
        delete window;
        window = nullptr;
    }
}