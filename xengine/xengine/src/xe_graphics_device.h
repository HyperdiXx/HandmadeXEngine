#pragma once

#include <rendering/api/renderAPI.h>
#include <xe_graphics_resource.h>

#include <types.h>

namespace xe_graphics
{
    class graphics_device
    {

    public:
        virtual ~graphics_device() {};

        virtual void clear(int flags) = 0;
        virtual void clear_color(real32 r, real32 g, real32 b, real32 a) = 0;
        virtual void set_viewport(int32 x, int32 y, int32 width, int32 height) = 0;
        virtual void draw_array() = 0;
        virtual void draw_indexed(int mode, uint32 count, int type, void *ind) = 0;

        virtual void bind_texture2d(const texture2D *tetxture) = 0;
        virtual void bind_shader(const shader *shader) = 0;
        virtual void bind_buffer(const vertex_buffer *vb) = 0;
        virtual void bind_buffer(const index_buffer *ib) = 0;
        virtual void bind_vertex_array(const vertex_array *va) = 0;
        virtual void bind_framebuffer(const framebuffer *fbo) = 0;

        //virtual void draw_model(Assets::Model *model, Shader *m_shader, glm::mat4 mat) = 0;
        //virtual void draw_quad(Geometry::Quad *quad, BasicMaterial *material) = 0;

        virtual void start_execution() = 0;
        virtual void end_execution() = 0;
       
        virtual bool create_texture2D(const char *path, texture2D* texture) = 0;
        virtual bool create_shader(const char* vertex, const char* fragment, shader* shader) = 0;
        virtual bool create_framebuffer(framebuffer *fbo) = 0;
        virtual bool create_vertex_buffer(real32 *vertices, uint32 size, vertex_buffer *vb) = 0;
        virtual bool create_index_buffer(uint32* indices, uint32 size, index_buffer *ib) = 0;
        virtual bool create_vertex_array(vertex_array *va) = 0;
        virtual bool create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout *buf_layout) = 0;
        virtual bool set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout) = 0;
        virtual bool add_vertex_buffer(vertex_array *va, vertex_buffer *vb) = 0;
        virtual bool set_index_buffer(vertex_array *va, index_buffer *ib) = 0;

        inline int get_screen_width() const { return screen_width; }
        inline int get_screen_height() const { return screen_height; }
        inline bool get_is_fullscreen() const { return fullscreen; }
        inline bool get_is_vsync() const { return vsync; }
        
        static APIs::RenderAPI::API get_api() { return APIs::RenderAPI::get_api(); }
    
    protected:
        int32 screen_width = 0;
        int32 screen_height = 0;
        
        bool32 fullscreen= false;
        bool32 vsync = true;
    };
}
