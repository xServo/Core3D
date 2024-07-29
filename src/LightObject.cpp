#include "LightObject.hpp"

LightObject::LightObject(unsigned int shader, unsigned int id) {
  m_ShaderID = shader;
  m_LightID = id;
  u_LightPos = glGetUniformLocation(shader, ("lights[" + std::to_string(m_LightID) + "].lightPos").c_str());
  u_LightColor = glGetUniformLocation(shader, ("lights[" + std::to_string(m_LightID) + "].lightColor").c_str());
  
}

void LightObject::SetPos(glm::vec3 pos) {
  m_Pos = pos;
  glUniform3f(u_LightPos, m_Pos.x, m_Pos.y, m_Pos.z);
}

void LightObject::SetColor(glm::vec3 color) {
  m_Color = color;
  glUniform3f(u_LightColor, m_Color.x, m_Color.y, m_Color.z);
}
