#include "forwardrender.h"

bool XEngine::Rendering::ForwardRender::init()
{





    return true;
}

void XEngine::Rendering::ForwardRender::update()
{

}

void XEngine::Rendering::ForwardRender::renderScene(Scene *scene)
{
    scene->drawScene();
}

void XEngine::Rendering::ForwardRender::renderMesh()
{
}

void XEngine::Rendering::ForwardRender::renderQuad()
{
}
