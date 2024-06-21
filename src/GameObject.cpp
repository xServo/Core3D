#include "GameObject.hpp"
#include "data.hpp"

GameObject::GameObject()
  : vao(positions, 8), ib(indicies, 36){

    translate = glm::vec3(0, 0, 0);
    m_Position = glm::vec3(0, 0, 0);
    shaderID = 0;
  }

void GameObject::Bind() {
  if (shaderID == 0) {
    std::cout << "Error: Failed to bind GameObject! No shader bound. \nUse this.shaderID= " << std::endl;
    return;
  }

  vao.Bind();
  ib.Bind();


  if (translate != glm::vec3(0,0,0)) {
    m_Position += translate;
    glm::mat4 matTranslate = glm::mat4(1);
    matTranslate = glm::translate(matTranslate, m_Position);
    int u_Translate = glGetUniformLocation(shaderID, "u_Translate");
    glUniformMatrix4fv(u_Translate, 1, GL_FALSE, &matTranslate[0][0]);
    translate = glm::vec3(0, 0, 0);
  }

}
GameObject::~GameObject() {

}
