#pragma once

#ifndef QUAD_RENDER_COMMAND_H
#define QUAD_RENDER_COMMAND_H

#include "rendercommand.h"

#include <runtime/geometry/quad.h>
#include <runtime/core/rendering/api/base/texture2d.h>

namespace XEngine
{
    namespace Rendering
    {
        class QuadRenderCommand : public RenderCommand
        {
        public:
            QuadRenderCommand(RenderCommandType type) : m_type(type) {}
            
            void set(Geometry::Quad *quad, Shader *shader, Texture2D* texture)
            {
                m_shader = shader;
                m_quad = quad;
                m_texture = texture;
            }

            void set(Geometry::Quad *quad, Shader *shader, glm::vec4* color)
            {
                m_shader = shader;
                m_quad = quad;
                m_color = *color;
            }

            virtual void execute() override
            {
                if(m_texture != nullptr)
                    m_texture->activate_bind(0);

                m_shader->bind();
                m_shader->setVec4("u_color", m_color);

                m_quad->get_vertex_array()->bind();

                RenderCommand::draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
                m_quad->get_vertex_array()->unbind();

                m_shader->unbind();
            };

        private:
            RenderCommandType m_type;
            Shader *m_shader;
            Texture2D *m_texture;
            Geometry::Quad* m_quad;
            glm::vec4 m_color;
        };
    }
}
#endif // !QUAD_RENDERCOMMAND_H

