#include "transforms.h"

XEngine::Math::Transform::~Transform()
{

}

void XEngine::Math::Transform::setTranslation(vec3f trans)
{
   
}


void XEngine::Math::Transform::setRotation()
{

}

void XEngine::Math::Transform::setScale(vec3f scale)
{

}

mat4 XEngine::Math::Transform::MVP()
{
    return mat4(mProjection * mView * mModel);
}

