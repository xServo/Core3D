#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <string>
#include <vector>
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "Input.hpp"
#include "model.hpp"
#include "level0.hpp"
#include "stb_image.h"
#include "texture.hpp"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {
  // TODO finish phong lighting   TODO DONE
  // TODO GameObject ID system 
    //  create id on construct
    //  add id to renderer
    //  auto render each GameObject
  // TODO fix movement TODO DONE
  // TODO ImGUI
  // TODO input class;  TODO DONE
  // TODO model loading; TODO DONE
  // TODO textures 
  // TODO model textures 
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
  model.Scale(glm::vec3(0.2, 0.2, 0.2));
  model.Translate(glm::vec3(2, -0.2, 1));
  /* LEVEL GEN */ 
  // TODO MAKE THIS A CLASS
  GameObject bulb(shader);
  bulb.IsLit(false);
  bulb.Scale(glm::vec3(0.1, 0.1, 0.1));
  bulb.Translate(glm::vec3(1, 0.5, 1));
  GameObject floor(shader);
  floor.Color(glm::vec3(1,0,0));
  floor.Translate(glm::vec3(1,-0.5,1));
  floor.Scale(glm::vec3(7,0.001,7));
  floor.Shininess(2);
  GameObject floor2(shader);
  floor2.Color(glm::vec3(0,0,1));
  floor2.Translate(glm::vec3(1,1,1));
  floor2.Scale(glm::vec3(6,0.001,6));
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

  // TODO temp lighting
  int u_LightPos = glGetUniformLocation(shader, "u_LightPos");
  glm::vec3 lightPos = glm::vec3(1, 0.5, 1);
  glUniform3f(u_LightPos, lightPos.x, lightPos.y, lightPos.z);
  int u_LightColor = glGetUniformLocation(shader, "u_LightColor");
  glm::vec3 lightColor = glm::vec3(0.43, 0.33, 0.44);
  glUniform3f(u_LightColor, lightColor.x, lightColor.y, lightColor.z);

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
    textures.Bind(3);
    model.Bind();

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
  renderer.quit();
}
