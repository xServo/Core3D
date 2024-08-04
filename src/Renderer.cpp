#include "Renderer.hpp"
/* ---------------------------PUBLIC---------------------------- */
Renderer::Renderer(const int WIDTH, const int HEIGHT)
: SCREEN_WIDTH(WIDTH), SCREEN_HEIGHT(HEIGHT), editor(), textures() {
  GLFWwindow* gWindow = nullptr;
  isUI = true;
  Init();
  Shader();
  Projection();
  textures.Init();
}

void Renderer::ImGuiInit() {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // disable ini files
  io.IniFilename = NULL;
  /* io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls */
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(gWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
  ImVec4 windowBgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray background
  ImVec4 textColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);     // Yellow text
  ImVec4 menuBarColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Blue color for the menu bar
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
  if (isUI) {
    editor.UILoop();
  }

                           // ImGui::Text("Hello, world %d", 123);
}
void Renderer::ImGuiEnd() {
  // Rendering
  // (Your code clears your framebuffer, renders your other stuff etc.)
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // (Your code calls glfwSwapBuffers() etc.)
}

void Renderer::Draw() {
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // use ib
  // GLCall(glDrawArrays(GL_TRIANGLES, 0, 36)); // use vertex matrix
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
void Renderer::Wireframe(bool flag) {
  if (flag == true) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // enable wireframe mode:w
    isWireFrame = true;
  } else if (flag == false) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // enable wireframe mode:w
    isWireFrame = false;
  }
}

void Renderer::ToggleUI() {
  if (isUI) {
    isUI = false;
  } else {
    isUI = true;
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
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // mouse
    glViewport(0, 0, 800, 600);
    if (!gWindow) {
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
/* ---------------------------PRIVATE---------------------------- */
void Renderer::Projection() {
  glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
  int u_Perspective = glGetUniformLocation(shaderID, "u_Perspective");
  glUniformMatrix4fv(u_Perspective, 1, GL_FALSE, &perspective[0][0]);
}

void Renderer::Shader() {
  ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
  shaderID = CreateShader(source.VertexSource, source.FragmentSource);
  glUseProgram(shaderID);
  camera.shaderID = shaderID;
  camera.Bind();
  textures.shaderID = shaderID;
}

