#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"

class GameObject {
  private:
    VertexArray vao; 
    IndexBuffer ib;

    glm::vec3 m_Color;
    glm::vec3 m_Position;
    /* MATRICES */ 
    glm::mat4 m_Rotate; 
    glm::mat4 m_Translate; 
    glm::mat4 m_Scale; 
    /* UNIFORMS */ 
    int u_Color;
    int u_Rotate;
    int u_Translate;
    int u_Scale;

  public: 
    GameObject(unsigned int shader);
    void Color(glm::vec3 color);
    void Bind();
    void Rotate(float theta, glm::vec3 rotationAxis);
    void Translate(glm::vec3 translate);
    void Scale(glm::vec3 scale);

    unsigned int shaderID;
    int ID;
};
