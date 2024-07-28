# pragma once
#include <iostream>
#include <cmath>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Editor {
  private:
  public:
    Editor();
    ~Editor();
    void UILoop();
    std::vector<GameObject*> objects;
    struct Object {
      glm::vec3 pos;
    };
    void AddObject(GameObject* obj);
};
