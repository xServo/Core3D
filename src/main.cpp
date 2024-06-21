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


void init();
void quit();
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 10.0f;
std::string keyPressed;

GLFWwindow* gWindow = NULL;
void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    init();

    Renderer renderer(gWindow);

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
    glm::mat4 rotate = glm::mat4(1.0f); // initialize identity matrix
    rotate = glm::rotate(rotate, glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    int u_Rotate = glGetUniformLocation(shader, "u_Rotate");
    glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &rotate[0][0]);

    // translate
    cube.translate = glm::vec3(0,0,-5);
    cube.Bind();

    // scale scaling
    glm::mat4 scale = glm::mat4(1);
    scale = glm::scale(scale, glm::vec3(0.5, 0.5, 0.5)); // scales to 0.5x
    int u_Scale = glGetUniformLocation(shader, "u_Scale");
    glUniformMatrix4fv(u_Scale, 1, GL_FALSE, &scale[0][0]);

    // uniform stuff
    // mat4 rotate;
    // mat4 view;
    // mat4 projection;

    int u_location = glGetUniformLocation(shader, "u_Color");
    float r = 0.0f;
    float incr = 0.002f;
    while (!glfwWindowShouldClose(gWindow)) {
        rotate = glm::rotate(rotate, glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &rotate[0][0]);
        r += incr;
        if (r > 0.5f) {
            r = 0.5f;
            incr = -0.002f;
        } else if (r < 0) {
            r = 0;
            incr = 0.002f;
        }

        renderer.Clear();
        cube.translate = glm::vec3(0.002,-0.002,0);
        cube.Bind();
        renderer.Draw();

        GLCall(glfwPollEvents());
        // input  callback
        GLCall(glfwSetKeyCallback(gWindow, InputCallback));
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
    quit();
    // printf("hello world\n");
}

void init() {
    if (!glfwInit()) {
        printf("Error! Failed to initialize gflw");
    } else {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        gWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "graphics ryan graphcis", NULL, NULL);
        glViewport(0, 0, 800, 600);
        if (!gWindow)
        {
            printf("Error! Failed to create OpenGL context or window");
            return;
        } else {
            glfwMakeContextCurrent(gWindow);

            glfwSwapInterval(1); // enable vsync

            printf("GLEW Version %s\n", glewGetString(GLEW_VERSION));
            printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
                return;
            }
        }
    }
}
void quit() {
    printf("Quitting...\n");
    glfwDestroyWindow(gWindow);
    glfwTerminate();
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
      keyPressed = "e";
      std::cout << "yes" << std::endl;
    }
}
