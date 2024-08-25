#include "LightObject.hpp"

/* private */
void LightObject::SetLightPos(glm::vec3 pos) {
  m_Pos = pos;
  glUniform3f(u_LightPos, m_Pos.x, m_Pos.y, m_Pos.z);
}

/* public */
LightObject::LightObject(unsigned int shader, unsigned int lightID) : GameObject(shader) {
  m_ShaderID = shader;
  m_LightID = lightID;
  u_LightPos = glGetUniformLocation(m_ShaderID, ("lights[" + std::to_string(m_LightID) + "].lightPos").c_str());
  u_LightColor = glGetUniformLocation(m_ShaderID, ("lights[" + std::to_string(m_LightID) + "].lightColor").c_str());
}

void LightObject::Color(glm::vec3 color) {
  GameObject::Color(color);
  m_Color = color;
  glUniform3f(u_LightColor, m_Color.x, m_Color.y, m_Color.z);
}

void LightObject::Translate(glm::vec3 translate) {
  GameObject::Translate(translate);
  SetLightPos(GetPos());
}

void LightObject::SetPos(glm::vec3 pos) {
  GameObject::SetPos(pos);
  SetLightPos(pos);
}
