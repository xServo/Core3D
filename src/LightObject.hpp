#pragma once
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "gl_assert.hpp"
class LightObject {
private:
  /* ids */
  unsigned int m_ShaderID;
  int m_LightID;
  /* attributes */
  glm::vec3 m_Pos;
  glm::vec3 m_Color;
  /* uniforms */
  int u_LightPos;
  int u_LightColor;

public:
  LightObject(unsigned int shader, unsigned int id);

  void SetPos(glm::vec3 pos);
  void SetColor(glm::vec3 color);
};
