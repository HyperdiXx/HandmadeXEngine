#include "terrain.h"

#include "../core/rendering/pipeline/shader.h"

void XEngine::Terrain::Terrain::init(int w, int d, float step)
{
    this->width = w;
    this->depth = d;
    this->step = step;

    this->height = new float(width * depth);
}

void XEngine::Terrain::Terrain::clear()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteVertexArrays(1, &vertex_buf);
    glDeleteVertexArrays(TER_TERRAIN_NUM_INDEX_BUFFERS, &index_buf[0]);

    terMesh->clear();
    delete height;
}

float XEngine::Terrain::Terrain::utilTerrain(int x, int z)
{
    /* Terrain's Z extends towards -Z, but our vertices need positive numbers */
    z = -z;

    /* Find offsets of the coords into a terrain quad */
    float offx = fmodf(x, step);
    float offz = fmodf(z, step);

    /* Compute the plane equation for the triangle we are in */
    glm::vec3 p1, p2, p3;
    float A, B, C, D;
    if (offx + offz <= step) {
        /* First triangle in the quad */
        p1.x = trunc(x / step);
        p1.z = trunc(z / step);
        p1.y = TERRAIN((int)p1.x, (int)p1.z);

        p2.x = trunc(x / step) + 1;
        p2.z = trunc(z / step);
        p2.y = TERRAIN((int)p2.x, (int)p2.z);

        p3.x = trunc(x / step);
        p3.z = trunc(z / step) + 1;
        p3.y = TERRAIN((int)p3.x, (int)p3.z);
    }
    else {
        /* Second triangle in the quad */
        p1.x = trunc(x / step) + 1;
        p1.z = trunc(z / step);
        p1.y = TERRAIN((int)p1.x, (int)p1.z);

        p2.x = trunc(x / step);
        p2.z = trunc(z / step) + 1;
        p2.y = TERRAIN((int)p2.x, (int)p2.z);

        p3.x = trunc(x / step) + 1;
        p3.z = trunc(z / step) + 1;
        p3.y = TERRAIN((int)p3.x, (int)p3.z);
    }

    /* Above we compute X,Z coords as vertex indices so we could use TERRAIN()
     * to compute heights at specific vertices, but to apply the plane equation
     * we need to turn the coordinates into world units
     */
    p1.x *= step;
    p1.z *= step;
    p2.x *= step;
    p2.z *= step;
    p3.x *= step;
    p3.z *= step;

    /* FIXME: we probably want to pre-compute plane equations for each
     * triangle in the terrain rather than recomputing them all the time
     */
    A = (p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z);
    B = (p2.z - p1.z) * (p3.x - p1.x) - (p3.z - p1.z) * (p2.x - p1.x);
    C = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    D = -(A * p1.x + B * p1.y + C * p1.z);

    /* Use the plane equation to find Y given (X,Z) */
    return (-D - C * z - A * x) / B;
}

void XEngine::Terrain::Terrain::generateMesh()
{
    terMesh = new TerrainMesh();
    terMesh->init();
    int vertW = width;
    int vertD = depth;

    for (int x = 0; x < vertW; x++)
    {
        for (int z = 0; z < vertD; z++)
        {
            float ny = TERRAIN(x, z);
            glm::vec3 v0 = glm::vec3(x * step, ny, -z * step);
            glm::vec3 n0 = calculateNormals(x, z);
            terMesh->addVertex(v0.x, v0.y, v0.z, n0.x, n0.y, n0.z);
        }
    }

    uint32 numInd = vertW - 1 * vertD * 2 + vertW - 2 + vertD - 2;

    indices = new unsigned(numInd);

}

glm::vec3 XEngine::Terrain::Terrain::calculateNormals(unsigned x, unsigned z)
{
    if (x == 0)
        x = 1;
    if (z == 0)
        z = 1;
    float hl = TERRAIN(x - 1, z);
    float hr = TERRAIN(x + 1, z);
    float hd = TERRAIN(x, z + 1); /* Terrain expands towards -Z */
    float hu = TERRAIN(x, z - 1);
    glm::vec3 n = glm::vec3(hl - hr, 2.0f, hd - hu);
    n = glm::normalize(n);
    return n;
}

void XEngine::Terrain::Terrain::generateHeightFromTexture(Texture2D * tex, float offset, float scale)
{
    uint8_t *pixels = (uint8_t *)tex->getPixel();
    float scale_x = ((float)tex->getWidth()) / (width - 1);
    float scale_z = ((float)tex->getHeight()) / (depth - 1);

    for (int x = 0; x < width; x++) {
        for (int z = 0; z < depth; z++) {
            int img_x = (int)truncf(x * scale_x);
            int img_y = (int)truncf(z * scale_z);
            float h = pixels[img_y * tex->getWidth() * 4 + img_x * 4];

            /* Normalize height to [-1, 1] */
            h = h / 127.5 - 1.0f;

            /* Apply scale */
            h *= scale;

            /* Apply height offset */
            h += offset;

            setHeight(x, z, h);
        }
    }
}

void XEngine::Terrain::Terrain::prepare(glm::mat4 &cam)
{
    Shader *sh = new Shader("src/shaders/terrain.vs", "src/shaders/terrain.fs");
    
    sh->enableShader();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOWWIDTH / (float)WINDOWHEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = cam;
    glm::mat4 viewInv = glm::inverse(view);
    glm::mat4 model = glm::mat4(1.0);
    
    sh->setMat4("projection", projection);
    sh->setMat4("view", view);
    sh->setMat4("model", model);
    sh->setMat4("viewInv", viewInv);

    bind();
}

void XEngine::Terrain::Terrain::render(glm::mat4 &cam)
{
    prepare(cam);
    glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, (void *)getOffsetIndices());
    finish();
}

void XEngine::Terrain::Terrain::finish()
{
    unbind();
}

void XEngine::Terrain::Terrain::bind()
{
    if (vao == 0) {

        TerrainMesh *mesh = terMesh;

        unsigned vertex_count = mesh->vertices.size();
        //assert(vertex_count == terMesh->normals.size());

        /* Interleave attributes for better performance on some platforms. We
         * need a buffer large enough to store 2 vec3 attributes per vertex
         * (position and normal).
         */
        unsigned vertex_byte_size = 2 * sizeof(glm::vec3);
        unsigned vertex_float_size = vertex_byte_size / sizeof(float);
        unsigned bytes = vertex_count * vertex_byte_size;

        uint8 *vertex_data = new uint8(bytes);

        float *vertex_data_f = (float *)vertex_data;
        for (unsigned i = 0; i < vertex_count; i++) 
        {
            memcpy(&vertex_data_f[vertex_float_size * i], &mesh->vertices[i], sizeof(glm::vec3));
            memcpy(&vertex_data_f[vertex_float_size * i + 3], &mesh->normals[i], sizeof(glm::vec3));
        }

        glGenBuffers(1, &vertex_buf);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
        glBufferData(GL_ARRAY_BUFFER, bytes, vertex_data, GL_STATIC_DRAW);
        delete vertex_data;

        ibuf_idx = 0;
        glGenBuffers(TER_TERRAIN_NUM_INDEX_BUFFERS, index_buf);
        for (unsigned i = 0; i < TER_TERRAIN_NUM_INDEX_BUFFERS; i++)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                TER_TERRAIN_MAX_IB_BYTES,
                i == ibuf_idx ? indices : NULL,
                GL_DYNAMIC_DRAW);
        }
        ibuf_used = num_indices;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf[ibuf_idx]);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,                  // Attribute index
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            vertex_byte_size,   // stride
            (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,                  // Attribute index
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            vertex_byte_size,   // stride
            (void*)sizeof(glm::vec3) // array buffer offset
        );

       /* ter_dbg(LOG_VBO,
            "TERRAIN: VBO: INFO: Uploaded %u bytes (%u KB) "
            "for %u vertices (%u bytes/vertex)\n",
            bytes, bytes / 1024, vertex_count, vertex_byte_size);*/

        unsigned index_bytes = TER_TERRAIN_MAX_IB_BYTES;
        unsigned num_indices = TER_TERRAIN_MAX_IB_BYTES / sizeof(int);
        /*ter_dbg(LOG_VBO,
            "TERRAIN: VBO: INFO: Uploaded %u bytes (%u KB) "
            "for %u indices (%u bytes/index)\n",
            index_bytes, index_bytes / 1024, num_indices, sizeof(int));*/
    }
    else 
    {
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        /* Always bind the current index buffer explicitly, it seems as if binding
         * the VAO doesn't reliably bind the first index buffer when ibuf_idx = 0.
         * Otherwise we should  only need to bind if ibuf_idx > 0, but this does not
         * work. Maybe intel drivers are not storing the index buffer binding in
         * the VAO state?
         */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf[ibuf_idx]);
    }
}

void XEngine::Terrain::Terrain::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

float XEngine::Terrain::Terrain::getHeightat(float x, float y)
{
    return 0.0f;
}

inline size_t XEngine::Terrain::Terrain::getOffsetIndices()
{
    return ibuf_used - num_indices * sizeof(unsigned int);
}

float XEngine::Terrain::Terrain::getWidth()
{
    return step * (width - 1);
}

float XEngine::Terrain::Terrain::getHeight()
{
    return step * (depth - 1);
}

void XEngine::Terrain::Terrain::setHeight(unsigned w, unsigned d, float h)
{
    TERRAIN(w, d) = h;
}
