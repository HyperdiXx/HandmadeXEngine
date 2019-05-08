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
#define TER_TERRAIN_NUM_INDEX_BUFFERS 3
#define TER_TERRAIN_MAX_IB_BYTES (((TER_TERRAIN_VX - 1) * (TER_TERRAIN_VZ * 2) + (TER_TERRAIN_VX - 2) + (TER_TERRAIN_VZ - 2)) * sizeof(unsigned) * 2)
#define TER_TERRAIN_MAX_IB_INDICES (TER_TERRAIN_MAX_IB_BYTES / sizeof(unsigned))

        class Terrain
        {
        public:


            void init();
            void clear();

            void calculatenormals();


        private:
            int w, h;

            unsigned *indices;
            unsigned num_indices;

            unsigned vao;
            unsigned vertex_buf;

            unsigned index_buf[TER_TERRAIN_NUM_INDEX_BUFFERS];
            unsigned ibuf_idx;
            unsigned ibuf_used;
            unsigned ibuf_cur_offset;

            Rendering::BPMaterial* material;
            TerrainMesh *terMesh;

            glm::mat4 prev_mvp;
            bool prev_mvp_valid;
        };


    }

}
#endif // !TERRAINH

