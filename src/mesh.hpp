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
  glm::vec2 TexCoords;
};
struct Texture {
  unsigned int ID;
  std::string Type;
};

class Mesh {
  private:  
    VertexArray vao; 
    IndexBuffer ib;
  
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures; 
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh();
    // TODO DRAW CALL FUNCTION THAT TAKES IN SHADER 
};