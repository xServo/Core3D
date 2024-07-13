#include "mesh.hpp"
// empty constructor
Mesh::Mesh() 
  : vao(NULL, NULL, NULL),
    ib(NULL,0) {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) 
  : vertices(vertices),
    indices(indices),
    textures(textures),
    vao(&vertices[0], vertices.size(), sizeof(Vertex)/sizeof(float)),
    ib(&indices[0], (unsigned int)indices.size() * sizeof(Vertex)) {
}