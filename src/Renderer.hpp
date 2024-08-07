#pragma once

#include <iostream>
#include <signal.h>
#include <cmath>
#include <glew.h>
#include <glfw3.h>
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Camera.hpp"
#include "editor.hpp"
#include "gl_assert.hpp"

class Renderer {
  public:
    Renderer(const int WIDTH, const int HEIGHT);
    Editor editor;
    // RENDER VARS
    GLFWwindow* gWindow;
    Camera camera;
    // STATE VARS
    unsigned int shaderID;
    float deltaTime;
    bool isWireFrame;
    bool isUI;

    // STATE
    void Wireframe(bool flag);
    void ToggleUI();
    void DeltaTime();

    // IMGUI
    void ImGui();
    void ImGuiInit();
    void ImGuiEnd();
    void ImGuiUI();

    // RENDER
    void Draw();
    void Swap();
    void Clear();
    // CORE
    void Init();
    void Quit();

  private:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const float NEAR_PLANE = 0.01; 
    const float FAR_PLANE = 50;
    float m_LastFrameTime;

    void Shader();
    void Projection();
};
