#pragma once
#include "IndexBuffer.hpp"
#include "LightObject.hpp"
#include "VertexArray.hpp"
#include "gl_assert.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include <iostream>
#include <string>

class GameObject {
private:
  VertexArray vao;
  IndexBuffer ib;
  Model *m_Model;
  std::string m_ModelPath;

  /* ATTRIBUTES */
  std::string m_Name;
  glm::vec3 m_Position;
  float m_Shininess;
  glm::vec3 m_Color;
  bool m_IsLit;
  bool m_IsTextured;
  int m_TextureSlot;
  glm::vec3 m_Size;
  /* CHILDREN */
  bool m_HasLight;
  int m_LightID = -1;
  std::unique_ptr<LightObject> m_Light;
  /* MATRICES */
  glm::mat4 m_Rotate;
  glm::mat4 m_Translate;
  glm::mat4 m_Scale;
  /* UNIFORMS */
  int u_Shininess;
  int u_Color;
  int u_IsLit;
  int u_IsTextured;
  int u_Rotate;
  int u_Translate;
  int u_Scale;

public:
  unsigned int shaderID;
  unsigned int editorID;
  std::string name;

  GameObject(unsigned int shader);
  ~GameObject();
  void Color(glm::vec3 color);
  void Shininess(float shine);
  void Bind();
  void Draw();
  void Rotate(float theta, glm::vec3 rotationAxis);
  void Translate(glm::vec3 translate);
  void SetName(std::string name);
  void SetPos(glm::vec3 pos);
  void Scale(glm::vec3 scale);
  void SetSize(glm::vec3 scale);
  void SetIsLit(bool lit);
  void SetIsTextured(bool tex);
  void TextureSlot(int tex);
  void InitModel(std::string path);
  void InitLight(int lightID);
  glm::vec3 GetPos() const;
  glm::vec3 GetColor() const;
  glm::vec3 GetSize() const;
  bool GetIsLit() const;
  std::string GetModelPath();
  std::string GetName();
  int GetTextureSlot() const;
  float GetShine() const;
  int GetLightID() const;
  bool GetIsTextured() const;
  bool GetHasLight() const;
};
