
#include "xe_graphics_device_gl.h"

#include "xe_core.h"

#include "runtime/core/utility/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#define MAX_COLOR_ATT 4

using namespace xe_graphics;

xe_graphics::graphics_device_gl::graphics_device_gl(HWND window_handle, bool fullscreen)
{
    this->fullscreen = fullscreen;

    RECT rect = RECT();
    GetClientRect(window_handle, &rect);
    this->screen_width = rect.right - rect.left;
    this->screen_height = rect.bottom - rect.top;

    HDC dc = GetDC(window_handle);

    PIXELFORMATDESCRIPTOR pixel_format_descriptor = {};
    pixel_format_descriptor.nSize = sizeof(pixel_format_descriptor);
    pixel_format_descriptor.nVersion = 1;
    pixel_format_descriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixel_format_descriptor.cColorBits = 32;
    pixel_format_descriptor.cAlphaBits = 8;
    pixel_format_descriptor.iLayerType = PFD_MAIN_PLANE;

    int pixel_format_index = ChoosePixelFormat(dc, &pixel_format_descriptor);
    PIXELFORMATDESCRIPTOR sug_pixel_format;
    DescribePixelFormat(dc, pixel_format_index, sizeof(sug_pixel_format), &sug_pixel_format);
    SetPixelFormat(dc, pixel_format_index, &sug_pixel_format);

    HGLRC gl_render_context = wglCreateContext(dc);
    if (!wglMakeCurrent(dc, gl_render_context))
    {
        xe_utility::error("Cannot create OpenGL context!!!");
    }

    ReleaseDC(window_handle, dc);
}

xe_graphics::graphics_device_gl::~graphics_device_gl()
{

}

void xe_graphics::graphics_device_gl::clear(int flags)
{
    glClear(flags);
}

void xe_graphics::graphics_device_gl::clear_color(real32 r, real32 g, real32 b, real32 a)
{
    glClearColor(r, g, b, a);
}

void xe_graphics::graphics_device_gl::set_viewport(int32 x, int32 y, int32 width, int32 height)
{
    glViewport(x, y, width, height);
}

void xe_graphics::graphics_device_gl::enable(int type)
{
    glEnable(type);
}

void xe_graphics::graphics_device_gl::disable(int type)
{
    glDisable(type);
}

void xe_graphics::graphics_device_gl::draw_array(int mode, uint32 first, uint32 count)
{
    glDrawArrays(mode, first, count);
}

void xe_graphics::graphics_device_gl::draw_indexed(int mode, uint32 count, int type, void *ind)
{
    glDrawElements(mode, count, type, ind);
}

void xe_graphics::graphics_device_gl::activate_bind_texture2d(const texture2D * texture)
{
    //if (last_bound_unit_texture != texture->id)
    //{
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        last_bound_unit_texture = texture->id;
    //}
}

void xe_graphics::graphics_device_gl::activate_texture2d(uint32 index)
{
    //if (last_activated_texture != index)
    //{
        glActiveTexture(GL_TEXTURE0 + index);
        last_activated_texture = index;
    //}
}

void xe_graphics::graphics_device_gl::bind_texture2d(const texture2D *texture)
{
    //if (last_bound_unit_texture != texture->id)
    //{
        glBindTexture(GL_TEXTURE_2D, texture->id);
        last_bound_unit_texture = texture->id;
    //}
}

void xe_graphics::graphics_device_gl::bind_buffer(const vertex_buffer *vb)
{
    //if (last_bound_unit_vbuffer != vb->id)
    //{
        glBindBuffer(GL_ARRAY_BUFFER, vb->id);
        last_bound_unit_vbuffer = vb->id;
    //}        
}

void xe_graphics::graphics_device_gl::bind_buffer(const index_buffer *ib)
{
    //if (last_bound_unit_ibuffer != ib->id)
    //{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
        last_bound_unit_ibuffer = ib->id;
    //}      
}

void xe_graphics::graphics_device_gl::bind_shader(const shader *shader)
{
    glUseProgram(shader->id);
}

void xe_graphics::graphics_device_gl::bind_vertex_array(const vertex_array *va)
{
    //if (last_bound_unit_vao != va->id)
    //s{
        glBindVertexArray(va->id);
        last_bound_unit_vao = va->id;
    //}
}

void xe_graphics::graphics_device_gl::bind_framebuffer(const framebuffer *fbo)
{
    if (last_bound_unit_fbo != fbo->id)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo->id);
        last_bound_unit_fbo = fbo->id;
    }
}

void xe_graphics::graphics_device_gl::bind_for_read(const framebuffer * fbo)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo->id);
}

void xe_graphics::graphics_device_gl::bind_for_write(const framebuffer *fbo)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo->id);
}

void xe_graphics::graphics_device_gl::add_color_texture2D(texture2D *texture, uint32 color_attachment_id, framebuffer *fbo)
{
    if (color_attachment_id > MAX_COLOR_ATT)
        return;

    GLuint type_of_tex = GL_COLOR_ATTACHMENT0 + color_attachment_id;

    fbo->color_textures[color_attachment_id] = texture;
    set_texture2D(type_of_tex, texture);
    fbo->buffers.push_back(type_of_tex);
    glDrawBuffers((GLsizei)fbo->buffers.size(), fbo->buffers.data());
}

void xe_graphics::graphics_device_gl::add_depth_texture2D(texture2D * depth, framebuffer * fbo)
{
}

void xe_graphics::graphics_device_gl::add_depth_texture2D(uint32 w, uint32 h, framebuffer * fbo)
{
}

void xe_graphics::graphics_device_gl::set_texture2D(uint32 type, texture2D *texture)
{
    glFramebufferTexture(GL_FRAMEBUFFER, type, texture->id, 0);
}

void xe_graphics::graphics_device_gl::check_framebuffer()
{
    GLuint error = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if(error != GL_FRAMEBUFFER_COMPLETE)
    {
        // Log::error during framebuffer setup;

        switch (error)
        {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            break;

        }
    }

    
}

void xe_graphics::graphics_device_gl::unbind_texture2d()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void xe_graphics::graphics_device_gl::unbind_vertex_array()
{
    glBindVertexArray(0);
}

void xe_graphics::graphics_device_gl::unbind_shader()
{
    glUseProgram(0);
}

void xe_graphics::graphics_device_gl::set_bool(const std::string & name, bool value, shader *shd)
{
    glUniform1i(glGetUniformLocation(shd->id, name.c_str()), (int)value);
}

void xe_graphics::graphics_device_gl::set_int(const std::string & name, int32 value, shader* shd)
{
    glUniform1i(glGetUniformLocation(shd->id, name.c_str()), value);
}

void xe_graphics::graphics_device_gl::set_float(const std::string & name, real32 value, shader *shd)
{
    glUniform1f(glGetUniformLocation(shd->id, name.c_str()), value);
}

void xe_graphics::graphics_device_gl::set_vec2(const std::string & name, const glm::vec2& value, shader *shd)
{
    glUniform2fv(glGetUniformLocation(shd->id, name.c_str()), 1, &value[0]);
}

void xe_graphics::graphics_device_gl::set_vec2(const std::string & name, real32 x, real32 y, shader *shd)
{
    glUniform2f(glGetUniformLocation(shd->id, name.c_str()), x, y);
}

void xe_graphics::graphics_device_gl::set_vec3(const std::string & name, const glm::vec3& value, shader *shd)
{
    glUniform3fv(glGetUniformLocation(shd->id, name.c_str()), 1, &value[0]);
}

void xe_graphics::graphics_device_gl::set_vec3(const std::string & name, real32 x, real32 y, real32 z, shader *shd)
{
    glUniform3f(glGetUniformLocation(shd->id, name.c_str()), x, y, z);
}

void xe_graphics::graphics_device_gl::set_vec4(const std::string & name, const glm::vec4 & value, shader *shd)
{
    glUniform4fv(glGetUniformLocation(shd->id, name.c_str()), 1, &value[0]);
}

void xe_graphics::graphics_device_gl::set_vec4(const std::string & name, real32 x, real32 y, real32 z, real32 w, shader *shd)
{
    glUniform4f(glGetUniformLocation(shd->id, name.c_str()), x, y, z, w);
}

void xe_graphics::graphics_device_gl::set_mat2(const std::string & name, const glm::mat2 & mat, shader *shd)
{
    glUniformMatrix2fv(glGetUniformLocation(shd->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void xe_graphics::graphics_device_gl::set_mat3(const std::string & name, const glm::mat3& mat, shader *shd)
{
    glUniformMatrix3fv(glGetUniformLocation(shd->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void xe_graphics::graphics_device_gl::set_mat4(const std::string & name, const glm::mat4 & mat, shader *shd)
{
    glUniformMatrix4fv(glGetUniformLocation(shd->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

bool xe_graphics::graphics_device_gl::create_texture2D(const char *path, texture2D *texture)
{
    return create_texture2D(path, nullptr, texture);
}

bool xe_graphics::graphics_device_gl::create_texture2D(const char *path, const char *dir, texture2D *texture)
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


    int channels;
    
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* image = stbi_load(path_res, &texture->desc.width, &texture->desc.height, &channels, 0);

    if (!image)
        return false;

    GLenum internal_format = 0, data_format = 0;
    if (channels == 4)
    {
        internal_format = GL_RGBA8;
        data_format = GL_RGBA;
    }
    else if (channels == 3)
    {
        internal_format = GL_RGB8;
        data_format = GL_RGB;
    }

    glGenTextures(1, (GLuint*)&texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, data_format, texture->desc.width, texture->desc.height, 0, data_format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

    return true;
}

bool xe_graphics::graphics_device_gl::create_shader(const char *vertex_code, const char *fragment_code, shader *shd)
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

        xe_utility::error("Vertex shader");
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

        xe_utility::error("Fragment shader");
        xe_utility::error(buffer);

        delete[] buffer;
        
        return false;
    }

    shd->id = glCreateProgram();
    glAttachShader(shd->id, vertex);
    glAttachShader(shd->id, fragment);
    glLinkProgram(shd->id);
    glValidateProgram(shd->id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

bool xe_graphics::graphics_device_gl::create_framebuffer(framebuffer *fbo)
{
    glGenFramebuffers(1, (GLuint*)fbo->id);

    return false;
}


bool xe_graphics::graphics_device_gl::create_vertex_buffer(real32 *vertices, uint32 size, vertex_buffer *vb)
{
    vb->data = vertices;

    glGenBuffers(1, (GLuint*)&vb->id);
    glBindBuffer(GL_ARRAY_BUFFER, vb->id);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vb->data, GL_STATIC_DRAW);

    if (vb->data)
        return true;

    return false;
}

bool xe_graphics::graphics_device_gl::create_index_buffer(uint32 *indices, uint32 size, index_buffer *ib)
{
    ib->data = indices;

    glGenBuffers(1, (GLuint*)&ib->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), ib->data, GL_STATIC_DRAW);

    if (ib->data)
        return true;

    return false;
}

bool xe_graphics::graphics_device_gl::create_vertex_array(vertex_array *va)
{
    glGenVertexArrays(1, (GLuint*)&va->id);
    
    return true;
}

bool xe_graphics::graphics_device_gl::create_buffer_layout(std::initializer_list<buffer_element>& element, buffer_layout *buf_layout)
{  
    buf_layout->elements = element;

    uint32 offset = 0;
    buf_layout->stride = 0;

    for (int i = 0; i < buf_layout->elements.size(); i++)
    {
        auto element = buf_layout->elements.at(i);
        element.offset = offset;
        offset += element.size;
        buf_layout->stride += element.size;
    }

    return true;
}

bool xe_graphics::graphics_device_gl::set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout)
{
    vb->layout = *buf_layout;

    return true;
}

bool xe_graphics::graphics_device_gl::add_vertex_buffer(vertex_array *va, vertex_buffer *vb)
{
    glBindVertexArray(va->id);
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

bool xe_graphics::graphics_device_gl::set_index_buffer(vertex_array *va, index_buffer *ib)
{
    // assert 
    if (ib != nullptr)
    {
        glBindVertexArray(va->id);
        bind_buffer(ib);
        va->ib = ib;
        return true;
    }

    return false;
}

void xe_graphics::graphics_device_gl::destroy_texture2D(texture2D * tex)
{
    glDeleteTextures(1, (GLuint*)&tex->id);
}

void xe_graphics::graphics_device_gl::destroy_framebuffer(framebuffer * fbo)
{
    glDeleteFramebuffers(1, (GLuint*)fbo->id);
}

void xe_graphics::graphics_device_gl::start_execution()
{

}

void xe_graphics::graphics_device_gl::end_execution()
{

}
