#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <runtime/types.h>
#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/ecs/component.h>
#include "vertex.h"

namespace XEngine
{
    namespace Assets
    {       
        class Mesh
        {
        public:

            Mesh(std::vector<VertexStruct> vert, std::vector<uint32> ind, std::vector<TextureStruct> text)
                : vertices(vert), indices(ind), textures(text)
            {
                setupMesh();
            };

            //void renderMeshes(Shader *shader);

            std::vector<VertexStruct> vertices;
            std::vector<uint32> indices;
            std::vector<TextureStruct> textures;


        private:
            void setupMesh();

        private:
            uint32 VAO, VBO, EBO;
        };


        class Model : public Component
        {
        public:
            Model() {};

            Model(const std::string& path, bool gamma)
            {
                isGammaCorrected = gamma;
                loadModel(path);
            }

            std::vector<TextureStruct> texturesl;
            std::vector<Mesh> meshes;

            std::string parent_dir;
            bool isGammaCorrected;

        private:
            void loadModel(std::string const &path);
            BPMaterialSpec loadMaterial(aiMaterial* mat);
            void processNode(aiNode *node, const aiScene* scene);
            Mesh processMesh(aiMesh *mesh, const aiScene* scene);
            uint32 loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma);
            std::vector<TextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        };

    }
}
