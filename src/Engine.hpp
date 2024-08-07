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
#include <array>
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

// must assign shaderID
struct ObjectAttrib {
  unsigned int editorID;
  unsigned int shaderID = -1;
  unsigned int lightID;
  std::string name;
  std::string modelPath;
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
    void LoadLevel(const int level[7][7]);
    void KeyBindings();
    void BeginFrame();
    void EndFrame();

    Engine();
    ~Engine();
  public:
    // singleton
    static Engine& Instance() {
        static Engine INSTANCE;
        return INSTANCE;
    }  
    /* OBJ MANAGEMENT */
    void AddObject(GameObject* obj);
    void MapAttrib(GameObject* obj);
    GameObject* LoadObject(const ObjectAttrib &attrib);
    /* OBJ CONTAINERS */
    std::vector<GameObject*> objects;
    std::unordered_map<GameObject*, ObjectAttrib> attribMap;
    /* CORE */ 
    void Init();
};
