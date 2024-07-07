#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ShaderCompiler.hpp"

#include "level0.hpp"


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

std::string keyPressed;
void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
float lastX = SCREEN_WIDTH/2;
float lastY = SCREEN_HEIGHT/2;
float yaw;
float pitch;

int main() {
  // TODO finish phong lighting   TODO DONE
  // TODO GameObject ID system 
  //  create id on construct
  //  add id to renderer
  //  auto render each GameObject
  // TODO fix movement
  // TODO ImGUI
  // TODO input class; events?
  // TODO model loading;
  renderer.ImGuiInit();

  unsigned int shader = renderer.shaderID;

  /* GameObject cube(shader); */
  /* cube.Translate(glm::vec3(2,0,-9)); */
  /* cube.Scale(glm::vec3(1,1.3,1)); */
  /* cube.Color(glm::vec3(0.3, 0.77, 1)); */

  /* GameObject cube2(shader); */
  /* cube2.Translate(glm::vec3(-2,0,-13)); */
  /* cube2.Scale(glm::vec3(1,1.5,10)); */

  GameObject floor(shader);
  floor.Color(glm::vec3(1,0,0));
  floor.Translate(glm::vec3(0,-0.5,-5));
  floor.Scale(glm::vec3(10,0.001,10));
  GameObject floor2(shader);
  floor2.Color(glm::vec3(0,0,1));
  floor2.Translate(glm::vec3(0,1,-5));
  floor2.Scale(glm::vec3(10,0.001,10));

  std::vector<GameObject*> walls;
  for (int i=1;i<level0Size+1;i++) {
    for (int j=1;j<level0Size+1;j++) {
      if (level0[i-1][j-1] == 1) {
        GameObject* wall = new GameObject(shader);  
        wall->Translate(glm::vec3(i, 0, j));
        wall->Translate(glm::vec3(-5, 0, -10));
        walls.push_back(wall);
      }
    }
  }
  /* GameObject* w1 = new GameObject(shader); */
  /* walls.push_back(w1); */
  /* w1->Translate(glm::vec3(-5,0,0)); */

  // TODO temp lighting
  int u_LightPos = glGetUniformLocation(shader, "u_LightPos");
  glm::vec3 lightPos = glm::vec3(0, 0.5, 0);
  glUniform3f(u_LightPos, lightPos.x, lightPos.y, lightPos.z);
  int u_LightColor = glGetUniformLocation(shader, "u_LightColor");
  glm::vec3 lightColor = glm::vec3(0.43, 0, 0.44);
  glUniform3f(u_LightColor, lightColor.x, lightColor.y, lightColor.z);

  float r = 0.0f;
  float incr = 0.002f;
  while (!glfwWindowShouldClose(renderer.gWindow)) {
    // rotation
    /* cube.Rotate(0.1, glm::vec3(1,0,1)); */
    r += incr;
    if (r > 0.5f) {
      r = 0.5f;
      incr = -0.002f;
    } else if (r < 0) {
      r = 0;
      incr = 0.002f;
    }
    /* // TODO temp lighting */
    /* glm::vec3 lightPos = glm::vec3(0, r * 1.4, 0); */
    /* glUniform3f(u_LightPos, lightPos.x, lightPos.y, lightPos.z); */
    /* glm::vec3 lightColor = glm::vec3(r+0.23, r-0.3, 0.34); */
    /* glUniform3f(u_LightColor, lightColor.x, lightColor.y, lightColor.z); */

    /* BEGIN FRAME */
    renderer.ImGui(); 
    renderer.DeltaTime();
    renderer.Clear();
    /* HANDLE INPUT */
    GLCall(glfwPollEvents());
    GLCall(glfwSetKeyCallback(renderer.gWindow, InputCallback));  // key callback
    glfwSetCursorPosCallback(renderer.gWindow, MouseCallback);   // mouse callback
    renderer.camera.Look(pitch, yaw);
    for (int i=0;i<keyPressed.length();i++) {
      if (keyPressed != "") {
        std::cout << keyPressed << std::endl;
      }
      switch (keyPressed[i]) {
        case 'e':
          if (renderer.isWireframe) {
            renderer.Wireframe(false);
          } else {
            renderer.Wireframe(true);
          }
          keyPressed = "";
          break;
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
      }
    }

    /* TODO draw binds every GameObject in "scene" TODO */
    /* DRAW FRAME */
    renderer.Draw();
    floor.Bind();
    renderer.Draw();
    floor2.Bind();
    renderer.Draw();
    for (auto it : walls) { 
      it->Bind();
      renderer.Draw();
    } 

    renderer.ImGuiEnd();
    renderer.Swap();


    // printf("hello world\n");
  }
  // Clean up dynamically allocated objects
  for (auto wall : walls) {
    delete wall;
  }
  renderer.quit();
}

void GetDeltaTime(double &deltaTime, double lastFrameTime) {
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch (key) {
    case GLFW_KEY_E:
      if (action == GLFW_PRESS) {
        keyPressed = "e";
      }
      break;
    case GLFW_KEY_W:
      if (action == GLFW_PRESS) {
        keyPressed += "w";
      }
      break;
    case GLFW_KEY_S:
      if (action == GLFW_PRESS) {
        keyPressed = "s";
      }
      break;
    case GLFW_KEY_A:
      if (action == GLFW_PRESS) {
        keyPressed = "a";
      }
      break;
    case GLFW_KEY_D:
      if (action == GLFW_PRESS) {
        keyPressed += "d";
      }
      break;
    case GLFW_KEY_T:
      if (action == GLFW_PRESS) {
        keyPressed = "t";
      }
      break;
    case GLFW_KEY_G:
      if (action == GLFW_PRESS) {
        keyPressed = "g";
      }
      break;
  }
  size_t search;
  switch (key) {
    case GLFW_KEY_E:
      if (action == GLFW_RELEASE) {
        if (keyPressed == "e") {
          keyPressed = "";
        }
      }
      break;
    case GLFW_KEY_W:
      if (action == GLFW_RELEASE) {
        search = keyPressed.find('w');
        if (search != std::string::npos) {
          keyPressed.erase(search, 1);
        }
      }
      break;
    case GLFW_KEY_S:
      if (action == GLFW_RELEASE) {
        search = keyPressed.find('s');
        if (search != std::string::npos) {
          keyPressed.erase(search, 1);
        }
      }
      break;
    case GLFW_KEY_A:
      if (action == GLFW_RELEASE) {
        search = keyPressed.find('a');
        if (search != std::string::npos) {
          keyPressed.erase(search, 1);
        }
      }
      break;
    case GLFW_KEY_D:
      if (action == GLFW_RELEASE) {
        search = keyPressed.find('d');
        if (search != std::string::npos) {
          keyPressed.erase(search, 1);
        }
      }
      break;
    case GLFW_KEY_T:
      if (action == GLFW_RELEASE) {
        if (keyPressed == "t") {
          keyPressed = "";
        }
      }
      break;
    case GLFW_KEY_G:
      if (action == GLFW_RELEASE) {
        if (keyPressed == "g") {
          keyPressed = "";
        }
      }
      break;
  }
}
void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;
  const float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;
  yaw   += xoffset;
  pitch += yoffset;
  if(pitch > 89.0f)
    pitch = 89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;
}
