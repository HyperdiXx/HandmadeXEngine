#include "tile.h"

void XEngine::Terrain::Tile::init(uint32 w, uint32 h, real32 x, real32 y, uint32 tex)
{
    this->width = w;
    this->height = h;

    vertices[0] = glm::vec2(0.0f, 0.0f);
    vertices[1] = glm::vec2(w, 0.0f);
    vertices[2] = glm::vec2(0.0f, h);
    vertices[3] = glm::vec2(0.0f, h);
    vertices[4] = glm::vec2(w, 0.0f);
    vertices[5] = glm::vec2(w, h);

    uv[0] = glm::vec2(0.0f, 0.0f);
    uv[1] = glm::vec2(1.0f, 0.0f);
    uv[2] = glm::vec2(0.0f, 1.0f);
    uv[3] = glm::vec2(0.0f, 1.0f);
    uv[4] = glm::vec2(1.0f, 0.0f);
    uv[5] = glm::vec2(1.0f, 1.0f);
    
    pos = glm::vec3(x, y, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    texture = tex;
}

void XEngine::Terrain::Tile::render()
{




}

void XEngine::Terrain::Tile::bind()
{
    if (vao == 0)
    {
        glGenBuffers(1, &vertex_buf);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &uv_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }
    else
    {
        glBindVertexArray(vao);
    }
}
