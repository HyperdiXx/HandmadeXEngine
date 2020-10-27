
static bool32 calculate_tspace;

Matrix4x4 fromAiToGlm(const aiMatrix4x4 &ai_mat)
{
    Matrix4x4 res = createMat4x4();

    res.data[0] = ai_mat.a1;
    res.data[1] = ai_mat.b1;
    res.data[2] = ai_mat.c1;
    res.data[3] = ai_mat.d1;

    res.data[0 + 1 * 4] = ai_mat.a2;
    res.data[1 + 1 * 4] = ai_mat.b2;
    res.data[2 + 1 * 4] = ai_mat.c2;
    res.data[3 + 1 * 4] = ai_mat.d2;

    res.data[0 + 2 * 4] = ai_mat.a3;
    res.data[1 + 2 * 4] = ai_mat.b3;
    res.data[2 + 2 * 4] = ai_mat.c3;
    res.data[2 + 2 * 4] = ai_mat.d3;

    res.data[0 + 3 * 4] = ai_mat.a4;
    res.data[1 + 3 * 4] = ai_mat.b4;
    res.data[2 + 3 * 4] = ai_mat.c4;
    res.data[3 + 3 * 4] = ai_mat.d4;

    return res;
}

std::vector<TextureWrapper> loadTexturesFromMaterial(Model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type)
{
    std::vector<TextureWrapper> textures;
    for (uint32 i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);

        bool skip = false;
        for (uint16 j = 0; j < mdl->model_textures.size(); j++)
        {
            if (std::strcmp(mdl->model_textures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(mdl->model_textures[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            TextureWrapper texture;

            GraphicsDevice *device = getGDevice();

            Texture2D* texture_crt = new Texture2D();
            texture_crt->desc.dimension = TEXTURE_2D;

            device->createTexture2D(str.C_Str(), mdl->parent_dir.c_str(), texture_crt);

            texture.texture = texture_crt;
            texture.type = texture_type;
            texture.path = str.C_Str();
            textures.push_back(texture);
            mdl->model_textures.push_back(texture);
        }
    }

    return textures;
}

Vertex *getVertexType(Model *mdl)
{
    return mdl->vertex_type;
}

/*void parse_animations(anim_model * model, const aiScene * ai_scene)
{
    for (uint32 i = 0; i < ai_scene->mNumAnimations; i++)
    {
        aiAnimation *ai_animation = ai_scene->mAnimations[i];

        animation anim = {};

        anim.name = ai_animation->mName.C_Str();
        anim.ticks_per_second = ai_animation->mTicksPerSecond;
        anim.duration = ai_animation->mDuration;

        for (uint32 j = 0; ai_animation->mNumChannels; j++)
        {
            aiNodeAnim* ai_channel = ai_animation->mChannels[j];

            //KeyFrame* frame = new KeyFrame();
            //frame->name = ai_channel->mNodeName.C_Str();

            for (uint32 q = 0; q < ai_channel->mNumPositionKeys; q++)
            {
                aiVectorKey ai_key = ai_channel->mPositionKeys[i];
                //PositionKey p_key = { ai_key.mTime, { ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                //frame->add_position_key(p_key);
            }

            for (uint32 w = 0; w < ai_channel->mNumRotationKeys; w++)
            {
                aiQuatKey ai_key = ai_channel->mRotationKeys[i];
                //RotationKey r_key = { ai_key.mTime,{ ai_key.mValue.w, ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                //frame->add_rotation_key(r_key);
            }

            for (uint32 e = 0; e < ai_channel->mNumScalingKeys; e++)
            {
                aiVectorKey ai_key = ai_channel->mScalingKeys[i];
                //PositionKey s_key = { ai_key.mTime ,{ ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                //frame->add_scale_key(s_key);
            }

            //anim->add_keyframe(frame);
        }

        model->animations.push_back(anim);
    }
}*/

void parseMaterials(Model *m, Mesh *mesh, aiMesh *ai_mesh, const aiScene *scene)
{
    aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];

    std::vector<TextureWrapper> diffuseMaps = loadTexturesFromMaterial(m, material, aiTextureType_DIFFUSE, "tex_diff");
    for (uint16 i = 0; i < diffuseMaps.size(); i++)
        mesh->mesh_textures.push_back(diffuseMaps[i]);

    std::vector<TextureWrapper> specularMaps = loadTexturesFromMaterial(m, material, aiTextureType_SPECULAR, "tex_spec");
    for (uint16 i = 0; i < specularMaps.size(); i++)
        mesh->mesh_textures.push_back(specularMaps[i]);

    std::vector<TextureWrapper> normalMaps = loadTexturesFromMaterial(m, material, aiTextureType_NORMALS, "tex_norm");
    for (uint16 i = 0; i < normalMaps.size(); i++)
        mesh->mesh_textures.push_back(normalMaps[i]);

    std::vector<TextureWrapper> height_tex = loadTexturesFromMaterial(m, material, aiTextureType_HEIGHT, "tex_height");
    for (uint16 i = 0; i < height_tex.size(); i++)
        mesh->mesh_textures.push_back(height_tex[i]);

    // pbr rough
    std::vector<TextureWrapper> roughness_tex = loadTexturesFromMaterial(m, material, aiTextureType_SHININESS, "tex_roughness");
    for (uint16 i = 0; i < roughness_tex.size(); i++)
        mesh->mesh_textures.push_back(roughness_tex[i]);
}

void memCpyvec(aiVector3D &aivec3, Vec3 &vec3)
{
    memcpy(&vec3, &aivec3, sizeof(aivec3));
}

void memCpymatrix(aiMatrix4x4 & aimat, Matrix4x4 &mat4)
{
    memcpy(&mat4, &aimat, sizeof(aimat));
    transposeMat(mat4);
}

void calcWeight(uint32 id, real32 weight, Vec4i &bone_id, Vec4 &wts)
{
    for (uint16 i = 0; i < 4; i++)
    {
        if (wts.data[i] == 0.0f)
        {
            wts.data[i] = weight;
            bone_id.data[i] = id;
            break;
        }
    }
}

void parseFaces(Mesh *mesh, aiMesh *aimesh)
{
    for (uint32 i = 0; i < aimesh->mNumFaces; i++)
    {
        aiFace face = aimesh->mFaces[i];

        for (uint32 j = 0; j < face.mNumIndices; j++)
        {
            mesh->addIndex(face.mIndices[j]);

        }
    }
}

Model *parseStaticModel(const aiScene *scene, const std::string &path)
{
    Model *mode = new Model();

    if (calculate_tspace)
    {
        mode->vertex_type = new PositionNormalTBUV();
    }
    else
    {
        mode->vertex_type = new PositionNormalUV();
    }

    mode->parent_dir = path.substr(0, path.find_last_of('/'));
    mode->root = parseNode(mode, scene->mRootNode, scene);

    //Log::info("Static model " + model->root->name + " loaded!");

    return mode;
}

ModelNode *parseNode(Model *model, aiNode *ai_node, const aiScene *scene)
{
    ModelNode* cur_node = new ModelNode();
    cur_node->name = ai_node->mName.C_Str();

    for (uint16 i = 0; i < ai_node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[ai_node->mMeshes[i]];
        cur_node->addMesh(parseMesh(model, mesh, scene));
    }

    for (uint16 i = 0; i < ai_node->mNumChildren; i++)
    {
        cur_node->addChild(parseNode(model, ai_node->mChildren[i], scene));
    }

    return cur_node;
}

Mesh *parseMesh(Model *model, aiMesh *ai_mesh, const aiScene *scene)
{
    Mesh* mes = new Mesh();

    parseVert(mes, ai_mesh);
    parseFaces(mes, ai_mesh);
    parseMaterials(model, mes, ai_mesh, scene);

    Render::createMesh(mes, model->vertex_type, calculate_tspace);

    return mes;
}

Model* loadModelFromFile(const std::string &path, bool32 calculate_tb)
{
    Assimp::Importer importer;

    // @FLip UV ???
    uint32 flags = aiProcess_Triangulate;

    if (calculate_tb)
    {
        flags |= aiProcess_CalcTangentSpace;
    }

    const aiScene* scene = importer.ReadFile(path, flags);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        print_error(importer.GetErrorString());
        return nullptr;
    }

    calculate_tspace = calculate_tb;

    Model *result = parseStaticModel(scene, path);

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

void parseVert(Mesh *meh, aiMesh *aimesh)
{
    meh->vertices_fl.reserve(aimesh->mNumVertices);

    meh->bounding_box.min = createVec3(FLT_MAX, FLT_MAX, FLT_MAX);
    meh->bounding_box.max = createVec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    Vec3 pos;

    for (uint32 i = 0; i < aimesh->mNumVertices; i++)
    {
        if (aimesh->HasPositions())
        {
            // @SpeedUp: memcpy above
            meh->vertices_fl.push_back(aimesh->mVertices[i].x);
            meh->vertices_fl.push_back(aimesh->mVertices[i].y);
            meh->vertices_fl.push_back(aimesh->mVertices[i].z);

            pos.x = aimesh->mVertices[i].x;
            pos.y = aimesh->mVertices[i].y;
            pos.z = aimesh->mVertices[i].z;

            meh->bounding_box.min.x = min(pos.x, meh->bounding_box.min.x);
            meh->bounding_box.min.y = min(pos.y, meh->bounding_box.min.y);
            meh->bounding_box.min.z = min(pos.z, meh->bounding_box.min.z);

            meh->bounding_box.max.x = max(pos.x, meh->bounding_box.max.x);
            meh->bounding_box.max.y = max(pos.y, meh->bounding_box.max.y);
            meh->bounding_box.max.z = max(pos.z, meh->bounding_box.max.z);
        }

        if (aimesh->HasNormals())
        {
            meh->vertices_fl.push_back(aimesh->mNormals[i].x);
            meh->vertices_fl.push_back(aimesh->mNormals[i].y);
            meh->vertices_fl.push_back(aimesh->mNormals[i].z);
        }

        if (aimesh->HasTangentsAndBitangents())
        {
            meh->vertices_fl.push_back(aimesh->mTangents[i].x);
            meh->vertices_fl.push_back(aimesh->mTangents[i].y);
            meh->vertices_fl.push_back(aimesh->mTangents[i].z);

            meh->vertices_fl.push_back(aimesh->mBitangents[i].x);
            meh->vertices_fl.push_back(aimesh->mBitangents[i].y);
            meh->vertices_fl.push_back(aimesh->mBitangents[i].z);
        }

        if (aimesh->HasTextureCoords(0))
        {
            meh->vertices_fl.push_back(aimesh->mTextureCoords[0][i].x);
            meh->vertices_fl.push_back(aimesh->mTextureCoords[0][i].y);
        }
        else
        {
            meh->vertices_fl.push_back(0.0f);
            meh->vertices_fl.push_back(0.0f);
        }
    }
}

void Mesh::addVertex(PositionNormalUV vertex)
{
    vertices.push_back(vertex);
}

void Mesh::addVertex(PositionNormalTBUV vertex)
{
    vertices_tab.push_back(vertex);
}

void Mesh::addVertex(real32 vertex)
{
    vertices_fl.push_back(vertex);
}

void Mesh::addIndex(uint32 ind)
{
    indices.push_back(ind);
}

void ModelNode::addChild(ModelNode *child)
{
    children.push_back(child);
}

void ModelNode::addMesh(Mesh *msh)
{
    meshes.push_back(msh);
}

AnimModel::AnimModel(const std::string &path)
{
    static const uint32_t import_flags =
        aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
        aiProcess_Triangulate |             // Make sure we're triangles
        aiProcess_SortByPType |             // Split meshes by primitive type
        aiProcess_GenNormals |              // Make sure we have legit normals
        aiProcess_GenUVCoords |             // Convert UVs if required 
        aiProcess_OptimizeMeshes |          // Batch draws where possible
        aiProcess_ValidateDataStructure;    // Validation

    assimp_importer = std::make_unique<Assimp::Importer>();

    scene = assimp_importer->ReadFile(path.c_str(), import_flags);
    bool32 isAnimationsLoaded = scene->mAnimations != nullptr;
    
    global_inverse_transform = inverseMat(fromAiToGlm(scene->mRootNode->mTransformation));

    uint32 vertexCount = 0;
    uint32 indexCount = 0;

    anim_meshes.reserve(scene->mNumMeshes);

    for (size_t i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[i];

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

        updateNodeTransform(scene->mRootNode);

        for (size_t m = 0; m < scene->mNumMeshes; m++)
        {
            aiMesh* mesh = scene->mMeshes[m];
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
    }

    // GPU data creation

    /*GraphicsDevice *device = getGDevice();

    va.buffers.push_back(new VertexBuffer);
    va.ib = new IndexBuffer;

    device->createVertexArray(&va);
    device->bindVertexArray(&va);
    device->createVertexBuffer(anim_vertices.data(), (uint32)anim_vertices.size() * sizeof(PositionNormalUVBW), DRAW_TYPE::STATIC, va.buffers[0]);
    device->createIndexBuffer(anim_indices.data(), (uint32)anim_indices.size(), va.ib);

    using namespace xe_graphics;

    BufferLayout buffer_layout = {};

    std::initializer_list<xe_graphics::BufferElement> init_list =
    {
        { "aPos",         ElementType::Float3, },
        { "aNormal",      ElementType::Float3, },
        { "aTangent",     ElementType::Float3, },
        { "aBitangent",   ElementType::Float3, },
        { "aUV",          ElementType::Float2, },
        { "aBoneIDs",     ElementType::Int4, },
        { "aBoneWeights", ElementType::Float4, }
    };

    device->createBufferLayout(init_list, &buffer_layout);
    device->setVertexBufferLayout(va.buffers[0], &buffer_layout);
    device->addVertexBuffer(&va, va.buffers[0]);
    device->setIndexBuffer(&va, va.ib);*/
}

Model::Model(Model && m)
{
    root = m.root;
    vertex_type = m.vertex_type;
    parent_dir = std::move(m.parent_dir);
    model_textures = std::move(m.model_textures);
    nodes = std::move(m.nodes);
}

Model &Model::operator=(Model && m) noexcept
{
    root = m.root;
    vertex_type = m.vertex_type;
    parent_dir = std::move(m.parent_dir);
    model_textures = std::move(m.model_textures);
    nodes = std::move(m.nodes);
    return *this;
}

AnimModel::AnimModel(AnimModel && m)
{
    activeAnimation = m.activeAnimation;
    global_inverse_transform = std::move(m.global_inverse_transform);

    assimp_importer = std::move(m.assimp_importer);;
    scene = m.scene;

    anim_meshes = std::move(m.anim_meshes);
    bones_map = std::move(m.bones_map);
    bones_info = std::move(m.bones_info);

    anim_vertices = std::move(m.anim_vertices);
    anim_indices = std::move(m.anim_indices);
    bone_transformation = std::move(m.bone_transformation);

    bones_count = m.bones_count;
    animation_speed = m.animation_speed;
    animation_time = m.animation_time;

    va = std::move(m.va);
}

AnimModel &AnimModel::operator=(AnimModel && m) noexcept
{
    activeAnimation = m.activeAnimation;
    global_inverse_transform = std::move(m.global_inverse_transform);

    assimp_importer = std::move(m.assimp_importer);;
    scene = m.scene;

    anim_meshes = std::move(m.anim_meshes);
    bones_map = std::move(m.bones_map);
    bones_info = std::move(m.bones_info);

    anim_vertices = std::move(m.anim_vertices);
    anim_indices = std::move(m.anim_indices);
    bone_transformation = std::move(m.bone_transformation);

    bones_count = m.bones_count;
    animation_speed = m.animation_speed;
    animation_time = m.animation_time;

    va = std::move(m.va);
    return *this;
}

void AnimModel::update(real32 dt)
{
    if (activeAnimation)
    {
        real32 ticks_per_second = (real32)(activeAnimation->mTicksPerSecond != 0 ? activeAnimation->mTicksPerSecond : 25.0f);
        animation_time += dt * ticks_per_second;
        animation_time = fmod(animation_time, (real32)activeAnimation->mDuration);

        transformBones(animation_time);
    }
}

const aiNodeAnim *AnimModel::findAnimNodeByName(const aiAnimation *animation, const std::string &node_name)
{
    for (uint32_t i = 0; i < animation->mNumChannels; i++)
    {
        const aiNodeAnim* nodeAnim = animation->mChannels[i];
        if (std::string(nodeAnim->mNodeName.data) == node_name)
        {
            return nodeAnim;
        }
    }

    return nullptr;
}

uint32_t AnimModel::getTranslationIndexForNode(real32 anim_time, const aiNodeAnim *node_anim)
{
    for (uint32_t i = 0; i < node_anim->mNumPositionKeys - 1; i++)
    {
        if (anim_time < (real32)node_anim->mPositionKeys[i + 1].mTime)
            return i;
    }

    return 0;
}

uint32_t AnimModel::getRotationIndexForNode(real32 anim_time, const aiNodeAnim *node_anim)
{
    for (uint32_t i = 0; i < node_anim->mNumRotationKeys - 1; i++)
    {
        if (anim_time < (real32)node_anim->mRotationKeys[i + 1].mTime)
            return i;
    }

    return 0;
}

uint32_t AnimModel::getScaleIndexForNode(real32 anim_time, const aiNodeAnim *node_anim)
{
    for (uint32_t i = 0; i < node_anim->mNumScalingKeys - 1; i++)
    {
        if (anim_time < (real32)node_anim->mScalingKeys[i + 1].mTime)
            return i;
    }

    return 0;
}

Vec3 AnimModel::getTranslationBetweenFrames(real32 dt, const aiNodeAnim *na)
{
    Vec3 translation = createVec3(0.0f, 0.0f, 0.0f);

    if (na->mNumPositionKeys == 1)
    {
        auto res = na->mPositionKeys[0].mValue;
        translation.x = res.x;
        translation.y = res.y;
        translation.z = res.z;

        return translation;
    }

    uint32 index_frame = getTranslationIndexForNode(dt, na);

    uint32 next_pos_index_frame = index_frame + 1;

    real32 deltaTime = (real32)(na->mPositionKeys[next_pos_index_frame].mTime - na->mPositionKeys[index_frame].mTime);
    real32 factor = (dt - (real32)na->mPositionKeys[index_frame].mTime) / deltaTime;
    if (factor < 0.0f)
        factor = 0.0f;

    aiVectorKey currentFrame = na->mPositionKeys[index_frame];
    aiVectorKey nextFrame = na->mPositionKeys[next_pos_index_frame];

    const aiVector3D& start = currentFrame.mValue;
    const aiVector3D& end = nextFrame.mValue;
    aiVector3D delta = end - start;

    auto aiVec = (start + factor * delta);

    translation.x = aiVec.x;
    translation.y = aiVec.y;
    translation.z = aiVec.z;

    return translation;
}

Quaternion AnimModel::getRotationBetweenFrames(real32 dt, const aiNodeAnim *na)
{
    if (na->mNumRotationKeys == 1)
    {
        auto v = na->mRotationKeys[0].mValue;
        return createQuat(v.w, v.x, v.y, v.z);
    }

    uint32_t RotationIndex = getRotationIndexForNode(dt, na);
    uint32_t NextRotationIndex = (RotationIndex + 1);

    real32 deltaTime = (real32)(na->mRotationKeys[NextRotationIndex].mTime - na->mRotationKeys[RotationIndex].mTime);
    real32 factor = (dt - (real32)na->mRotationKeys[RotationIndex].mTime) / deltaTime;
    if (factor < 0.0f)
        factor = 0.0f;

    const aiQuaternion& StartRotationQ = na->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = na->mRotationKeys[NextRotationIndex].mValue;
    auto q = aiQuaternion();

    aiQuaternion::Interpolate(q, StartRotationQ, EndRotationQ, factor);
    q = q.Normalize();
    return createQuat(q.w, q.x, q.y, q.z);
}

Vec3 AnimModel::getScaleBetweenFrames(float dt, const aiNodeAnim *na)
{
    Vec3 scale = createVec3(0.0f, 0.0f, 0.0f);

    if (na->mNumScalingKeys == 1)
    {
        auto scl = na->mScalingKeys[0].mValue;
        scale.x = scl.x;
        scale.y = scl.y;
        scale.z = scl.z;

        return scale;
    }

    uint32 index = getScaleIndexForNode(dt, na);
    uint32 next_index = (index + 1);

    real32 deltaTime = (real32)(na->mScalingKeys[next_index].mTime - na->mScalingKeys[index].mTime);
    real32 factor = (dt - (real32)na->mScalingKeys[index].mTime) / deltaTime;
    if (factor < 0.0f)
        factor = 0.0f;

    const auto& start = na->mScalingKeys[index].mValue;
    const auto& end = na->mScalingKeys[next_index].mValue;
    auto delta = end - start;
    auto aiVec = start + factor * delta;

    scale.x = aiVec.x;
    scale.y = aiVec.y;
    scale.z = aiVec.z;

    return scale;
}

void AnimModel::readNodeHierarchy(real32 anim_time, const aiNode *pNode, const Matrix4x4 &parentTransform)
{
    std::string current_node_name(pNode->mName.data);
    Matrix4x4 transform_node(fromAiToGlm(pNode->mTransformation));

    const aiNodeAnim* findedNode = findAnimNodeByName(activeAnimation, current_node_name);

    if (findedNode)
    {
        Vec3 translationVec = getTranslationBetweenFrames(anim_time, findedNode);
        
        Matrix4x4 translationMatrix = createMat4x4();
        translateMat(translationMatrix, createVec3(translationVec.x, translationVec.y, translationVec.z));

        Quaternion quaternion = getRotationBetweenFrames(anim_time, findedNode);
        Matrix4x4 rotationMatrix = toMat4(quaternion);

        Vec3 scaleVec = getScaleBetweenFrames(anim_time, findedNode);
       
        Matrix4x4 scaleMatrix = createMat4x4();
        scaleMat(scaleMatrix, createVec3(scaleVec.x, scaleVec.y, scaleVec.z));

        transform_node = translationMatrix * rotationMatrix * scaleMatrix;
    }

    Matrix4x4 globalTransformMatrix = parentTransform * transform_node;

    if (bones_map.find(current_node_name) != bones_map.end())
    {
        uint32 BoneIndex = bones_map[current_node_name];
        bones_info[BoneIndex].transform = global_inverse_transform * globalTransformMatrix * bones_info[BoneIndex].offset;
    }

    for (uint32 i = 0; i < pNode->mNumChildren; i++)
    {
        readNodeHierarchy(anim_time, pNode->mChildren[i], globalTransformMatrix);
    }
}

void AnimModel::transformBones(real32 dt)
{
    Matrix4x4 defaultMat = createMat4x4();
    readNodeHierarchy(dt, scene->mRootNode, defaultMat);
    bone_transformation.resize(bones_count);
    for (uint32 i = 0; i < bones_count; i++)
    {
        bone_transformation[i] = bones_info[i].transform;
    }
}

void AnimModel::updateNodeTransform(aiNode *node, const Matrix4x4 &parent_transform)
{
    Matrix4x4 transform = parent_transform * fromAiToGlm(node->mTransformation);
    
    for (uint32 i = 0; i < node->mNumMeshes; i++)
    {
        uint32 mesh = node->mMeshes[i];
        anim_meshes[mesh].transform = transform;
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++)
    {
        updateNodeTransform(node->mChildren[i], transform);
    }
}