#pragma once
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "gl_assert.hpp"
#include "model.hpp"
#include "LightObject.hpp"

class GameObject {
  private:
    VertexArray vao; 
    IndexBuffer ib;
    Model* m_Model; 

    /* ATTRIBUTES */
    glm::vec3 m_Position;
    float m_Shininess;
    glm::vec3 m_Color;
    bool m_IsLit;
    bool m_IsTextured;
    glm::vec3 m_Size;
    /* CHILDREN */
    bool m_hasLight;
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
    void SetPos(glm::vec3 pos);
    void Scale(glm::vec3 scale);
    void SetSize(glm::vec3 scale);
    void IsLit(bool lit);
    void IsTextured(bool tex);
    void InitModel(std::string path);
    void InitLight(unsigned int lightID);
    glm::vec3 GetPos();
    glm::vec3 GetColor();
    glm::vec3 GetSize();
    bool GetIsLit();
};
