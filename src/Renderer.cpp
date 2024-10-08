#include "Renderer.hpp"
#include "Engine.hpp"
#include "VertData.hpp"

/* ---------------------------PUBLIC---------------------------- */
Renderer::Renderer(const int WIDTH, const int HEIGHT)
    : SCREEN_WIDTH(WIDTH),
      SCREEN_HEIGHT(HEIGHT),
      textures(),
      ppBuffer(WIDTH, HEIGHT),
      shadowBuffer(SHADOW_RES, SHADOW_RES) {
  GLFWwindow* gWindow = nullptr;
  projectionFOV = 40;
  isUI = true;
  Init();
  shaderID = Shader("res/shaders/basic.shader");
  skyboxShader = Shader("res/shaders/skybox.shader");
  ppShader = Shader("res/shaders/pp.shader");
  shadowShader = Shader("res/shaders/shadow.shader");
  displayShadowShader = Shader("res/shaders/debug_shadow.shader");
  ppShader = Shader("res/shaders/pp.shader");
  glUseProgram(shaderID);
  textures.shaderID = shaderID;
  Projection();
  textures.Init();
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
}

void Renderer::ImGuiInit() {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  // disable ini files
  io.IniFilename = NULL;
  /* io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls */
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(gWindow, true);  // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
  ImVec4 windowBgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);  // Dark gray background
  ImVec4 textColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);      // Yellow text
  ImVec4 menuBarColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);   // Blue color for the menu bar
  ImGui::PushStyleColor(ImGuiCol_MenuBarBg, menuBarColor);
  ImGui::PushStyleColor(ImGuiCol_WindowBg, windowBgColor);
  ImGui::PushStyleColor(ImGuiCol_Text, textColor);
}

void Renderer::ImGui() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  /* ImGui::ShowDemoWindow(); // Show demo window! :) */
}
void Renderer::ImGuiEnd() {
  // Rendering
  // (Your code clears your framebuffer, renders your other stuff etc.)
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // (Your code calls glfwSwapBuffers() etc.)
}

void Renderer::GLDraw() {
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);  // use ib
  // GLCall(glDrawArrays(GL_TRIANGLES, 0, 36)); // use vertex matrix
}

// renders everything
void Renderer::Draw(const std::vector<GameObject*>& objects) {
  textures.boundSlot = -1;  // set directly as boundSlot is only used for game objects
  /* ---------- SHADOW MAPPING --------- */
  BindShader(shadowShader);
  ShadowProj();
  shadowBuffer.Bind();
  glClear(GL_DEPTH_BUFFER_BIT);
  DrawObjects(objects, shadowShader);
  /* ---------- MAIN PASS --------- */
  BindShader(shaderID);
  Projection();
  ppBuffer.Bind();
  Clear();
  DrawObjects(objects, shaderID);
  SkyboxDraw();
  /* ---------- POST PROCESSING --------- */
  // disable wireframe
  bool tempWireFrame = isWireFrame;
  if (tempWireFrame) {
    Wireframe(false);
  }
  // PP texture slot
  textures.Bind(9);
  BindShader(ppShader);
  FrameBuffer::BindDefault();
  glClear(GL_COLOR_BUFFER_BIT);
  // render to screen quad
  glBindVertexArray(ppVao);
  glDisable(GL_DEPTH_TEST);
  // set the texture that gets drawn
  glBindTexture(GL_TEXTURE_2D, ppBuffer.GetTexture());
  glDrawArrays(GL_TRIANGLES, 0, 6);

  /* OPTIONALLY DRAW SHADOW BUFFER TO SCREEN */
  if (m_RenderShadowBuffer) {
    BindShader(displayShadowShader);
    GLCall(glActiveTexture(GL_TEXTURE7));
    GLCall(glBindTexture(GL_TEXTURE_2D, shadowBuffer.GetTexture()));
    int u_DepthMap = glGetUniformLocation(displayShadowShader, "u_DepthMap");
    glUniform1i(u_DepthMap, 7);
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
  }

  /* ---------- SWAP --------- */
  glEnable(GL_DEPTH_TEST);
  BindShader(shaderID);
  ImGuiEnd();
  Swap();
  // reenable wireframe
  if (tempWireFrame) {
    Wireframe(true);
  }
}

void Renderer::DrawObjects(const std::vector<GameObject*>& objects, unsigned int shader) {
  for (auto it : objects) {
    it->SetShader(shader);  // TODO TODO PERFORMANCE MAKE IT STATIC TODO
    if (shader == shaderID) {
      if (it->GetIsTextured() && it->GetTextureSlot() != textures.boundSlot) {
        textures.Bind(it->GetTextureSlot());
      }
    }
    it->Bind();
  }
}

void Renderer::Swap() {
  // Enable depth test
  GLCall(glEnable(GL_DEPTH_TEST));
  // Accept fragment if it closer to the camera than the former one
  GLCall(glDepthFunc(GL_LESS));

  GLCall(glfwSwapBuffers(gWindow));
}
void Renderer::Clear() {
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::ToggleShadowBufferView() {
  if (m_RenderShadowBuffer) {
    m_RenderShadowBuffer = false;
  } else {
    m_RenderShadowBuffer = true;
  }
}

unsigned int Renderer::SkyboxLoadCubemap(std::vector<std::string> faces) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(0);
  for (unsigned int i = 0; i < faces.size(); i++) {
    unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
      stbi_image_free(data);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  stbi_set_flip_vertically_on_load(1);
  return textureID;
}

void Renderer::SkyboxInit() {
  GLCall(glActiveTexture(GL_TEXTURE6));
  textures.boundSlot = -1;
  // skybox VAO
  GLCall(glGenVertexArrays(1, &skyboxVAO));
  GLCall(glGenBuffers(1, &skyboxVBO));
  GLCall(glBindVertexArray(skyboxVAO));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW));
  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
  // load cubemap
  std::vector<std::string> faces{
      "res/textures/skybox/right.jpg",
      "res/textures/skybox/left.jpg",
      "res/textures/skybox/top.jpg",
      "res/textures/skybox/bottom.jpg",
      "res/textures/skybox/front.jpg",
      "res/textures/skybox/back.jpg"};
  skyboxTex = SkyboxLoadCubemap(faces);
  // set shader uniform
  BindShader(skyboxShader);
  unsigned int u_Skybox = glGetUniformLocation(skyboxShader, "u_Skybox");
  GLCall(glUniform1i(u_Skybox, RESERVED_TEX_SLOT::SKYBOX));
  BindShader(shaderID);
}

void Renderer::SkyboxDraw() {
  BindShader(skyboxShader);
  glDepthFunc(GL_LEQUAL);
  // pass matrices from the player
  // the matrices begin as mat3 and then go back to mat4 as to not apply wrong translations
  glm::mat4 view = glm::mat4(glm::mat3(Engine::Instance().player.camera.GetViewMatrix()));
  unsigned int u_View = glGetUniformLocation(skyboxShader, "u_View");
  GLCall(glUniformMatrix4fv(u_View, 1, GL_FALSE, &view[0][0]));

  glm::mat4 projection = m_ProjectionMatrix;
  unsigned int u_Projection = glGetUniformLocation(skyboxShader, "u_Projection");
  GLCall(glUniformMatrix4fv(u_Projection, 1, GL_FALSE, &projection[0][0]));
  // skybox cube
  GLCall(glBindVertexArray(skyboxVAO));
  GLCall(glActiveTexture(GL_TEXTURE6));
  textures.boundSlot = -1;
  glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
  BindShader(shaderID);
}

void Renderer::ShadowStart() {
  GLCall(glUniform1i(ppTexUniform, RESERVED_TEX_SLOT::SHADOW));
  shadowBuffer.SetTexType(FrameBuffer::DEPTH);
  shadowBuffer.Init();
}

void Renderer::ppStart() {
  BindShader(ppShader);
  ppTexUniform = glGetUniformLocation(ppShader, "u_Texture");
  GLCall(glUniform1i(ppTexUniform, 9));
  ppBuffer.SetTexType(FrameBuffer::RGB);
  ppBuffer.Init();
  glGenVertexArrays(1, &ppVao);
  glGenBuffers(1, &ppVBO);
  glBindVertexArray(ppVao);
  glBindBuffer(GL_ARRAY_BUFFER, ppVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadVert), &screenQuadVert, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  // return to the default shader and drawing buffer
  BindShader(shaderID);
  ppBuffer.Bind();
}

void Renderer::Wireframe(bool flag) {
  if (flag == true) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // enable wireframe mode
    isWireFrame = true;
  } else if (flag == false) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // enable wireframe mode
    isWireFrame = false;
  }
}

void Renderer::Init() {
  if (!glfwInit()) {
    printf("Error! Failed to initialize gflw");
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    gWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "graphics ryan graphcis", NULL, NULL);
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // mouse
    // glViewport(0, 0, 100, 100);
    if (!gWindow) {
      printf("Error! Failed to create OpenGL context or window");
      return;
    } else {
      glfwMakeContextCurrent(gWindow);

      glfwSwapInterval(1);  // enable vsync

      printf("GLEW Version %s\n", glewGetString(GLEW_VERSION));
      printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
      GLenum err = glewInit();
      if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return;
      }
      glfwGetFramebufferSize(gWindow, &m_InitialWidth, &m_InitialHeight);
    }
  }

  GLCall(glEnable(GL_CULL_FACE));
}

void Renderer::Quit() {
  printf("Quitting...\n");
  // imgui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  // glfw
  GLCall(glDeleteProgram(shaderID));
  glfwDestroyWindow(gWindow);
  glfwTerminate();
}

void Renderer::DeltaTime() {
  double currentFrameTime = glfwGetTime();
  deltaTime = currentFrameTime - m_LastFrameTime;
  m_LastFrameTime = currentFrameTime;
}

unsigned int Renderer::Shader(const std::string& path) {
  ShaderProgramSource source = ParseShader(path);
  unsigned int tempID = CreateShader(source.VertexSource, source.FragmentSource);
  return tempID;
}
/* ---------------------------PRIVATE---------------------------- */
void Renderer::Projection() {
  m_ProjectionMatrix = glm::perspective(glm::radians(projectionFOV), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), NEAR_PLANE, FAR_PLANE);
  int u_Perspective = glGetUniformLocation(shaderID, "u_Perspective");
  GLCall(glUniformMatrix4fv(u_Perspective, 1, GL_FALSE, &m_ProjectionMatrix[0][0]));

  glViewport(0, 0, m_InitialWidth, m_InitialHeight);
}

void Renderer::ShadowProj() {
  float near_plane = 0.1f;
  float far_plane = 7.5f;
  glm::mat4 lightProjection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);

  // TODO GIVE REAL LIGHT VALUE
  glm::mat4 lightView = glm::lookAt(shadowPos, glm::vec3(0.0f, shadowPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 lightSpaceMatrix = lightProjection * lightView;

  // pass matrix to the shader
  int shadowShaderLightMatrix = glGetUniformLocation(shadowShader, "u_LightSpace");
  GLCall(glUniformMatrix4fv(shadowShaderLightMatrix, 1, GL_FALSE, &lightSpaceMatrix[0][0]));
  // now for main shader
  BindShader(shaderID);
  int shaderLightMatrix = glGetUniformLocation(shaderID, "u_LightSpace");
  GLCall(glUniformMatrix4fv(shaderLightMatrix, 1, GL_FALSE, &lightSpaceMatrix[0][0]));

  // pass the shadow map
  GLCall(glActiveTexture(GL_TEXTURE8));
  glBindTexture(GL_TEXTURE_2D, shadowBuffer.GetTexture());
  int shadowMap = glGetUniformLocation(shaderID, "u_ShadowMap");
  glUniform1i(shadowMap, RESERVED_TEX_SLOT::SHADOW);

  // FOR displaying shadow buffer
  int near = glGetUniformLocation(displayShadowShader, "near_plane");
  int far = glGetUniformLocation(displayShadowShader, "far_plane");
  GLCall(glUniform1f(near, near_plane));
  GLCall(glUniform1f(far, far_plane));
  BindShader(shadowShader);

  glViewport(0, 0, SHADOW_RES, SHADOW_RES);
}
