#include "Input.hpp"
namespace Input {
  float yaw = 0.0f;
  float pitch = 0.0f;
  float lastX = 0.0f;
  float lastY = 0.0f;
  std::string keyPressed = "";
  void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
      case GLFW_KEY_E:
        if (action == GLFW_PRESS) {
          keyPressed = "e";
        }
        break;
      case GLFW_KEY_W:
        if (action == GLFW_PRESS) {
          keyPressed += "w";
        }
        break;
      case GLFW_KEY_S:
        if (action == GLFW_PRESS) {
          keyPressed += "s";
        }
        break;
      case GLFW_KEY_A:
        if (action == GLFW_PRESS) {
          keyPressed += "a";
        }
        break;
      case GLFW_KEY_D:
        if (action == GLFW_PRESS) {
          keyPressed += "d";
        }
        break;
      case GLFW_KEY_T:
        if (action == GLFW_PRESS) {
          keyPressed = "t";
        }
        break;
      case GLFW_KEY_G:
        if (action == GLFW_PRESS) {
          keyPressed = "g";
        }
        break;
      case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS) {
          keyPressed = "\x1B";
        }
        break;
    }
    size_t search;
    switch (key) {
      case GLFW_KEY_E:
        if (action == GLFW_RELEASE) {
          if (keyPressed == "e") {
            keyPressed = "";
          }
        }
        break;
      case GLFW_KEY_W:
        if (action == GLFW_RELEASE) {
          search = keyPressed.find('w');
          if (search != std::string::npos) {
            keyPressed.erase(search, 1);
          }
        }
        break;
      case GLFW_KEY_S:
        if (action == GLFW_RELEASE) {
          search = keyPressed.find('s');
          if (search != std::string::npos) {
            keyPressed.erase(search, 1);
          }
        }
        break;
      case GLFW_KEY_A:
        if (action == GLFW_RELEASE) {
          search = keyPressed.find('a');
          if (search != std::string::npos) {
            keyPressed.erase(search, 1);
          }
        }
        break;
      case GLFW_KEY_D:
        if (action == GLFW_RELEASE) {
          search = keyPressed.find('d');
          if (search != std::string::npos) {
            keyPressed.erase(search, 1);
          }
        }
        break;
      case GLFW_KEY_T:
        if (action == GLFW_RELEASE) {
          if (keyPressed == "t") {
            keyPressed = "";
          }
        }
        break;
      case GLFW_KEY_G:
        if (action == GLFW_RELEASE) {
          if (keyPressed == "g") {
            keyPressed = "";
          }
        }
        break;
      case GLFW_KEY_ESCAPE:
        if (action == GLFW_RELEASE) {
          keyPressed = "";
        }
        break;
    }
  }

  void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw   += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
  }
}
