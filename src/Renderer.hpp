#pragma once

#include <iostream>
#include <signal.h>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Camera.hpp"
#ifdef _WIN32
#include <intrin.h>
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
          x;\
          ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#include <signal.h>
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
      x;\
      ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#endif

void GLClearError(); 
bool GLLogCall(const char* function, const char* file, int line); 

class Renderer {
  public:
    Renderer(const int WIDTH, const int HEIGHT)
      : SCREEN_WIDTH(WIDTH), SCREEN_HEIGHT(HEIGHT) {
        GLFWwindow* gWindow = NULL;
        init();
        Shader();
        Projection();
      }
    GLFWwindow* gWindow;
    Camera camera;

    unsigned int shaderID;
    float deltaTime;
    bool isWireFrame;

    std::vector<int> objects;

    void Draw();
    void Swap();
    void Clear();
    void Wireframe(bool flag);
    void DeltaTime();
    void init();
    void quit();
    void ImGui();
    void ImGuiInit();
    void ImGuiEnd();

  private:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const float NEAR_PLANE = 0.01; 
    const float FAR_PLANE = 50;
    float m_LastFrameTime;

    void Shader();
    void Projection();
};
