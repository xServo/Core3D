#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) 
  : vertices(vertices), indices(indices), vao(vertices, 36), ib(indices, 36) {
  // TODO MAKE VAO AND IB ACCEPT std::vector
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  // TODO CREATE VERTEX ARRAY
  // vertices.size() * sizeof(Vertex)
}