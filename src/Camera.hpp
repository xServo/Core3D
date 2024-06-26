#pragma once
#include <glew.h>
#include <glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
  public: 
    Camera();
    unsigned int shaderID;
    void Bind();
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
  private:
    glm::vec3 m_Pos;
    glm::vec3 m_Target;  
    glm::vec3 m_Up;
    int u_View;
};
