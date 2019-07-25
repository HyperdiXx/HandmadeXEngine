#include "testapp.h"

XEngine::TestApp::TestApp(RenderAPI type)
{
    onStart();
}

void XEngine::TestApp::onStart()
{
    isRunning = true;

    /**
      * Setup all modules 
      */



    while (isRunning)
    {
        onUpdate(1.0f);
        onDraw();
        onPostUpdate();
    }

    onShutdown();
}

void XEngine::TestApp::onDraw()
{

}

void XEngine::TestApp::onUpdate(float dt)
{

}

void XEngine::TestApp::onPostUpdate()
{

}

void XEngine::TestApp::onShutdown()
{

}

