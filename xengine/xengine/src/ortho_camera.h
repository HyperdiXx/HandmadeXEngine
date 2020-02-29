#pragma once

#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H

#include "component.h"

#include <types.h>

#include <math/vec2f.h>
#include <math/vec3f.h>
//#include <mat4.h>

#include <glm/glm.hpp>

#include "config.h"

namespace XEngine
{
    class OrthoCamera : public Component
    {
    public:
        OrthoCamera(real32 left = 0.0f, real32 right = WINDOWS_WIDTH, real32 bottom = 0.0f, real32 top = WINDOWS_HEIGHT);

        void calculateProjection(real32 left, real32 right, real32 bottom, real32 top);

        void setPosition(const vec3f& pos) { mPosition = pos; calculateViewMatrix(); };
        void setRotation(real32 rot) { mRotation = rot; calculateViewMatrix(); };

        const vec3f& getPosition() const { return mPosition; }
        const real32 getRotation() const { return mRotation; }
        const glm::mat4& getProjection() const { return mProjection; };
        const glm::mat4& getView() const { return mView; };
        const glm::mat4& getViewProjection() const { return mViewProjection; };
    private:
        void calculateViewMatrix();
    private:
        vec3f mPosition = { 0.0f, 0.0f, 0.0f };
        real32 mRotation = 0.0f;

        glm::mat4 mProjection;
        glm::mat4 mView;
        glm::mat4 mViewProjection;
    };
}


#endif // !ORTHO_CAMERA_H

