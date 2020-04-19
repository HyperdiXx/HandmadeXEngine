
#include "xe_graphics_device_gl.h"
#include "xe_core.h"

#include "runtime/core/utility/log.h"

#include <GL/GL.h>
#include <external/wglext.h>

namespace xe_graphics
{
    constexpr uint32 convert_to_gl_type(DRAW_TYPE draw_type)
    {
        uint32 res = 0;

        switch (draw_type)
        {
        case STATIC:
            res |= GL_STATIC_DRAW;
            break;
        case DYNAMIC:
            res |= GL_DYNAMIC_DRAW;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_primitive_type(PRIMITIVE_TOPOLOGY type)
    {
        uint32 res = 0;

        switch (type)
        {
        case TRIANGLE:
            res |= GL_TRIANGLES;
            break;
        case TRIANGLE_STRIP:
            res |= GL_TRIANGLE_STRIP;
            break;
        case LINE:
            res |= GL_LINE;
            break;
        case LINE_LOOP:
            res |= GL_LINE_LOOP;
            break;
        case LINE_STRIP:
            res |= GL_LINE_STRIP;
            break;
        case POINT:
            res |= GL_POINT;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_buffer_type_gl(BUFFER_TYPE buf_type)
    {
        uint32 res = 0;

        switch (buf_type)
        {
        case VERTEX:
            res |= GL_ARRAY_BUFFER;
            break;
        case INDEX:
            res |= GL_ELEMENT_ARRAY_BUFFER;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_texture_type_gl(TEXTURE_TYPE tex_type)
    {
        uint32 res = 0;

        switch (tex_type)
        {
        case COLOR:
        case DEPTH:
        case HDR:
            res |= GL_TEXTURE_2D;
            break;
        case CUBEMAP:
            res |= GL_TEXTURE_CUBE_MAP;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_texture_wrapping_type_gl(TEXTURE_WRAPPING tex_type)
    {
        uint32 res = 0;

        switch (tex_type)
        {
        case TEXTURE_ADDRESS_REPEAT:
            res |= GL_REPEAT;
            break;
        case TEXTURE_ADDRESS_MIR_REPEAT:
            res |= GL_MIRRORED_REPEAT;
            break;
        case TEXTURE_ADDRESS_CLAMP:
            res |= GL_CLAMP_TO_EDGE;
            break;
        case TEXTURE_ADDRESS_BORDER:
            res |= GL_CLAMP_TO_BORDER;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_texture_sampling_type_gl(TEXTURE_SAMPLING tex_type)
    {
        uint32 res = 0;

        switch (tex_type)
        {
        case LINEAR:
            res |= GL_LINEAR;
            break;
        case NEAREST:
            res |= GL_NEAREST;
            break;
        case LINEAR_MIPMAP_LINEAR:
            res |= GL_LINEAR_MIPMAP_LINEAR;
            break;
        case LINEAR_MIPMAP_NEAREST:
            res |= GL_LINEAR_MIPMAP_NEAREST;
            break;
        case NEAREST_MIPMAP_LINEAR:
            res |= GL_NEAREST_MIPMAP_LINEAR;
            break;
        case NEAREST_MIPMAP_NEAREST:
            res |= GL_NEAREST_MIPMAP_NEAREST;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_texture_wrapping_axis_type_gl(TEXTURE_WRAPPING_AXIS tex_wrapping_type)
    {
        uint32 res = 0;

        switch (tex_wrapping_type)
        {
        case TEXTURE_AXIS_S:
            res |= GL_TEXTURE_WRAP_S;
            break;
        case TEXTURE_AXIS_T:
            res |= GL_TEXTURE_WRAP_T;
            break;
        case TEXTURE_AXIS_R:
            res |= GL_TEXTURE_WRAP_R;
            break;
        default:
            break;
        }

        return res;
    }

    constexpr uint32 convert_texture_filter_operation_gl(TEXTURE_FILTER_OPERATION tex_filter_type)
    {
        uint32 res = 0;

        switch (tex_filter_type)
        {
        case MIN:
            res |= GL_TEXTURE_MIN_FILTER;
            break;
        case MAG:
            res |= GL_TEXTURE_MAG_FILTER;
            break;
        default:
            break;
        }

        return res;
    }

    graphics_device_gl::graphics_device_gl(HWND window_handle, bool32 vsync, bool32 fullscreen)
    {
        this->fullscreen = fullscreen;
        this->vsync = vsync;
        this->vp = {};
        
        xe_utility::info("GAPI - GL");

        RECT rect = RECT();
        GetClientRect(window_handle, &rect);
        this->vp.width = rect.right - rect.left;
        this->vp.height = rect.bottom - rect.top;

        HDC dc = GetDC(window_handle);

        PIXELFORMATDESCRIPTOR pixel_format_descriptor = {};
        pixel_format_descriptor.nSize = sizeof(pixel_format_descriptor);
        pixel_format_descriptor.nVersion = 1;
        pixel_format_descriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        pixel_format_descriptor.cColorBits = 32;
        pixel_format_descriptor.cAlphaBits = 8;
        pixel_format_descriptor.iLayerType = PFD_MAIN_PLANE;

   
        const int pixel_format_attrib_list[] = 
        {
             WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
             WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
             WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
             WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
             WGL_COLOR_BITS_ARB, 32,
             WGL_DEPTH_BITS_ARB, 24,
             WGL_STENCIL_BITS_ARB, 8,
             0 
        };

        int attributes[] = 
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4, 
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,
            WGL_CONTEXT_FLAGS_ARB, 
            WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0
        };

        int pixel_format = 0;
        UINT num_formats = 0;
        
        int pixel_format_index = ChoosePixelFormat(dc, &pixel_format_descriptor);        
        PIXELFORMATDESCRIPTOR sug_pixel_format;
        DescribePixelFormat(dc, pixel_format_index, sizeof(sug_pixel_format), &sug_pixel_format);
        SetPixelFormat(dc, pixel_format_index, &sug_pixel_format);

        HGLRC gl_render_context = wglCreateContext(dc);
        if (!wglMakeCurrent(dc, gl_render_context))
        {
            xe_utility::error("Cannot create OpenGL context!!!");
        }

#ifdef PLATFORM_WINDOWS

        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
       
        PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

        wglMakeCurrent(0, 0);

        wglDeleteContext(gl_render_context);
        ReleaseDC(window_handle, dc);
        
        // create modern gl context attribs
        if (wglCreateContextAttribsARB)
            gl_render_context = wglCreateContextAttribsARB(dc, 0, attributes);

        // create context modern gl 
        gl_render_context = wglCreateContext(dc);
        
        if (!wglMakeCurrent(dc, gl_render_context))
        {
            xe_utility::error("Cannot create OpenGL context!!!");
        }

        // set swap interval
        if (wglSwapIntervalEXT && vsync)
            wglSwapIntervalEXT(1);
        else
            wglSwapIntervalEXT(0);

#endif 
       
        ReleaseDC(window_handle, dc);
    }

    graphics_device_gl::~graphics_device_gl()
    {

    }

    void graphics_device_gl::clear(int flags)
    {
        glClearColor(clear_color_v[0], clear_color_v[1], clear_color_v[2], clear_color_v[3]);
        glClear(flags);
    }

    void graphics_device_gl::clear_color(real32 r, real32 g, real32 b, real32 a)
    {
        clear_color_v[0] = r;
        clear_color_v[1] = g;
        clear_color_v[2] = b;
        clear_color_v[3] = a;
    }

    void graphics_device_gl::set_viewport(int32 x, int32 y, int32 width, int32 height)
    {
        glViewport(x, y, width, height);
    }

    void graphics_device_gl::enable(int type)
    {
        glEnable(type);
    }

    void graphics_device_gl::disable(int type)
    {
        glDisable(type);
    }

    void graphics_device_gl::set_blend_func(int src, int dst)
    {
        glBlendFunc(src, dst);
    }

    void graphics_device_gl::set_cull_mode(int type)
    {
        glCullFace(type);
    }

    void graphics_device_gl::set_depth(bool32 type)
    {
        glDepthMask(type);
    }

    void graphics_device_gl::draw_array(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count)
    {
        uint32 gl_primitive_type = convert_primitive_type(mode);
        glDrawArrays(gl_primitive_type, first, count);
    }

    void graphics_device_gl::draw_indexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void *ind)
    {
        uint32 gl_primitive_type = convert_primitive_type(mode);
        glDrawElements(gl_primitive_type, count, type, ind);
    }

    void graphics_device_gl::activate_bind_texture(TEXTURE_TYPE type, const texture2D * texture)
    {
        if (last_bound_unit_texture != texture->id)
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(gl_texture_type, texture->id);
            last_bound_unit_texture = texture->id;
        }
    }

    void graphics_device_gl::activate_texture(uint32 index)
    {
        glActiveTexture(GL_TEXTURE0 + index);
    }

    void graphics_device_gl::bind_texture(TEXTURE_TYPE type, const texture2D *texture)
    {
        if (last_bound_unit_texture != texture->id)
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            glBindTexture(gl_texture_type, texture->id);
            last_bound_unit_texture = texture->id;
        }
    }

    void graphics_device_gl::bind_buffer(const vertex_buffer *vb)
    {
        if (last_bound_unit_vbuffer != vb->id)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vb->id);
            last_bound_unit_vbuffer = vb->id;
        }
    }

    void graphics_device_gl::bind_buffer(const index_buffer *ib)
    {
        if (last_bound_unit_ibuffer != ib->id)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
            last_bound_unit_ibuffer = ib->id;
        }
    }

    void graphics_device_gl::bind_shader(const shader *shader)
    {
        if (last_bound_unit_shader != shader->id)
        {
            glUseProgram(shader->id);
            last_bound_unit_shader = shader->id;
        }
    }

    void graphics_device_gl::bind_vertex_array(const vertex_array *va)
    {
        if (last_bound_unit_vao != va->id)
        {
            glBindVertexArray(va->id);
            last_bound_unit_vao = va->id;
        }
    }

    void graphics_device_gl::bind_framebuffer(const framebuffer *fbo)
    {
        if (last_bound_unit_fbo != fbo->fbo_id)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo_id);
            last_bound_unit_fbo = fbo->fbo_id;
        }
    }

    void graphics_device_gl::bind_renderbuffer(const framebuffer *fbo)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, fbo->rb_id);
    }

    void graphics_device_gl::bind_for_read(const framebuffer *fbo)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo->fbo_id);
    }

    void graphics_device_gl::bind_for_write(const framebuffer *fbo)
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo->fbo_id);
    }

    void graphics_device_gl::add_color_texture2D(texture2D *texture, uint32 color_attachment_id, framebuffer *fbo)
    {
        if (color_attachment_id > MAX_COLOR_ATT)
            return;

        GLuint type_of_tex = GL_COLOR_ATTACHMENT0 + color_attachment_id;

        fbo->color_textures.push_back(texture);
        texture2D *color_texture = fbo->color_textures[color_attachment_id];

        set_texture2D(type_of_tex, texture);
        fbo->buffers.push_back(type_of_tex);
        glDrawBuffers((GLsizei)fbo->buffers.size(), fbo->buffers.data());
    }

    void graphics_device_gl::add_depth_texture2D(texture2D *depth, framebuffer *fbo)
    {
        fbo->depth_texture = depth;
        bind_renderbuffer(fbo);
        set_depth_buffer_attachment(fbo);
    }

    void graphics_device_gl::add_depth_texture2D(uint32 w, uint32 h, framebuffer *fbo)
    {
        if (!fbo->depth_texture)
        {
            fbo->depth_texture = new texture2D();
            fbo->depth_texture->desc.width = w;
            fbo->depth_texture->desc.height = h;
            fbo->depth_texture->desc.dimension = TEXTURE_2D;
            fbo->depth_texture->desc.texture_type = DEPTH;

            //glGenTextures(1, &fbo->depth_texture->id);
            
            create_texture(fbo->depth_texture);
            bind_texture(TEXTURE_TYPE::DEPTH, fbo->depth_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
            
            set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
            set_texture_sampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, fbo->depth_texture->id, 0);
        }

        bind_renderbuffer(fbo);
        set_depth_buffer_attachment(fbo);
    }

    void graphics_device_gl::set_depth_buffer_attachment(const framebuffer *fbo)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, fbo->depth_texture->desc.width, fbo->depth_texture->desc.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->rb_id);
    }

    texture2D& graphics_device_gl::get_texture(uint32 number, const framebuffer *fbo)
    {
        if (fbo && number >= 0 <= MAX_COLOR_ATT)
            return *fbo->color_textures[number];
        // @Add return;
    }

    void graphics_device_gl::set_texture2D(uint32 type, texture2D *texture)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, texture->id, 0);
    }

    void graphics_device_gl::check_framebuffer()
    {
        GLuint error = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (error != GL_FRAMEBUFFER_COMPLETE)
        {
            xe_utility::error("Framebuffer setup");

            switch (error)
            {
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                xe_utility::error("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                xe_utility::error("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                xe_utility::error("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                xe_utility::error("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                xe_utility::error("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                xe_utility::error("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
                break;
            }
        }
    }

    void graphics_device_gl::unbind_texture(TEXTURE_TYPE texture)
    {
        uint32 gl_texture_type = convert_texture_type_gl(texture);
        glBindTexture(gl_texture_type, 0);
        last_bound_unit_texture = 0;
    }

    void graphics_device_gl::unbind_vertex_array()
    {
        glBindVertexArray(0);
        last_bound_unit_vao = 0;
    }

    void graphics_device_gl::unbind_shader()
    {
        glUseProgram(0);
        last_bound_unit_shader = 0;
    }

    void graphics_device_gl::unbind_framebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        last_bound_unit_fbo = 0;
    }

    void graphics_device_gl::set_bool(const std::string & name, bool value, shader *shd)
    {
        glUniform1i(glGetUniformLocation(shd->id, name.c_str()), (int)value);
    }

    void graphics_device_gl::set_int(const std::string & name, int32 value, shader* shd)
    {
        glUniform1i(glGetUniformLocation(shd->id, name.c_str()), value);
    }

    void graphics_device_gl::set_float(const std::string & name, real32 value, shader *shd)
    {
        glUniform1f(glGetUniformLocation(shd->id, name.c_str()), value);
    }

    void graphics_device_gl::set_vec2(const std::string & name, const glm::vec2& value, shader *shd)
    {
        glUniform2fv(glGetUniformLocation(shd->id, name.c_str()), 1, &value[0]);
    }

    void graphics_device_gl::set_vec2(const std::string & name, real32 x, real32 y, shader *shd)
    {
        glUniform2f(glGetUniformLocation(shd->id, name.c_str()), x, y);
    }

    void graphics_device_gl::set_vec3(const std::string & name, const glm::vec3& value, shader *shd)
    {
        glUniform3fv(glGetUniformLocation(shd->id, name.c_str()), 1, &value[0]);
    }

    void graphics_device_gl::set_vec3(const std::string & name, real32 x, real32 y, real32 z, shader *shd)
    {
        glUniform3f(glGetUniformLocation(shd->id, name.c_str()), x, y, z);
    }

    void graphics_device_gl::set_vec4(const std::string & name, const glm::vec4 & value, shader *shd)
    {
        glUniform4fv(glGetUniformLocation(shd->id, name.c_str()), 1, &value[0]);
    }

    void graphics_device_gl::set_vec4(const std::string &name, real32 x, real32 y, real32 z, real32 w, shader *shd)
    {
        glUniform4f(glGetUniformLocation(shd->id, name.c_str()), x, y, z, w);
    }

    void graphics_device_gl::set_mat2(const std::string &name, const glm::mat2 &mat, shader *shd)
    {
        glUniformMatrix2fv(glGetUniformLocation(shd->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void graphics_device_gl::set_mat3(const std::string &name, const glm::mat3 &mat, shader *shd)
    {
        glUniformMatrix3fv(glGetUniformLocation(shd->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void graphics_device_gl::set_mat4(const std::string &name, const glm::mat4 &mat, shader *shd)
    {
        glUniformMatrix4fv(glGetUniformLocation(shd->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    bool32 graphics_device_gl::create_texture(texture2D *texture)
    {
        return create_texture(1, texture);
    }

    bool32 graphics_device_gl::create_texture(uint32 count, texture2D *texture)
    {
        assert(count > 0);
        glGenTextures(count, &texture->id);
        texture->is_valid = true;
        return true;
    }

    bool32 graphics_device_gl::create_texture2D(const char *path, texture2D *texture)
    {
        return create_texture2D(path, nullptr, texture);
    }

    bool32 graphics_device_gl::create_texture2D(const char *path, TEXTURE_TYPE tex_type, texture2D *texture)
    {
        return create_texture2D(path, nullptr, tex_type, false, texture);
    }

    bool32 graphics_device_gl::create_texture2D(const char *path, TEXTURE_TYPE tex_type, bool32 gen_mip, texture2D *texture)
    {
        return create_texture2D(path, nullptr, tex_type, 0, gen_mip, texture);
    }

    bool32 graphics_device_gl::create_texture2D(const char *path, const char *dir, texture2D *texture)
    {
        return create_texture2D(path, dir, TEXTURE_TYPE::COLOR, true, texture);
    }

    bool32 graphics_device_gl::create_texture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, bool32 generate_mipmap, texture2D* texture)
    {
        const char *path_res;

        if (dir)
        {
            std::string filename(path);
            std::string dirname(dir);
            filename = dirname + '/' + filename;
            path_res = filename.c_str();
        }
        else
            path_res = path;

        int channels = 0;

        void *image = nullptr;

        switch (type)
        {
        case xe_graphics::COLOR:
        case xe_graphics::GREYSCALE:
        case xe_graphics::LUT:
        case xe_graphics::CUBEMAP:
        case xe_graphics::DEPTH:
            image = xe_core::load_texture_from_disc(path_res, texture->desc.width, texture->desc.height, channels, 0, true);
            break;
        case xe_graphics::HDR:
            image = xe_core::load_texturef_from_disc(path_res, texture->desc.width, texture->desc.height, channels, 0, true);
            break;
        default:
            break;
        }
        
        if (!image)
        {
            xe_utility::error("Failed to load texture: " + std::string(path));
            return false;
        }

        GLenum internal_format = 0, data_format = 0;
        if (channels == 1)
        {
            internal_format = GL_RED;
            data_format = GL_RED;
        }
        else if (channels == 3)
        {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
        }
        else if (channels == 4)
        {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
        }

        create_texture(texture);
        bind_texture(type, texture);

        switch (type)
        {
        case xe_graphics::COLOR:
        case xe_graphics::LUT:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            load_texture_gpu(type, texture->desc.width, texture->desc.width, internal_format, data_format, image);

            set_texture_wrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);
            set_texture_wrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);

            set_texture_sampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
            set_texture_sampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::NEAREST);

            break;
        case xe_graphics::GREYSCALE:
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            load_texture_gpu(type, texture->desc.width, texture->desc.width, internal_format, data_format, image);
            set_texture_wrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);
            set_texture_wrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);

            set_texture_sampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
            set_texture_sampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::NEAREST);
            break;
        case xe_graphics::HDR:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, texture->desc.width, texture->desc.height, 0, data_format, GL_FLOAT, image);
            
            set_texture_wrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
            set_texture_wrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

            set_texture_sampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            set_texture_sampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

            break;
        case xe_graphics::CUBEMAP:
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, texture->desc.width, texture->desc.height, 0, data_format, GL_UNSIGNED_BYTE, image);
            break;
        case xe_graphics::DEPTH:
            break;
        default:
            break;
        }


        if (generate_mipmap)
            generate_texture_mipmap(type);

        unbind_texture(type);

        xe_core::delete_data(image);

        return true;
    }

    bool32 graphics_device_gl::create_texture2D(uint32 width, uint32 height, texture2D *texture)
    {
        texture->desc.width = width;
        texture->desc.height = height;
        texture->desc.dimension = TEXTURE_2D;

        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    bool32 graphics_device_gl::create_texture2D(const char *path, const char *dir, TEXTURE_TYPE type, bool32 generate_mipmap, texture2D *texture)
    {
        return create_texture2D(path, dir, type, 0, generate_mipmap, texture);
    }

    bool32 graphics_device_gl::create_shader(const char *vertex_code, const char *fragment_code, shader *shd)
    {
        std::string file_vs = xe_core::read_file_string(vertex_code);
        std::string file_fs = xe_core::read_file_string(fragment_code);

        const GLchar *vs_file_code = (GLchar*)file_vs.c_str();
        const GLchar *fs_file_code = (GLchar*)file_fs.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vs_file_code, NULL);
        glCompileShader(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fs_file_code, NULL);
        glCompileShader(fragment);

        GLint status_vertex;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &status_vertex);

        if (status_vertex != GL_TRUE)
        {
            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

            GLchar* buffer = new GLchar[length];
            GLint buflength;
            glGetShaderInfoLog(vertex, length, &buflength, buffer);

            xe_utility::error("Vertex shader: " + std::string(vertex_code));
            xe_utility::error(buffer);

            delete[] buffer;

            return false;
        }

        GLint status_fragment;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &status_fragment);

        if (status_fragment != GL_TRUE)
        {
            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

            GLchar* buffer = new GLchar[length];
            GLint buflength;
            glGetShaderInfoLog(fragment, length, &buflength, buffer);

            xe_utility::error("Fragment shader: " + std::string(fragment_code));
            xe_utility::error(buffer);

            delete[] buffer;

            return false;
        }

        shd->id = glCreateProgram();
        glAttachShader(shd->id, vertex);
        glAttachShader(shd->id, fragment);
        glLinkProgram(shd->id);
        glValidateProgram(shd->id);

        destroy_shader(vertex);
        destroy_shader(fragment);

        return true;
    }

    bool32 graphics_device_gl::create_framebuffer(uint32 count, framebuffer *fbo)
    {
        glGenFramebuffers(count, &fbo->fbo_id);
        
        return true;
    }

    bool32 graphics_device_gl::create_render_buffer(uint32 count, framebuffer *fbo)
    {
        glGenRenderbuffers(count, &fbo->rb_id);

        return true;
    }

    bool32 graphics_device_gl::create_vertex_buffer(real32 *vertices, uint32 size, DRAW_TYPE draw_type, vertex_buffer *vb)
    {
        vb->data = vertices;

        glGenBuffers(1, &vb->id);
        glBindBuffer(GL_ARRAY_BUFFER, vb->id);

        uint32 draw_type_gl = convert_to_gl_type(draw_type);

        glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vb->data, draw_type_gl);

        if (vb->data)
            return true;

        return false;
    }

    bool32 graphics_device_gl::create_index_buffer(uint32 *indices, uint32 size, index_buffer *ib)
    {
        ib->data = indices;
        ib->count = size;

        glGenBuffers(1, &ib->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), ib->data, GL_STATIC_DRAW);

        if (ib->data)
            return true;

        return false;
    }

    bool32 graphics_device_gl::create_vertex_array(vertex_array *va)
    {
        glGenVertexArrays(1, &va->id);

        return true;
    }

    bool32 graphics_device_gl::create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout *buf_layout)
    {
        buf_layout->elements = element;

        uint32 offset = 0;
        buf_layout->stride = 0;

        for (uint32 i = 0; i < buf_layout->elements.size(); i++)
        {
            auto &element = buf_layout->elements.at(i);
            element.offset = offset;
            offset += element.size;
            buf_layout->stride += element.size;
        }

        return true;
    }

    bool32 graphics_device_gl::set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout)
    {
        vb->layout = *buf_layout;

        return true;
    }

    bool32 graphics_device_gl::add_vertex_buffer(vertex_array *va, vertex_buffer *vb)
    {
        bind_vertex_array(va);
        if (vb != nullptr)
            bind_buffer(vb);

        const auto& buffer_layout = vb->layout;

        for (uint16 i = 0; i < buffer_layout.elements.size(); i++)
        {
            auto cur_element = buffer_layout.elements.at(i);
            glEnableVertexAttribArray(va->ibuffer_index);
            glVertexAttribPointer(va->ibuffer_index, cur_element.element_type_count(), GL_FLOAT, GL_FALSE, buffer_layout.stride, (void*)cur_element.offset);
            va->ibuffer_index++;
        }

        va->buffers.push_back(vb);

        return false;
    }

    bool32 graphics_device_gl::set_index_buffer(vertex_array *va, index_buffer *ib)
    {
        // assert 
        if (ib != nullptr)
        {
            bind_vertex_array(va);
            bind_buffer(ib);
            va->ib = ib;
            return true;
        }

        return false;
    }

    void graphics_device_gl::set_texture_wrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler)
    {
        uint32 gl_texture_type = convert_texture_type_gl(type);
        uint32 gl_wrapping_axis = convert_texture_wrapping_axis_type_gl(wrapping_axis);
        uint32 gl_wrapping = convert_texture_wrapping_type_gl(sampler);
        glTexParameteri(gl_texture_type, gl_wrapping_axis, gl_wrapping);
    }

    void graphics_device_gl::set_texture_sampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler)
    {
        uint32 gl_texture_type = convert_texture_type_gl(type);
        uint32 gl_texture_filter = convert_texture_filter_operation_gl(filter_operation);
        uint32 gl_texture_sampling = convert_texture_sampling_type_gl(sampler);
        glTexParameteri(gl_texture_type, gl_texture_filter, gl_texture_sampling);
    }

    void graphics_device_gl::load_texture_gpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void *image)
    {
        uint32 gl_texture_type = convert_texture_type_gl(texture_t);
        glTexImage2D(gl_texture_type, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image);
    }

    // @Special cubemap
    void graphics_device_gl::load_texture_gpu(int texture_t, int width, int height, int internal_format, int data_format, const void *image)
    {
        glTexImage2D(texture_t, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image);
    }

    void graphics_device_gl::generate_texture_mipmap(TEXTURE_TYPE texture_t)
    {
        uint32 gl_t = convert_texture_type_gl(texture_t);
        glGenerateMipmap(gl_t);
    }

    void graphics_device_gl::destroy_texture2D(texture2D *tex)
    {
        if (!tex->is_valid)
            return;
        glDeleteTextures(1, &tex->id);
    }

    void graphics_device_gl::destroy_framebuffer(framebuffer *fbo)
    {
        glDeleteFramebuffers(1, &fbo->fbo_id);
    }

    void graphics_device_gl::destroy_shader(uint32 id)
    {
        glDeleteShader(id);
    }

    void graphics_device_gl::set_draw_buffer(uint32 type)
    {
        glDrawBuffer(type);
    }

    void graphics_device_gl::set_draw_buffers(uint32 count, void *pointer)
    {
        glDrawBuffers(2, (uint32*)pointer);
    }

    void graphics_device_gl::set_read_buffer(uint32 type)
    {
        glReadBuffer(type);
    }

    void graphics_device_gl::check_error()
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            const char* erro_char = (const char*)err;
        }
    }

    void graphics_device_gl::unbind_buffer(BUFFER_TYPE type)
    {
        uint32 type_gl = convert_buffer_type_gl(type);
        glBindBuffer(type_gl, 0);
    }

    void graphics_device_gl::start_execution()
    {
        clear_color(clear_color_v[0], clear_color_v[1], clear_color_v[2], clear_color_v[3]);
        clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void graphics_device_gl::end_execution()
    {       
        SwapBuffers(xe_platform::get_dc());
    }
}
