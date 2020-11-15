#ifndef GRAPHICS_DEVICE_GL_CPP
#define GRAPHICS_DEVICE_GL_CPP

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
  
    void GraphicsDeviceGL::setAPI()
    {
        api = API_TYPE::OPENGL;
    }

    bool32 GraphicsDeviceGL::createTexture(Texture2D *texture)
    {
        return createTexture(1, texture);
    }

    bool32 GraphicsDeviceGL::createTexture(uint32 count, Texture2D *texture)
    {
        assert(count > 0);
        glGenTextures(count, &texture->rhi.getIDRef());
        
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

    internal 
    std::string concatPath(const char *path, const char *dir)
    {
        std::string result(path);

        if (dir)
        {
            std::string dirname(dir);
            result = dirname + '/' + result;
        }        

        return result;
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, const char* dir, TEXTURE_TYPE type, uint32 i, uint32 samples, bool32 generate_mipmap, Texture2D* texture)
    {
        std::string path_str = concatPath(path, dir);
        const char *path_res = path_str.c_str();

        /*std::string filename(path);
        
        if (dir)
        {
            std::string dirname(dir);
            filename = dirname + '/' + filename;
            path_res = filename.c_str();
        }
        else
        {
            path_res = path;
        }*/
           
        int channels = 0;

        void *image = nullptr;
        
        GraphicsContext *context = Render::getContext();

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
            createTexture(texture);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture->rhi.getIDRef());            
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, texture->desc.width, texture->desc.height, GL_FALSE);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        }
        else
        {
            createTexture(texture);
            context->bindTexture(type, texture);

            switch (type)
            {
            case COLOR:
            case LUT:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
                loadTextureGpu(type, texture->desc.width, texture->desc.width, internal_format, data_format, image);

                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);

                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

                break;
            case GREYSCALE:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                loadTextureGpu(type, texture->desc.width, texture->desc.width, internal_format, data_format, image);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_REPEAT);

                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR_MIPMAP_LINEAR);
                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
                break;
            case HDR:                
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);
                setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, TEXTURE_WRAPPING::TEXTURE_ADDRESS_CLAMP);

                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);
                setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, texture->desc.width, texture->desc.height, 0, data_format, GL_FLOAT, image);

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
        {
            generateTextureMipmap(type);
        }

        context->unbindTexture(type);

        xe_core::deleteData(image);

        return true;
    }

    bool32 GraphicsDeviceGL::createTexture2D(TEXTURE_TYPE type, PIXEL_FORMAT px, PIXEL_INTERNAL_FORMAT ipx, PIXEL_TYPE pxl_type, uint32 width, uint32 height, uint32 mip_count, TextureSampler &sampler, Texture2D *texture)
    {
        texture->desc.width = width;
        texture->desc.height = height;
        texture->desc.dimension = TEXTURE_2D;
        texture->desc.mip_count = mip_count;
        texture->desc.texture_type = type;
        texture->desc.pixel_format = px;
        texture->desc.internal_pixel_format = ipx;
        texture->desc.pxl_type = pxl_type;
        texture->desc.sampler = sampler;

        uint32 glTextureType = convert_texture_type_gl(type);
        uint32 glPixelFormat = convert_pixel_format_to_gl(px);
        uint32 glInternalPixelType = convert_internal_pixel_format_to_gl(ipx);
        uint32 glPixelType = convert_pixel_type_to_gl(pxl_type);

        glGenTextures(1, &texture->rhi.getIDRef());
        glBindTexture(glTextureType, texture->rhi.getID());

        setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_S, sampler.wrapping_s);
        setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_T, sampler.wrapping_t);

        if (type == TEXTURE_TYPE::CUBEMAP)
        {
            setTextureWrapping(type, TEXTURE_WRAPPING_AXIS::TEXTURE_AXIS_R, sampler.wrapping_r);
        }

        setTextureSampling(type, TEXTURE_FILTER_OPERATION::MIN, sampler.pxl_sampling_min);
        setTextureSampling(type, TEXTURE_FILTER_OPERATION::MAG, sampler.pxl_sampling_mag);

        glTexImage2D(glTextureType, 0, glPixelFormat, width, height, 0, glInternalPixelType, glPixelType, 0);

        if (mip_count > 0)
        {
            generateTextureMipmap(type);
        }

        glBindTexture(glTextureType, 0);

        return true;
    }

    bool32 GraphicsDeviceGL::createTexture2D(Texture2D *texture)
    {
        TextureDesc& desc = texture->desc;

        return createTexture2D(desc.texture_type, desc.pixel_format, desc.internal_pixel_format, desc.pxl_type, desc.width, desc.height, desc.mip_count, desc.sampler, texture);
    }

    bool32 GraphicsDeviceGL::createTexture2D(const char *path, const char *dir, TEXTURE_TYPE type, bool32 generate_mipmap, Texture2D *texture)
    {
        return createTexture2D(path, dir, type, 0, 1, generate_mipmap, texture);
    }

    bool32 GraphicsDeviceGL::createShader(const char *vertex_code, const char *fragment_code, Shader *shd)
    {
        std::string vs_source = xe_core::readFileToString(vertex_code);
        std::string fs_source = xe_core::readFileToString(fragment_code);

        uint32 vertex_id = compileShader(SHADER_TYPE::VS, vs_source);
        uint32 pixel_id = compileShader(SHADER_TYPE::PS, fs_source);

        if (vertex_id == -1 || pixel_id == -1)
        {
            return false;
        }

        shd->rhi.setID(createShaderProgram(vertex_id, pixel_id));
        
        return true;
    }

    internal 
    GLenum GetShaderTypeFromString(const std::string& type)
    {        
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;
        if (type == "compute")
            return GL_COMPUTE_SHADER;

        return GL_NONE;
    }

    internal 
    std::unordered_map<GLenum, std::string> SplitShader(const std::string &file_source)
    {
        std::unordered_map<GLenum, std::string> result = {};

        const char* token_type = "#shader";
        size_t token_length = strlen(token_type);
        size_t token_pos = file_source.find(token_type, 0);
        
        while (token_pos != std::string::npos)
        {
            size_t eol = file_source.find_first_of("\r\n", token_pos);
            
            size_t begin = token_pos + token_length + 1;
            std::string type = file_source.substr(begin, eol - begin);
            
            size_t next_line_pos = file_source.find_first_not_of("\r\n", eol);
            token_pos = file_source.find(token_type, next_line_pos);
            auto shaderType = GetShaderTypeFromString(type);
            result[shaderType] = file_source.substr(next_line_pos, token_pos - (next_line_pos == std::string::npos ? file_source.size() - 1 : next_line_pos));
        }

        return result;
    }

    bool32 GraphicsDeviceGL::createShader(const char *shader_path, Shader *shd)
    {
        std::string source = xe_core::readFileToString(shader_path);

        std::unordered_map<GLenum, std::string> split_shaders = SplitShader(source);
        
        uint32 vertex_id = compileShader(SHADER_TYPE::VS, split_shaders[GL_VERTEX_SHADER]);
        uint32 pixel_id = compileShader(SHADER_TYPE::PS, split_shaders[GL_FRAGMENT_SHADER]);

        if (vertex_id == INVALID_ID || pixel_id == INVALID_ID)
        {
            return false;
        }

        shd->rhi.setID(createShaderProgram(vertex_id, pixel_id));

        return true;
    }

    internal 
    uint32 convertShaderToGLType(SHADER_TYPE type)
    {
        uint32 res = 0;

        switch (type)
        {
        case SHADER_TYPE::VS:
        {
            res |= GL_VERTEX_SHADER;
        } break;
        case SHADER_TYPE::PS:
        {
            res |= GL_FRAGMENT_SHADER;
        } break;
        default:
            break;
        }

        return res;
    }

    uint32 GraphicsDeviceGL::compileShader(SHADER_TYPE type, std::string &shader_source)
    {
        const GLchar *shader_code = (GLchar*)shader_source.c_str();

        uint32 shader_type = convertShaderToGLType(type);

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

            return INVALID_ID;
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

    internal GLenum convertToGLAttachment(RENDER_TARGET_TYPE type)
    {
        switch (type)
        {
        case  RTColor0:
        {
            return GL_COLOR_ATTACHMENT0;
        } break;
        case RTColor1:
        {
            return GL_COLOR_ATTACHMENT1;
        } break;
        case RTColor2:
        {
            return GL_COLOR_ATTACHMENT2;
        } break;
        case RTColor3:
        {
            return GL_COLOR_ATTACHMENT3;
        } break;
        case RTDepth:
        {
            return GL_DEPTH_ATTACHMENT;
        } break;
        case RTStencil:
        {
            return GL_STENCIL_ATTACHMENT;
        } break;
        case RTDepthStencil:
        {
            return GL_DEPTH_STENCIL_ATTACHMENT;
        } break;
        default:
            print_error("Specify framebuffer attachment type!!!");
            return GL_INVALID_ENUM;
            break;
        }
    }

    internal 
    bool32 attachDepthStencil(const FramebufferDesc& desc, const FramebufferSpecs &specs, Framebuffer *fbo, RENDER_TARGET_TYPE attach)
    {
        TextureDesc depthStencil = desc.ds;

        Texture2D depthStencilTex = Texture2D::create(depthStencil.width, depthStencil.height, depthStencil.texture_type, depthStencil.pixel_format, depthStencil.internal_pixel_format, depthStencil.pxl_type, depthStencil.mip_count, depthStencil.sampler);

        fbo->tex_attachments[attach] = depthStencilTex;
        GLenum attachName = convertToGLAttachment(attach);
        glFramebufferTexture(GL_FRAMEBUFFER, attachName, depthStencilTex.rhi.getID(), 0);
       
        return true;
    }

    internal 
    bool32 attachColors(const FramebufferDesc& desc, const FramebufferSpecs &specs, Framebuffer *fbo)
    {
        for (uint32 i = 0; i < MAX_COLOR_FRAMEBUFFER_ATTACHMENTS; ++i)
        {
            TextureDesc texDesc = desc.attachments[i];

            Texture2D textureColor = Texture2D::create(texDesc.width, texDesc.height, texDesc.texture_type, texDesc.pixel_format, texDesc.internal_pixel_format, texDesc.pxl_type, texDesc.mip_count, texDesc.sampler);
           
            fbo->tex_attachments[i] = textureColor;

            GLenum attachName = (GLenum)(GL_COLOR_ATTACHMENT0 + i);
            glFramebufferTexture(GL_FRAMEBUFFER, attachName, textureColor.rhi.getID(), 0);
            fbo->color_attach[i] = attachName;
            fbo->colorAttachCount++;
        }

        return true;
    }

    bool32 GraphicsDeviceGL::createFramebuffer(const FramebufferDesc& desc, const FramebufferSpecs &specs, Framebuffer *fbo)
    {
        glGenFramebuffers(specs.framebuffer_count, &fbo->rhi.getIDRef());
        glBindFramebuffer(GL_FRAMEBUFFER, fbo->rhi.getID());

        bool32 isAttachedColors = attachColors(desc, specs, fbo);              

        bool32 isAttachedDS = attachDepthStencil(desc, specs, fbo, RENDER_TARGET_TYPE::RTDepth);
          
        glDrawBuffers(fbo->colorAttachCount, fbo->color_attach);        

        GLenum fbState = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        bool32 isCompleted = GL_FRAMEBUFFER_COMPLETE == fbState;
        
        if (!isCompleted)
        {            
            switch (fbState)
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

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        if (!isCompleted)
        {
            print_error("Failed to create Framebuffer!");
            return false;
        }

        return true;
    }

    bool32 GraphicsDeviceGL::createRenderbuffer(uint32 count, Framebuffer *fbo)
    {
        glGenRenderbuffers(count, &fbo->rb.rhi.getIDRef());
        
        return true;
    }

    bool32 GraphicsDeviceGL::createVertexBuffer(void *vertices, uint32 size, DRAW_TYPE draw_type, VertexBuffer *vb)
    {
        vb->data = vertices;
        
        glCreateBuffers(1, &vb->rhi.getIDRef());
        glBindBuffer(GL_ARRAY_BUFFER, vb->rhi.getID());

        uint32 draw_type_gl = convert_draw_type_to_gl_type(draw_type);
        //glNamedBufferData(vb->id, size, vb->data, draw_type_gl);
        glBufferData(GL_ARRAY_BUFFER, size, vb->data, draw_type_gl);
        
        return vb->data ? true : false;
    }

    bool32 GraphicsDeviceGL::createIndexBuffer(uint32 *indices, uint32 size, IndexBuffer *ib)
    {
        ib->index_data = indices;
        ib->count = size;

        glCreateBuffers(1, &ib->rhi.getIDRef());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->rhi.getID());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->count * sizeof(GLuint), ib->index_data, GL_STATIC_DRAW);
        
        return ib->index_data ? true : false;
    }

    bool32 GraphicsDeviceGL::createIndexBuffer(Index *indices, uint32 size, IndexBuffer *ib)
    {
        ib->data = indices;
        ib->count = size;

        glCreateBuffers(1, &ib->rhi.getIDRef());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->rhi.getID());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->count * sizeof(GLuint), ib->data, GL_STATIC_DRAW);
            //glNamedBufferData(ib->id, ib->count * sizeof(GLuint), ib->data, GL_STATIC_DRAW);
        //});

        return ib->data ? true : false;
    }

    bool32 GraphicsDeviceGL::createVertexArray(VertexArray *va)
    {
        glCreateVertexArrays(1, &va->rhi.getIDRef());
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
            glBindVertexArray(va->rhi.getID());
            
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
            glBindVertexArray(va->rhi.getID());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->rhi.getID());
            va->ib = ib;
        //});

        return true;
    }

    void GraphicsDeviceGL::setTextureWrapping(TEXTURE_TYPE type, TEXTURE_WRAPPING_AXIS wrapping_axis, TEXTURE_WRAPPING sampler)
    {
        //Render::pushCommand([type, wrapping_axis, sampler]() mutable
        //{
            uint32 gl_texture_type = convert_texture_type_gl(type);
            uint32 gl_wrapping_axis = convert_texture_wrapping_axis_type_gl(wrapping_axis);
            uint32 gl_wrapping = convert_texture_wrapping_type_gl(sampler);
            glTexParameteri(gl_texture_type, gl_wrapping_axis, gl_wrapping);

        //});
    }

    void GraphicsDeviceGL::setTextureSampling(TEXTURE_TYPE type, TEXTURE_FILTER_OPERATION filter_operation, TEXTURE_SAMPLING sampler)
    {
        //Render::pushCommand([type, filter_operation, sampler]() mutable
        //{
            uint32 gl_texture_type = convert_texture_type_gl(type);
            uint32 gl_texture_filter = convert_texture_filter_operation_gl(filter_operation);
            uint32 gl_texture_sampling = convert_texture_sampling_type_gl(sampler);
            glTexParameteri(gl_texture_type, gl_texture_filter, gl_texture_sampling);
        //});        
    }

    void GraphicsDeviceGL::loadTextureGpu(TEXTURE_TYPE texture_t, int width, int height, int internal_format, int data_format, const void *image)
    {
        //Render::pushCommand([texture_t, width, height, internal_format, data_format, image]() mutable
        //{
            uint32 gl_texture_type = convert_texture_type_gl(texture_t);
            glTexImage2D(gl_texture_type, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image);
        //});
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
        uint32 gl_t = convert_texture_type_gl(texture_t);
        glGenerateMipmap(gl_t);
    }

    void GraphicsDeviceGL::addColorTexture2D(Texture2D *texture, uint32 color_attachment_id, Framebuffer *fbo)
    {
        if (color_attachment_id > MAX_COLOR_ATT)
            return;

        GLuint type_of_tex = GL_COLOR_ATTACHMENT0 + color_attachment_id;

        /*fbo->color_textures.push_back(texture);
        Texture2D *color_texture = fbo->color_textures[color_attachment_id];

        setTexture2DFbo(type_of_tex, TEXTURE_TYPE::COLOR, texture);
        fbo->buffers.push_back(type_of_tex);
        glDrawBuffers((GLsizei)fbo->buffers.size(), fbo->buffers.data());*/

    }

    void GraphicsDeviceGL::addDepthTexture2D(Texture2D *depth, Framebuffer *fbo)
    {
        GraphicsContext *context = Render::getContext();
        //fbo->depth_texture = depth;
        context->bindRenderbuffer(fbo);
        setDepthBufferAttachment(fbo);
    }

    void GraphicsDeviceGL::addDepthTexture2D(uint32 w, uint32 h, Framebuffer *fbo)
    {
        GraphicsContext *context = Render::getContext();

        /*if (!fbo->depth_texture)
        {
            fbo->depth_texture = new Texture2D();
            fbo->depth_texture->desc.width = w;
            fbo->depth_texture->desc.height = h;
            fbo->depth_texture->desc.dimension = TEXTURE_2D;
            fbo->depth_texture->desc.texture_type = DEPTH;
                        
            createTexture(fbo->depth_texture);
            context->bindTexture(TEXTURE_TYPE::DEPTH, fbo->depth_texture);
            loadTextureGpu(TEXTURE_TYPE::COLOR, w, h, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

            setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MAG, TEXTURE_SAMPLING::LINEAR);
            setTextureSampling(TEXTURE_TYPE::COLOR, TEXTURE_FILTER_OPERATION::MIN, TEXTURE_SAMPLING::LINEAR);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, fbo->depth_texture->id, 0);
        }*/

        context->bindRenderbuffer(fbo);
        setDepthBufferAttachment(fbo);
    }

    void GraphicsDeviceGL::setDepthBufferAttachment(const Framebuffer *fbo)
    {
        GraphicsContext *context = Render::getContext();

        //setRenderbuffer(GL_DEPTH_COMPONENT32, fbo->depth_texture->desc.width, fbo->depth_texture->desc.height);
        setFramebufferRenderbufferAttachment(fbo);
    }

    void GraphicsDeviceGL::setDepthBufferAttachment(uint32 w, uint32 h, const Framebuffer *fbo)
    {
        setRenderbuffer(GL_DEPTH_COMPONENT32, w, h);
        setFramebufferRenderbufferAttachment(fbo);
    }

    Texture2D *GraphicsDeviceGL::getTexture(uint32 number, const Framebuffer *fbo)
    {
        //if (fbo && number >= 0 && number <= MAX_COLOR_ATT)
        //{
        //    return *fbo->color_textures[number];
        //}

        return nullptr;
    }

    void GraphicsDeviceGL::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, Texture2D *texture)
    {
        uint32 tex_t = convert_texture_type_gl(tex_type);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, tex_t, texture->rhi.getID(), 0);
    }

    void GraphicsDeviceGL::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D * texture)
    {
        uint32 tex_t = convert_texture_type_gl(tex_type);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, tex_t + i, texture->rhi.getID(), 0);
    }

    void GraphicsDeviceGL::setTexture2DFbo(uint32 attach_type, TEXTURE_TYPE tex_type, uint32 i, Texture2D * texture, uint32 mip)
    {
        uint32 tex_t = convert_texture_type_gl(tex_type);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attach_type, tex_t + i, texture->rhi.getID(), mip);
    }

    void GraphicsDeviceGL::setRenderbuffer(int depth_component, uint32 width, uint32 height)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, depth_component, width, height);
    }

    void GraphicsDeviceGL::setFramebufferRenderbufferAttachment(const Framebuffer *fbo)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->rb.rhi.getID());
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

    void GraphicsDeviceGL::destroyTexture2D(Texture2D *tex)
    {
        if (tex->isValid())
        {
            uint32 id = tex->rhi.getID();
            glDeleteTextures(1, &id);
        }
    }

    void GraphicsDeviceGL::destroyFramebuffer(Framebuffer *fbo)
    {  
        uint32 id = fbo->rhi.getID();
        glDeleteFramebuffers(1, &id);       
    }

    void GraphicsDeviceGL::destroyShader(uint32 id)
    {
        glDeleteShader(id);
    }

    void GraphicsDeviceGL::destroyBuffer(VertexBuffer *vb)
    {
        uint32 id = vb->rhi.getID();
        glDeleteBuffers(1, &id);
    }

    void GraphicsDeviceGL::destroyBuffer(IndexBuffer *ib)
    {
        uint32 id = ib->rhi.getID();
        glDeleteBuffers(1, &id);
    }

    void GraphicsDeviceGL::setDrawBuffer(uint32 type)
    {
        glDrawBuffer(type);
    }

    void GraphicsDeviceGL::setDrawBuffers(uint32 count, void *pointer)
    {
        glDrawBuffers(count, (uint32*)pointer);
    }

    void GraphicsDeviceGL::setReadBuffer(uint32 type)
    {
         glReadBuffer(type);
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
#endif