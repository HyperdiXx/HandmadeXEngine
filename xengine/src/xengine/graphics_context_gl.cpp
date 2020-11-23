

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
    {
        res |= GL_TEXTURE_2D;
    } break;
    case CUBEMAP:
    {
        res |= GL_TEXTURE_CUBE_MAP;
    } break;
    case CUBEMAP_POSITIVE:
    {
        res |= GL_TEXTURE_CUBE_MAP_POSITIVE_X;
    } break;
    case DEPTH_STENCIL:
    {
        res |= GL_DEPTH_STENCIL;
    } break;
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

constexpr uint32 convert_internal_pixel_format_to_gl(PIXEL_INTERNAL_FORMAT pixel)
{
    uint32 res = 0;

    switch (pixel)
    {
    case IFRGB:
    {
        res |= GL_RGB;
    } break;
    case IFRGBA:
    {
        res |= GL_RGBA;
    } break;
    case IFDEPTH:
    {
        res |= GL_DEPTH_COMPONENT;
    } break;
    case IFDEPTHSTENCIL:
    {
        res |= GL_DEPTH_STENCIL;
    } break;
    case IFRG:
    {
        res |= GL_RG;
    } break;
    case IFR:
    {
        res |= GL_RED;
    } break;            
    default:
        break;
    }

    return res;
}


constexpr uint32 convert_pixel_type_to_gl(PIXEL_TYPE pixel)
{
    uint32 res = 0;

    switch (pixel)
    {
    case PTUBYTE:
    {
        res |= GL_UNSIGNED_BYTE;
    } break;
    case PTUSHORT:
    {
        res |= GL_UNSIGNED_SHORT;
    } break;  
    case PTUINT:
    {
        res |= GL_UNSIGNED_INT;
    } break;
    case PTFLOAT:
    {
        res |= GL_FLOAT;
    } break;            
    default:
        break;
    }

    return res;
}

constexpr uint32 convert_pixel_format_to_gl(PIXEL_FORMAT pixel)
{
    uint32 res = 0;

    switch (pixel)
    {
    case RGBA8:
    {
        res |= GL_RGBA;
    } break;
    case RGBA16:
    {
        res |= GL_RGBA16;
    } break;
    case RGBA8F:
    {
        res |= 0;
    } break;
    case RGBA16F:
    {
        res |= GL_RGBA16F;
    } break;
    case Depth24:
    {
        res |= GL_DEPTH_COMPONENT;
    } break;
    case Depth32:
    {
        res |= GL_DEPTH_COMPONENT;
    } break;
    case Stencil24:
    {
        res |= 0;
    } break;
    case Stencil32:
    {
        res |= 0;
    } break;
    case DepthStencil32:
    {
        res |= GL_DEPTH_STENCIL;
    } break;
    default:
        break;
    }

    return res;
}

void GraphicsContextGL::clear(int flags)
{
    glClear(flags);
}

void GraphicsContextGL::clearColor(real32 r, real32 g, real32 b, real32 a)
{
    clear_color_v[0] = r;
    clear_color_v[1] = g;
    clear_color_v[2] = b;
    clear_color_v[3] = a;
    glClearColor(clear_color_v[0], clear_color_v[1], clear_color_v[2], clear_color_v[3]);
}

void GraphicsContextGL::clearColor(const Vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}

void GraphicsContextGL::setViewport(int32 x, int32 y, int32 width, int32 height)
{
    glViewport(x, y, width, height);
}

// @ Store all stuff in context state like dx
void GraphicsContextGL::enable(int type)
{
    glEnable(type);
}

void GraphicsContextGL::disable(int type)
{
    glDisable(type);
}

void GraphicsContextGL::setBlendFunc(int src, int dst)
{
    glBlendFunc(src, dst);
}

void GraphicsContextGL::setDepthFunc(int type)
{
    glDepthFunc(type);
}

void GraphicsContextGL::setCullMode(int type)
{
    glCullFace(type);
}

void GraphicsContextGL::setDepth(bool32 type)
{
    glDepthMask(type);
}

void GraphicsContextGL::setLineWidth(uint32 line_width)
{
    //Render::pushCommand([=]()
    //{
    glLineWidth(line_width);
    //});
}

void GraphicsContextGL::drawArray(PRIMITIVE_TOPOLOGY mode, uint32 first, uint32 count)
{
    //Render::pushCommand([=]()
    //{
    uint32 gl_primitive_type = convert_primitive_type(mode);
    glDrawArrays(gl_primitive_type, first, count);
    //});
}

void GraphicsContextGL::drawIndexed(PRIMITIVE_TOPOLOGY mode, uint32 count, int type, void *ind)
{
    uint32 gl_primitive_type = convert_primitive_type(mode);
    glDrawElements(gl_primitive_type, count, type, ind);
}

void GraphicsContextGL::pushDataToBuffer(uint32 index, BUFFER_TYPE type, uint32 offset, uint64 size, void *data)
{
    uint32 buf_type = convert_buffer_type_gl(type);
    glBufferSubData(buf_type, offset, size, data);
}

void GraphicsContextGL::activateBindTexture(TEXTURE_TYPE type, const Texture2D *texture)
{
    const GPUHandler id = texture->rhi.getID();
    if (last_bound_unit_texture != id)
    {
        uint32 gl_texture_type = convert_texture_type_gl(type);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(gl_texture_type, id);
        last_bound_unit_texture = id;
    }
}

void GraphicsContextGL::activateBindTexture(TEXTURE_TYPE type, const Cubemap *texture)
{
    const GPUHandler id = texture->rhi.getID();
    if (last_bound_unit_texture != id)
    {
        uint32 gl_texture_type = convert_texture_type_gl(type);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(gl_texture_type, id);
        last_bound_unit_texture = id;
    }
}

void GraphicsContextGL::activateTexture(uint32 index)
{
    glActiveTexture(GL_TEXTURE0 + index);
}

void GraphicsContextGL::bindTexture(TEXTURE_TYPE type, const Texture2D *texture)
{
    const GPUHandler id = texture->rhi.getID();
    if (last_bound_unit_texture != id)
    {
        uint32 gl_texture_type = convert_texture_type_gl(type);
        glBindTexture(gl_texture_type, id);
        last_bound_unit_texture = id;
    }
}

void GraphicsContextGL::bindTexture(TEXTURE_TYPE type, uint32 index)
{
    if (last_bound_unit_texture != index)
    {
        uint32 gl_texture_type = convert_texture_type_gl(type);
        glBindTexture(gl_texture_type, index);
        last_bound_unit_texture = index;
    }
}

void GraphicsContextGL::bindBuffer(const VertexBuffer *vb)
{
    const GPUHandler id = vb->rhi.getID();
    if (last_bound_unit_vbuffer != id)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        last_bound_unit_vbuffer = id;
    }
}

void GraphicsContextGL::bindBuffer(const IndexBuffer *ib)
{
    const GPUHandler id = ib->rhi.getID();
    if (last_bound_unit_ibuffer != id)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        last_bound_unit_ibuffer = id;
    }
}

void GraphicsContextGL::bindShader(const Shader *shd)
{
    const GPUHandler id = shd->rhi.getID();
    if (last_bound_unit_shader != id)
    {
        glUseProgram(id);
        last_bound_unit_shader = id;
    }
}

void GraphicsContextGL::bindVertexArray(const VertexArray *va)
{
    const GPUHandler id = va->rhi.getID();
    if (last_bound_unit_vao != id)
    {
        glBindVertexArray(id);
        last_bound_unit_vao = id;
    }
}

void GraphicsContextGL::bindFramebuffer(const Framebuffer *fbo)
{
    const GPUHandler id = fbo->rhi.getID();
    if (last_bound_unit_fbo != id)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        last_bound_unit_fbo = id;
    }        
}

void GraphicsContextGL::bindRenderbuffer(const Framebuffer *fbo)
{
    glBindRenderbuffer(GL_RENDERBUFFER, fbo->rb.rhi.getID());
}

void GraphicsContextGL::bindForRead(const Framebuffer *fbo)
{
    const GPUHandler id = fbo->rhi.getID();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
}

void GraphicsContextGL::bindForWrite(const Framebuffer *fbo)
{
    const GPUHandler id = fbo->rhi.getID();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
}

void GraphicsContextGL::unbindTexture(TEXTURE_TYPE texture)
{
    uint32 gl_texture_type = convert_texture_type_gl(texture);
    glBindTexture(gl_texture_type, 0);
    last_bound_unit_texture = 0;
}

void GraphicsContextGL::unbindVertexArray()
{
    glBindVertexArray(0);
    last_bound_unit_vao = 0;
}

void GraphicsContextGL::unbindShader()
{
    glUseProgram(0);
    last_bound_unit_shader = 0;
}

void GraphicsContextGL::unbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    last_bound_unit_fbo = 0;
}

void GraphicsContextGL::unbindBuffer(BUFFER_TYPE type)
{
    uint32 type_gl = convert_buffer_type_gl(type);
    glBindBuffer(type_gl, 0);
}


void GraphicsContextGL::setBool(const uint32 loc, bool value)
{
    glUniform1i(loc, (int)value);
}

void GraphicsContextGL::setInt(const uint32 loc, int32 value)
{
    glUniform1i(loc, value);
}

void GraphicsContextGL::setFloat(const uint32 loc, real32 value)
{
    glUniform1f(loc, value);
}

void GraphicsContextGL::setVec2(const uint32 loc, const Vec2& value)
{
    glUniform2fv(loc, 1, value.data);
}

void GraphicsContextGL::setVec2(const uint32 loc, real32 x, real32 y)
{
    glUniform2f(loc, x, y);
}

void GraphicsContextGL::setVec3(const uint32 loc, const Vec3& value)
{
    setVec3(loc, value.x, value.y, value.z);
}

void GraphicsContextGL::setVec3(const uint32 loc, real32 x, real32 y, real32 z)
{
    glUniform3f(loc, x, y, z);
}

void GraphicsContextGL::setVec4(const uint32 loc, const Vec4& value)
{
    setVec4(loc, value.x, value.y, value.z, value.w);
}

void GraphicsContextGL::setVec4(const uint32 loc, real32 x, real32 y, real32 z, real32 w)
{
    glUniform4f(loc, x, y, z, w);
}

void GraphicsContextGL::setMat2(const uint32 loc, const Matrix2x2 &mat)
{
    glUniformMatrix2fv(loc, 1, GL_FALSE, mat.data);
}

void GraphicsContextGL::setMat3(const uint32 loc, const Matrix3x3 &mat)
{
    //int location = glGetUniformLocation(shd->id, name.c_str());
    glUniformMatrix3fv(loc, 1, GL_FALSE, (const real32*)mat.data);
}

void GraphicsContextGL::setMat4(const uint32 loc, const Matrix4x4 &mat)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const real32*)mat.data);
}

int GraphicsContextGL::getBufferLocation(uint32 id, const char *name)
{
    return glGetUniformLocation(id, name);
}

void GraphicsContextGL::setShaderBuffer(const ShaderUniformProperty *prop_type)
{
    switch (prop_type->type)
    {
        case ShaderUniformType::Mat4x4:
        {
            glUniformMatrix4fv(prop_type->location, 1, GL_FALSE, (const real32*)prop_type->value);
        } break;
        case ShaderUniformType::Vec3Uniform:
        {
            glUniform3fv(prop_type->location, 1, (const real32*)(prop_type->value));
        } break;
        case ShaderUniformType::Vec4Uniform:
        {
            glUniform4fv(prop_type->location, 1, (const real32*)(prop_type->value));
        } break;

        case ShaderUniformType::Mat3x3:
        {
            glUniformMatrix3fv(prop_type->location, 1, GL_FALSE, (const real32*)(prop_type->value));
        } break;
        case ShaderUniformType::Float:
        {
            //glUniform1fv(prop_type->location, 1, (GLfloat)(prop_type->value));
        } break;
        case ShaderUniformType::Int:
        {
            //glUniform1iv(prop_type->location, 1, (GLint)(&prop_type->value));
        } break;
        default:
        {
            print_error("Invalid uniform type used to set value");
            assert(false);
        } break;
    };
}

void GraphicsContextGL::startExecution()
{
    clearColor(clear_color_v[0], clear_color_v[1], clear_color_v[2], clear_color_v[3]);
    clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsContextGL::endExecution()
{
    //SwapBuffers(xe_platform::get_dc());
}