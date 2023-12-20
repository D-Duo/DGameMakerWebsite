#pragma once

#include "EngineGlobals.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Components.h"
#include "Mesh.h"

class FileLoader
{
public:

	static vector<shared_ptr<Mesh>> MeshloadFromFile(const string& path) {
        vector<shared_ptr<Mesh>> mesh_ptrs;

        string filepath = "Assets/Meshes/" + path;
        ifstream file(filepath.c_str());
        if (file.good()) {
            //load meshes           

            const auto scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
            for (size_t m = 0; m < scene->mNumMeshes; ++m) {

                const auto mesh = scene->mMeshes[m];
                const auto faces = mesh->mFaces;

                vec3f* texCoords = (vec3f*)mesh->mTextureCoords[0];
                bool isNull = false;

                if (!mesh->HasTextureCoords(0))
                {
                    isNull = true;
                }

                vector<Mesh::V3T2> vertex_data;
                for (size_t i = 0; i < mesh->mNumVertices; ++i) {
                    Mesh::V3T2  v;

                    if(!isNull)
                        v = { (vec3f&)mesh->mVertices[i], vec2f(texCoords[i].x, texCoords[i].y) };
                    else
                        v = { (vec3f&)mesh->mVertices[i], vec2f(0, 0) };
                    vertex_data.push_back(v);
                }

                vector<unsigned int> index_data;
                for (size_t f = 0; f < mesh->mNumFaces; ++f) {
                    index_data.push_back(faces[f].mIndices[0]);
                    index_data.push_back(faces[f].mIndices[1]);
                    index_data.push_back(faces[f].mIndices[2]);
                }

                auto loadedMesh = make_shared<Mesh>(Mesh::Formats::F_V3T2, vertex_data.data(), vertex_data.size(), index_data.data(), index_data.size());
                loadedMesh->mMaterialIndex = mesh->mMaterialIndex;
                loadedMesh->path = filepath;
                loadedMesh->name = mesh->mName.C_Str();
                mesh_ptrs.push_back(loadedMesh);
            }

            aiReleaseImport(scene);
        }
        else {
            cout << "FILE NOT FOUND :: MESH COMPONENT CONSTRUCTOR" << endl;
        }

        return mesh_ptrs;
    }

    static vector<shared_ptr<Texture2D>> TextureloadFromFile(const string& path) {

        //load textures
        vector<shared_ptr<Texture2D>> texture_ptrs;

        string filepath = "Assets/Meshes/" + path;
        ifstream file(filepath.c_str());
        if (file.good()) {

            const auto scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
            for (size_t t = 0; t < scene->mNumMaterials; ++t) {
                aiString aiPath;
                scene->mMaterials[t]->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
                size_t slash_pos = path.rfind('/');
                if (slash_pos == std::string::npos) slash_pos = path.rfind('\\');
                std::string folder_path = (slash_pos != std::string::npos) ? path.substr(0, slash_pos + 1) : "Assets/Textures/";
                std::string texPath = folder_path + aiScene::GetShortFilename(aiPath.C_Str());

                auto texture_ptr = make_shared<Texture2D>(texPath);

                texture_ptrs.push_back(texture_ptr);
            }

            aiReleaseImport(scene);
        }
        else {
            cout << "FILE NOT FOUND :: MESH COMPONENT CONSTRUCTOR" << endl;
        }
        return texture_ptrs;
    }

    static vector<glm::mat4> TransformloadFromFile(const string& path, vector<shared_ptr<Mesh>> mesh_ptrs) {

        vector<glm::mat4> transforms;

        string filepath = "Assets/Meshes/" + path;
        ifstream file(filepath.c_str());
        if (file.good()) {
            //load meshes           

            const auto scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
            for (auto mesh : mesh_ptrs) {
                                
                // Extract transformation matrix from the associated node
                const aiNode* node = scene->mRootNode->FindNode(mesh->name.c_str());
                if (node != NULL) {
                    aiMatrix4x4 matrix = node->mTransformation;

                    // Create a glm::mat4 from aiMatrix4x4
                    glm::mat4 transformMatrix(
                        matrix.a1, matrix.b1, matrix.c1, matrix.d1,
                        matrix.a2, matrix.b2, matrix.c2, matrix.d2,
                        matrix.a3, matrix.b3, matrix.c3, matrix.d3,
                        matrix.a4, matrix.b4, matrix.c4, matrix.d4
                    );
                    transforms.push_back(transformMatrix);
                }
                else {
                    glm::mat4 transformMatrix = glm::identity<mat4>();
                    transforms.push_back(transformMatrix);
                }                
            }

            aiReleaseImport(scene);
        }
        else {
            cout << "FILE NOT FOUND :: MESH COMPONENT CONSTRUCTOR" << endl;
        }

        return transforms;
    }
};