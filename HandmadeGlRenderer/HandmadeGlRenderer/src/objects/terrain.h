#pragma once

#ifndef TERRAINH
#define TERRAINH

#include "terrainutils/terrainmesh.h"
#include "../core/rendering/pipeline/materials/bpmaterial.h"
#include "../xenpch.h"


namespace XEngine
{
    namespace Terrain
    {
#define TER_TERRAIN_VX 251
#define TER_TERRAIN_VZ 251
#define TER_TERRAIN_TILE_SIZE 0.5f
#define TER_TERRAIN_NUM_INDEX_BUFFERS 3
#define TER_TERRAIN_MAX_IB_BYTES (((TER_TERRAIN_VX - 1) * (TER_TERRAIN_VZ * 2) + (TER_TERRAIN_VX - 2) + (TER_TERRAIN_VZ - 2)) * sizeof(unsigned) * 2)
#define TER_TERRAIN_MAX_IB_INDICES (TER_TERRAIN_MAX_IB_BYTES / sizeof(unsigned))
#define TERRAIN(w, d) height[(w) * depth + (d)]
        class Terrain
        {
        public:
            Terrain() {};
            ~Terrain() { clear(); }


            void init(int w, int d, float step);
            void clear();
            
            float utilTerrain(int x, int z);

            void generateMesh();
            glm::vec3 calculateNormals(unsigned x, unsigned z);

            void generateHeightFromTexture(Texture2D *tex, float offset, float scale);

            void prepare(glm::mat4 &cam);
            void render(glm::mat4 &cam);
            void finish();

            void bind();
            void unbind();

            float getHeightat(float x, float y);

            inline size_t getOffsetIndices();

            float getWidth();
            float getHeight();

            void setHeight(unsigned w, unsigned d, float h);

        private:
            int width, depth;
            float step;
            float *height;

            unsigned *indices;
            unsigned num_indices;

            unsigned int vao;
            unsigned int vertex_buf;

            unsigned int index_buf[TER_TERRAIN_NUM_INDEX_BUFFERS];
            unsigned int ibuf_idx;
            unsigned int ibuf_used;
            unsigned int ibuf_cur_offset;

            Rendering::BPMaterial* material;
            TerrainMesh *terMesh;

            glm::mat4 prev_mvp;
            bool prev_mvp_valid;
        };


    }

}
#endif // !TERRAINH

