const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 900;
Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

Input::lastX = SCREEN_WIDTH/2;  // init cursor pos
Input::lastY = SCREEN_HEIGHT/2; // init cursor pos

unsigned int shader = renderer.shaderID;

Texture textures;
textures.shaderID = shader;

textures.Generate("res/textures/slage.png", 0);
textures.Generate("res/textures/portal_wall.png", 1);
textures.Generate("res/models/backpack/diffuse.jpg", 3);

renderer.camera.Pos(glm::vec3(1, 0, 1));
// backpack
GameObject model(shader);
model.InitModel("res/models/backpack/backpack.obj");
model.Color(glm::vec3(0.32,0.2,1));
model.IsLit(true);
model.SetSize(glm::vec3(0.2, 0.2, 0.2));
model.Translate(glm::vec3(2, -0.2, 1));
/* LEVEL GEN */ 
Editor::ObjectAttrib cubeAttrib;
cubeAttrib.name = "my cube";
cubeAttrib.pos = glm::vec3(1,0.5,1);
cubeAttrib.color = glm::vec3(1,0,1);
cubeAttrib.shaderID = shader;
cubeAttrib.isTextured = false;
GameObject* myCube = renderer.editor.LoadObject(cubeAttrib);
// TODO MAKE THIS A CLASS
GameObject bulb(shader);
bulb.name = "Bulb";
bulb.Color(glm::vec3(0.53, 0.13, 0.54));
bulb.IsLit(false);
bulb.SetSize(glm::vec3(0.1, 0.1, 0.1));
bulb.Translate(glm::vec3(1, 0.5, 1));
bulb.InitLight(0);
renderer.editor.AddObject(&bulb);
/* TODO editor::AddObject needs to be called LAST this is not good */
GameObject bulb2(shader);
bulb2.name = "Bulb2";
bulb2.Color(glm::vec3(0.13, 0.43, 0.54));
bulb2.IsLit(false);
bulb2.SetSize(glm::vec3(0.1, 0.1, 0.1));
bulb2.Translate(glm::vec3(4, 0.5, 4));
bulb2.InitLight(1);
renderer.editor.AddObject(&bulb2);
GameObject floor(shader);
floor.Color(glm::vec3(1,0,0));
floor.Translate(glm::vec3(1,-0.5,1));
floor.SetSize(glm::vec3(7,0.001,7));
floor.Shininess(2);
GameObject floor2(shader);
floor2.Color(glm::vec3(0,0,1));
floor2.Translate(glm::vec3(1,1,1));
floor2.SetSize(glm::vec3(6,0.001,6));
floor2.Shininess(2);
/* WALL GEN */
std::vector<GameObject*> walls;
for (int i=1;i<level0Size+1;i++) {
  for (int j=1;j<level0Size+1;j++) {
    if (level0[i-1][j-1] == 1) {
      GameObject* wall = new GameObject(shader);  
      wall->IsTextured(true);
      wall->Shininess(10);
      wall->Translate(glm::vec3(i, 0, j));
      wall->Translate(glm::vec3(-7, 0, -7));
      walls.push_back(wall);
    }
  }
}
/* FLOOR GEN */
std::vector<GameObject*> floors;
for (int i=1;i<level0Size+1;i++) {
  for (int j=1;j<level0Size+1;j++) {
    GameObject* floor = new GameObject(shader);  
    floor->Shininess(10);
    floor->Translate(glm::vec3(i, 0, j));
    floor->Translate(glm::vec3(-7, -1.5, -7));
    floors.push_back(floor);
  }
}
/* ROOF GEN */
std::vector<GameObject*> roofs;
for (int i=1;i<level0Size+1;i++) {
  for (int j=1;j<level0Size+1;j++) {
    GameObject* roof = new GameObject(shader);  
    roof->Shininess(10);
    roof->Translate(glm::vec3(i, 0, j));
    roof->Translate(glm::vec3(-7, 2, -7));
    roofs.push_back(roof);
  }
}


glfwSetKeyCallback(renderer.gWindow, Input::KeyCallback);  // key callback
glfwSetCursorPosCallback(renderer.gWindow, Input::MouseCallback);   // mouse callback
renderer.ImGuiInit();
while (!glfwWindowShouldClose(renderer.gWindow)) {
  /* BEGIN FRAME */
  renderer.ImGui(); 
  renderer.DeltaTime();
  renderer.Clear();
  /* ROTATE */ 
  model.Rotate(renderer.deltaTime*10, glm::vec3(0,1,0));
  /* HANDLE INPUT */
  GLCall(glfwPollEvents());
  renderer.camera.Look(Input::pitch, Input::yaw);
  /* INPUT BINDS */
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
  /* DRAW FRAME */
  textures.Bind(0);
  bulb.Bind();
  bulb2.Bind();
  textures.Bind(3);
  model.Bind();
  myCube->Bind();

  textures.Bind(1);

  for (auto it : walls) { 
    it->Bind();
  } 
  textures.Bind(0);
  for (auto it : floors) { 
    it->Bind();
  } 
  for (auto it : roofs) { 
    it->Bind();
  } 
  renderer.ImGuiEnd();
  renderer.Swap();


  // printf("hello world\n");
}
// delete heap
for (auto wall : walls) {
  delete wall;
}
for (auto floor : floors) {
  delete floor;
}
for (auto roof : roofs) {
  delete roof;
}
renderer.Quit();

void Engine::LoadScene() {

}
