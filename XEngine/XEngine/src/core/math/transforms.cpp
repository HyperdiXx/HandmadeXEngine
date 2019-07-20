#include "transforms.h"

XEngine::Math::Transform::~Transform()
{

}

void XEngine::Math::Transform::setTranslation(glm::vec3 trans)
{
    mModel = glm::translate(mModel, trans);
}


void XEngine::Math::Transform::setRotation()
{

}

void XEngine::Math::Transform::setScale(glm::vec3 scale)
{
    mModel = glm::scale(mModel, scale);
}

glm::mat4 XEngine::Math::Transform::MVP()
{
    return glm::mat4(mProjection * mView * mModel);
}

