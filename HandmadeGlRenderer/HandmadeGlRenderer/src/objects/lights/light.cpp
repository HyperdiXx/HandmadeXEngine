#include "light.h"

XEngine::Rendering::Light::Light(glm::vec3 p, glm::vec4 c) : pos(p), color(c)
{
}

void XEngine::Rendering::Light::init()
{
}

void XEngine::Rendering::Light::setPos(glm::vec3 p)
{
    pos = p;
}

void XEngine::Rendering::Light::setColor(glm::vec4 c)
{
    color = c;
}
