#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ogl/renderdata.hpp>

class VertexBuffer
{
  public:
    void init();
    void upload_data(Mesh vertexData);
    void bind();
    void unbind();
    void draw(GLuint mode, unsigned int start, unsigned int num);
    void clean_up();

  private:
    GLuint m_vao = 0;
    GLuint m_vertex_vbo = 0;
};
