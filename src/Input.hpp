#pragma once
#include <string>
#include <glew.h>
#include <glfw3.h>

namespace Input {
enum KEY : char {
  ESC,
  SHIFT,
  SHIFT_REL,
};
extern float yaw;
extern float pitch;
extern float lastX;
extern float lastY;
extern std::string keyPressed;
extern bool isMouseLock;
void ResetCursor();
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void Search(char tar);
}  // namespace Input
