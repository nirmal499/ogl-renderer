#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
  public:
    bool init(unsigned int width, unsigned int height);
    bool resize(unsigned int newWidth, unsigned int newHeight);
    void bind();
    void unbind();
    void draw_to_screen();
    void clean_up();

  private:
    unsigned int m_buffer_width = 640;
    unsigned int m_buffer_height = 480;
    GLuint m_buffer = 0;
    GLuint m_color_texture = 0;
    GLuint m_depth_buffer = 0;

    bool check_complete();
};
