#pragma once

#ifndef TERRAINH
#define TERRAINH

#include <vector>

#define GLM_FORCE_RADIANS 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class TerrainMesh
{
public:
    TerrainMesh()
    {
        pos = {};
        normals = {};
    }
    ~TerrainMesh()
    {

    }

    void addVertex(glm::vec3 posa, glm::vec3 normala);

    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> normals;
};

class Terrain
{
public:

    Terrain(unsigned width, unsigned depth, float step)
    {
        terMesh = (TerrainMesh*)malloc(sizeof(TerrainMesh));
    }

    ~Terrain()
    {
        free(terMesh);
    }

    int w, h;


    void calculatenormals();

    TerrainMesh * terMesh;
};


#endif // !TERRAINH

