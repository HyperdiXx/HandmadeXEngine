#pragma once

#ifndef GL_RENDER_H
#define GL_RENDER_H

#include "render.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLRender : public Render
        {
        public:
            
            virtual void clear(int flags) override;
            virtual void clear_color(real32 r, real32 g, real32 b, real32 a) override;
            virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) override;

            virtual void draw_model(Assets::Model *model, Shader *shader, glm::mat4 mat) override;
            virtual void draw_quad(Geometry::Quad *quad, Shader *shader, Texture2D *texture) override;
            virtual void draw_quad(Geometry::Quad *quad, Shader *shader, glm::vec4 *color) override;

            virtual Texture2D* create_texture2D(const char *path) override;
            virtual Shader* create_shader(const char* vertex, const char* fragment) override;
            virtual FrameBuffer* create_framebuffer() override;
            virtual VertexBuffer* create_vertex_buffer(real32 *vertices, uint32 size) override;
            virtual IndexBuffer* create_index_buffer(uint32* indices, uint32 size) override;
            virtual VertexArray* create_vertex_array() override;

        private:

        };
    }
}
#endif // GL_RENDER_H

