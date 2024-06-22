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
    glm::mat4 m_Rotate; 

  public: 
    GameObject();
    ~GameObject();
    void Bind();
    void Rotate(float theta, glm::vec3 rotationAxis);
    void Translate(glm::vec3 translate);
    void Scale(glm::vec3 scale);

    unsigned int shaderID;


};
