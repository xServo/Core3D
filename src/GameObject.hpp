#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

class GameObject {
  private:
    /* float* m_Positions = positions; */
    /* unsigned int* m_Indicies = indicies; */
    VertexArray vao; 
    IndexBuffer ib;
    glm::vec3 m_Position;

  public: 
    GameObject();
    ~GameObject();

    glm::vec3 translate;
    unsigned int shaderID;


    void Bind();
};
