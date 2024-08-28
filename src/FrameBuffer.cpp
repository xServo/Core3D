#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height) {
}

void FrameBuffer::BindDefault() {
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Bind() {
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));
}

void FrameBuffer::Init() {
  // frame buffer object
  GLCall(glGenFramebuffers(1, &m_FBO));
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));
  // texture
  GLCall(glGenTextures(1, &m_Texture));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
  GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0));
  // render buffer object
  unsigned int m_RBO;
  GLCall(glGenRenderbuffers(1, &m_RBO));
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RBO));
  GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
  GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO));

  // check if frame buffer is complete
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Error, could not create framebuffer" << std::endl;
    ASSERT(0);
  }
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));  // unbind
}
