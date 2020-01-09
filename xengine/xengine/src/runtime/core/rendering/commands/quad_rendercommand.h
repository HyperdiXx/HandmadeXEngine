#pragma once

#ifndef QUAD_RENDER_COMMAND_H
#define QUAD_RENDER_COMMAND_H

#include "rendercommand.h"

#include <runtime/core/geometry/quad.h>

namespace XEngine
{
    namespace Rendering
    {
        class QuadRenderCommand : public RenderCommand
        {
        public:
            QuadRenderCommand(RenderCommandType type) : m_type(type) {}
            
            void set(Geometry::Quad *quad, Shader *shader)
            {
                m_shader = shader;
                m_quad = quad;
            }

            virtual void execute()
            {
                m_shader->bind();

                m_quad->get_vertex_array()->bind();

                RenderCommand::draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
                m_quad->get_vertex_array()->unbind();

                m_shader->unbind();
            };

        private:
            RenderCommandType m_type;
            Shader *m_shader;
            Geometry::Quad* m_quad;            
        };
    }
}
#endif // !QUAD_RENDERCOMMAND_H

