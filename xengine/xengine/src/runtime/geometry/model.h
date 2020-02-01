#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <types.h>
#include <rendering/api/base/shader.h>
#include <component.h>
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

    class Animation;

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

        struct Bone
        {
            std::string name;
            glm::mat4 transform;
            glm::mat4 offset;
            Bone *parent;
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
            std::vector<TextureWrapper> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        };

        struct AnimNode
        {
            std::string name;
            std::vector<AnimNode*> nodes;
        };

        class AnimatedMesh 
        {
        public:
            AnimatedMesh(std::vector<AnimVertex> vert, std::vector<uint32> ind, std::vector<TextureWrapper> text)
                : vertices(vert), indices(ind), mesh_textures(text)
            {
                setup_anim_mesh();
            }

            void add_weight(uint32 vert_index, uint32 bone_index, GLuint bone_id, GLfloat weight);
            void add_vertex(AnimVertex vertex);
            void add_index(uint32 ind);

            std::vector<std::shared_ptr<Bone>> bones;
            std::vector<AnimVertex> vertices;
            std::vector<uint32> indices;
            std::vector<TextureWrapper> mesh_textures;

        private:
            void setup_anim_mesh();
        private:
            uint32 VAO, VBO, EBO;
        };

        class AnimatedModel
        {
        public:
            AnimNode *root;
            void add_bone(std::shared_ptr<Bone> bone);
            void add_animation(XEngine::Animation *animation);
        private:
            void update_transformations();
        private:
            double tick = 0.0;
            uint32 m_cur_anim = 0;
            std::unordered_map<std::string, size_t> m_anim_map;
            std::vector<std::unique_ptr<Animation>> m_animations;
        };
    }
}
