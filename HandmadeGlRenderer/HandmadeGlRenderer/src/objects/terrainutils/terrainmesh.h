#pragma once

#include <vector>

#define GLM_FORCE_RADIANS 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace XEngine
{
    namespace Terrain
    {
        class TerrainMesh
        {
        public:
            TerrainMesh();
            ~TerrainMesh();
            void init();
            void clear();

            void addVertex(float x, float y, float z, float nx, float ny, float nz);

        public:
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
        };

    }
}
