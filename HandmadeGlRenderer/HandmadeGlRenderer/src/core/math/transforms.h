#pragma once

#include "../../xenpch.h"

namespace XEngine
{
    namespace Math
    {
        class Transform
        {
        public:
            Transform(glm::mat4 m, glm::mat4 v, glm::mat4 proj);
            ~Transform();
            
            void setTranslation(glm::vec3 trans);
            void setRotation();
            void setScale(glm::vec3 scale);

            glm::mat4 MVP();

            inline const glm::mat4& getModelMatrix() const { return mModel; };
            inline const glm::mat4& getViewMatrix() const { return mView; };
            inline const glm::mat4& getProjectionMatrix() const { return mProjection; };
        private:

            glm::mat4 mModel;
            glm::mat4 mView;
            glm::mat4 mProjection;

        };
    }
}
