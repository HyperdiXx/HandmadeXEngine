#include "batchrenderer.h"


namespace XEngine
{
    namespace Rendering
    {
        
        void BatchRenderer2d::init()
        {
            glGenVertexArrays(1, &mVAO);
            glGenBuffers(1, &mVBO);
            glBindVertexArray(mVAO);
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferData(GL_ARRAY_BUFFER, RENDER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, (const GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, (const GLvoid*)(3 * GL_FLOAT));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}