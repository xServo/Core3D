#include "Engine.hpp"
#include <iostream>
#include <ostream>
#include "GameObject.hpp"
#include "LightObject.hpp"
// personal sceen size pref
#ifdef _WIN32
#define S_HEIGHT 1280
#define S_WIDTH 2320
#else
#define S_HEIGHT 800
#define S_WIDTH 1390
#endif

// TODO temp
bool Engine::CanMoveTo(glm::vec3 toPos) {
  char buffer[256];
  toPos += 2;
  int toX = std::floor(toPos.x / 2) + 2;
  int toZ = std::floor(toPos.z / 2) + 2;
  if (level0[toX][toZ] == 1) {
    std::snprintf(buffer, sizeof(buffer), "\nX:%i Z:%i \nBlocked", toX, toZ);
    debugString = buffer;
    return false;
  } else {
    std::snprintf(buffer, sizeof(buffer), "\nX:%i Z:%i \nClear", toX, toZ);
    debugString = buffer;
    return true;
  }
}

Engine::Engine()
    : SCREEN_HEIGHT(S_HEIGHT), SCREEN_WIDTH(S_WIDTH), renderer(SCREEN_WIDTH, SCREEN_HEIGHT) {
  /* pre update loop things */
  // editorUpdateCallback = nullptr;
  Input::lastX = float(SCREEN_WIDTH) / 2;   // init cursor pos
  Input::lastY = float(SCREEN_HEIGHT) / 2;  // init cursor pos
  /* set shader ids */
  shader = renderer.shaderID;
  /* init input callbacks */
  glfwSetKeyCallback(renderer.gWindow, Input::KeyCallback);  // key callback
  glfwSetCursorPosCallback(renderer.gWindow,
                           Input::MouseCallback);  // mouse callback
  /* init imgui */
  renderer.ImGuiInit();
}

Engine::~Engine() {
  if (saveEnabled)
    SaveObjects("res/save1.json");
  renderer.Quit();
}

void Engine::LoadScene() {}

void Engine::ToggleUI() {
  if (isUI)
    isUI = false;
  else
    isUI = true;
}

// get ui loop pointer
void Engine::SetEditorUpdateCallback(std::function<void()> callback) {
  editorUpdateCallback = callback;
}

void Engine::Init() {
  // TODO TODO TODO
  // json with textures to load, level arr to load, specific objs to load
  // game behavior (whats in the main loop/keybindings function)
  // TODO TODO TODO
  // scene
  renderer.camera.Pos(glm::vec3(1, 0, 1));
  renderer.textures.Generate("res/textures/slage.png", 0);
  renderer.textures.Generate("res/textures/portal_wall.png", 1);
  renderer.textures.Generate("res/models/backpack/diffuse.jpg", 3);
  /* LEVEL GEN */
  if (levelLoadingEnabled) {
    LoadLevel(level0);
  }
  // backpack
  ObjectAttrib backpackAttrib;
  backpackAttrib.name = "Backpack";
  backpackAttrib.color = glm::vec3(0.32, 0.2, 1);
  backpackAttrib.modelPath = "res/models/backpack/backpack.obj";
  backpackAttrib.size = glm::vec3(0.2, 0.2, 0.2);
  backpackAttrib.pos = glm::vec3(2, -0.2, 1);
  backpackAttrib.textureSlot = 3;
  backpackAttrib.shaderID = shader;
  GameObject* backpack = LoadAttrib(backpackAttrib);

  LightObject bulb1(shader, 0);
  bulb1.name = "Bulb1";
  bulb1.SetPos(glm::vec3(1, 0.5, 1));
  bulb1.Color(glm::vec3(0.53, 0.13, 0.54));
  bulb1.SetIsLit(false);
  bulb1.SetIsTextured(false);
  bulb1.SetSize(glm::vec3(0.1, 0.1, 0.1));
  AddObject(&bulb1);

  LightObject bulb2(shader, 1);
  bulb2.name = "Bulb2";
  bulb2.Color(glm::vec3(0.13, 0.43, 0.54));
  bulb2.SetIsLit(false);
  bulb2.SetIsTextured(false);
  bulb2.SetSize(glm::vec3(0.1, 0.1, 0.1));
  bulb2.SetPos(glm::vec3(4, 0.5, 4));
  AddObject(&bulb2);

  GameObject box(shader);
  box.SetIsLit(false);
  box.SetSize(glm::vec3(0.05, 1, 0.05));
  box.SetPos(glm::vec3(0, 0.5, 0));
  AddObject(&box);

  GameObject box2(shader);
  box2.SetIsLit(false);
  box2.SetSize(glm::vec3(0.05, 1, 0.05));
  box2.SetPos(glm::vec3(2, 0.1, 2));
  AddObject(&box2);

  GameObject box3(shader);
  box3.SetIsLit(false);
  box3.SetSize(glm::vec3(0.05, 1, 0.05));
  box3.SetPos(glm::vec3(4, 0.1, 2));
  AddObject(&box3);

  PreLoop();
  /* main loop */
  while (!glfwWindowShouldClose(renderer.gWindow)) {
    BeginFrame();

    MainLoop();

    EndFrame();
  }
}

void Engine::KeyBindings() {
  for (int i = 0; i < Input::keyPressed.length(); i++) {
    switch (Input::keyPressed[i]) {
      case 'w': {
        glm::vec3 newPos = renderer.camera.MoveForward();
        if (CanMoveTo(newPos) || !playMode) {
          renderer.camera.Pos(newPos);
        }
        break;
      }
      case 's': {
        glm::vec3 newPos = renderer.camera.MoveBackward();
        if (CanMoveTo(newPos) || !playMode) {
          renderer.camera.Pos(newPos);
        }
        break;
      }
      case 'a': {
        glm::vec3 newPos = renderer.camera.MoveLeft();
        if (CanMoveTo(newPos) || !playMode) {
          renderer.camera.Pos(newPos);
        }
        break;
      }
      case 'd': {
        glm::vec3 newPos = renderer.camera.MoveRight();
        if (CanMoveTo(newPos) || !playMode) {
          renderer.camera.Pos(newPos);
        }
        break;
      }
      case 't':
        renderer.camera.MoveUp();
        break;
      case 'g':
        renderer.camera.MoveDown();
        break;
      case 'e':
        ToggleUI();
        Input::keyPressed = "";
        break;
      case 'r':
        if (renderer.isWireFrame)
          renderer.Wireframe(false);
        else
          renderer.Wireframe(true);
        Input::keyPressed = "";
        break;
      case Input::ESC:
        if (Input::isMouseLock == true) {
          glfwSetInputMode(renderer.gWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
          Input::isMouseLock = false;
        } else if (Input::isMouseLock == false) {
          glfwSetInputMode(renderer.gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
          Input::ResetCursor();
          Input::isMouseLock = true;
        }
        Input::keyPressed = "";
        break;
      case Input::SHIFT:
        renderer.camera.isRunning = true;
        break;
      case Input::SHIFT_REL:  // Shift release
        renderer.camera.isRunning = false;
        break;
    }
  }
}

void Engine::GetResolution() {
  std::cout << "Resolution: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;
}

/* obj management */
void Engine::AddObject(GameObject* obj) {
  MapAttrib(obj);
  objects.push_back(obj);
}

void Engine::MapAttrib(GameObject* obj) {
  ObjectAttrib attrib;
  attrib.name = obj->GetName();
  attrib.editorID = obj->editorID;
  attrib.shaderID = obj->shaderID;
  attrib.pos = obj->GetPos();
  attrib.color = obj->GetColor();
  attrib.size = obj->GetSize();
  attrib.modelPath = obj->GetModelPath();
  attrib.isLit = obj->GetIsLit();
  /* if (obj->GetHasLight()) */
  /*   attrib.lightID = obj->GetLightID(); */
  if (obj->GetIsTextured())
    attrib.textureSlot = obj->GetTextureSlot();
  attribMap[obj] = attrib;  // divine intellect
}

GameObject* Engine::LoadAttrib(const ObjectAttrib& attrib) {
  // if shader is undefined use current engine shader
  int tempShaderID = shader;
  if (attrib.shaderID == -1)
    tempShaderID = attrib.shaderID;

  GameObject* obj = new GameObject(tempShaderID);

  obj->SetName(attrib.name);
  obj->Color(attrib.color);
  obj->SetSize(attrib.size);
  obj->SetPos(attrib.pos);
  obj->SetIsLit(attrib.isLit);

  if (!attrib.modelPath.empty())
    obj->InitModel(attrib.modelPath);
  if (attrib.shine != -1)
    obj->Shininess(attrib.shine);
  /* if (attrib.lightID != -1) */
  /*   obj->InitLight(attrib.lightID); */
  if (attrib.textureSlot != -1) {
    obj->SetIsTextured(true);
    obj->TextureSlot(attrib.textureSlot);
  } else
    obj->SetIsTextured(false);

  AddObject(obj);
  return obj;
}

void Engine::LoadLevel(const int levelArr[7][7]) {
  int levelSize = 7;
  float offset = 7;
  /* WALL GEN */
  ObjectAttrib levelAttrib;
  levelAttrib.shaderID = shader;
  levelAttrib.shine = 10;
  for (int i = 1; i < levelSize + 1; i++) {
    for (int j = 1; j < levelSize + 1; j++) {
      if (levelArr[i - 1][j - 1] == 1) {
        levelAttrib.name = "wall";
        levelAttrib.pos = glm::vec3((i * 2) - offset, 0, (j * 2) - offset);
        levelAttrib.textureSlot = 1;
        /* objects.push_back(LoadAttrib(levelAttrib)); */
        LoadAttrib(levelAttrib);
      }
    }
  }
  /* FLOOR GEN */
  for (int i = 1; i < levelSize + 1; i++) {
    for (int j = 1; j < levelSize + 1; j++) {
      levelAttrib.name = "floor";
      levelAttrib.pos = glm::vec3((i * 2) - offset, -1.5, (j * 2) - offset);
      levelAttrib.textureSlot = 1;  // 0
      /* objects.push_back(LoadAttrib(levelAttrib)); */
      LoadAttrib(levelAttrib);
    }
  }
  /* ROOF GEN */
  for (int i = 1; i < levelSize + 1; i++) {
    for (int j = 1; j < levelSize + 1; j++) {
      levelAttrib.name = "roof";
      levelAttrib.pos = glm::vec3((i * 2) - 7, 2, (j * 2) - 7);
      levelAttrib.textureSlot = 0;
      /* objects.push_back(LoadAttrib(levelAttrib)); */
      LoadAttrib(levelAttrib);
    }
  }
}

void Engine::SaveObjects(std::string filePath) {
  using json = nlohmann::json;
  std::ofstream f(filePath);
  if (!f.is_open()) {
    std::cerr << "Error, could not open the file!" << std::endl;
    return;
  }

  for (auto obj : objects) {
    json o;
    ObjectAttrib attrib = attribMap[obj];
    o["name"] = attrib.name;
    o["editorID"] = attrib.editorID;
    o["shaderID"] = attrib.shaderID;
    /* o["lightID"] = attrib.lightID; */
    o["pos"] = {attrib.pos.x, attrib.pos.y, attrib.pos.z};
    o["size"] = {attrib.size.x, attrib.size.y, attrib.size.z};
    o["textureSlot"] = attrib.textureSlot;
    o["color"] = {attrib.color.x, attrib.color.y, attrib.color.z};
    o["modelPath"] = attrib.modelPath;
    o["shine"] = attrib.shine;
    // f << o.dump(2) << "\n"; // pretty json
    f << o << "\n";
  }

  f.close();
}

void Engine::LoadObjects(const std::string& filePath) {
  using json = nlohmann::json;
  std::ifstream f(filePath);
  if (!f.is_open()) {
    std::cerr << "Error, could not open the file!" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(f, line)) {
    json j;
    try {
      j = json::parse(line);
    } catch (json::parse_error& e) {
      std::cerr << "JSON parse error: " << e.what() << std::endl;
      continue;
    }

    ObjectAttrib attrib;
    /* TODO floats? DONT WORK */
    attrib.shaderID = shader;
    attrib.name = j["name"];
    attrib.textureSlot = j["textureSlot"];
    attrib.pos = glm::vec3(j["pos"][0], j["pos"][1], j["pos"][2]);
    attrib.color = glm::vec3(j["color"][0], j["color"][1], j["color"][2]);
    attrib.size = glm::vec3(j["size"][0], j["size"][1], j["size"][2]);
    LoadAttrib(attrib);
  }

  f.close();
}

void Engine::PreLoop() {
  renderer.ppStart();
  if (loadEnabled) {
    LoadObjects("res/save1.json");
  }
}

void Engine::BeginFrame() {
  renderer.ImGui();
  // load editor ui if enabled
  if (editorUpdateCallback && isUI) {
    editorUpdateCallback();
  }
  renderer.DeltaTime();
  renderer.Clear();
  /* HANDLE INPUT */
  GLCall(glfwPollEvents());
  renderer.camera.Look(Input::pitch, Input::yaw);
  KeyBindings();
}

void Engine::MainLoop() {
}

void Engine::EndFrame() {
  renderer.Clear();
  renderer.DrawObjects(objects);
  renderer.Draw();
}
