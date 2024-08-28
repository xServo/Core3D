#include <iostream>
#include "gl_assert.hpp"

class FrameBuffer {
private:
  unsigned int m_FBO;
  unsigned int m_Texture;
  unsigned int m_RBO;
  int m_Width;
  int m_Height;
public:
  static void BindDefault();

  FrameBuffer(int width, int height); 
  void Bind();
  void Init();
  inline unsigned int GetTexture() { return m_Texture; };
  inline unsigned int GetRBO() { return m_RBO; };
};