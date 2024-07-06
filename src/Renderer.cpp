#include <iostream>
#include <sstream>
#include <fstream>
#include "Renderer.hpp"
#include "ShaderCompiler.hpp"

void GLClearError() {
  while(glGetError());
}
bool GLLogCall(const char* function, const char* file, int line) {
  while(GLenum error = glGetError()) {
    std::cout << "[OpenGL error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}


void Renderer::ImGuiInit() { 
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  /* io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls */
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(gWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
}

void Renderer::ImGui() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::ShowDemoWindow(); // Show demo window! :)
}
void Renderer::ImGuiEnd() {
  // Rendering
  // (Your code clears your framebuffer, renders your other stuff etc.)
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // (Your code calls glfwSwapBuffers() etc.)
}
void Renderer::Draw() {
  /* glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // use ib */
  GLCall(glDrawArrays(GL_TRIANGLES, 0, 36)); // use vertex matrix
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
    isWireframe = true;
  } else if (flag == false) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // enable wireframe mode:w
    isWireframe = false;
  }
}

void Renderer::init() {
  if (!glfwInit()) {
    printf("Error! Failed to initialize gflw");
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    gWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "graphics ryan graphcis", NULL, NULL);
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
}

void Renderer::quit() {
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
}
 void Renderer::DeltaTime() {
    double currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - m_LastFrameTime;
    m_LastFrameTime = currentFrameTime;
    camera.deltaTime = deltaTime;
 }
