#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <signal.h>
#include <cmath>
#include <glew.h>
#include <glfw3.h>
#include "ShaderCompiler.hpp"
#include "texture.hpp"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "gl_assert.hpp"
#include "GameObject.hpp"
#include "FrameBuffer.hpp"

class Renderer {
public:
  Renderer(const int WIDTH, const int HEIGHT);
  Texture textures;
  /* RENDER VARS */
  GLFWwindow* gWindow;
  /* STATE VARS */
  unsigned int shaderID;
  float deltaTime;
  bool isWireFrame;
  bool isUI;

  /* STATE */
  void Wireframe(bool flag);
  void DeltaTime();

  /* IMGUI */
  void ImGui();
  void ImGuiInit();
  void ImGuiEnd();
  void ImGuiUI();

  /* RENDER */
  unsigned int Shader(const std::string& path);
  void GLDraw();
  void Draw();
  void DrawObjects(const std::vector<GameObject*>& objects);
  void Swap();
  void Clear();
  /* FRAMEBUFFER */
  FrameBuffer ppBuffer;
  void ppStart();
  unsigned int ppTexture;
  float screenQuadVert[24] = {
      -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f};
  unsigned int tempBuffer;
  unsigned int ppShader;
  unsigned int ppVao;
  unsigned int ppVBO;
  int ppTexUniform;

  /* CORE */
  void Init();
  void Quit();

private:
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;
  const float NEAR_PLANE = 0.01f;
  const float FAR_PLANE = 50.0f;
  float m_LastFrameTime;

  void Projection();
};
