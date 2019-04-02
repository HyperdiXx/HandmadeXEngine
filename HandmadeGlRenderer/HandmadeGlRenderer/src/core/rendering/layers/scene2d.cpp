#include "scene2d.h"

XEngine::Rendering::Scene2D::Scene2D() : Layer(new Renderer2d(), mShader, glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f))
{


}

XEngine::Rendering::Scene2D::~Scene2D()
{


}
