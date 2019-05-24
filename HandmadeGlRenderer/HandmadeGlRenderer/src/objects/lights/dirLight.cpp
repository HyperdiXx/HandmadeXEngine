#include "dirLight.h"

XEngine::Rendering::DirLight::DirLight(glm::vec3 p, glm::vec4 c) : Light(p, c)
{
    
}

void XEngine::Rendering::DirLight::setDir(glm::vec3 d)
{
    dir = d;
}
