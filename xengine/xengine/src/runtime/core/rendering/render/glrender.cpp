#include "glrender.h"

#include <runtime/core/rendering/commands/model_command.h>
#include <runtime/core/rendering/commands/quad_rendercommand.h>
#include <runtime/core/rendering/api/opengl/gltexture2d.h>
#include <runtime/core/rendering/api/opengl/glshader.h>

namespace XEngine
{
    namespace Rendering
    {
        void GLRender::clear(int flags)
        {
            RenderCommand::clear(flags);
        }

        void GLRender::clear_color(real32 r, real32 g, real32 b, real32 a)
        {
            RenderCommand::clear_color(r, g, b, a);
        }

        void GLRender::set_viewport(int32 x, int32 y, int32 width, int32 height)
        {
            RenderCommand::set_viewport(x, y, width, height);
        }

        void GLRender::draw_model(Assets::Model *model, Shader *shader, glm::mat4 mat)
        {
            ModelRenderCommand *render_command = new ModelRenderCommand(RenderCommandType::MODEL);
            render_command->set(model, shader, mat);
            add(render_command);
        }

        // TODO: add material with shader and texture
        void GLRender::draw_quad(Geometry::Quad *quad, Shader *shader)
        {
            QuadRenderCommand *render_command = new QuadRenderCommand(RenderCommandType::QUAD);
            render_command->set(quad, shader);
            add(render_command);
        }

        Texture2D* GLRender::create_texture2D(const char *path)
        {
            return new GLTexture2D(path);
        }
        Shader * GLRender::create_shader(const char *vertex, const char *fragment)
        {
            return new GLShader(vertex, fragment);
        }
        FrameBuffer * GLRender::create_framebuffer()
        {
            return nullptr;
        }
        VertexBuffer * GLRender::create_vertex_buffer(real32 * vertices, uint32 size)
        {
            return nullptr;
        }
        IndexBuffer * GLRender::create_index_buffer(uint32 * indices, uint32 size)
        {
            return nullptr;
        }
        VertexArray * GLRender::create_vertex_array()
        {
            return nullptr;
        }
    }
}
