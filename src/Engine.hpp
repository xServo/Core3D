#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <string>
#include <vector>
#include "Engine.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "editor.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "Input.hpp"
#include "model.hpp"
#include "level0.hpp"
#include "stb_image.h"
#include "texture.hpp"
#include "gl_assert.hpp"

class Engine {
  private:
    // tmp 
    void LoadScene();
  public
    Update();
};
