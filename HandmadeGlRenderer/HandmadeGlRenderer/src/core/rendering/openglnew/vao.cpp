

#include "vao.h"


void addIndexBuffer(std::vector<unsigned int> indices, IndexBuffer & index)
{

}

void addVertexBuffer(VertexAO *ao, std::vector<float> values, int dimension, int row)
{
    bindVAO(ao);


}

void vertexAttribPointers(int n, uint32 ds)
{
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
}

void setAttribPointersFloat()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void createVertexBuffer(GeometryBuffer *geo, std::vector<float> d)
{
    glGenVertexArrays(1, &geo->vao);
    glGenBuffers(1, &geo->vbo);
    glBindVertexArray(geo->vao);
    glBindBuffer(GL_ARRAY_BUFFER, geo->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d.size(), &d[0], GL_STATIC_DRAW);
    setAttribPointersFloat();
    glBindVertexArray(0);
}

void createIndexBuffer()
{

}

void bindVAO(VertexAO *ao)
{
    glBindVertexArray(ao->id);

    for (int i = 0; i < ao->attribs.size(); ++i)
    {
        glEnableVertexAttribArray(ao->attribs[i]);
    }
}

void unbindVAO(VertexAO *ao)
{
    for (int i = 0; i < ao->attribs.size(); i++) {
        glDisableVertexAttribArray(ao->attribs[i]);
    }

    glBindVertexArray(0);
}

void test(int *planeVertices, int* vertices)
{
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
}

void delGeometry(GeometryBuffer* b)
{
    glDeleteVertexArrays(1, &b->vao);
    glDeleteBuffers(1, &b->vbo);
}
