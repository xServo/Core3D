#include "Renderer.hpp"
/* ---------------------------PUBLIC---------------------------- */
Renderer::Renderer(const int WIDTH, const int HEIGHT)
    : SCREEN_WIDTH(WIDTH), SCREEN_HEIGHT(HEIGHT), textures() {
  GLFWwindow* gWindow = nullptr;
  isUI = true;
  Init();
  shaderID = Shader("res/shaders/basic.shader");
  glUseProgram(shaderID);
  camera.shaderID = shaderID;
  camera.Bind();
  textures.shaderID = shaderID;
  Projection();
  textures.Init();
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

void Renderer::Draw() {
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);  // use ib
  // GLCall(glDrawArrays(GL_TRIANGLES, 0, 36)); // use vertex matrix
}

void Renderer::DrawObjects(const std::vector<GameObject*>& objects) {
  for (auto it : objects) {
    if (it->GetIsTextured() && it->GetTextureSlot() != textures.boundSlot) {
      textures.Bind(it->GetTextureSlot());
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

unsigned int Renderer::GenFrameBuffer() {
  unsigned int fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  // texture
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
  tempColorBufferTexture = texture;

  // render buffer object
  unsigned int rbo;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

  // check if frame buffer is complete
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Error, could not create framebuffer" << std::endl;
    ASSERT(0);
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
  return fbo;
}

void Renderer::DrawFrameBuffer(unsigned int id) {
  // Clear();
  // glBindVertexArray(quadVAO);
  // glDisable(GL_DEPTH_TEST);
  // glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
  // glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Wireframe(bool flag) {
  if (flag == true) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // enable wireframe mode:w
    isWireFrame = true;
  } else if (flag == false) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // enable wireframe mode:w
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
    glViewport(0, 0, 800, 600);
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
  camera.deltaTime = deltaTime;
}

unsigned int Renderer::Shader(const std::string &path) {
  ShaderProgramSource source = ParseShader(path);
  unsigned int tempID = CreateShader(source.VertexSource, source.FragmentSource);
  return tempID;
}
/* ---------------------------PRIVATE---------------------------- */
void Renderer::Projection() {
  glm::mat4 perspective = glm::perspective(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), NEAR_PLANE, FAR_PLANE);
  int u_Perspective = glGetUniformLocation(shaderID, "u_Perspective");
  glUniformMatrix4fv(u_Perspective, 1, GL_FALSE, &perspective[0][0]);
}


