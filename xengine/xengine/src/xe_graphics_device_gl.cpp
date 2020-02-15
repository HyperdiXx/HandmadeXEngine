
#include "xe_graphics_device_gl.h"

#include "xe_core.h"

#include "runtime/core/utility/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

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

void xe_graphics::graphics_device_gl::draw_array()
{

}

void xe_graphics::graphics_device_gl::draw_indexed(int mode, uint32 count, int type, void * ind)
{
    glDrawElements(mode, count, type, ind);
}

void xe_graphics::graphics_device_gl::bind_texture2d(const texture2D * tetxture)
{
}

void xe_graphics::graphics_device_gl::bind_shader(const shader * shader)
{
}

void xe_graphics::graphics_device_gl::bind_buffer(const vertex_buffer * vb)
{
    if (last_bound_unit != vb->id)    
        glBindBuffer(GL_ARRAY_BUFFER, vb->id);
    
}

void xe_graphics::graphics_device_gl::bind_buffer(const index_buffer * ib)
{
    if (last_bound_unit != ib->id)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);

}

void xe_graphics::graphics_device_gl::bind_vertex_array(const vertex_array * va)
{
    if (last_bound_unit != va->id)
        glBindVertexArray(va->id);
}

void xe_graphics::graphics_device_gl::bind_framebuffer(const framebuffer * fbo)
{
    if (last_bound_unit != fbo->id)
        glBindFramebuffer(GL_FRAMEBUFFER, fbo->id);
}

bool xe_graphics::graphics_device_gl::create_texture2D(const char * path, texture2D *texture)
{
    int channels;
    
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* image = stbi_load(path, &texture->width, &texture->height, &channels, 0);

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, data_format, texture->width, texture->height, 0, data_format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

    return true;
}

bool xe_graphics::graphics_device_gl::create_shader(const char *vertex_code, const char *fragment_code, shader * shd)
{
    xe_core::file file_vs = xe_core::read_whole_file(vertex_code);
    xe_core::file file_fs = xe_core::read_whole_file(fragment_code);
    
    const GLchar *vs_file_code = (GLchar*)file_vs.data;
    const GLchar *fs_file_code = (GLchar*)file_fs.data;

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

        xe_utility::error("Vertex shader error!!!");
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

        xe_utility::error("Fragment shader error!!!");
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLshort), ib->data, GL_STATIC_DRAW);

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

    for (int i = 0; i < buf_layout->elements.size(); i++)
    {
        uint32 offset = 0;
        auto cur_element = buf_layout->elements.at(i);
        cur_element.m_offset = offset;
        offset += cur_element.m_size;
        buf_layout->stride += cur_element.m_size;
    }

    return true;
}

bool xe_graphics::graphics_device_gl::set_vertex_buffer_layout(vertex_buffer *vb, buffer_layout *buf_layout)
{
    

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
        glVertexAttribPointer(va->ibuffer_index, cur_element.element_type_count(), GL_FLOAT, GL_FALSE, buffer_layout.stride, (void*)cur_element.m_offset);
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
    }

    return false;
}

void xe_graphics::graphics_device_gl::start_execution()
{

}

void xe_graphics::graphics_device_gl::end_execution()
{

}
