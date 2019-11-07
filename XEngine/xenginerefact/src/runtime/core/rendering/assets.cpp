//#include "assets.h"
//#include "types.h"
//#include "../xenpch.h"
//#include "../tiny_obj_loader.h"
//
//
//
//void Assets::loadObj(const char* filename)
//{
//    tinyobj::attrib_t attrib;
//    std::vector<tinyobj::shape_t> shapes;
//    std::vector<tinyobj::material_t> materials;
//    std::string warn, err;
//
//    std::string name = filename;
//    std::string path = name.substr(0, name.find_last_of("/") + 1);
//
//    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) 
//    {
//        std::cout << "Error while loading mesh\n";
//        throw std::runtime_error(warn + err);
//    }
//
//    //Mesh mesh;
//    //Mat mat;
//
//    //mesh.alloc();
//    //mat.alloc();
//
//    //child->addComponent<MeshFilter>()->mesh = mesh;
//    //child->addComponent<Renderer>()->material = mat.get();
//
//
//    for (uint32 i = 0; i < shapes.size(); i++)
//    {
//     /*   ref_ptr<Mesh> mesh;
//        ref_ptr<mat::Std::Instance> mat;
//
//        mesh.alloc();
//        mat.alloc();
//
//        child->addComponent<MeshFilter>()->mesh = mesh;
//        child->addComponent<Renderer>()->material = mat.get();*/
//
//        std::vector<glm::vec3> vertices;
//        std::vector<glm::vec3> normals;
//        std::vector<glm::vec2> uv;
//        std::vector<uint32> indices;
//
//        for (size_t j = 0; j < shapes[i].mesh.indices.size(); ++j)
//        {
//            indices.push_back(shapes[i].mesh.indices[j]);
//        }
//
//        
//
//        for (uint32 j = 0; j < shapes[i].mesh.indices.size(); ++j)
//        {
//            indices.push_back(shapes[i].mesh.indices[j]);
//        }
//
//        for (uint32 j = 0; j < shapes[i].mesh.positions.size(); j += 3)
//        {
//            vertices.push_back(glm::vec3(shapes[i].mesh.positions[j], shapes[i].mesh.positions[j + 1], shapes[i].mesh.positions[j + 2]));
//        }
//
//        for (uint32 j = 0; j < shapes[i].mesh.normals.size(); j += 3)
//        {
//            normals.push_back(glm::vec3(shapes[i].mesh.normals[j], shapes[i].mesh.normals[j + 1], shapes[i].mesh.normals[j + 2]));
//        }
//
//        for (uint32 j = 0; j < shapes[i].mesh.texcoords.size(); j += 2)
//        {
//            uv.push_back(glm::vec2(shapes[i].mesh.texcoords[j], 1.0f - shapes[i].mesh.texcoords[j + 1]));
//        }
//
//        mesh->set_indices(indices);
//        mesh->set_vertices(vertices);
//        mesh->set_normals(normals);
//        mesh->set_uv(uv);
//    }
//
//    m_shapes.clear();
//    m_materials.clear();
//
//    return obj;
//}
//
//
