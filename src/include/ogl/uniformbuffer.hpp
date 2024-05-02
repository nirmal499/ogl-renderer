#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

class UniformBuffer
{
  public:
    void init();
    void upload_ubo_data(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    void clean_up();

  private:
    GLuint m_ubo_buffer = 0;
};
