#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "gl_assert.hpp"
#include "stb_image.h"

class Texture {
  private:
    int u_Texture;
    
  public:  
    unsigned int shaderID;
    Texture();
    void Generate(std::string path, int slot);
    void Bind(int slot);
    void Init();
};
