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
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 10.0f;
std::string keyPressed;

Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    renderer.init();


    GameObject cube;

    // TODO color buffer

    // shader stuff
    ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    cube.shaderID = shader;

    // projection stuff
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
    int u_Perspective = glGetUniformLocation(shader, "u_Perspective");

    glUniformMatrix4fv(u_Perspective, 1, GL_FALSE, &perspective[0][0]);

    // rotate
    /* cube.Rotate(0, glm::vec3(0,0,0)); */

    // translate
    cube.Translate(glm::vec3(0,0,-8));
    cube.Bind();

    // scale scaling
    cube.Scale(glm::vec3(1,1.3,1));

    // uniform stuff
    // mat4 rotate;
    // mat4 view;
    // mat4 projection;

    int u_location = glGetUniformLocation(shader, "u_Color");
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
        cube.Translate(glm::vec3(0.002,-0.002,0));
        cube.Bind();
        renderer.Draw();

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
    GLCall(glUniform4f(u_location, r, 0.3, -r, 1));
    
    GLCall(glDeleteProgram(shader));
    renderer.quit();
    // printf("hello world\n");
}


void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
      keyPressed = "e";
      std::cout << "yes" << std::endl;
    }
}
