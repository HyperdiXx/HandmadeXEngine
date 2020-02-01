#pragma once

#include "component.h"
#include <math/vec3f.h>
#include <math/mat4.h>

namespace XEngine
{
    namespace Math
    {
        class Transform : public Component
        {
        public:
            Transform() {};
            ~Transform();
            
            void setTranslation(vec3f trans);
            void setRotation();
            void setScale(vec3f scale);

            mat4 MVP();

            inline const mat4& getModelMatrix() const { return mModel; };
            inline const mat4& getViewMatrix() const { return mView; };
            inline const mat4& getProjectionMatrix() const { return mProjection; };
            inline const mat4& getViewProjMatrix() const { return mProjection * mView; };
        private:

            mat4 mModel = mat4(1.0f);
            mat4 mView = mat4(1.0f);
            mat4 mProjection = mat4(1.0f);

        };
    }
}
