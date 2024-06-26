#include <iostream>
#include <sstream>
#include <fstream>
#include "Renderer.hpp"
#include "ShaderCompiler.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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


void Renderer::Draw() {
    // Render here (currently just a clear color)

    // draw call
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // use ib
    /* GLCall(glDrawArrays(GL_TRIANGLES, 0, 36*3)); // use vertex matrix */
      
    // Swap buffers to display the updated frame
    // Poll for and process events
    /* GLCall(glfwPollEvents()); */
}
void Renderer::Clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
void Renderer::Wireframe(bool flag) {
  if (flag == true) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // enable wireframe mode:w
    m_Wireframe = true;
  } else if (flag == false) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // enable wireframe mode:w
    m_Wireframe = false;
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
}
