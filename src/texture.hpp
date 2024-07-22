#pragma once
#include <vector>
#include "Renderer.hpp"
#include "stb_image.h"

class Texture {
  private:
    
  public:  
    unsigned int shaderID;
    Texture();
    void Generate(std::string path, int slot);
    void Bind(int slot);
};
