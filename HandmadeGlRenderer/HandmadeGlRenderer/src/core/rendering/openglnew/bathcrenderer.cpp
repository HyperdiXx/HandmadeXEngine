#include "batchrenderer.h"


namespace XEngine
{
    namespace Rendering
    {
        void BatchRenderer2d::start()
        {
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            mBuf = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void BatchRenderer2d::end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer2d::submit(const Renderable2d * renderObj)
        {
            const glm::vec2& size = renderObj->getCount();
            const glm::vec3& pos = renderObj->getPos();
            const glm::vec4& color = renderObj->getColor();

            mBuf->pos = pos;
            mBuf->color = color;
            mBuf++;

            mBuf->pos = glm::vec3(pos.x, pos.y + size.y, pos.z);
            mBuf->color = color;
            mBuf++;

            mBuf->pos = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
            mBuf->color = color;
            mBuf++;

            mBuf->pos = glm::vec3(pos.x + size.x, pos.y, pos.z);
            mBuf->color = color;
            mBuf++;

            mIndCount += 6;
        }

        void BatchRenderer2d::flush()
        {
            glBindVertexArray(mVAO);
            mIBO->bind();
            glDrawElements(GL_TRIANGLES, mIndCount, GL_UNSIGNED_SHORT, NULL);
            mIBO->unbind();
            glBindVertexArray(0);
        }

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
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, RENDER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GL_FLOAT)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLushort indices[RENDER_INDICES_SIZE];
            float offset = 0;

            for (size_t i = 0; i < RENDER_INDICES_SIZE; i += 6)
            {
                indices[i] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;
                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }

            mIBO = new IndexBuffer(indices, RENDER_INDICES_SIZE);

            glBindVertexArray(0);


        }
    }
}