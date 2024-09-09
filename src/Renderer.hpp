#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <signal.h>
#include <cmath>
#include <glew.h>
#include <glfw3.h>
#include "ShaderCompiler.hpp"
#include "fwd.hpp"
#include "texture.hpp"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "gl_assert.hpp"
#include "GameObject.hpp"
#include "FrameBuffer.hpp"

// TEXTURE SLOTS
// 8 IS RESERVED FOR SHADOW MAP
// 9 IS RESERVED FOR POST PROCESSING
enum RESERVED_TEX_SLOT {
  SKYBOX = 6,
  SHADOW = 8,
};

class Renderer {
public:
  Renderer(const int WIDTH, const int HEIGHT);
  Texture textures;
  /* RENDER VARS */
  GLFWwindow* gWindow;
  float projectionFOV;
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
  void Draw(const std::vector<GameObject*>& objects);
  void DrawObjects(const std::vector<GameObject*>& objects, unsigned int shader);
  void Swap();
  void Clear();
  void ToggleShadowBufferView();
  /* SKYBOX */
  unsigned int skyboxVAO;
  unsigned int skyboxVBO;
  unsigned int skyboxTex;
  unsigned int skyboxShader;
  unsigned int SkyboxLoadCubemap(std::vector<std::string> faces);
  void SkyboxInit();
  void SkyboxDraw();
  /* FRAMEBUFFER */
  FrameBuffer shadowBuffer;
  glm::vec3 shadowPos;
  FrameBuffer ppBuffer;
  unsigned int ppTexture;
  void ppStart();
  void ShadowStart();
  unsigned int tempBuffer;
  unsigned int ppShader;
  unsigned int shadowShader;
  unsigned int displayShadowShader;
  unsigned int ppVao;
  unsigned int ppVBO;
  int ppTexUniform;

  /* CORE */
  void Init();
  void Quit();

private:
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;
  int m_InitialWidth;   // THIS is needed due to mac displays reporting resolution inacuratley
  int m_InitialHeight;  // THIS is needed due to mac displays reporting resolution inacuratley

  const float NEAR_PLANE = 0.01f;
  const float FAR_PLANE = 50.0f;
  static const int SHADOW_RES = 1024;
  glm::mat4 m_ProjectionMatrix;
  float m_LastFrameTime;
  bool m_RenderShadowBuffer;

  void Projection();
  void ShadowProj();
};
