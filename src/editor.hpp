# pragma once
#include <iostream>
#include <cmath>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <unordered_map>
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Editor {
  private:
    void MapAttrib(GameObject* obj);
  public:
    struct ObjectAttrib {
      unsigned int editorID;
      unsigned int shaderID;
      unsigned int lightID;
      std::string name;
      glm::vec3 pos;
      glm::vec3 color = glm::vec3(1,1,1);
      glm::vec3 size = glm::vec3(1,1,1);
      bool isLit = true;
      bool isLight = false;
      bool isTextured;
    };
    Editor();
    ~Editor();
    std::vector<GameObject*> objects;
    std::unordered_map<GameObject*, ObjectAttrib> attribMap;
    void UILoop();
    void AddObject(GameObject* obj);
    // void GenObject(ObjectAttrib attrib);
    // void SaveObject();
    GameObject* LoadObject(ObjectAttrib attrib);
};
