#include "terrainmesh.h"

void XEngine::Terrain::TerrainMesh::init()
{
    this->vertices = std::vector<glm::vec3>();
    this->normals = std::vector<glm::vec3>();
}

void XEngine::Terrain::TerrainMesh::clear()
{
    this->vertices.clear();
    std::vector<glm::vec3>(this->vertices).swap(this->vertices);
    this->normals.clear();
    std::vector<glm::vec3>(this->normals).swap(this->normals);
}

void XEngine::Terrain::TerrainMesh::addVertex(float x, float y, float z, float nx, float ny, float nz)
{
    glm::vec3 v = glm::vec3(x, y, z);
    glm::vec3 n = glm::vec3(nx, ny, nz);
    this->vertices.push_back(v);
    this->normals.push_back(n);
}
