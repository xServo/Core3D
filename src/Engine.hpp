#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <string>
#include <vector>
#include "Engine.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "editor.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "Input.hpp"
#include "model.hpp"
#include "level0.hpp"
#include "stb_image.h"
#include "gl_assert.hpp"

// subsystems
// texture manager
// Renderer
// model loader

struct ObjectAttrib {
  unsigned int editorID;
  unsigned int shaderID;
  unsigned int lightID;
  std::string name;
  glm::vec3 pos;
  glm::vec3 color = glm::vec3(1,1,1);
  float shine = -1;
  glm::vec3 size = glm::vec3(1,1,1);
  bool isLit = true;
  bool isLight = false;
  int textureSlot;
  /* TODO BIND TEXTURE ON DRAW OF GAMEOBJECT */
};
class Engine {
  private:
    const int SCREEN_HEIGHT;
    const int SCREEN_WIDTH;
    /* SUBSYSTEMS */
    Renderer renderer;
    unsigned int shader;

    void LoadScene();
    void KeyBindings();

    Engine();
    ~Engine();
  public:
    static Engine& Instance() {
        static Engine INSTANCE;
        return INSTANCE;
    }  
    /* OBJ MANAGEMENT */
    void AddObject(GameObject* obj);
    void MapAttrib(GameObject* obj);
    GameObject* LoadObject(ObjectAttrib attrib);
    /* OBJ CONTAINERS */
    std::vector<GameObject*> objects;
    std::unordered_map<GameObject*, ObjectAttrib> attribMap;
    /* CORE */ 
    void Init();
};
