#include "batchsprite.h"

XEngine::Rendering::BatchSprite::BatchSprite(float x, float y, float width, float height, glm::vec4 & color) :
    Renderable2d(glm::vec3(x, y, 0), glm::vec2(width, height), color)
{



}

XEngine::Rendering::BatchSprite::BatchSprite(float x, float y, float width, float height, Texture2D* text) :
    Renderable2d(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f))
{



}
