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
        void enable(int type) override;
        void disable(int type) override;
        void set_cull_mode(int type) override;
        void draw_array(int mode, uint32 first, uint32 count) override;
        void draw_indexed(int mode, uint32 count, int type, void *ind) override;
       
        void activate_bind_texture2d(const texture2D *texture) override;
        void activate_texture2d(uint32 index) override;
        void bind_texture2d(const texture2D *tetxture) override;
        void bind_shader(const shader *shader) override;
        void bind_buffer(const vertex_buffer *vb) override;
        void bind_buffer(const index_buffer *ib) override;
        void bind_vertex_array(const vertex_array *va) override;
        void bind_framebuffer(const framebuffer *fbo) override;
        void bind_renderbuffer(const framebuffer *fbo) override;
        void bind_for_read(const framebuffer *fbo) override;
        void bind_for_write(const framebuffer *fbo) override;

        void add_color_texture2D(texture2D *texture, uint32 color_attachment_id, framebuffer *fbo) override;
        void add_depth_texture2D(texture2D *depth, framebuffer *fbo) override;
        void add_depth_texture2D(uint32 w, uint32 h, framebuffer *fbo) override;
        void set_depth_buffer_attachment(const framebuffer *fbo) override;
        texture2D& get_texture(uint32 number, const framebuffer *fbo) override;
        void set_texture2D(uint32 type, texture2D *texture) override;

        void check_framebuffer() override;

        void unbind_texture2d() override;
        void unbind_vertex_array() override;
        void unbind_shader() override;
        void unbind_framebuffer() override;

        void set_bool(const std::string &name, bool value, shader *shd) override;
        void set_int(const std::string &namee, int32 value, shader *shd) override;
        void set_float(const std::string& name, real32 value, shader *shd) override;
        void set_vec2(const std::string &name, const glm::vec2 &value, shader *shd) override;
        void set_vec2(const std::string &name, real32 x, real32 y, shader *shd) override;
        void set_vec3(const std::string &name, const glm::vec3 &value, shader *shd) override;
        void set_vec3(const std::string &name, real32 x, real32 y, real32 z, shader *shd) override;
        void set_vec4(const std::string &name, const glm::vec4 &value, shader *shd) override;
        void set_vec4(const std::string &name, real32 x, real32 y, real32 z, real32 w, shader *shd) override;
        void set_mat2(const std::string &name, const glm::mat2 &mat, shader *shd) override;
        void set_mat3(const std::string &name, const glm::mat3 &mat, shader *shd) override;
        void set_mat4(const std::string &name, const glm::mat4 &mat, shader *shd) override;

        bool create_texture2D(const char *path, texture2D *texture) override;
        bool create_texture2D(const char *path, const char *dir, texture2D *texture) override;
        bool create_texture2D(uint32 width, uint32 height, texture2D* texture) override;
        bool create_shader(const char* vertex, const char* fragment, shader *shader) override;
        bool create_framebuffer(const uint32 count, framebuffer *fbo) override;
        bool create_render_buffer(const uint32 count, framebuffer *fbo) override;
        bool create_vertex_buffer(real32 *vertices, uint32 size, vertex_buffer *vb) override;        
        bool create_index_buffer(uint32* indices, uint32 size, index_buffer *ib) override;
        bool create_vertex_array(vertex_array *va) override;
        bool create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout *buf_layout) override;
        bool set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout) override;
        bool add_vertex_buffer(vertex_array *va, vertex_buffer *vb) override;
        bool set_index_buffer(vertex_array *va, index_buffer *ib) override;

        void destroy_texture2D(texture2D *tex) override;
        void destroy_framebuffer(framebuffer *fbo) override;
        
        void start_execution() override;
        void end_execution() override;
    private:
        uint32 last_bound_unit_texture;
        uint32 last_activated_texture;
        uint32 last_bound_unit_vao;
        uint32 last_bound_unit_vbuffer;
        uint32 last_bound_unit_ibuffer;
        uint32 last_bound_unit_fbo;
        uint32 last_bound_unit_shader;
    };
}

