#include "GameObject.hpp"
#include "data.hpp"

GameObject::GameObject(unsigned int shader)
    : vao(d_Positions, 36, 8), ib(d_Indicies, 36) {
  m_Model = nullptr;

  int ID;
  m_Color = glm::vec3(1, 1, 1);
  m_Shininess = 16;
  m_Metallic = 0;
  m_Roughness = 0.2f;
  m_AO = 0.5;
  m_IsLit = true;
  m_IsTextured = false;
  m_Position = glm::vec3(0, 0, 0);
  /* MATRICES */
  m_Rotate = glm::mat4(1);
  m_Scale = glm::mat4(1);
  m_Translate = glm::mat4(1);

  SetShader(shader);
  Bind();
}

GameObject::~GameObject() { delete m_Model; }

void GameObject::InitModel(std::string path) {
  if (m_Model == nullptr) {
    m_ModelPath = path;
    m_Model = new Model(path.c_str());
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
  glUniform1f(u_Roughness, m_Roughness);
  glUniform1f(u_AO, m_AO);
  glUniform1f(u_Metallic, m_Metallic);
  glUniform3f(u_Color, m_Color.x, m_Color.y, m_Color.z);
  glUniform1i(u_IsLit, m_IsLit);
  glUniform1i(u_IsTextured, m_IsTextured);

  // calculate model matrix
  glm::mat4 modelMat = m_Translate * m_Rotate * m_Scale;
  glUniformMatrix4fv(u_Model, 1, GL_FALSE, &modelMat[0][0]);

  // TODO TEMP
  Draw();
}

void GameObject::Draw() {
  if (m_Model == nullptr) {
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);  // use ib
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

void GameObject::SetRoughness(float rough) {
  m_Roughness = rough;
  glUniform1f(u_Roughness, m_Roughness);
}

void GameObject::SetAO(float ao) {
  m_AO = ao;
  glUniform1f(u_AO, m_AO);
}

void GameObject::SetMetallic(float metallic) {
  m_Metallic = metallic;
  glUniform1f(u_Metallic, m_Metallic);
}

void GameObject::Rotate(float theta, glm::vec3 rotationAxis) {
  m_Rotate = glm::rotate(m_Rotate, glm::radians(theta), rotationAxis);
}

void GameObject::Translate(glm::vec3 translate) {
  if (translate == glm::vec3(0, 0, 0)) {
    return;
  }
  m_Position += translate;
  m_Translate = glm::translate(m_Translate, m_Position);
}

void GameObject::SetName(std::string name) { m_Name = name; }

void GameObject::SetShader(unsigned int shader) {
  shaderID = shader;
  /* UNIFORMS */
  // pbr
  u_Metallic = glGetUniformLocation(shaderID, "material.metallic");
  u_Roughness = glGetUniformLocation(shaderID, "material.roughness");
  u_AO = glGetUniformLocation(shaderID, "material.ao");
  // phong
  u_Shininess = glGetUniformLocation(shaderID, "material.shininess");
  // misc
  u_Color = glGetUniformLocation(shaderID, "u_Color");
  u_IsLit = glGetUniformLocation(shaderID, "u_IsLit");
  u_IsTextured = glGetUniformLocation(shaderID, "u_IsTextured");
  // model
  u_Model = glGetUniformLocation(shaderID, "u_Model");
}

void GameObject::SetPos(glm::vec3 pos) {
  m_Position = pos;
  m_Translate = glm::translate(glm::mat4(1), m_Position);
}

void GameObject::Scale(glm::vec3 scale) {
  m_Scale = glm::mat4(1);
  m_Size *= scale;
  m_Scale = glm::scale(m_Scale, m_Size);
}

void GameObject::SetSize(glm::vec3 scale) {
  m_Scale = glm::mat4(1);
  m_Size = scale;
  m_Scale = glm::scale(m_Scale, m_Size);
}

void GameObject::SetIsLit(bool lit) {
  m_IsLit = lit;
  glUniform1i(u_IsLit, m_IsLit);
}

void GameObject::SetIsTextured(bool tex) {
  m_IsTextured = tex;
  glUniform1i(u_IsTextured, m_IsTextured);
}

void GameObject::TextureSlot(int tex) {
  if (tex == -1) {
    SetIsTextured(false);
  } else {
    SetIsTextured(true);
    m_TextureSlot = tex;
  }
}

glm::vec3 GameObject::GetPos() const { return m_Position; }
glm::vec3 GameObject::GetColor() const { return m_Color; }
glm::vec3 GameObject::GetSize() const { return m_Size; }
bool GameObject::GetIsLit() const { return m_IsLit; }
std::string GameObject::GetModelPath() { return m_ModelPath; }
std::string GameObject::GetName() { return m_Name; }
int GameObject::GetTextureSlot() const { return m_TextureSlot; }
float GameObject::GetShine() const { return m_Shininess; }
bool GameObject::GetIsTextured() const { return m_IsTextured; }
