#include "VertexArray.hpp"

VertexArray::VertexArray(const void* positions, unsigned int size) 
  : size(size) {
  unsigned int vSize = 6;
  GLCall(glGenVertexArrays(1, &m_ID));  
  GLCall(glBindVertexArray(m_ID));
  VertexBuffer vb(positions, (vSize*size)*sizeof(float));
  GLCall(glEnableVertexAttribArray(0));
  // 0 = vertex; 1 = colors; 2 = normals
  // index, values per vertex, type, normalize?, size of vertex in bytes, offset to first vertex 
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)0));
  GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)(sizeof(float)*3))); GLCall(glEnableVertexAttribArray(2));

  // default color
  float colors[] = {
    0.583f,  0.771f,  0.014f,

    0.597f,  0.770f,  0.761f,
    0.597f,  0.770f,  0.761f,

    0.014f,  0.184f,  0.576f,
    0.014f,  0.184f,  0.576f,

    0.997f,  0.513f,  0.064f,

    0.055f,  0.953f,  0.042f,

    0.982f,  0.099f,  0.879f,
  };
  float colorArr[] = {
    0.3, 0.77, 1,
    0.3, 0.77, 1,
    0.3, 0.77, 1,
    0.3, 0.77, 1,
    0.3, 0.77, 1,
    0.3, 0.77, 1,
    0.3, 0.77, 1,
    0.3, 0.77, 1,
  };

  // this doesnt work? TODO
  /* float colorArr[size*3]; */
  /* GenColor(glm::vec3(0,1,0.014f), ass); */
  /* for (int i=0; i<size*3; i++) { */
  /*   std::cout << ass[i] << std::endl; */
  /* }; */

  BindColor(colorArr);

  // UNBIND
  GLCall(glBindVertexArray(0));
}

void VertexArray::Bind() {
  GLCall(glBindVertexArray(m_ID));
}
void VertexArray::GenColor(glm::vec3 color, float colors[]) {
  for (int i=0;i<=size*3;i+=3) { // danger: vzise?
    colors[i] = color.x;
    colors[i+1] = color.y;
    colors[i+2] = color.z;
  }
}
void VertexArray::BindColor(float colorArray[]) {
  // color buffer
  unsigned int cb;
  GLCall(glGenBuffers(1, &cb)); 
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, cb));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*size, colorArray, GL_STATIC_DRAW));
  GLCall(glEnableVertexAttribArray(1));
  GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0)); 
}
