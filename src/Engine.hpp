#pragma once
#include <array>
#include <fstream>
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameObject.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "editor.hpp"
#include "gl_assert.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "level0.hpp"
#include "model.hpp"
#include "nlohmann/json.hpp"
#include "stb_image.h"

// must assign shaderID
struct ObjectAttrib {
  /* ID */
  int editorID = -1;
  int shaderID = -1;  // unsigned
  int lightID = -1;
  /* basic attributes */
  std::string name;
  glm::vec3 pos = glm::vec3(0, 0, 0);
  glm::vec3 size = glm::vec3(1, 1, 1);
  /* graphics */
  glm::vec3 color = glm::vec3(1, 1, 1);
  int textureSlot = -1;
  std::string modelPath;
  float shine = -1;
  bool isLit = true;
  /* TODO BIND TEXTURE ON DRAW OF GAMEOBJECT */
};

class Engine {
private:
  const int SCREEN_HEIGHT;
  const int SCREEN_WIDTH;
  /* SUBSYSTEMS */
  Renderer renderer;
  unsigned int shader;
  std::function<void()> editorUpdateCallback;
  bool isUI;

  void LoadScene();
  void LoadLevel(const int level[7][7]);
  void KeyBindings();
  void PreLoop();
  void BeginFrame();
  void MainLoop();
  void EndFrame();
  /* JSON */
  void SaveObjects(std::string filePath);
  void LoadObjects(const std::string& filePath);

  Engine();
  ~Engine();

public:
  bool levelLoadingEnabled = true;
  bool saveEnabled = false;
  bool loadEnabled = false;
  // singleton
  static Engine& Instance() {
    static Engine INSTANCE;
    return INSTANCE;
  }
  // outside get stuff
  void GetResolution();
  /* OBJ MANAGEMENT */
  void AddObject(GameObject* obj);
  void MapAttrib(GameObject* obj);
  GameObject* LoadAttrib(const ObjectAttrib& attrib);
  /* OBJ CONTAINERS */
  std::vector<GameObject*> objects;
  std::unordered_map<GameObject*, ObjectAttrib> attribMap;
  /* EDITOR UI */
  void ToggleUI();
  void SetEditorUpdateCallback(std::function<void()> callback);
  /* CORE */
  void Init();
};
