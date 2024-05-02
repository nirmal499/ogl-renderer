#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
  public:
    bool load_texture(std::string textureFilename);
    void bind();
    void unbind();
    void clean_up();

  private:
    GLuint m_texture = 0;
    int m_texture_width = 0;
    int m_texture_height = 0;
    int m_no_of_channels = 0;
    std::string m_texture_name;
};
