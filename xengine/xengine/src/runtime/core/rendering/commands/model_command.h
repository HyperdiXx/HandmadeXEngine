#pragma once

#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include "rendercommand.h"

#include <runtime/core/geometry/model.h>
#include <glm/glm.hpp>
namespace XEngine
{
    namespace Rendering
    {
        class ModelRenderCommand : public RenderCommand
        {
        public:
            ModelRenderCommand(RenderCommandType type) : m_type(type) {}
            
            void set(Assets::Model* model, Shader* shader, glm::mat4 matrix)
            {
                m_model = model;
                m_shader = shader;
                m_model_matrix = matrix;
            }

            virtual void execute()
            {
                m_shader->bind();
                
                m_shader->unbind();
            };

        private:           
            glm::mat4 m_model_matrix = glm::mat4(1.0f);
            RenderCommandType m_type;
            Assets::Model *m_model;
            Shader *m_shader;
        };
    }
}
#endif // !MODEL_COMMAND_H

