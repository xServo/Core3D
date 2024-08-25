#pragma once
#include <iostream>
#include <string>
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "gl_assert.hpp"

class LightObject : public GameObject {
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
  /* set */
  void SetLightPos(glm::vec3 pos);

public:
  LightObject(unsigned int shader, unsigned int lightID);
  void Color(glm::vec3 color) override;
  void Translate(glm::vec3 translate) override;
  void SetPos(glm::vec3 pos) override;
  inline int GetLightID() const { return m_LightID; };
};
