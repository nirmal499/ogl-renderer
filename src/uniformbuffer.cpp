#include <glm/gtc/type_ptr.hpp>

#include <ogl/uniformbuffer.hpp>
#include <tool/logger.hpp>

void UniformBuffer::init()
{
  /* create UBO for 2x 4x4 matrices */
  glGenBuffers(1, &m_ubo_buffer);

  glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_buffer);
  glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::upload_ubo_data(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
  glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_buffer);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(viewMatrix));
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo_buffer, 0, 2 * sizeof(glm::mat4));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::clean_up()
{
  glDeleteBuffers(1, &m_ubo_buffer);
}
