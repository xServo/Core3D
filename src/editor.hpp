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
      unsigned int id;
      glm::vec3 pos;
      glm::vec3 color;
    };
    Editor();
    ~Editor();
    std::vector<GameObject*> objects;
    std::unordered_map<GameObject*, ObjectAttrib> attribMap;
    void UILoop();
    void AddObject(GameObject* obj);
    // void GenObject(ObjectAttrib attrib);
    // void SaveObject();
    // void LoadObject();
};
