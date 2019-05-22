#include "dirLight.h"

XEngine::Rendering::DirLight::DirLight(glm::vec3 p, glm::vec4 c, glm::vec3 d) : Light(p, c)
{
    this->dir = d;
}

void XEngine::Rendering::DirLight::setDir(glm::vec3 d)
{
}
