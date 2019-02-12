#pragma once

#ifndef MODEL
#define MODEL

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
#include <string>

#include "types.h"
#include "shader.h"


struct VertexX
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Texture
{
    uint16 id;
    std::string name;
    char* type;
};

struct Mesh
{
    std::vector<VertexX> vertices;
    std::vector<uint32> indices;
    std::vector<Texture> textures;
    uint32 VAO, VBO, EBO;
};

//TODO: write own substr
struct Model
{
    std::vector<Mesh> meshs;
    std::vector<Texture> texturesl;
    std::string dir;
    std::string filename;

};


void setupmeshopengl(Mesh *mesh);
void loadModelopengl(Model *model);
void processNode(aiNode *node, const aiScene *s, Model *model);
Mesh processMesh(Model* model, aiMesh *mesh, const aiScene* scene);
Mesh setupMesh(std::vector<VertexX> vert, std::vector<uint32> ind, std::vector<Texture> text);
std::vector<Texture> loadTextureVec(Model *model, aiMaterial *mat, aiTextureType type, char* name);
uint32 readtexturefromfile(const char* path, std::string &namedir);
void drawMesh(Mesh* mesh, Shader *shader); 
void drawMeshFrom(Model *model, Shader *shader);
#endif