#pragma once

#include "xe_graphics_resource.h"

#include <glm/glm.hpp>
#include <types.h>

#define MAX_COLOR_ATT 4

namespace xe_graphics
{
    class render_pass;

    class graphics_device
    {

    public:
        virtual ~graphics_device() {};

        virtual void clear(int flags) = 0;
        virtual void clear_color(real32 r, real32 g, real32 b, real32 a) = 0;
        virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) = 0;
        virtual void enable(int type) = 0;
        virtual void disable(int type) = 0;
        virtual void set_blend_func(int src, int dst) = 0;
        virtual void set_cull_mode(int type) = 0;
        virtual void set_depth(bool32 type) = 0;
        virtual void draw_array(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count) = 0;
        virtual void draw_indexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void *ind) = 0;

        virtual void activate_bind_texture(TEXTURE_TYPE type, const texture2D *texture) = 0;
        virtual void activate_texture(uint32 index) = 0;
        virtual void bind_texture(TEXTURE_TYPE type, const texture2D *texture) = 0;
        virtual void bind_shader(const shader *shader) = 0;
        virtual void bind_buffer(const vertex_buffer *vb) = 0;
        virtual void bind_buffer(const index_buffer *ib) = 0;
        virtual void bind_vertex_array(const vertex_array *va) = 0;
        virtual void bind_framebuffer(const framebuffer *fbo) = 0;
        virtual void bind_renderbuffer(const framebuffer *fbo) = 0;
        virtual void bind_for_read(const framebuffer *fbo) = 0;
        virtual void bind_for_write(const framebuffer *fbo) = 0;

        virtual void add_color_texture2D(texture2D *texture, uint32 color_attachment_id, framebuffer *fbo) = 0;
        virtual void add_depth_texture2D(texture2D *depth, framebuffer *fbo) = 0;
        virtual void add_depth_texture2D(uint32 w, uint32 h, framebuffer *fbo) = 0;
        virtual void set_depth_buffer_attachment(const framebuffer *fbo) = 0;
        virtual void set_texture2D(uint32 type, texture2D *texture) = 0;
        virtual texture2D& get_texture(uint32 number, const framebuffer *fbo) = 0;
        virtual void check_framebuffer() = 0;

        virtual void unbind_texture(TEXTURE_TYPE texture) = 0;
        virtual void unbind_vertex_array() = 0;
        virtual void unbind_shader() = 0;
        virtual void unbind_framebuffer() = 0;
        virtual void unbind_buffer(BUFFER_TYPE type) = 0;

        // shader
        virtual void set_bool(const std::string &name, bool value, shader *shd) = 0;
        virtual void set_int(const std::string &namee, int32 value, shader* shd) = 0;
        virtual void set_float(const std::string& name, real32 value, shader* shd) = 0;
        virtual void set_vec2(const std::string &name, const glm::vec2 &value, shader* shd) = 0;
        virtual void set_vec2(const std::string &name, real32 x, real32 y, shader* shd) = 0;
        virtual void set_vec3(const std::string &name, const glm::vec3 &value, shader* shd) = 0;
        virtual void set_vec3(const std::string &name, real32 x, real32 y, real32 z, shader* shd) = 0;
        virtual void set_vec4(const std::string &name, const glm::vec4 &value, shader* shd) = 0;
        virtual void set_vec4(const std::string &name, real32 x, real32 y, real32 z, real32 w, shader* shd) = 0;
        virtual void set_mat2(const std::string &name, const glm::mat2 &mat, shader* shd) = 0;
        virtual void set_mat3(const std::string &name, const glm::mat3 &mat, shader* shd) = 0;
        virtual void set_mat4(const std::string &name, const glm::mat4 &mat, shader* shd) = 0;

        virtual void start_execution() = 0;
        virtual void end_execution() = 0;
       
        virtual bool32 create_texture(texture2D *texture) = 0;
        virtual bool32 create_texture2D(const char *path, texture2D* texture) = 0;
        virtual bool32 create_texture2D(const char *path, const char* dir, texture2D* texture) = 0;
        virtual bool32 create_texture2D(const char *path, const char* dir, TEXTURE_TYPE type, bool32 generate_mipmap, texture2D* texture) = 0;
        virtual bool32 create_texture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, bool32 generate_mipmap, texture2D* texture) = 0;
        virtual bool32 create_texture2D(uint32 width, uint32 height, texture2D* texture) = 0;
        virtual bool32 create_shader(const char* vertex, const char* fragment, shader* shader) = 0;
        virtual bool32 create_framebuffer(const uint32 count, framebuffer *fbo) = 0;
        virtual bool32 create_render_buffer(const uint32 count, framebuffer *fbo) = 0;
        virtual bool32 create_vertex_buffer(real32 *vertices, uint32 size, DRAW_TYPE draw_type, vertex_buffer *vb) = 0;
        virtual bool32 create_index_buffer(uint32* indices, uint32 size, index_buffer *ib) = 0;
        virtual bool32 create_vertex_array(vertex_array *va) = 0;
        virtual bool32 create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout *buf_layout) = 0;
        virtual bool32 set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout) = 0;
        virtual bool32 add_vertex_buffer(vertex_array *va, vertex_buffer *vb) = 0;
        virtual bool32 set_index_buffer(vertex_array *va, index_buffer *ib) = 0;

        virtual void set_texture_wrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler) = 0;
        virtual void set_texture_sampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler) = 0;

        virtual void load_texture_gpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, unsigned char* image) = 0;
        virtual void load_texture_gpu(int texture_t, int width, int height, int internal_format, int data_format, unsigned char* image) = 0;
        virtual void generate_texture_mipmap(TEXTURE_TYPE texture_t) = 0;
        
        virtual void destroy_texture2D(texture2D *tex) = 0;
        virtual void destroy_framebuffer(framebuffer *fbo) = 0;
        virtual void destroy_shader(uint32 id) = 0;

        inline bool32 get_is_fullscreen() const { return fullscreen; }
        inline bool32 get_is_vsync() const { return vsync; }
        
        //static APIs::RenderAPI::API get_api() { return APIs::RenderAPI::get_api(); }
    
    protected:
        bool32 fullscreen = false;
        bool32 vsync = true;

        viewport vp;

        real32 clear_color_v[4];
    };
}
