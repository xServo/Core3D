#include <iostream>
#include "Renderer.hpp"

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

Renderer::Renderer(GLFWwindow* window) {
    gWindow = window;
}
void Renderer::Draw() {
    // Render here (currently just a clear color)

    // draw call
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // use ib
    /* GLCall(glDrawArrays(GL_TRIANGLES, 0, 36*3)); // use vertex matrix */
    // Enable depth test
    GLCall(glEnable(GL_DEPTH_TEST));
    // Accept fragment if it closer to the camera than the former one
    GLCall(glDepthFunc(GL_LESS));
    
    // Swap buffers to display the updated frame
    GLCall(glfwSwapBuffers(gWindow));
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
