#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <rendering/api/renderAPI.h>
#include <rendering/commands/rendercommand.h>
#include <perspective_camera.h>

#include <xenpch.h>

namespace XEngine
{
    class OrthoCamera;
    class RenderCommandExecutor;

    namespace Rendering
    {
        class Shader;
        class Texture2D;
        class BasicMaterial;
        class VertexBuffer;
        class IndexBuffer;
        class VertexArray;
        class FrameBuffer;
    };

    namespace Assets
    {
        class Model;
    }

    namespace Geometry
    {
        class Quad;
    }

    namespace Rendering
    {
        class Render
        {
        public:
            virtual ~Render() {};

            virtual void clear(int flags) = 0;
            virtual void clear_color(real32 r, real32 g, real32 b, real32 a) = 0;
            virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) = 0;
            
            virtual void draw_model(Assets::Model *model, Shader *m_shader, glm::mat4 mat) = 0;

            // Later setup only material
            virtual void draw_quad(Geometry::Quad *quad, BasicMaterial *material) = 0;
            
            void start_execution();
            void end_execution();

            void add(RenderCommand *command);

            virtual Texture2D* create_texture2D(const char *path) = 0;
            virtual Shader* create_shader(const char* vertex, const char* fragment) = 0;
            virtual FrameBuffer* create_framebuffer() = 0;
            virtual VertexBuffer* create_vertex_buffer(real32 *vertices, uint32 size) = 0;
            virtual IndexBuffer* create_index_buffer(uint32* indices, uint32 size) = 0;
            virtual VertexArray* create_vertex_array() = 0;

            inline PerspectiveCamera& get_camera3D() { return m_camera3D; } 

            static APIs::RenderAPI::API get_api() { return APIs::RenderAPI::get_api(); }

            static Render* create();
        protected:
            PerspectiveCamera m_camera3D;
        private:
            std::vector<RenderCommand*> m_commands;
            RenderCommandExecutor *m_command_executor = nullptr;
            glm::mat4 m_world_matrix = glm::mat4(1.0f);
        };
    }
}
#endif // !RENDER_H

