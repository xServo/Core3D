#include "Camera.hpp"

Camera::Camera() {
  m_Pos = glm::vec3(0,0,0);
  m_Target = glm::vec3(0,0,-1);
  m_Up = glm::vec3(0,1,0);
  speed = 1.5;
} 


void Camera::Bind() {
  m_Target = m_Pos + glm::vec3(0,0,-1);

  // locations happen here because shader is not bound upon construction 
  u_View = glGetUniformLocation(shaderID, "u_View");
  glm::mat4 view = glm::lookAt(m_Pos, m_Target, m_Up);
  glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]);

  u_ViewPos = glGetUniformLocation(shaderID, "u_ViewPos");
  glUniform3f(u_ViewPos, m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::MoveForward() {
  m_Pos += glm::vec3(0,0,-1) * speed * deltaTime;
  Bind();
}
void Camera::MoveBackward() {
  m_Pos += glm::vec3(0,0,1) * speed * deltaTime;
  Bind();
}
void Camera::MoveLeft() {
  m_Pos += glm::vec3(-1,0,0) * speed * deltaTime;
  Bind();
}
void Camera::MoveRight() {
  m_Pos += glm::vec3(1,0,0) * speed * deltaTime;
  Bind();
}
void Camera::MoveUp() {
  m_Pos += glm::vec3(0,1,0) * speed * deltaTime;
  Bind();
}
void Camera::MoveDown() {
  m_Pos += glm::vec3(0,-1,0) * speed * deltaTime;
  Bind();
}
