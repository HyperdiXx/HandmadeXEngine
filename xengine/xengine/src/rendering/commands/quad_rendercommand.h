#pragma once

#ifndef QUAD_RENDER_COMMAND_H
#define QUAD_RENDER_COMMAND_H

#include "rendercommand.h"

#include <runtime/geometry/quad.h>
#include <rendering/api/base/texture2d.h>
#include <rendering/pipeline/materials/basicmaterial.h>

namespace XEngine
{
    namespace Rendering
    {
        class QuadRenderCommand : public RenderCommand
        {
        public:
            QuadRenderCommand(RenderCommandType type) : m_type(type) {}
            
            void set(Geometry::Quad *quad, BasicMaterial *material)
            {
                m_quad = quad;
                m_material = material;
            }
          
            virtual void execute() override
            {
                Texture2D *texture = m_material->get_texture2D();
                Shader *shader = m_material->get_shader();
                
                if(texture != nullptr)
                    texture->activate_bind(0);

                shader->bind();
                shader->setVec4("u_color", m_color);

                m_quad->get_vertex_array()->bind();

                RenderCommand::draw_indexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
                m_quad->get_vertex_array()->unbind();

                shader->unbind();
            };

        private:
            RenderCommandType m_type;
            BasicMaterial *m_material;
            Geometry::Quad* m_quad;
            glm::vec4 m_color;
        };
    }
}
#endif // !QUAD_RENDERCOMMAND_H

