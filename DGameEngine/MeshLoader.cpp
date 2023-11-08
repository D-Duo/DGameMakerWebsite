#include "MeshLoader.h"
#include <filesystem>

namespace fs = filesystem;


void MeshLoader::loadFromFile(const string& path, Scene& myScene) {

    string filepath = "Assets/Meshes/" + path;

    auto scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    //const aiSceneExt& scene = *(aiSceneExt*)scene_ptr;

    //load textures
   /* vector<Texture2D::Ptr> texture_ptrs;
    for (const auto& material : scene.materials()) {

        aiString aiPath;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
        fs::path texPath = fs::path(path).parent_path().parent_path().append("Textures") / fs::path(aiPath.C_Str()).filename();
        auto texture_ptr = make_shared<Texture2D>(texPath.string());
        texture_ptrs.push_back(texture_ptr);
    }*/

    //load meshes
    vector<Mesh::Ptr> mesh_ptrs;
    for (size_t m = 0; m < scene->mNumMeshes; ++m) {

        const auto mesh = scene->mMeshes[m];
        const auto faces = mesh->mFaces;

        vec3f* texCoords = (vec3f*)mesh->mTextureCoords[0];

        vector<Mesh::V3T2> vertex_data;
        for (size_t i = 0; i < mesh->mNumVertices; ++i) {
            Mesh::V3T2 v = { (vec3f&)mesh->mVertices, vec2f(texCoords[i].x, texCoords[i].y) };
            vertex_data.push_back(v);
        }

        vector<unsigned int> index_data;
        for (size_t f = 0; f < mesh->mNumFaces; ++f) {
            index_data.push_back(faces[f].mIndices[0]);
            index_data.push_back(faces[f].mIndices[1]);
            index_data.push_back(faces[f].mIndices[2]);
        }

        auto loadedMesh = make_shared<Mesh>(Mesh::Formats::F_V3T2, vertex_data.data(), vertex_data.size(), index_data.data(), index_data.size());

        //load Texture
        aiString aiPath;
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
        fs::path texPath = fs::path(path).parent_path().parent_path().append("Textures") / fs::path(aiPath.C_Str()).filename();
        auto text_ptr = make_shared<Texture2D>(texPath.string());
        Mesh pep;
        //Create GameObject
        myScene.CreateGameObject(path, move(loadedMesh), move(text_ptr));
    }

    aiReleaseImport(scene);
}