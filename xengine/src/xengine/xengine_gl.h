
#include <glad/glad.h>

struct texture2D
{
    GLuint id;
    int width;
    int height;
};

struct shader
{
    GLuint id;
};

struct vertex_buffer
{
    GLuint id;
    real32 *data;
};

struct index_buffer
{
    GLuint id;
    uint32 *data;
};

struct vertex_array
{
    GLuint id;
    vertex_buffer *buffer_arr;
    index_buffer *index_buffer;
};
