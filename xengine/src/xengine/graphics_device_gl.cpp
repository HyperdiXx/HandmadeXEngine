#ifndef GRAPHICS_DEVICE_GL_CPP
#define GRAPHICS_DEVICE_GL_CPP

constexpr uint32 convert_draw_type_to_gl_type(DRAW_TYPE draw_type)
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
        res |= GL_LINES;
        break;
    case LINE_LOOP:
        res |= GL_LINE_LOOP;
        break;
    case LINE_STRIP:
        res |= GL_LINE_STRIP;
        break;
    case POINTLESS:
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
    case CUBEMAP_POSITIVE:
        res |= GL_TEXTURE_CUBE_MAP_POSITIVE_X;
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

/*static PIXELFORMATDESCRIPTOR get_pixel_format_desc()
{
    PIXELFORMATDESCRIPTOR pixel_format_descriptor = {};
    pixel_format_descriptor.nSize = sizeof(pixel_format_descriptor);
    pixel_format_descriptor.nVersion = 1;
    pixel_format_descriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixel_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    pixel_format_descriptor.cColorBits = 32;
    pixel_format_descriptor.cDepthBits = 24;
    pixel_format_descriptor.cAlphaBits = 8;
    pixel_format_descriptor.iLayerType = PFD_MAIN_PLANE;
    return pixel_format_descriptor;
}*/

GraphicsDeviceGL::GraphicsDeviceGL(HWND window_handle, bool32 vsync, bool32 fullscreen)
    {
        /*this->fullscreen = fullscreen;
        this->vsync = vsync;
        this->vp = {};
        
        xe_utility::info("GAPI - GL");
        
        //@ Correct : grab useful size for vp store
        RECT rect = RECT();
        //GetClientRect(window_handle, &rect);
        GetWindowRect(window_handle, &rect);
        this->vp.width = rect.right - rect.left;
        this->vp.height = rect.bottom - rect.top;

        HDC dc = GetDC(window_handle);

        PIXELFORMATDESCRIPTOR pixel_format_descriptor = get_pixel_format_desc();

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
        {
            gl_render_context = wglCreateContextAttribsARB(dc, 0, attributes);
        }

        // create context modern gl 
        gl_render_context = wglCreateContext(dc);
        
        if (!wglMakeCurrent(dc, gl_render_context))
        {
            xe_utility::error("Cannot create OpenGL context!!!");
        }
        
        // set swap interval
        if (wglSwapIntervalEXT && vsync)
        {
            wglSwapIntervalEXT(1);
        }
        else
        {
            wglSwapIntervalEXT(0);
        }
#endif 
       
        ReleaseDC(window_handle, dc);*/
    }

    GraphicsDeviceGL::~GraphicsDeviceGL()
    {

    }

    void GraphicsDeviceGL::clear(int flags)
    {         
        glClear(flags);
    }

    void GraphicsDeviceGL::clearColor(real32 r, real32 g, real32 b, real32 a)
    {
        clear_color_v[0] = r;
        clear_color_v[1] = g;
        clear_color_v[2] = b;
        clear_color_v[3] = a;
        glClearColor(clear_color_v[0], clear_color_v[1], clear_color_v[2], clear_color_v[3]);
    }

    void GraphicsDeviceGL::setAPI()
    {
        api = API_TYPE::OPENGL;
    }

    void GraphicsDeviceGL::clearColor(const Vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void GraphicsDeviceGL::setViewport(int32 x, int32 y, int32 width, int32 height)
    {
        glViewport(x, y, width, height);
    }

    // @ Store all stuff in context state  like dx

    void GraphicsDeviceGL::enable(int type)
    {
        glEnable(type);
    }

    void GraphicsDeviceGL::disable(int type)
    {
        glDisable(type);
    }
    
    void GraphicsDeviceGL::setBlendFunc(int src, int dst)
    {
        glBlendFunc(src, dst);
    }

    void GraphicsDeviceGL::setDepthFunc(int type)
    {
        glDepthFunc(type);
    }

    void GraphicsDeviceGL::setCullMode(int type)
    {
        glCullFace(type);
    }

    void GraphicsDeviceGL::setDepth(bool32 type)
    {
        glDepthMask(type);
    }

    void GraphicsDeviceGL::setLineWidth(uint32 line_width)
    {
        //Render::pushCommand([=]()
        //{
            glLineWidth(line_width);
        //});
    }

    void GraphicsDeviceGL::drawArray(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count)
    {
        //Render::pushCommand([=]()
        //{
            uint32 gl_primitive_type = convert_primitive_type(mode);
            glDrawArrays(gl_primitive_type, first, count);
        //});
    }

    void GraphicsDeviceGL::drawIndexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void *ind)
    {
        //Render::pushCommand([mode, count, type, ind]()
        //{
            uint32 gl_primitive_type = convert_primitive_type(mode);
            glDrawElements(gl_primitive_type, count, type, ind);
        //});
    }

    void GraphicsDeviceGL::pushDataToBuffer(uint32 index, BUFFER_TYPE type, uint32 offset, uint64 size, void *data)
    {
        //Render::pushCommand([=]()
        //{
            uint32 buf_type = convert_buffer_type_gl(type);
            glBufferSubData(buf_type, offset, size, data);
            //glNamedBufferSubData(index, offset, size, data);
        //});
    }

    void GraphicsDeviceGL::activateBindTexture(TEXTURE_TYPE type, const Texture2D *texture)
    {
        if (last_bound_unit_texture != texture->id)
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(gl_texture_type, texture->id);
            last_bound_unit_texture = texture->id;
        }
    }

    void GraphicsDeviceGL::activateBindTexture(TEXTURE_TYPE type, const Cubemap *texture)
    {
        if (last_bound_unit_texture != texture->id)
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(gl_texture_type, texture->id);
            last_bound_unit_texture = texture->id;
        }
    }

    void GraphicsDeviceGL::activateTexture(uint32 index)
    {
        glActiveTexture(GL_TEXTURE0 + index);
    }

    void GraphicsDeviceGL::bindTexture(TEXTURE_TYPE type, const Texture2D *texture)
    {
        if (last_bound_unit_texture != texture->id)
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            glBindTexture(gl_texture_type, texture->id);
            last_bound_unit_texture = texture->id;
        }
    }

    void GraphicsDeviceGL::bindTexture(TEXTURE_TYPE type, uint32 index)
    {
        if (last_bound_unit_texture != index)
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            glBindTexture(gl_texture_type, index);
            last_bound_unit_texture = index;
        }
    }

    void GraphicsDeviceGL::bindBuffer(const VertexBuffer *vb)
    {
        //Render::pushCommand([this, vb]()
        //{
            if (last_bound_unit_vbuffer != vb->id)
            {
                glBindBuffer(GL_ARRAY_BUFFER, vb->id);
                last_bound_unit_vbuffer = vb->id;
            }
        //});
    }

    void GraphicsDeviceGL::bindBuffer(const IndexBuffer *ib)
    {       
        //Render::pushCommand([this, ib]()
        //{
            if (last_bound_unit_ibuffer != ib->id)
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
                last_bound_unit_ibuffer = ib->id;
            }
        //});
    }

    void GraphicsDeviceGL::bindShader(const Shader *shd)
    {
        //Render::pushCommand([this, shd]()
        //{
            if (last_bound_unit_shader != shd->id)
            {
                glUseProgram(shd->id);
                last_bound_unit_shader = shd->id;
            }
        //});
    }

    void GraphicsDeviceGL::bindVertexArray(const VertexArray *va)
    {
        //Render::pushCommand([this, va]()
        //{
            if (last_bound_unit_vao != va->id)
            {

                glBindVertexArray(va->id);
                last_bound_unit_vao = va->id;
            }
        //});          
    }

    void GraphicsDeviceGL::bindFramebuffer(const Framebuffer *fbo)
    {
        //Render::pushCommand([=]()
        //{
            if (last_bound_unit_fbo != fbo->fbo_id)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo_id);
                last_bound_unit_fbo = fbo->fbo_id;
            }
        //});        
    }

    void GraphicsDeviceGL::bindRenderbuffer(const Framebuffer *fbo)
    {
        Render::pushCommand([fbo]()
        {
            glBindRenderbuffer(GL_RENDERBUFFER, fbo->rb_id);
        });
    }

    void GraphicsDeviceGL::bindForRead(const Framebuffer *fbo)
    {
        Render::pushCommand([fbo]()
        {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo->fbo_id);
        });
    }

    void GraphicsDeviceGL::bindForWrite(const Framebuffer *fbo)
    {
        Render::pushCommand([fbo]()
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo->fbo_id);
        });
    }

    void GraphicsDeviceGL::addColorTexture2D(Texture2D *texture, uint32 color_attachment_id, Framebuffer *fbo)
    {
        if (color_attachment_id > MAX_COLOR_ATT)
            return;

        GLuint type_of_tex = GL_COLOR_ATTACHMENT0 + color_attachment_id;

        fbo->color_textures.push_back(texture);
        Texture2D *color_texture = fbo->color_textures[color_attachment_id];

        setTexture2DFbo(type_of_tex, TEXTURE_TYPE::COLOR, texture);
        fbo->buffers.push_back(type_of_tex);
        glDrawBuffers((GLsizei)fbo->buffers.size(), fbo->buffers.data());
    }

    void GraphicsDeviceGL::addDepthTexture2D(Texture2D *depth, Framebuffer *fbo)
    {
        fbo->depth_texture = depth;
        bindRenderbuffer(fbo);
        setDepthBufferAttachment(fbo);
    }

    void GraphicsDeviceGL::addDepthTexture2D(uint32 w, uint32 h, Framebuffer *fbo)
    {
        if (!fbo->depth_texture)
        {
            fbo->depth_texture = new Texture2D();
            fbo->depth_texture->desc.width = w;
            fbo->depth_texture->desc.height = h;
            fbo->depth_texture->desc.dimension = TEXTURE_2D;
            fbo->depth_texture->desc.texture_type = DEPTH;
        
            createTexture(fbo->depth_texture);
            bindTexture(TEXTURE_TYPE::DEPTH, fbo->depth_texture);
            loadTextureGpu(TEXTURE_TYPE::COLOR, w, h, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
            
            setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
            setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
            
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, fbo->depth_texture->id, 0);
        }

        bindRenderbuffer(fbo);
        setDepthBufferAttachment(fbo);
    }

    void GraphicsDeviceGL::setDepthBufferAttachment(const Framebuffer *fbo)
    {
        setRenderbuffer(GL_DEPTH_COMPONENT32, fbo->depth_texture->desc.width, fbo->depth_texture->desc.height);
        setFramebufferRenderbufferAttachment(fbo);
    }

    void GraphicsDeviceGL::setDepthBufferAttachment(uint32 w, uint32 h, const Framebuffer *fbo)
    {
        setRenderbuffer(GL_DEPTH_COMPONENT32, w, h);
        setFramebufferRenderbufferAttachment(fbo);
    }

    Texture2D& GraphicsDeviceGL::getTexture(uint32 number, const Framebuffer *fbo)
    {
        if (fbo && number >= 0 && number <= MAX_COLOR_ATT)
        {
            return *fbo->color_textures[number];
        }
        
        //return Texture2D();
    }

    void GraphicsDeviceGL::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, Texture2D *texture)
    {
        uint32 tex_t = convert_texture_type_gl(tex_type);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, tex_t, texture->id, 0);
    }

    void GraphicsDeviceGL::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D * texture)
    {
        uint32 tex_t = convert_texture_type_gl(tex_type);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, tex_t + i, texture->id, 0);
    }

    void GraphicsDeviceGL::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D * texture, uint32 mip)
    {
        uint32 tex_t = convert_texture_type_gl(tex_type);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, tex_t + i, texture->id, mip);
    }

    void GraphicsDeviceGL::setRenderbuffer(int depth_component, uint32 width, uint32 height)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, depth_component, width, height);
    }

    void GraphicsDeviceGL::setFramebufferRenderbufferAttachment(const Framebuffer *fbo)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->rb_id);
    }

    void GraphicsDeviceGL::checkFramebuffer()
    {
        GLuint error = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (error != GL_FRAMEBUFFER_COMPLETE)
        {
            print_error("Framebuffer setup");

            switch (error)
            {
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                print_error("GL_Framebuffer_INCOMPLETE_ATTACHMENT");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                print_error("GL_Framebuffer_INCOMPLETE_MISSING_ATTACHMENT");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                print_error("GL_Framebuffer_INCOMPLETE_DRAW_BUFFER");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                print_error("GL_Framebuffer_INCOMPLETE_LAYER_TARGETS");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                print_error("GL_Framebuffer_INCOMPLETE_READ_BUFFER");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                print_error("GL_Framebuffer_INCOMPLETE_MULTISAMPLE");
                break;
            }
        }
    }

    void GraphicsDeviceGL::unbindTexture(TEXTURE_TYPE texture)
    {
        uint32 gl_texture_type = convert_texture_type_gl(texture);
        glBindTexture(gl_texture_type, 0);
        last_bound_unit_texture = 0;
    }

    void GraphicsDeviceGL::unbindVertexArray()
    {
        Render::pushCommand([&]()
        {
            glBindVertexArray(0);
        });
        last_bound_unit_vao = 0;
    }

    void GraphicsDeviceGL::unbindShader()
    {
        Render::pushCommand([&]()
        {
            glUseProgram(0);
        });
        last_bound_unit_shader = 0;
    }

    void GraphicsDeviceGL::unbindFramebuffer()
    {
        //Render::pushCommand([&]()
        //{
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //});

        last_bound_unit_fbo = 0;
    }

    void GraphicsDeviceGL::setBool(const std::string & name, bool value, Shader *shd)
    {
        Render::pushCommand([name, value, shd]()
        {
            glUniform1i(glGetUniformLocation(shd->id, name.c_str()), (int)value);
        });
    }

    void GraphicsDeviceGL::setInt(const std::string &name, int32 value, Shader* shd)
    {
        Render::pushCommand([name, value, shd]()
        {
            glUniform1i(glGetUniformLocation(shd->id, name.c_str()), value);
        });
    }

    void GraphicsDeviceGL::setFloat(const std::string &name, real32 value, Shader *shd)
    {
        Render::pushCommand([name, value, shd]()
        {
            glUniform1f(glGetUniformLocation(shd->id, name.c_str()), value);
        });
    }

    void GraphicsDeviceGL::setVec2(const std::string &name, const Vec2& value, Shader *shd)
    {
        int location = glGetUniformLocation(shd->id, name.c_str());
        glUniform2fv(location, 1, value.data);
    }

    void GraphicsDeviceGL::setVec2(const std::string &name, real32 x, real32 y, Shader *shd)
    {
        Render::pushCommand([name, x, y, shd]()
        {
            glUniform2f(glGetUniformLocation(shd->id, name.c_str()), x, y);
        });
    }

    void GraphicsDeviceGL::setVec3(const std::string &name, const Vec3& value, Shader *shd)
    {
        setVec3(name, value.x, value.y, value.z, shd);
    }

    void GraphicsDeviceGL::setVec3(const std::string &name, real32 x, real32 y, real32 z, Shader *shd)
    {
        //Render::pushCommand([name, x, y, z, shd]()
        //{
        int location = glGetUniformLocation(shd->id, name.c_str());
        glUniform3f(location, x, y, z);
        //});
    }

    void GraphicsDeviceGL::setVec4(const std::string &name, const Vec4& value, Shader *shd)
    {
        setVec4(name, value.x, value.y, value.z, value.w, shd);
    }

    void GraphicsDeviceGL::setVec4(const std::string &name, real32 x, real32 y, real32 z, real32 w, Shader *shd)
    {
        int location = glGetUniformLocation(shd->id, name.c_str());
        glUniform4f(location, x, y, z, w);
    }

    void GraphicsDeviceGL::setMat2(const std::string &name, const Matrix2x2 &mat, Shader *shd)
    {
        int location = glGetUniformLocation(shd->id, name.c_str());
        glUniformMatrix2fv(location, 1, GL_FALSE, mat.data);
    }

    void GraphicsDeviceGL::setMat3(const std::string &name, const Matrix3x3 &mat, Shader *shd)
    {
        int location = glGetUniformLocation(shd->id, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, mat.data);
    }

    void GraphicsDeviceGL::setMat4(const std::string &name, const Matrix4x4 &mat, Shader *shd)
    {
        //Render::pushCommand([name, mat, shd]()
        //{
            int location = glGetUniformLocation(shd->id, name.c_str());
            glUniformMatrix4fv(location, 1, GL_FALSE, mat.data);        
        //});
    }

    bool32 GraphicsDeviceGL::createTexture(Texture2D *texture)
    {
        return createTexture(1, texture);
    }

    bool32 GraphicsDeviceGL::createTexture(uint32 count, Texture2D *texture)
    {
        assert(count > 0);
        glGenTextures(count, &texture->id);
        texture->is_valid = true;
        return true;
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, Texture2D *texture)
    {
        return createTexture2D(path, nullptr, texture);
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, TEXTURE_TYPE tex_type, Texture2D *texture)
    {
        return createTexture2D(path, nullptr, tex_type, false, texture);
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, TEXTURE_TYPE tex_type, uint32 samples, bool32 gen_mip, Texture2D *texture)
    {
        return createTexture2D(path, nullptr, tex_type, 0, samples, gen_mip, texture);
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, const char *dir, Texture2D *texture)
    {
        return createTexture2D(path, dir, TEXTURE_TYPE::COLOR, true, texture);
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, uint32 samples, bool32 generate_mipmap, Texture2D* texture)
    {
        const char *path_res;

        std::string filename(path);
        
        if (dir)
        {
            std::string dirname(dir);
            filename = dirname + '/' + filename;
            path_res = filename.c_str();
        }
        else
        {
            path_res = path;
        }
            
        int channels = 0;

        void *image = nullptr;

        switch (type)
        {
        case COLOR:
        case GREYSCALE:
        case LUT:
        case CUBEMAP:
        case DEPTH:
            image = xe_core::loadTextureFromDisc(path_res, texture->desc.width, texture->desc.height, channels, 0, true);
            break;
        case HDR:
            image = xe_core::loadTextureFloatFromDisc(path_res, texture->desc.width, texture->desc.height, channels, 0, true);
            break;
        default:
            break;
        }
        
        if (!image)
        {
            //xe_utility::error("Failed to load texture: " + std::string(path));
            return false;
        }

        GLenum internal_format = 0, data_format = 0;
        if (channels == 1)
        {
            internal_format = GL_R8;
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

        if (samples > 1)
        {
            glGenTextures(1, &texture->id);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture->id);
            texture->is_valid = true;
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, texture->desc.width, texture->desc.height, GL_FALSE);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        }
        else
        {
            createTexture(texture);
            bindTexture(type, texture);

            switch (type)
            {
            case COLOR:
            case LUT:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
                loadTextureGpu(type, texture->desc.width, texture->desc.width, internal_format, data_format, image);

                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);

                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::NEAREST);

                break;
            case GREYSCALE:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                loadTextureGpu(type, texture->desc.width, texture->desc.width, internal_format, data_format, image);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);

                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::NEAREST);
                break;
            case HDR:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, texture->desc.width, texture->desc.height, 0, data_format, GL_FLOAT, image);

                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

                break;
            case CUBEMAP:
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, texture->desc.width, texture->desc.height, 0, data_format, GL_UNSIGNED_BYTE, image);
                break;
            case DEPTH:
                break;
            default:
                break;
            }
        }

        
        if (generate_mipmap)
            generateTextureMipmap(type);

        unbindTexture(type);

        //xe_core::deleteData(image);

        return true;
    }

    bool32 GraphicsDeviceGL::createTexture2D(uint32 width, uint32 height, Texture2D *texture)
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

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, const char *dir, TEXTURE_TYPE type, bool32 generate_mipmap, Texture2D *texture)
    {
        return createTexture2D(path, dir, type, 0, 1, generate_mipmap, texture);
    }

    bool32 GraphicsDeviceGL::createShader(const char *vertex_code, const char *fragment_code, Shader *shd)
    {
        std::string vs_source = xe_core::readFileString(vertex_code);
        std::string fs_source = xe_core::readFileString(fragment_code);

        uint32 vertex_id = compileShader(SHADER_TYPE::VS, vs_source);
        uint32 pixel_id = compileShader(SHADER_TYPE::PS, fs_source);

        if (vertex_id == -1 || pixel_id == -1)
        {
            return false;
        }

        shd->id = createShaderProgram(vertex_id, pixel_id);
        
        return true;
    }

    uint32 GraphicsDeviceGL::compileShader(SHADER_TYPE type, std::string &shader_source)
    {
        const GLchar *shader_code = (GLchar*)shader_source.c_str();

        uint32 shader_type = 0;

        switch (type)
        {
        case SHADER_TYPE::VS:
        {
            shader_type |= GL_VERTEX_SHADER;
        } break;
        case SHADER_TYPE::PS:
        {
            shader_type |= GL_FRAGMENT_SHADER;
        } break;
        default:
            break;
        }

        uint32 id = glCreateShader(shader_type);
        glShaderSource(id, 1, &shader_code, NULL);
        glCompileShader(id);
        
        GLint status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);

        if (status != GL_TRUE)
        {
            GLint length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            GLchar* buffer = alloc_mem GLchar[length];
            GLint buflength;
            glGetShaderInfoLog(id, length, &buflength, buffer);

            print_error("Shader: " + std::string(shader_code));
            print_error(buffer);

            delete[] buffer;

            return -1;
        }
        
        return id;
    }
    
    uint32 GraphicsDeviceGL::createShaderProgram(uint32 id_vs, uint32 id_pixel)
    {
        uint32 id = glCreateProgram();

        glAttachShader(id, id_vs);
        glAttachShader(id, id_pixel);
        glLinkProgram(id);
        glValidateProgram(id);

        destroyShader(id_vs);
        destroyShader(id_pixel);

        return id;
    }

    bool32 GraphicsDeviceGL::createFramebuffer(uint32 count, Framebuffer *fbo)
    {
        //Render::pushCommand([&]()
        //{
            glGenFramebuffers(count, &fbo->fbo_id);
        //});
        
        return true;
    }

    bool32 GraphicsDeviceGL::createRenderbuffer(uint32 count, Framebuffer *fbo)
    {
        //Render::pushCommand([&]()
        //{
            glGenRenderbuffers(count, &fbo->rb_id);
        //});
        
        return true;
    }

    bool32 GraphicsDeviceGL::createVertexBuffer(void *vertices, uint32 size, DRAW_TYPE draw_type, VertexBuffer *vb)
    {
        vb->data = vertices;
        
        //Render::pushCommand([vb, size, draw_type]() mutable
        //{
            //glCreateBuffers(1, &vb->id);
        glCreateBuffers(1, &vb->id);
        glBindBuffer(GL_ARRAY_BUFFER, vb->id);

            uint32 draw_type_gl = convert_draw_type_to_gl_type(draw_type);
            //glNamedBufferData(vb->id, size, vb->data, draw_type_gl);
            glBufferData(GL_ARRAY_BUFFER, size, vb->data, draw_type_gl);
        //});

        return vb->data ? true : false;
    }

    bool32 GraphicsDeviceGL::createIndexBuffer(uint32 *indices, uint32 size, IndexBuffer *ib)
    {
        ib->index_data = indices;
        ib->count = size;

        //Render::pushCommand([ib]() mutable
        //{
            glCreateBuffers(1, &ib->id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->count * sizeof(GLuint), ib->index_data, GL_STATIC_DRAW);
            //glNamedBufferData(ib->id, ib->count * sizeof(GLuint), ib->index_data, GL_STATIC_DRAW);
        //});

        return ib->index_data ? true : false;
    }

    bool32 GraphicsDeviceGL::createIndexBuffer(Index *indices, uint32 size, IndexBuffer *ib)
    {
        ib->data = indices;
        ib->count = size;

        //Render::pushCommand([ib]() mutable
        //{
            glCreateBuffers(1, &ib->id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->count * sizeof(GLuint), ib->data, GL_STATIC_DRAW);
            //glNamedBufferData(ib->id, ib->count * sizeof(GLuint), ib->data, GL_STATIC_DRAW);
        //});

        return ib->data ? true : false;
    }

    bool32 GraphicsDeviceGL::createVertexArray(VertexArray *va)
    {
        //Render::pushCommand([va]() mutable
        //{
            glCreateVertexArrays(1, &va->id);
        //});
        
        return true;
    }

    bool32 GraphicsDeviceGL::createBufferLayout(std::initializer_list<BufferElement>& element, BufferLayout *buf_layout)
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

    bool32 GraphicsDeviceGL::setVertexBufferLayout(VertexBuffer *vb, BufferLayout *buf_layout)
    {
        vb->layout = *buf_layout;

        return true;
    }

    bool32 GraphicsDeviceGL::addVertexBuffer(VertexArray *va, VertexBuffer *vb)
    {
        //Render::pushCommand([va, vb]() mutable
        //{
            glBindVertexArray(va->id);
            
            const auto& buffer_layout = vb->layout;

            for (uint16 i = 0; i < buffer_layout.elements.size(); i++)
            {
                auto cur_element = buffer_layout.elements.at(i);

                glEnableVertexAttribArray(va->ibuffer_index);
                glVertexAttribPointer(va->ibuffer_index, cur_element.elementTypeCount(), GL_FLOAT, GL_FALSE, buffer_layout.stride, (const void*)cur_element.offset);

                va->ibuffer_index++;
            }            
        //});

        return false;
    }

    bool32 GraphicsDeviceGL::setIndexBuffer(VertexArray *va, IndexBuffer *ib)
    {
        // assert      
        
        //Render::pushCommand([va, ib]() mutable
        //{
            glBindVertexArray(va->id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
            va->ib = ib;
        //});

        return true;
    }

    void GraphicsDeviceGL::setTextureWrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler)
    {
        Render::pushCommand([type, wrapping_axis, sampler]() mutable
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            uint32 gl_wrapping_axis = convert_texture_wrapping_axis_type_gl(wrapping_axis);
            uint32 gl_wrapping = convert_texture_wrapping_type_gl(sampler);
            glTexParameteri(gl_texture_type, gl_wrapping_axis, gl_wrapping);

        });
    }

    void GraphicsDeviceGL::setTextureSampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler)
    {
        Render::pushCommand([type, filter_operation, sampler]() mutable
        {
            uint32 gl_texture_type = convert_texture_type_gl(type);
            uint32 gl_texture_filter = convert_texture_filter_operation_gl(filter_operation);
            uint32 gl_texture_sampling = convert_texture_sampling_type_gl(sampler);
            glTexParameteri(gl_texture_type, gl_texture_filter, gl_texture_sampling);
        });        
    }

    void GraphicsDeviceGL::loadTextureGpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void *image)
    {
        Render::pushCommand([texture_t, width, height, internal_format, data_format, image]() mutable
        {
            uint32 gl_texture_type = convert_texture_type_gl(texture_t);
            glTexImage2D(gl_texture_type, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image);
        });
    }

    // @Special cubemap
    void GraphicsDeviceGL::loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, const void *image)
    {
        glTexImage2D(texture_t, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image);
    }

    void GraphicsDeviceGL::loadTextureGpu(int texture_t, int width, int height, int internal_format, int data_format, int data_type, const void * image)
    {
        glTexImage2D(texture_t, 0, internal_format, width, height, 0, data_format, data_type, image);
    }

    void GraphicsDeviceGL::generateTextureMipmap(TEXTURE_TYPE texture_t)
    {
        Render::pushCommand([texture_t]() mutable
        {
            uint32 gl_t = convert_texture_type_gl(texture_t);
            glGenerateMipmap(gl_t);
        });
    }

    void GraphicsDeviceGL::destroyTexture2D(Texture2D *tex)
    {
        Render::pushCommand([tex]() mutable
        {
            if (tex->is_valid)
            {
                glDeleteTextures(1, &tex->id);
            }
        });
    }

    void GraphicsDeviceGL::destroyFramebuffer(Framebuffer *fbo)
    {
        Render::pushCommand([fbo]() mutable
        {
            glDeleteFramebuffers(1, &fbo->fbo_id);
        });
    }

    void GraphicsDeviceGL::destroyShader(uint32 id)
    {
        //Render::pushCommand([id]() mutable
        //{
            glDeleteShader(id);
        //});
    }

    void GraphicsDeviceGL::destroyBuffer(VertexBuffer *vb)
    {
        //Render::pushCommand([vb]() mutable
        //{
            glDeleteBuffers(1, &vb->id);
        //});
    }

    void GraphicsDeviceGL::destroyBuffer(IndexBuffer *ib)
    {
        //Render::pushCommand([ib]() mutable
       // {
            glDeleteBuffers(1, &ib->id);
        //});
    }

    void GraphicsDeviceGL::setDrawBuffer(uint32 type)
    {
        Render::pushCommand([type]() mutable
        {
            glDrawBuffer(type);
        });
    }

    void GraphicsDeviceGL::setDrawBuffers(uint32 count, void *pointer)
    {
        Render::pushCommand([count, pointer]() mutable
        {
            glDrawBuffers(count, (uint32*)pointer);
        });
    }

    void GraphicsDeviceGL::setReadBuffer(uint32 type)
    {
        Render::pushCommand([type]() mutable
        {
            glReadBuffer(type);
        });
    }

    void GraphicsDeviceGL::checkError()
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            const char* erro_char = (const char*)err;
            //printf("%s", erro_char);
        }
    }

    void GraphicsDeviceGL::loadBindings()
    {
        //if (!gladLoadGL())
        //{
        //    print_error("Failed to init OpenGL loader!\n");
        //}
            
        const char *gl_vendor = (char*)glGetString(GL_VENDOR);
        const char *gl_renderer = (char*)glGetString(GL_RENDERER);
        const char *gl_version = (char*)glGetString(GL_VERSION);

        print_info(gl_vendor);
        print_info(gl_renderer);
        print_info(gl_version);
    }

    void GraphicsDeviceGL::unbindBuffer(BUFFER_TYPE type)
    {
        uint32 type_gl = convert_buffer_type_gl(type);
        glBindBuffer(type_gl, 0);
    }

    void GraphicsDeviceGL::startExecution()
    {
        clearColor(clear_color_v[0], clear_color_v[1], clear_color_v[2], clear_color_v[3]);
        clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GraphicsDeviceGL::endExecution()
    {     
        int add = 0;
        //SwapBuffers(xe_platform::get_dc());
    }

#endif