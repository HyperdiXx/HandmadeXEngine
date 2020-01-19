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
    namespace Rendering
    {
        class Texture2D;
        class VertexBuffer;
        class VertexArray;
        class IndexBuffer;
    }

    namespace Assets
    {       
        class Mesh
        {
        public:
            Mesh() {};

            Mesh(std::vector<StaticVertex> vert, std::vector<uint32> ind, std::vector<TextureWrapper> text)
                : vertices(vert), indices(ind), mesh_textures(text)
            {
                setup_mesh();
            };       

            void add_vertex(StaticVertex vertex);
            void add_index(uint32 ind);
            
            inline uint32 get_vao() { return VAO; }
            inline uint32 get_vbo() { return VBO; }
            inline uint32 get_ebo() { return EBO; }
        public:
            std::vector<StaticVertex> vertices;
            std::vector<uint32> indices;
            std::vector<TextureWrapper> mesh_textures;
        public:
            void setup_mesh();
        private:         
            uint32 VAO, VBO, EBO;

        };
       
        struct Node
        {
            void add_child(Node* child);
            void add_mesh(Mesh *mesh);
        
            std::string name;            
            std::vector<Mesh*> meshes;
            std::vector<Node*> children;
        };

        class Model
        {
        public:
           
            
        public:
            Node* root;
            std::string parent_dir;
            std::vector<TextureWrapper> model_textures;
            std::vector<Node*> nodes;
        private:         
            BPMaterialSpec loadMaterial(aiMaterial* mat);
            //uint32 loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma);
            std::vector<TextureWrapper> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        };

        class AnimatedModel
        {
        public:

        };
    }
}
