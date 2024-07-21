#include "VertexArray.hpp"

VertexArray::VertexArray(const void* positions, unsigned int vCount, unsigned int vSize)  
  : vCount(vCount), vSize(vSize) {
  GLCall(glGenVertexArrays(1, &m_ID));  
  GLCall(glBindVertexArray(m_ID));
  VertexBuffer vb(positions, (vCount*vSize)*sizeof(float));
  GLCall(glEnableVertexAttribArray(0));
  GLCall(glEnableVertexAttribArray(1));
  // 0 = vertex; 1 = normals;
  // index, values per vertex, type, normalize?, size of vertex in bytes, offset to first vertex 
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)0));
  GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, (void*)(sizeof(float)*3))); 

  // UNBIND
  GLCall(glBindVertexArray(0));
}

void VertexArray::Bind() {
  GLCall(glBindVertexArray(m_ID));
}