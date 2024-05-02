#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <ogl/texture.hpp>
#include <tool/logger.hpp>

void Texture::clean_up()
{
  glDeleteTextures(1, &m_texture);
}

bool Texture::load_texture(std::string textureFilename)
{
  m_texture_name = textureFilename;

  stbi_set_flip_vertically_on_load(true);
  unsigned char *textureData = stbi_load(textureFilename.c_str(), &m_texture_width, &m_texture_height, &m_no_of_channels, 0);

  if (!textureData)
  {
    Logger::log(1, "%s error: could not load file '%s'\n", __FUNCTION__, m_texture_name.c_str());
    stbi_image_free(textureData);
    return false;
  }

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* glTexImage2D is important */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texture_width, m_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(textureData);

  Logger::log(1, "%s: texture '%s' loaded (%dx%d, %d channels)\n", __FUNCTION__, m_texture_name.c_str(), m_texture_width, m_texture_height, m_no_of_channels);
  return true;
}

void Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
