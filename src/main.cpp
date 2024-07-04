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

#include "ShaderCompiler.hpp"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

std::string keyPressed;

Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
  // TODO finish phong lighting
  // TODO fix movement
  // TODO input class; events?
  // TODO model loading;

  unsigned int shader = renderer.shaderID;

  GameObject cube(shader);
  cube.Translate(glm::vec3(2,0,-9));
  cube.Scale(glm::vec3(1,1.3,1));
  cube.Color(glm::vec3(0.3, 0.77, 1));

  GameObject cube2(shader);

  // camera
  /* renderer.camera.pos = glm::vec3(0,0,0); */
  /* renderer.camera.target = glm::vec3(0,0,-1); */
  /* renderer.camera.up = glm::vec3(0,1,0); */
  /* glm::mat4 view = glm::lookAt(renderer.camera.pos, renderer.camera.target, renderer.camera.up); */
  /* int u_View = glGetUniformLocation(shader, "u_View"); */
  /* glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]); */

  float r = 0.0f;
  float incr = 0.002f;
  while (!glfwWindowShouldClose(renderer.gWindow)) {
    cube.Rotate(0.1, glm::vec3(1,0,1));
    r += incr;
    if (r > 0.5f) {
      r = 0.5f;
      incr = -0.002f;
    } else if (r < 0) {
      r = 0;
      incr = 0.002f;
    }

    renderer.Clear();

    /* TODO draw binds every GameObject in "scene" TODO */
    cube.Bind();
    renderer.Draw();
    cube2.Bind();
    renderer.Draw();

    renderer.Swap();

    GLCall(glfwPollEvents());
    // input  callback
    GLCall(glfwSetKeyCallback(renderer.gWindow, InputCallback));
    // handle input
    switch (keyPressed[0]) {
      case 'e':
        if (renderer.m_Wireframe) {
          renderer.Wireframe(false);
        } else {
          renderer.Wireframe(true);
        }
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
    // reset input 
    keyPressed = "";
    // printf("hello world\n");
  }
  renderer.quit();
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
        keyPressed = "w";
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
        keyPressed = "d";
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
}
