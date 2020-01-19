#include "model_loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <runtime/geometry/model.h>
#include <runtime/core/rendering/api/base/texture2D.h>

namespace XEngine
{
    std::vector<Assets::TextureWrapper> load_textures_from_material(Assets::Model *model, aiMaterial *material, aiTextureType type, std::string texture_type)
    {
        using namespace Assets;
        using namespace Rendering;

        std::vector<TextureWrapper> textures;
        for (uint32 i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->GetTexture(type, i, &str);
            
            bool skip = false;
            for (uint16 j = 0; j < model->model_textures.size(); j++)
            {
                if (std::strcmp(model->model_textures[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(model->model_textures[j]);
                    skip = true; 
                    break;
                }
            }

            if (!skip)
            {   
                TextureWrapper texture;
                texture.texture = Texture2D::create(str.C_Str(), model->parent_dir.c_str());
                texture.type = texture_type;
                texture.path = str.C_Str();
                textures.push_back(texture);
                model->model_textures.push_back(texture);  
            }
        }
        return textures;
    }

    void parse_materials(Assets::Model *model, Assets::Mesh *mesh, aiMesh* ai_mesh, const aiScene *scene)
    {
        using namespace Assets;
        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
        
        std::vector<TextureWrapper> diffuseMaps = load_textures_from_material(model, material, aiTextureType_DIFFUSE, "tex_diff");             
        for(uint16 i = 0; i < diffuseMaps.size(); i++)
            mesh->mesh_textures.push_back(diffuseMaps[i]);

        std::vector<TextureWrapper> specularMaps = load_textures_from_material(model, material, aiTextureType_SPECULAR, "tex_spec");
        for (uint16 i = 0; i < specularMaps.size(); i++)
            mesh->mesh_textures.push_back(specularMaps[i]);

        std::vector<TextureWrapper> normalMaps = load_textures_from_material(model, material, aiTextureType_HEIGHT, "tex_norm");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);
        
        std::vector<TextureWrapper> heightMaps = load_textures_from_material(model, material, aiTextureType_AMBIENT, "tex_height");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);
    }

    void parse_vert(Assets::Mesh* mesh, aiMesh *aimesh)
    {
        using namespace Assets;

        std::vector<StaticVertex> vertices;
        std::vector<uint32> indices;
        std::vector<TextureWrapper> textures;

        for (uint32 i = 0; i < aimesh->mNumVertices; i++)
        {
            StaticVertex vertex;
            vec3f vector;

            if (aimesh->HasPositions())
            {
                vector.x = aimesh->mVertices[i].x;
                vector.y = aimesh->mVertices[i].y;
                vector.z = aimesh->mVertices[i].z;
                vertex.pos = vector;
            }

            if (aimesh->HasNormals())
            {
                vector.x = aimesh->mNormals[i].x;
                vector.y = aimesh->mNormals[i].y;
                vector.z = aimesh->mNormals[i].z;
                vertex.normal = vector;
            }

            if (aimesh->HasTextureCoords(0))
            {
                vec2f uv;

                uv.x = aimesh->mTextureCoords[0][i].x;
                uv.y = aimesh->mTextureCoords[0][i].y;

                vertex.uv = uv;
            }
            else
                vertex.uv = vec2f(0.0f, 0.0f);

            // @Note : not using tbn right now
            /*if (aimesh->HasTangentsAndBitangents())
            {
                vector.x = aimesh->mTangents[i].x;
                vector.y = aimesh->mTangents[i].y;
                vector.z = aimesh->mTangents[i].z;
                //vertex.tangent = vector;

                vector.x = aimesh->mBitangents[i].x;
                vector.y = aimesh->mBitangents[i].y;
                vector.z = aimesh->mBitangents[i].z;
                //vertex.bitangent = vector;
            }*/

            mesh->add_vertex(vertex);
        }
    }

    void parse_faces(Assets::Mesh* mesh, aiMesh *aimesh)
    {
        for (uint32 i = 0; i < aimesh->mNumFaces; i++)
        {
            aiFace face = aimesh->mFaces[i];
            for (uint32 j = 0; j < face.mNumIndices; j++)
                mesh->add_index(face.mIndices[j]);
        }
    }

    Assets::Mesh* parse_mesh(Assets::Model *model, aiMesh* ai_mesh, const aiScene *scene)
    {
        using namespace XEngine::Assets;

        Mesh* mesh = new Mesh();
        parse_vert(mesh, ai_mesh);
        parse_faces(mesh, ai_mesh);
        parse_materials(model, mesh, ai_mesh, scene);
        mesh->setup_mesh();

        return mesh;
    }

    Assets::Node* parse_node(Assets::Model* model, aiNode* ai_node, const aiScene *scene)
    {
        using namespace Assets;

        Node* cur_node = new Node();
        cur_node->name = ai_node->mName.C_Str();

        for (uint16 i = 0; i < ai_node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[ai_node->mMeshes[i]];
            cur_node->add_mesh(parse_mesh(model, mesh, scene));
        }

        for (uint16 i = 0; i < ai_node->mNumChildren; i++)
        {
            cur_node->add_child(parse_node(model, ai_node->mChildren[i], scene));
        }

        return cur_node;
    }
    
    Assets::Model* parse_static_model(const aiScene* scene, const std::string &path)
    {
        Assets::Model *model = new Assets::Model();

        model->parent_dir = path.substr(0, path.find_last_of('/'));
        model->root = parse_node(model, scene->mRootNode, scene);

        Log::info("Static model " + model->root->name + " loaded!");
        
        return model;
    }

    Assets::AnimatedModel *parse_anim_model(const aiScene* scene)
    {
        Assets::AnimatedModel* anim_model = new Assets::AnimatedModel();

        if (scene->HasAnimations())
        {
            
        }

        Log::info("Animated model " + anim_model->root->name + " loaded!");

        return anim_model;
    }

    Assets::Model* ModelLoader::load_model_from_file(const std::string const & path)
    {
        using namespace XEngine::Assets;

        Assimp::Importer importer;
        // @FLip UV ???
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::error(importer.GetErrorString());
            return nullptr;
        }

        Assets::Model *result = parse_static_model(scene, path);
        
        return result;
    }

    Assets::AnimatedModel * ModelLoader::load_anim_model_from_file(const std::string const & path)
    {
        using namespace XEngine::Assets;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::error(importer.GetErrorString());
            return nullptr;
        }

        Assets::AnimatedModel*result = parse_anim_model(scene);

        return result;
    }
};
