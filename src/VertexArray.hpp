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
    int size;
    VertexArray(const void* positions, unsigned int size);
    void Bind();
  private:
    void GenColor(glm::vec3 color, float colors[]);
    void BindColor(float colorArray[]);
};
