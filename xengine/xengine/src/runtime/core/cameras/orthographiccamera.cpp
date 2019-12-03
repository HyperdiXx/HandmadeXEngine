#include "orthographiccamera.h"

#include <glm/gtc/matrix_transform.hpp>

XEngine::OrthoCamera::OrthoCamera(real32 left, real32 right, real32 bottom, real32 top)
{
    mView = glm::mat4(1.0f);
    mProjection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    mViewProjection = mProjection * mView;
    
}

void XEngine::OrthoCamera::calculateProjection(real32 left, real32 right, real32 bottom, real32 top)
{
    mProjection = glm::ortho(left, right, bottom, top,-1.0f, 1.0f);
    mViewProjection = mProjection * mView;
}

void XEngine::OrthoCamera::calculateViewMatrix()
{
    glm::vec3 mpos(mPosition.x, mPosition.y, mPosition.z);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), mpos);

    mView = glm::inverse(transform);
    mViewProjection = mProjection * mView;
}
