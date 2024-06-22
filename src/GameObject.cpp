#include "GameObject.hpp"
#include "data.hpp"

GameObject::GameObject()
  : vao(positions, 8), ib(indicies, 36) {

    m_Position = glm::vec3(0, 0, 0);
    m_Rotate = glm::mat4(1.0f); 
    shaderID = 0;
  }
GameObject::~GameObject() {

}

void GameObject::Bind() {
  if (shaderID == 0) {
    std::cout << "Error: Failed to bind GameObject! No shader bound. \nUse this.shaderID= " << std::endl;
    return;
  }
  vao.Bind();
  ib.Bind();
}

void GameObject::Rotate(float theta, glm::vec3 rotationAxis) {
  m_Rotate = glm::rotate(m_Rotate, glm::radians(theta), rotationAxis);
  int u_Rotate = glGetUniformLocation(shaderID, "u_Rotate");
  glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &m_Rotate[0][0]);
}

void GameObject::Translate(glm::vec3 translate) {
    m_Position += translate;
    glm::mat4 matTranslate = glm::mat4(1);
    matTranslate = glm::translate(matTranslate, m_Position);
    int u_Translate = glGetUniformLocation(shaderID, "u_Translate");
    glUniformMatrix4fv(u_Translate, 1, GL_FALSE, &matTranslate[0][0]);
}

void GameObject::Scale(glm::vec3 scale) {
    glm::mat4 matScale = glm::mat4(1);
    matScale = glm::scale(matScale, scale); // scales to 0.5x
    int u_Scale = glGetUniformLocation(shaderID, "u_Scale");
    glUniformMatrix4fv(u_Scale, 1, GL_FALSE, &matScale[0][0]);
}
