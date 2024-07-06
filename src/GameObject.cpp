#include "GameObject.hpp"
#include "data.hpp"

GameObject::GameObject(unsigned int shader)
  : vao(positions, 36), ib(indicies, 36) {
    shaderID = shader;

    int ID;
    m_Color = glm::vec3(1,1,1);
    m_Position = glm::vec3(0, 0, 0);
    /* MATRICES */
    m_Rotate = glm::mat4(1); 
    m_Scale = glm::mat4(1);
    m_Translate = glm::mat4(1);

    /* UNIFORMS */
    u_Color = glGetUniformLocation(shaderID, "u_Color");
    u_Rotate = glGetUniformLocation(shaderID, "u_Rotate");
    u_Translate = glGetUniformLocation(shaderID, "u_Translate");
    u_Scale = glGetUniformLocation(shaderID, "u_Scale");
    Bind();
  }

void GameObject::Bind() {
  vao.Bind();
  ib.Bind();
  glUniform3f(u_Color, m_Color.x, m_Color.y, m_Color.z);
  glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &m_Rotate[0][0]);
  glUniformMatrix4fv(u_Translate, 1, GL_FALSE, &m_Translate[0][0]);
  glUniformMatrix4fv(u_Scale, 1, GL_FALSE, &m_Scale[0][0]);
}

void GameObject::Color(glm::vec3 color) {
  m_Color = color;
  glUniform3f(u_Color, m_Color.x, m_Color.y, m_Color.z);
}

void GameObject::Rotate(float theta, glm::vec3 rotationAxis) {
  m_Rotate = glm::rotate(m_Rotate, glm::radians(theta), rotationAxis);
  glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &m_Rotate[0][0]);
}

void GameObject::Translate(glm::vec3 translate) {
  m_Position += translate;
  m_Translate = glm::translate(m_Translate, m_Position);
  glUniformMatrix4fv(u_Translate, 1, GL_FALSE, &m_Translate[0][0]);
}

void GameObject::Scale(glm::vec3 scale) {
  m_Scale = glm::scale(m_Scale, scale);
  glUniformMatrix4fv(u_Scale, 1, GL_FALSE, &m_Scale[0][0]);
}
