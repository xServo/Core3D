#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "gl_assert.hpp"
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
