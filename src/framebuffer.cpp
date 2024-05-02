#include <ogl/framebuffer.hpp>
#include <tool/logger.hpp>

bool Framebuffer::init(unsigned int width, unsigned int height)
{
  m_buffer_width = width;
  m_buffer_height = height;

  glGenFramebuffers(1, &m_buffer);
  glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);
  glEnable(GL_FRAMEBUFFER_SRGB);

  /* color texture */
  glGenTextures(1, &m_color_texture);
  glBindTexture(GL_TEXTURE_2D, m_color_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,  0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_texture, 0);
  Logger::log(1, "%s: added color buffer\n", __FUNCTION__);

  /* render buffer as depth buffer */
  glGenRenderbuffers(1, &m_depth_buffer);
  glBindRenderbuffer(GL_RENDERBUFFER, m_depth_buffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_buffer);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  Logger::log(1, "%s: added depth renderbuffer\n", __FUNCTION__);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return this->check_complete();
}

void Framebuffer::clean_up()
{
  this->unbind();

  glDeleteTextures(1, &m_color_texture);
  glDeleteRenderbuffers(1, &m_depth_buffer);
  glDeleteFramebuffers(1, &m_buffer);
}

bool Framebuffer::resize(unsigned int newWidth, unsigned int newHeight) {
  Logger::log(1, "%s: resizing framebuffer from %dx%d to %dx%d\n", __FUNCTION__, m_buffer_width, m_buffer_height, newWidth, newHeight);
  m_buffer_width = newWidth;
  m_buffer_height = newHeight;

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glDeleteTextures(1, &m_color_texture);
  glDeleteRenderbuffers(1, &m_depth_buffer);
  glDeleteFramebuffers(1, &m_buffer);

  return init(newWidth, newHeight);
}

void Framebuffer::bind()
{
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_buffer);
}

void Framebuffer::unbind()
{
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::draw_to_screen()
{
  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_buffer);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, m_buffer_width, m_buffer_height, 0, 0, m_buffer_width, m_buffer_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

bool Framebuffer::check_complete()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);

  GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (result != GL_FRAMEBUFFER_COMPLETE)
  {
    Logger::log(1, "%s error: framebuffer is NOT complete\n", __FUNCTION__);
    return false;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  Logger::log(1, "%s: framebuffer is complete\n", __FUNCTION__);
  return true;
}
