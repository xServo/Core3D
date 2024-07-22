#include "VertexArray.hpp"

VertexArray::VertexArray(const void* positions, unsigned int vCount, unsigned int vSize)  
  : vCount(vCount), vSize(vSize) {
  GLCall(glGenVertexArrays(1, &m_ID));  
  GLCall(glBindVertexArray(m_ID));
  VertexBuffer vb(positions, (vCount*vSize)*sizeof(float));
  // 0 = vertex; 1 = normals; 2 = tex coords;
  // index, values per vertex, type, normalize?, size of vertex in bytes, offset to first vertex 
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)0));
  GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)(sizeof(float)*3))); 
  GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)(sizeof(float)*6)));
  GLCall(glEnableVertexAttribArray(0));
  GLCall(glEnableVertexAttribArray(1));
  GLCall(glEnableVertexAttribArray(2));

  // UNBIND
  GLCall(glBindVertexArray(0));
}

void VertexArray::Bind() {
  GLCall(glBindVertexArray(m_ID));
}