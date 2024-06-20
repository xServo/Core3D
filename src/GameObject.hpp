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
  public: 
    GameObject();

    ~GameObject();

    void Bind();
    void Translate(glm::vec3 vec);
};
