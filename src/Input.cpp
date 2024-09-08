#include "Input.hpp"
namespace Input {
float yaw = 0.0f;
float pitch = 0.0f;
float lastX = 0.0f;
float lastY = 0.0f;
bool isMouseLock = true;
std::string keyPressed = "";
void ResetCursor() {
  // TODO is it possible to set the curosr position (to be at dead center)?
  lastY = 0.0f;
}
void Search(char tar) {
  size_t search = keyPressed.find(tar);
  if (search != std::string::npos) {
    keyPressed.erase(search, 1);
  }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch (key) {
    case GLFW_KEY_E:
      if (action == GLFW_PRESS)
        keyPressed = "e";
      if (action == GLFW_RELEASE)
        Search('e');
      break;
    case GLFW_KEY_R:
      if (action == GLFW_PRESS)
        keyPressed = "r";
      if (action == GLFW_RELEASE)
        Search('r');
      break;
    case GLFW_KEY_W:
      if (action == GLFW_PRESS)
        keyPressed += "w";
      if (action == GLFW_RELEASE)
        Search('w');
      break;
    case GLFW_KEY_S:
      if (action == GLFW_PRESS)
        keyPressed += "s";
      if (action == GLFW_RELEASE)
        Search('s');
      break;
    case GLFW_KEY_A:
      if (action == GLFW_PRESS)
        keyPressed += "a";
      if (action == GLFW_RELEASE)
        Search('a');
      break;
    case GLFW_KEY_D:
      if (action == GLFW_PRESS)
        keyPressed += "d";
      if (action == GLFW_RELEASE)
        Search('d');
      break;
    case GLFW_KEY_T:
      if (action == GLFW_PRESS)
        keyPressed += "t";
      if (action == GLFW_RELEASE)
        Search('t');
      break;
    case GLFW_KEY_G:
      if (action == GLFW_PRESS)
        keyPressed += "g";
      if (action == GLFW_RELEASE)
        Search('g');
      break;
    case GLFW_KEY_H:
      if (action == GLFW_PRESS)
        keyPressed = "h";
      if (action == GLFW_RELEASE)
        Search('h');
      break;
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS)
        keyPressed = ESC;
      if (action == GLFW_RELEASE)
        keyPressed = "";
      break;
    case GLFW_KEY_LEFT_SHIFT:
      if (action == GLFW_PRESS)
        Search(SHIFT_REL);
      keyPressed += SHIFT;
      if (action == GLFW_RELEASE) {
        Search(SHIFT);
        keyPressed += SHIFT_REL;
      }
      break;
  }
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
  if (!isMouseLock) return;
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;  // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;
  const float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;
  yaw += xoffset;
  pitch += yoffset;
  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;
}
}  // namespace Input
