#include "GameObject.hpp"
#include "data.hpp"

GameObject::GameObject(unsigned int shader)
  : vao(d_Positions, 36, 8), ib(d_Indicies, 36) {
    shaderID = shader;
    m_Model = nullptr;

    int ID;
    m_Color = glm::vec3(1, 1, 1);
    m_Shininess = 16;
    m_IsLit = true;
    m_IsTextured = true;
    m_Position = glm::vec3(0, 0, 0);
    /* MATRICES */
    m_Rotate = glm::mat4(1); 
    m_Scale = glm::mat4(1);
    m_Translate = glm::mat4(1);

    /* UNIFORMS */
    u_Shininess = glGetUniformLocation(shaderID, "material.shininess");
    u_Color = glGetUniformLocation(shaderID, "u_Color");
    u_IsLit = glGetUniformLocation(shaderID, "u_IsLit");
    u_IsTextured = glGetUniformLocation(shaderID, "u_IsTextured");
    u_Rotate = glGetUniformLocation(shaderID, "u_Rotate");
    u_Translate = glGetUniformLocation(shaderID, "u_Translate");
    u_Scale = glGetUniformLocation(shaderID, "u_Scale");

    Bind();
}

GameObject::~GameObject() {
  delete m_Model;
}

void GameObject::InitModel() {
  if (m_Model == nullptr) {
    m_Model = new Model("res/models/backpack/backpack.obj"); 
  } else {
    std::cout << "Error, GameObject already contains model!" << std::endl;
  }
}

void GameObject::Bind() {
  if (m_Model == nullptr) {
    vao.Bind();
    ib.Bind();
  }

  glUniform1f(u_Shininess, m_Shininess);
  glUniform3f(u_Color, m_Color.x, m_Color.y, m_Color.z);
  glUniform1i(u_IsLit, m_IsLit);
  glUniform1i(u_IsTextured, m_IsTextured);
  glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &m_Rotate[0][0]);
  glUniformMatrix4fv(u_Translate, 1, GL_FALSE, &m_Translate[0][0]);
  glUniformMatrix4fv(u_Scale, 1, GL_FALSE, &m_Scale[0][0]);

  // TODO TEMP
  Draw();
}

void GameObject::Draw() {
  if (m_Model == nullptr) {
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // use ib
  } else {
    m_Model->Draw();
  }
}

void GameObject::Color(glm::vec3 color) {
  m_Color = color;
  glUniform3f(u_Color, m_Color.x, m_Color.y, m_Color.z);
}

void GameObject::Shininess(float shine) {
  m_Shininess = shine;
  glUniform1f(u_Shininess, m_Shininess);
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

void GameObject::IsLit(bool lit) {
  m_IsLit = lit;
  glUniform1i(u_IsLit, m_IsLit);
}

void GameObject::IsTextured(bool tex) {
  m_IsTextured = tex;
  glUniform1i(u_IsTextured, m_IsTextured);
}

