#pragma once 
#include <glew.h>
#include <iostream>
#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class VertexArray {
  public:
    unsigned int m_ID;
    int vCount;
    int vSize;
    VertexArray(const void* positions, unsigned int vCount, unsigned int vSize); // vSize = how many floats per vertex (not in bytes); vSize*vCount = number of floats in the array
    void Bind();
  private:
    void BindColor(float colorArray[]);
};
