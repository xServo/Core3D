#include "texture.hpp"

Texture::Texture() {

}

void Texture::Init() {
  u_Texture = glGetUniformLocation(shaderID, "u_Texture");
  // transparency
  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  // set the texture wrapping parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // set texture filtering parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  stbi_set_flip_vertically_on_load(1);
}

void Texture::Generate(std::string path, int slot) {
  Bind(slot);
  // get id
  unsigned int texID;
  GLCall(glGenTextures(1, &texID));
  GLCall(glBindTexture(GL_TEXTURE_2D, texID));
  // load image
  int texWidth;
  int texHeight;
  int texNrChannels;
  unsigned char *data = stbi_load(path.c_str(), &texWidth, &texHeight, &texNrChannels, 4);
  std::cout << "height: " << texHeight
            << " width: " << texWidth
            << std::endl;
  if (data) {
    // gen texture and mipmap
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
  } else {
    std::cout << "Error, failed to load texture!" << std::endl;
    return;
  }
  stbi_image_free(data);
}

void Texture::Bind(int slot) {
  // texture uniform
  GLCall(glUniform1i(u_Texture, slot));
  switch (slot) {
    case 0:
      GLCall(glActiveTexture(GL_TEXTURE0)); 
      return;
    case 1:
      GLCall(glActiveTexture(GL_TEXTURE1)); 
      return;
    case 2:
      GLCall(glActiveTexture(GL_TEXTURE2)); 
      return;
    case 3:
      GLCall(glActiveTexture(GL_TEXTURE3)); 
      return;
    case 4:
      GLCall(glActiveTexture(GL_TEXTURE4)); 
      return;
    case 5:
      GLCall(glActiveTexture(GL_TEXTURE5)); 
      return;
    case 6:
      GLCall(glActiveTexture(GL_TEXTURE6)); 
      return;
    case 7:
      GLCall(glActiveTexture(GL_TEXTURE7)); 
      return;
    case 8:
      GLCall(glActiveTexture(GL_TEXTURE8)); 
      return;
    case 9:
      GLCall(glActiveTexture(GL_TEXTURE9)); 
      return;
    default:
      std::cout << "Error, invalid slot!" << std::endl;
  }
}
