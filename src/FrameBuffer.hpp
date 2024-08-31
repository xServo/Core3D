#include <iostream>
#include "gl_assert.hpp"

class FrameBuffer {
public:
  enum TexType {
    RGB,
    DEPTH
  };
  static void BindDefault();

  FrameBuffer(int width, int height); 
  void Bind();
  void Init();
  //  What type of texture does this frame buffer use
  inline void SetTexType(TexType type) { m_TexType = type; };
  inline unsigned int GetTexture() { return m_Texture; };
private:
  unsigned int m_FBO;
  unsigned int m_Texture;
  unsigned int m_RBO;
  TexType m_TexType = RGB; // default to rgb texture
  int m_Width;
  int m_Height;
};