#pragma once
#include <vector>
#include "Renderer.hpp"
#include "stb_image.h"

class Texture {
  private:
    int u_Texture;
    
  public:  
    unsigned int shaderID;
    Texture();
    void Generate(std::string path, int slot);
    void Bind(int slot);
};
