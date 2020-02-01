#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <xenpch.h>
#include <types.h>

namespace XEngine
{
    namespace Rendering
    {
        class Shader
        {
        public:        
            virtual ~Shader() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void setInt(const std::string& name, int value) = 0;
            virtual void setFloat(const std::string& name, float val) = 0;
            virtual void setVec2(const std::string& name, const glm::vec2& value) = 0;
            virtual void setVec3(const std::string& name, const glm::vec3& value) = 0;
            virtual void setVec4(const std::string& name, const glm::vec4& value) = 0;
            virtual void setMat3(const std::string& name, const glm::mat3& value) = 0;
            virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;

            virtual const std::string& getName() const = 0;

            static Shader* create();
        private:

        };
    }
}

#endif // !SHADER_H

