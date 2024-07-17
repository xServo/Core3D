#pragma once
#include <vector>
#include <string>
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  /* glm::vec2 TexCoords; */
};
struct Texture {
  unsigned int ID;
  std::string Type;
  std::string Path;
};

class Mesh {
  private:  
    VertexArray vao; 
    /* IndexBuffer ib; */
  
  public:
    std::vector<Vertex> vertices;
    /* std::vector<unsigned int> indices; */
    std::vector<Texture> textures; 
    /* Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures); */
    Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures);
    Mesh();
    void Draw();
    // TODO DRAW CALL FUNCTION THAT TAKES IN SHADER 
};
