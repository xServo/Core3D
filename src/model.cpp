#include "model.hpp"

Model::Model(std::string path) {
  LoadModel(path);
}

void Model::LoadModel(std::string path) {
  Assimp::Importer import;
  const aiScene* scene = import.ReadFile(path, ASSIMP_FLAGS);
  // check if root note loaded successfully
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cout << "Error, failed to load model! \nASSIMP - " << import.GetErrorString() << std::endl;
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
  // TODO TEMP TO PREVENT INFINITE LOOP
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}
Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
  // data to fill
  std::vector<Mesh::Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Mesh::Texture> textures;

  // walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Mesh::Vertex vertex;
    glm::vec3 vector;  // we declare a placeholder vector since assimp uses its
                       // own vector class that doesn't directly convert to
                       // glm's vec3 class so we transfer the data to this
                       // placeholder glm::vec3 first.
    // positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;
    // normals
    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    }
    // texture coordinates
    if (mesh->mTextureCoords[0])  // does the mesh contain texture coordinates?
    {
      glm::vec2 vec;
      // a vertex can contain up to 8 different texture coordinates. We thus
      // make the assumption that we won't use models where a vertex can have
      // multiple texture coordinates so we always take the first set (0).
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = vec;
    }
    /*   // tangent */
    /*   vector.x = mesh->mTangents[i].x; */
    /*   vector.y = mesh->mTangents[i].y; */
    /*   vector.z = mesh->mTangents[i].z; */
    /*   vertex.Tangent = vector; */
    /*   // bitangent */
    /*   vector.x = mesh->mBitangents[i].x; */
    /*   vector.y = mesh->mBitangents[i].y; */
    /*   vector.z = mesh->mBitangents[i].z; */
    /*   vertex.Bitangent = vector; */
    /* } else */
    /*   vertex.TexCoords = glm::vec2(0.0f, 0.0f); */

    vertices.push_back(vertex);
  }
  // now wak through each of the mesh's faces (a face is a mesh its triangle)
  // and retrieve the corresponding vertex indices.
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }
  /* // process materials */
  /* aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; */
  /* // we assume a convention for sampler names in the shaders. Each diffuse */
  /* // texture should be named as 'texture_diffuseN' where N is a sequential */
  /* // number ranging from 1 to MAX_SAMPLER_NUMBER. Same applies to other texture */
  /* // as the following list summarizes: diffuse: texture_diffuseN specular: */
  /* // texture_specularN normal: texture_normalN */

  /* // 1. diffuse maps */
  /* std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse"); */
  /* textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end()); */
  /* // 2. specular maps */
  /* std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular"); */
  /* textures.insert(textures.end(), specularMaps.begin(), specularMaps.end()); */
  /* // 3. normal maps */
  /* std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal"); */
  /* textures.insert(textures.end(), normalMaps.begin(), normalMaps.end()); */
  /* // 4. height maps */
  /* std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height"); */
  /* textures.insert(textures.end(), heightMaps.begin(), heightMaps.end()); */

  if (false) {
    for (const Mesh::Vertex& vertex : vertices) {
      std::cout << "Position: (" << vertex.Position.x << ", " << vertex.Position.y << ", " << vertex.Position.z << ")";
      std::cout << ", Normal: (" << vertex.Normal.x << ", " << vertex.Normal.y << ", " << vertex.Normal.z << ")";
      std::cout << std::endl;
    }
    for (const auto ee : indices) {
      std::cout << ", Indices: (" << ee << ")" << std::endl;
    }
    std::cout << indices.size() << std::endl;
  }
  // return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

std::vector<Mesh::Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
  std::vector<Mesh::Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    Mesh::Texture texture;
    texture.ID = TextureFromFile(str.C_Str(), m_Directory);
    texture.Type = typeName;
    texture.Path = str.C_Str();
    textures.push_back(texture);
  }
  return textures;
}
unsigned int Model::TextureFromFile(const char* path, const std::string& directory) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

void Model::Draw() {
  for (unsigned int i = 0; i < m_Meshes.size(); i++) m_Meshes[i].Draw();
}
