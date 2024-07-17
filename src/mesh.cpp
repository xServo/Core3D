#include "mesh.hpp"
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) 
  : vertices(vertices),
    indices(indices),
    textures(textures),
    vao(&vertices[0], vertices.size(), sizeof(Vertex)/sizeof(float)), // TODO vao accepts normals and texture coords
    ib(&indices[0], (unsigned int)indices.size() * sizeof(Vertex)) {
}

void Mesh::Draw() {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  for (unsigned int i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);  
    std::string number;
    std::string name = textures[i].Type;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);

    // shader.setInt(("material." + name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, textures[i].ID);
  }
  glActiveTexture(GL_TEXTURE0);

  // draw mesh
  vao.Bind();
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // TODO renderer draw call
  glBindVertexArray(0);
}
