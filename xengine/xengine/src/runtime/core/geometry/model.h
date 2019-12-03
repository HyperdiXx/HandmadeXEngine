#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <math/vec3f.h>
#include <math/vec2f.h>
#include <runtime/types.h>
#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/ecs/component.h>


namespace XEngine
{
    namespace Assets
    {
        struct VertexStruct
        {
            vec3f pos;
            vec3f normal;
            vec3f tangent;
            vec3f bitangent;
            vec2f uv;
        };

        struct TextureStruct
        {
            uint32 id;
            std::string path;
            std::string type;
        };

        struct BPMaterialSpec
        {
            vec3f dif;
            vec3f spec;
            vec3f ambient;
            float shiness;
        };

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

            uint32 VAO, VBO, EBO;
            void setupMesh();
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

            /*void drawMesh(Shader *shader)
            {
                for (unsigned int i = 0; i < meshes.size(); i++)
                    meshes.at(i).renderMeshes(shader);
            }*/

            std::vector<TextureStruct> texturesl;
            std::vector<Mesh> meshes;

            std::string dir;
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
