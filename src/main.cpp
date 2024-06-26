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
  // TODO color buffer

  unsigned int shader = renderer.shaderID;

  GameObject cube(shader);
  cube.Translate(glm::vec3(2,0,-9));
  cube.Scale(glm::vec3(1,1.3,1));

  GameObject cube2(shader);
  cube2.Translate(glm::vec3(-2,1,-9));
  cube2.Scale(glm::vec3(1,1,1));

  // camera
  renderer.camera.pos = glm::vec3(0,0,5);
  renderer.camera.target = glm::vec3(0,0,0);
  renderer.camera.up = glm::vec3(0,1,0);
  glm::mat4 view = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(0,1,0));
  int u_View = glGetUniformLocation(shader, "u_View");
  glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]);

  float r = 0.0f;
  float incr = 0.002f;
  while (!glfwWindowShouldClose(renderer.gWindow)) {
    cube.Rotate(0.1, glm::vec3(1,0,1));
    cube2.Rotate(0.1, glm::vec3(1,0,1));
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
    if (keyPressed == "e") {
      if (renderer.m_Wireframe == true) {
        renderer.Wireframe(false);
      } else if (renderer.m_Wireframe == false) {
        renderer.Wireframe(true);
      }
    }
    // reset input 
    keyPressed = "";


  }

  renderer.quit();
  // printf("hello world\n");
}


void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    keyPressed = "e";
    std::cout << "yes" << std::endl;
  }
}
