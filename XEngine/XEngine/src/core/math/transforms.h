#pragma once

#include "../ecs/component.h"
#include "../../xenpch.h"

namespace XEngine
{
    namespace Math
    {
        class Transform : public Component
        {
        public:
            Transform() {};
            ~Transform();
            
            void setTranslation(glm::vec3 trans);
            void setRotation();
            void setScale(glm::vec3 scale);

            glm::mat4 MVP();

            inline const glm::mat4& getModelMatrix() const { return mModel; };
            inline const glm::mat4& getViewMatrix() const { return mView; };
            inline const glm::mat4& getProjectionMatrix() const { return mProjection; };
            inline const glm::mat4& getViewProjMatrix() const { return mProjection * mView; };
        private:

            glm::mat4 mModel = glm::mat4(1.0f);
            glm::mat4 mView = glm::mat4(1.0f);
            glm::mat4 mProjection = glm::mat4(1.0f);

        };
    }
}
