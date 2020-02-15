#pragma once

#include "xe_graphics_device.h"
#include "xe_platform.h"

#include <glad/glad.h>

namespace xe_graphics
{
    class graphics_device_gl : public graphics_device
    {
    public:
        graphics_device_gl(HWND window, bool fullscreen);
        virtual ~graphics_device_gl();

        void clear(int flags) override;
        void clear_color(real32 r, real32 g, real32 b, real32 a) override;
        void set_viewport(int32 x, int32 y, int32 width, int32 height) override;
        void draw_array() override;
        void draw_indexed(int mode, uint32 count, int type, void *ind) override;

        void bind_texture2d(const texture2D *tetxture) override;
        void bind_shader(const shader *shader) override;
        void bind_buffer(const vertex_buffer *vb) override;
        void bind_buffer(const index_buffer *ib) override;
        void bind_vertex_array(const vertex_array *va) override;
        void bind_framebuffer(const framebuffer *fbo) override;

        bool create_texture2D(const char *path, texture2D *texture) override;
        bool create_shader(const char* vertex, const char* fragment, shader *shader) override;
        bool create_framebuffer(framebuffer *fbo) override;
        bool create_vertex_buffer(real32 *vertices, uint32 size, vertex_buffer *vb) override;
        bool create_index_buffer(uint32* indices, uint32 size, index_buffer *ib) override;
        bool create_vertex_array(vertex_array *va) override;
        bool create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout *buf_layout) override;
        bool set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout) override;
        bool add_vertex_buffer(vertex_array *va, vertex_buffer *vb) override;
        bool set_index_buffer(vertex_array *va, index_buffer *ib) override;

        void start_execution() override;
        void end_execution() override;
    private:
        uint32 last_bound_unit;
    };
}

