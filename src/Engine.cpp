#include "Engine.hpp"
// personal sceen size pref
#ifdef _WIN32
#define S_HEIGHT 1280
#define S_WIDTH 2320
#else
#define S_HEIGHT 900
#define S_WIDTH 1440
#endif

Engine::Engine() : 
  SCREEN_HEIGHT(S_HEIGHT), SCREEN_WIDTH(S_WIDTH), renderer(SCREEN_WIDTH, SCREEN_HEIGHT) {
  /* pre update loop things */
  Input::lastX = SCREEN_WIDTH/2;  // init cursor pos
  Input::lastY = SCREEN_HEIGHT/2; // init cursor pos
  /* set shader ids */
  shader = renderer.shaderID;
  /* init input callbacks */
  glfwSetKeyCallback(renderer.gWindow, Input::KeyCallback);  // key callback
  glfwSetCursorPosCallback(renderer.gWindow, Input::MouseCallback);   // mouse callback
  /* init imgui */
  renderer.ImGuiInit();
}

Engine::~Engine() {
  for (auto obj : objects) {
    delete(obj);
  }
  renderer.Quit();
}

void Engine::LoadScene() {
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
  LoadLevel(level0);
  // backpack
  ObjectAttrib backpackAttrib;
  backpackAttrib.color = glm::vec3(0.32,0.2,1);
  backpackAttrib.modelPath = "res/models/backpack/backpack.obj";
  backpackAttrib.size = glm::vec3(0.2, 0.2, 0.2);
  backpackAttrib.pos = glm::vec3(2, -0.2, 1);
  backpackAttrib.textureSlot = 3;
  backpackAttrib.shaderID = shader;
  GameObject* backpack = LoadObject(backpackAttrib);

  GameObject bulb(shader);
  bulb.name = "Bulb";
  bulb.Color(glm::vec3(0.53, 0.13, 0.54));
  bulb.IsLit(false);
  bulb.SetSize(glm::vec3(0.1, 0.1, 0.1));
  bulb.Translate(glm::vec3(1, 0.5, 1));
  bulb.InitLight(0);
  AddObject(&bulb);
  GameObject bulb2(shader);
  bulb2.name = "Bulb2";
  bulb2.Color(glm::vec3(0.13, 0.43, 0.54));
  bulb2.IsLit(false);
  bulb2.SetSize(glm::vec3(0.1, 0.1, 0.1));
  bulb2.Translate(glm::vec3(4, 0.5, 4));
  bulb2.InitLight(1);
  AddObject(&bulb2);

  /* main loop */
  while (!glfwWindowShouldClose(renderer.gWindow)) {
    BeginFrame();

    // game loop stuff
    backpack->Rotate(renderer.deltaTime*10, glm::vec3(0,1,0));

    EndFrame();
  }
}

void Engine::KeyBindings() {
    for (int i=0;i<Input::keyPressed.length();i++) {
    switch (Input::keyPressed[i]) {
      case 'w':
        renderer.camera.MoveForward();
        break;
      case 's':
        renderer.camera.MoveBackward();
        break;
      case 'a':
        renderer.camera.MoveLeft();
        break;  
      case 'd':
        renderer.camera.MoveRight();
        break;  
      case 't':
        renderer.camera.MoveUp();
        break;  
      case 'g':
        renderer.camera.MoveDown();
        break;  
      case 'e':
        renderer.ToggleUI();
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

/* obj management */
void Engine::AddObject(GameObject* obj) {
  MapAttrib(obj);
  objects.push_back(obj);
}

void Engine::MapAttrib(GameObject* obj) {
  ObjectAttrib attrib;
  /* if (obj->editorID != 0) { */
  /*   attrib.id = obj->editorID; */
  /* } else { */
  /*   std::cout << "Error generating attributes! No editorID on GameObject" << std::endl; */
  /* } */
  attrib.pos = obj->GetPos();
  attrib.color = obj->GetColor();
  attrib.size = obj->GetSize();
  attrib.isLit = obj->GetIsLit();
  attrib.modelPath = obj->GetModelPath();
  attribMap[obj] = attrib; // divine intellect
}

GameObject* Engine::LoadObject(const ObjectAttrib &attrib) {
  ASSERT(attrib.shaderID != -1);

  GameObject* obj = new GameObject(attrib.shaderID);
  obj->name = attrib.name;
  obj->Color(attrib.color);
  obj->IsLit(attrib.isLit);
  obj->SetSize(attrib.size);
  obj->Translate(attrib.pos);

  if (!attrib.modelPath.empty())
    obj->InitModel(attrib.modelPath);
  if (attrib.shine != -1)
    obj->Shininess(attrib.shine);
  if (attrib.isLight)
    ASSERT(attrib.lightID != -1);
    obj->InitLight(attrib.lightID);
  if (attrib.textureSlot != -1) {
    obj->IsTextured(true);
    obj->TextureSlot(attrib.textureSlot);
  }

  AddObject(obj);
  return obj;
}

void Engine::LoadLevel(const int levelArr[7][7]) {
  int levelSize = 7;
  /* WALL GEN */
  ObjectAttrib levelAttrib;
  levelAttrib.shaderID = shader;
  levelAttrib.shine = 10;
  for (int i=1;i<levelSize+1;i++) {
    for (int j=1;j<levelSize+1;j++) {
      if (levelArr[i-1][j-1] == 1) {
        levelAttrib.pos = glm::vec3((i*2)-7,0,(j*2)-7);
        levelAttrib.textureSlot = 1;
        objects.push_back(LoadObject(levelAttrib));
      }
    }
  }
  /* FLOOR GEN */
  for (int i=1;i<levelSize+1;i++) {
    for (int j=1;j<levelSize+1;j++) {
      levelAttrib.pos = glm::vec3((i*2)-7,-1.5,(j*2)-7);
      levelAttrib.textureSlot = 0;
      objects.push_back(LoadObject(levelAttrib));
    }
  }
  /* ROOF GEN */
  for (int i=1;i<levelSize+1;i++) {
    for (int j=1;j<levelSize+1;j++) {
      levelAttrib.pos = glm::vec3((i*2)-7,2,(j*2)-7);
      levelAttrib.textureSlot = 0;
      objects.push_back(LoadObject(levelAttrib));
    }
  }
}

void Engine::BeginFrame() {
  renderer.ImGui();
  renderer.DeltaTime();
  renderer.Clear();

  /* HANDLE INPUT */
  GLCall(glfwPollEvents());
  renderer.camera.Look(Input::pitch, Input::yaw);
  KeyBindings();
}

void Engine::EndFrame() {
  renderer.DrawObjects(objects);
  renderer.ImGuiEnd();
  renderer.Swap();
}
