
#ifndef ASSET_MANAGER_CPP
#define ASSET_MANAGER_CPP

std::string concatPath(const char *path, const char *dir)
{
    std::string result(path);

    if (dir)
    {
        std::string dirname(dir);
        result = dirname + '/' + result;
    }

    return result;
}

StaticModelAsset* AbstractAssetFactory::loadStaticModel(const char *name)
{
    StaticModelAsset *result = (StaticModelAsset*)allocateMemory(&asset_arena, sizeof(StaticModelAsset));
    


    return alloc_mem(result) StaticModelAsset();
}

AnimModelAsset* AbstractAssetFactory::loadAnimModel(const char *name)
{
    AnimModelAsset *result = (AnimModelAsset*)allocateMemory(&asset_arena, sizeof(AnimModelAsset));

    return alloc_mem(result) AnimModelAsset();
}

AudioClip* AbstractAssetFactory::loadAudioClip(const char *name)
{
    AudioClip *result = (AudioClip*)allocateMemory(&asset_arena, sizeof(AudioClip));

    return  alloc_mem(result) AudioClip();
}

TextureAsset* AbstractAssetFactory::loadTexture(const char *name)
{
    TextureAsset *result = (TextureAsset*)allocateMemory(&asset_arena, sizeof(TextureAsset));
    
    result->texture_info = xe_core::loadTextureFromDisc(name, result->width, result->height, result->channels, 0, true);
    result->setID(name);
    result->setAssetType(AssetType::AssetTexture2D);

    return alloc_mem(result) TextureAsset();
}

Scene* AbstractAssetFactory::loadScene(const char *name)
{
    Scene *result = (Scene*)allocateMemory(&asset_arena, sizeof(Scene));

   
    return alloc_mem(result) Scene();
}

Asset* AbstractAssetFactory::loadAsset(const char *resolved_path, AssetType type)
{
    Asset *result = 0;

    switch (type)
    {
        case AssetType::AssetTexture1D:
        {
             
        } break;
        case AssetType::AssetTexture2D:
        {
            result = loadTexture(resolved_path);
        } break;
        case AssetType::AssetTexture3D:
        {

        } break;
        case AssetType::AssetModel:
        {

        } break;
        case AssetType::AssetAnimModel:
        {
        
        } break;
        case AssetType::AssetAudio:
        {

        } break;
        case AssetType::AssetScene:
        {
            result = loadScene(resolved_path);
        } break;
        default:
        {

        } break;
    }

    if (result)
    {
        result->setAssetType(type);
    }
    
    return result;
}


TextureAsset* AssetManager::getTextureAsset(const char *path)
{
    TextureAsset *data = 0;
    
    auto it = textures.find(path);
    if (it != textures.end())
    {
        data = it->second;
    }
    else
    {
        data = AbstractAssetFactory::loadTexture(path);
        textures.insert(std::make_pair(path, data));
    }

    return data;
}

StaticModelAsset* AssetManager::getStaticModelAsset(const char *path)
{
    StaticModelAsset *data = 0;
    
    auto it = static_models.find(path);
    if (it != static_models.end())
    {
        data = it->second;
    }
    else
    {
        data = AbstractAssetFactory::loadStaticModel(path);
        static_models.insert(std::make_pair(path, data));
    }

    return data;
}

AnimModelAsset* AssetManager::getAnimModelAsset(const char *path)
{
    AnimModelAsset *data = 0;

    return data;
}

Model *ResourceManager::getModel(const char *path, bool32 calculate_tb)
{
    Model *result = 0;

    auto it = static_models.find(path);
    if (it != static_models.end())
    {
        result = it->second;
    }
    else
    {
        result = loadStaticModelFromFile(path, calculate_tb);
        static_models.insert(std::make_pair(path, result));
    }

    return result;
}

AnimModel *ResourceManager::getAnimModel(const char *path, bool32 calculate_tb)
{
    AnimModel *result = 0;

    auto it = anim_models.find(path);
    if (it != anim_models.end())
    {
        result = it->second;
    }
    else
    {
        result = loadAnimModelFromFile(path, calculate_tb);
        anim_models.insert(std::make_pair(path, result));
    }

    return result;
}

ModelNode* ResourceManager::parseNode(Model *model, aiNode *ai_node)
{
    ModelNode* cur_node = new ModelNode();
    cur_node->name = ai_node->mName.C_Str();

    for (uint16 i = 0; i < ai_node->mNumMeshes; i++)
    {
        aiMesh* mesh = m_scene->mMeshes[ai_node->mMeshes[i]];
        cur_node->addMesh(parseMesh(model, mesh, m_scene));
    }

    for (uint16 i = 0; i < ai_node->mNumChildren; i++)
    {
        cur_node->addChild(parseNode(model, ai_node->mChildren[i]));
    }

    return cur_node;
}

Model* ResourceManager::parseStaticModel(const std::string &path)
{
    Model *node = new Model();

    if (calculate_tspace)
    {
        node->vertex_type = new PositionNormalTBUV();
    }
    else
    {
        node->vertex_type = new PositionNormalUV();
    }

    node->asset_data.parent_dir = path.substr(0, path.find_last_of('/'));
    node->root = parseNode(node, m_scene->mRootNode);

    //Log::info("Static model " + model->root->name + " loaded!");

    return node;
}

Model* ResourceManager::loadStaticModelFromFile(const std::string &path, bool32 calculate_tb)
{
    // @FLip UV ???
    uint32 flags = aiProcess_Triangulate;

    if (calculate_tb)
    {
        flags |= aiProcess_CalcTangentSpace;
    }

    m_scene = m_importer.ReadFile(path, flags);
    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
    {
        print_error(m_importer.GetErrorString());
        return nullptr;
    }

    calculate_tspace = calculate_tb;

    Model *result = parseStaticModel(path);

    if (result)
    {
        print_info("Model " + result->root->name + " was loaded!");
    }
    else
    {
        print_error("Loading of model " + result->root->name + " was failed!");
    }

    return result;
}

AnimModel* ResourceManager::loadAnimModelFromFile(const std::string &path, bool32 calculate_tb)
{
    AnimModel *result = new AnimModel();
    
    /*static const uint32_t import_flags =
        aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
        aiProcess_Triangulate |             // Make sure we're triangles
        aiProcess_SortByPType |             // Split meshes by primitive type
        aiProcess_GenNormals |              // Make sure we have legit normals
        aiProcess_GenUVCoords |             // Convert UVs if required 
        aiProcess_OptimizeMeshes |          // Batch draws where possible
        aiProcess_ValidateDataStructure;    // Validation

    scene = m_importer.ReadFile(path.c_str(), import_flags);
    bool32 isAnimationsLoaded = m_scene->mAnimations != nullptr;

    global_inverse_transform = inverseMat(fromAiToGlm(m_scene->mRootNode->mTransformation));

    uint32 vertexCount = 0;
    uint32 indexCount = 0;

    anim_meshes.reserve(m_scene->mNumMeshes);

    for (size_t i = 0; i < m_scene->mNumMeshes; ++i)
    {
        aiMesh *mesh = m_scene->mMeshes[i];

        AnimNode anim_mesh = {};
        anim_mesh.start_vertex = vertexCount;
        anim_mesh.start_index = indexCount;
        anim_mesh.index_count = mesh->mNumFaces * 3;
        anim_mesh.material_index = mesh->mMaterialIndex;
        anim_meshes.push_back(anim_mesh);

        vertexCount += mesh->mNumVertices;
        indexCount += anim_mesh.index_count;

        for (size_t i = 0; i < mesh->mNumVertices; i++)
        {
            PositionNormalUVBW vertex;
            vertex.pos = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

            if (mesh->HasTangentsAndBitangents())
            {
                vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                vertex.bitangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
            }

            if (mesh->HasTextureCoords(0))
                vertex.uv = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };

            anim_vertices.push_back(vertex);
        }

        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (uint32 j = 0; j < face.mNumIndices; j++)
                anim_indices.push_back(face.mIndices[j]);
        }

        updateNodeTransform(m_scene->mRootNode);

        for (size_t m = 0; m < m_scene->mNumMeshes; m++)
        {
            aiMesh* mesh = m_scene->mMeshes[m];
            AnimNode& node = anim_meshes[m];

            for (size_t i = 0; i < mesh->mNumBones; i++)
            {
                aiBone* bone_loader = mesh->mBones[i];
                std::string boneName(bone_loader->mName.data);
                int boneIndex = 0;

                if (bones_map.find(boneName) == bones_map.end())
                {
                    boneIndex = bones_count;
                    bones_count++;
                    Bone bi;
                    bones_info.push_back(bi);
                    bones_info[boneIndex].offset = fromAiToGlm(bone_loader->mOffsetMatrix);
                    bones_map[boneName] = boneIndex;
                }
                else
                {
                    boneIndex = bones_map[boneName];
                }

                for (size_t j = 0; j < bone_loader->mNumWeights; j++)
                {
                    int vertexID = node.start_vertex + bone_loader->mWeights[j].mVertexId;
                    float weight = bone_loader->mWeights[j].mWeight;
                    anim_vertices[vertexID].addBone(boneIndex, weight);
                }
            }
        }
    }*/

    return result;
}

#endif
