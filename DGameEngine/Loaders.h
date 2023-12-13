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

        string filepath = "../DGameEditor/Assets/Meshes/" + path;
        ifstream file(filepath.c_str());
        if (file.good()) {
            //load meshes           

            const auto scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
            for (size_t m = 0; m < scene->mNumMeshes; ++m) {

                const auto mesh = scene->mMeshes[m];
                const auto faces = mesh->mFaces;

                vec3f* texCoords = (vec3f*)mesh->mTextureCoords[0];

                vector<Mesh::V3T2> vertex_data;
                for (size_t i = 0; i < mesh->mNumVertices; ++i) {
                    Mesh::V3T2 v = { (vec3f&)mesh->mVertices[i], vec2f(texCoords[i].x, texCoords[i].y)};
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

        string filepath = "../DGameEditor/Assets/Meshes/" + path;
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
};