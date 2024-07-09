#include "Camera.hpp"

Camera::Camera() {
  m_Pos = glm::vec3(0,0,0);
  m_Target = glm::vec3(0,0,-1);
  m_Up = glm::vec3(0,1,0);
  speed = 1.5;
  m_walkSpeed = speed;
  m_runSpeed = speed * 2;
  isRunning = false;
} 


void Camera::Bind() {
  // check for running
  if (isRunning == true) {
    speed = m_runSpeed;
  } else {
    speed = m_walkSpeed;
  }
  // locations happen here because shader is not bound upon construction 
  u_View = glGetUniformLocation(shaderID, "u_View");
  glm::mat4 view = glm::lookAt(m_Pos, m_Pos + m_Target, m_Up);
  glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]);

  u_ViewPos = glGetUniformLocation(shaderID, "u_ViewPos");
  glUniform3f(u_ViewPos, m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::Pos(glm::vec3 newPos) {
  m_Pos = newPos;
}
void Camera::MoveForward() {
  m_Pos += glm::vec3(m_Target.x, 0, m_Target.z) * speed * deltaTime;
  Bind();
}
void Camera::MoveBackward() {
  m_Pos -= glm::vec3(m_Target.x, 0, m_Target.z) * speed * deltaTime;
  Bind();
}
void Camera::MoveLeft() {
  m_Pos -= glm::normalize(glm::cross(m_Target, m_Up)) * speed * deltaTime;
  Bind();
}
void Camera::MoveRight() {
  m_Pos += glm::normalize(glm::cross(m_Target, m_Up)) * speed * deltaTime;
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
void Camera::Look(float pitch, float yaw) {
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  m_Target = glm::normalize(direction);    
  Bind();
}
