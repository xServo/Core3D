#include "model.hpp"

Model::Model(std::string path) {
  LoadModel(path);
}

void Model::LoadModel(std::string path) {
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path, ASSIMP_FLAGS);
  // check if root note loaded successfully
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cout << "ERROR Failed to load model! ASSIMP - " << import.GetErrorString() << std::endl;
    return;
  }
  m_Directory = path.substr(0, path.find_last_of('/'));

  // load each child node
  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
  // process all the node's meshes (if any)
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    m_Meshes.push_back(ProcessMesh(mesh, scene));
  }
  // then do the same for each of its children
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}
Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {

}
