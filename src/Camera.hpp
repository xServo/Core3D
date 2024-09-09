#pragma once
#include <glew.h>
#include <glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
  glm::vec3 m_Pos;
  glm::vec3 m_Target;
  glm::vec3 m_Up;
  int u_View;
  int u_ViewPos;
  float m_runSpeed;
  float m_walkSpeed;

public:
  Camera();
  float speed;
  float deltaTime;
  bool isRunning;
  unsigned int shaderID;

  void Bind();
  void Look(float pitch, float yaw);
  void Pos(glm::vec3 newPos);
  glm::vec3 MoveForward();
  glm::vec3 MoveBackward();
  glm::vec3 MoveLeft();
  glm::vec3 MoveRight();
  void MoveUp();
  void MoveDown();
  inline glm::vec3 GetPos() const { return m_Pos; };
  inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Pos, m_Pos + m_Target, m_Up); }
};
