#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include <vector>
#include "mesh.hpp"
#include "stb_image.h"

#define ASSIMP_FLAGS aiProcess_Triangulate | aiProcess_FlipUVs


class Model {
  private:
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;

    void LoadModel(std::string path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Mesh::Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory);
  public:
    Model(std::string path);
    void Draw();
};
